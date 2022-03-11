// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>

int main( void )
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 1024, 768, "Tutorial 03 - Matrices", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShadersTransformFeedback( "SimpleTransform.glsl", "SingleColor.glsl", "GeometryShader.glsl");

//	// Get a handle for our "MVP" uniform
//	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
//
//	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
//	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
//	// Or, for an ortho camera :
//	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates
//
//	// Camera matrix
//	glm::mat4 View       = glm::lookAt(
//								glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
//								glm::vec3(0,0,0), // and looks at the origin
//								glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
//						   );
//	// Model matrix : an identity matrix (model will be at the origin)
//	glm::mat4 Model      = glm::mat4(1.0f);
//	// Our ModelViewProjection : multiplication of our 3 matrices
//	glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around

	static const GLfloat g_vertex_buffer_data[] = { 
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
	};

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

//	do{

    // Clear the screen
    glClear( GL_COLOR_BUFFER_BIT );

    // Use our shader
    glUseProgram(programID);
    
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    GLfloat data[] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f };
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    GLint inputAttrib = glGetAttribLocation(programID, "inValue");
    glEnableVertexAttribArray(inputAttrib);
    glVertexAttribPointer(inputAttrib, 1, GL_FLOAT, GL_FALSE, 0, 0);
    
    //2nd VBO to store the Transform Feedback output
    GLuint tbo;
    glGenBuffers(1, &tbo);
    glBindBuffer(GL_ARRAY_BUFFER, tbo);
    // Change this line because the the output data will be 3 vertices
    // glBufferData(GL_ARRAY_BUFFER, sizeof(data), nullptr, GL_STATIC_READ);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data)*3, nullptr, GL_STATIC_READ);
    
    GLuint query;
    glGenQueries(1, &query);
    
    glEnable(GL_RASTERIZER_DISCARD);
    
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, tbo);
    
    // Begin the TF process
    // Change this because the geometry shader is spitting out triangles
    glBeginQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, query);
    glBeginTransformFeedback(GL_TRIANGLES);
    
    glDrawArrays(GL_POINTS, 0, 5);
    
    // End the TF process
    glEndTransformFeedback();
    glEndQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN);
    
    glFlush();
    
    // GLfloat feedback[5];
    //    glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, sizeof(feedback), feedback);
    //
    //    printf("%f %f %f %f %f\n", feedback[0], feedback[1], feedback[2], feedback[3], feedback[4]);
    
    GLuint primitives;
    glGetQueryObjectuiv(query, GL_QUERY_RESULT, &primitives);
    
    printf("%u primitives written!\n\n", primitives);
    
    GLfloat feedback[15];
    glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, sizeof(feedback), feedback);
    for (int i = 0; i < 15; i++) {
        printf("%f\n", feedback[i]);
    }
    
//

//		// Send our transformation to the currently bound shader,
//		// in the "MVP" uniform
//		// glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
//
//		// 1rst attribute buffer : vertices
//		glEnableVertexAttribArray(0);
//		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
//		glVertexAttribPointer(
//			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
//			3,                  // size
//			GL_FLOAT,           // type
//			GL_FALSE,           // normalized?
//			0,                  // stride
//			(void*)0            // array buffer offset
//		);
//
//		// Draw the triangle !
//		glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle
//
//		glDisableVertexAttribArray(0);
//
//		// Swap buffers
//		glfwSwapBuffers(window);
//		glfwPollEvents();

//	} // Check if the ESC key was pressed or the window was closed
//	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
//		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &tbo);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

