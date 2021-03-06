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
    int width = 1024;
    int height = 768;
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
    
    // Create and compile Transformed Feedback shaders
    GLuint programID = LoadShadersTransformFeedback("PreprocVertex.glsl", "", "GeometryProcessor.glsl");
    
    glUseProgram(programID);

    int const grid_size = 32;

    static GLfloat g_vertex_buffer_data[grid_size * grid_size * 3];
    int counter = 0;
    //Getting centers of all quads
    //TODO: This part needs to be in the Geometry processor for transform feed back
    for (float i = 0; i < grid_size; i++) {
        for (float j = 1; j < grid_size + 1; j++){
            g_vertex_buffer_data[counter++] = (i / (float) grid_size) * 2.0f - 1.0f;
            g_vertex_buffer_data[counter++] = (j / (float) grid_size) * 2.0f - 1.0f;
            g_vertex_buffer_data[counter++] = 2.0f/grid_size;
        }
    }
    
    
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    GLint inputAttrib = glGetAttribLocation(programID, "inValue");
    glEnableVertexAttribArray(inputAttrib);
    glVertexAttribPointer(inputAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    //2nd VBO to store the Transform Feedback output
    GLuint tbo;
    glGenBuffers(1, &tbo);
    glBindBuffer(GL_ARRAY_BUFFER, tbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data)*4, nullptr, GL_STATIC_READ);
    
    glEnable(GL_RASTERIZER_DISCARD);
    
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, tbo);
    
    GLuint query;
    glGenQueries(1, &query);
    glBeginQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, query);
    glBeginTransformFeedback(GL_POINTS);
    
    glDrawArrays(GL_POINTS, 0, grid_size * grid_size);
    
    glEndTransformFeedback();
    glEndQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN);
    
    glFlush();
    
    GLuint primitives;
    glGetQueryObjectuiv(query, GL_QUERY_RESULT, &primitives);
    printf("%u primitives written!\n\n", primitives);
    
//    GLfloat feedback[grid_size*grid_size];
//    glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, sizeof(feedback), feedback);
//    for (int i = 0; i < grid_size*grid_size; i++) {
//        printf("%f\n", feedback[i]);
//    }
    
    
    // Create and compile our GLSL program from the shaders
    GLuint programID2 = LoadShadersGeometry( "SimpleVertexShader.glsl", "SimpleFragmentShader.glsl", "SimpleGeometryShader.glsl");

//    GLuint vertexbuffer;
//    glGenBuffers(1, &vertexbuffer);
//    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    // Matrices
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::lookAt(
        vec3(4.0f,3.0f,3.0f),
        vec3(0.0f,0.0f,0.0f),
        vec3(0.0f,1.0f,0.0f)
        );
    glm::mat4 model = glm::mat4(1.0f);

    GLuint ViewID = glGetUniformLocation(programID2, "View");
    GLuint ProjectionID = glGetUniformLocation(programID2, "Projection");
    GLuint ModelID = glGetUniformLocation(programID2, "Model");

    glUniformMatrix4fv(ViewID, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(ProjectionID, 1, GL_FALSE, &proj[0][0]);
    
    
    //drawing process
    do{
        glDisable(GL_RASTERIZER_DISCARD);
        // Clear the screen
        glClear( GL_COLOR_BUFFER_BIT );

        // Use our shader
        glUseProgram(programID2);

        // Model matrix
        glUniformMatrix4fv(ModelID, 1, GL_FALSE, &model[0][0]);

        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, GL_TRANSFORM_FEEDBACK_BUFFER);
        glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0      // array buffer offset
        );

        // Draw the quads
        glDrawArrays(GL_POINTS, 0, primitives); // 3 indices starting at 0 -> 1 triangle

        glDisableVertexAttribArray(0);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

    // Cleanup VBO
//    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &tbo);
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(programID);
    glDeleteProgram(programID2);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}

