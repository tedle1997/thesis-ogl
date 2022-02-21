// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	int width = 1920;
	int height = 1080;
	window = glfwCreateWindow( width, height, "Tutorial 02 - Red triangle", NULL, NULL);
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
	// Changed to black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "SimpleVertexShader.glsl", "SimpleFragmentShader.glsl", "SimpleGeometryShader.glsl");

	int const grid_size = 32;

	static GLfloat g_vertex_buffer_data[grid_size * grid_size * 2];
	int counter = 0;

	for (float i = 1; i < grid_size+1; i++) {
		for (float j = 1; j < grid_size+1; j++){
			g_vertex_buffer_data[counter++] = (i / (float) grid_size) * 2.0f - 1.0f;
			g_vertex_buffer_data[counter++] = (j / (float) grid_size) * 2.0f - 1.0f;
			std::cout << counter - 2 << ":" << g_vertex_buffer_data[counter - 2] << std::endl;
			std::cout << counter - 1 << ":" << g_vertex_buffer_data[counter - 1] << std::endl;
		}
	}

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	// Matrices
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(
		vec3(4.0f,3.0f,3.0f),
		vec3(0.0f,0.0f,0.0f),
		vec3(0.0f,1.0f,0.0f)
		);
	glm::mat4 model = glm::mat4(1.0f);

	GLuint ViewID = glGetUniformLocation(programID, "View");
	GLuint ProjectionID = glGetUniformLocation(programID, "Projection");
	GLuint ModelID = glGetUniformLocation(programID, "Model");

	glUniformMatrix4fv(ViewID, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(ProjectionID, 1, GL_FALSE, &proj[0][0]);

	do{

		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT );

		// Use our shader
		glUseProgram(programID);

		// Model matrix
		glUniformMatrix4fv(ModelID, 1, GL_FALSE, &model[0][0]);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			1,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_POINTS, 0, 32*32); // 3 indices starting at 0 -> 1 triangle

		glDisableVertexAttribArray(0);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
