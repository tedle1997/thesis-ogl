// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <math.h>
using namespace std;

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
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>

// Include STB image reader
#define STB_IMAGE_IMPLEMENTATION
#include "common/stb_image.h"


void createNewTexture(GLuint * texture_name, int width, int height){
    glGenTextures(1, texture_name);
    glBindTexture(GL_TEXTURE_2D, *texture_name);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
}

// TODO: replace depth buffer generation with this
void createDepthBuffer(GLuint * depth_buffer_name, int width, int height){
    
}

//TODO: complete this and replace this with texture 0-14
void bindTexture(){
    
}

//TODO: complete this and replace this with subtexturecopy 0-14
void copyTexture(){
    
}

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
    int height = 1080;
    int width = height * 1.40625;
//    width = height * 1.8;
	window = glfwCreateWindow( width, height , "Tutorial 07 - Model Loading", NULL, NULL);
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
    // Hide the mouse and enable unlimited mouvement
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetCursorPos(window, width/2, height/2);

    // White background
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	// Cull triangles which normal is not towards the camera
//	glEnable(GL_CULL_FACE);
//    glCullFace(GL_FRONT);
    // DISABLE CULLING
    glDisable(GL_CULL_FACE);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
    
    GLuint programTFID = LoadShadersTransformFeedback("TFVertex.glsl", "", "TFGeometry.glsl");
    GLuint programDrawQuadID = LoadShadersTransformFeedback( "AdapGridVertex.glsl", "", "AdapGridGeometry.glsl");
	GLuint programRenderingID = LoadShaders( "TransformVertexShader.glsl" ,"SimpleFragmentShader.glsl");
    GLuint programID= LoadShaders("DisparityVertexShader.glsl", "DisparityFragmentShader.glsl");
    GLuint MaxPyrProgramID = LoadShaders("MaxPyrVertex.glsl", "MaxPyrFragmentShader.glsl");
    GLuint WarpingProgramID = LoadShaders("WarpingVertex.glsl", "WarpingFragment.glsl");
    GLuint OGProgramID = LoadShaders("OGvertex.glsl", "OGfragment.glsl");
    GLuint MinPyrProgramID = LoadShaders("MinPyrVertex.glsl", "MinPyrFragment.glsl");
    GLuint PlainProgramID = LoadShaders("PlainVertex.glsl", "PlainFragment.glsl");
    

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    GLuint ModelMatrixID = glGetUniformLocation(programID, "ModelMatrix");
    GLuint ViewMatrixID = glGetUniformLocation(programID, "ViewMatrix");
    GLuint ProjectionMatrixID = glGetUniformLocation(programID, "ProjectionMatrix");

	// Load the texture

    int width0, height0, nrChannels0;
    int width1, height1, nrChannels1;
    int width2, height2, nrChannels2;
    int width3, height3, nrChannels3;
    int width4, height4, nrChannels4;
    int width5, height5, nrChannels5;
    int width6, height6, nrChannels6;
    int width7, height7, nrChannels7;
    int width8, height8, nrChannels8;
    int width9, height9, nrChannels9;
    int width10, height10, nrChannels10;
    int width11, height11, nrChannels11;
    int width12, height12, nrChannels12;
    int width13, height13, nrChannels13;
    int width14, height14, nrChannels14;

    unsigned char *data0 = stbi_load("./Enter a title.zip/floor1.jpg", &width0, &height0, &nrChannels0, 0);
    unsigned char *data1 = stbi_load("./Enter a title.zip/veshalka.jpg", &width1, &height1, &nrChannels1, 0);
    unsigned char *data2 = stbi_load("./Enter a title.zip/doors1.jpg", &width2, &height2, &nrChannels2, 0);
    unsigned char *data3 = stbi_load("./Enter a title.zip/Alyscamps_Arles_dos.JPG", &width3, &height3, &nrChannels3, 0);
    unsigned char *data4 = stbi_load("./Enter a title.zip/belye.jpg", &width4, &height4, &nrChannels4, 0);
    unsigned char *data5 = stbi_load("./Enter a title.zip/bad1.jpg", &width5, &height5, &nrChannels5, 0);
    unsigned char *data6 = stbi_load("./Enter a title.zip/rest.jpg", &width6, &height6, &nrChannels6, 0);
    unsigned char *data7 = stbi_load("./Enter a title.zip/wall_staff.jpg", &width7, &height7, &nrChannels7, 0);
    unsigned char *data8 = stbi_load("./Enter a title.zip/table.jpg", &width8, &height8, &nrChannels8, 0);
    unsigned char *data9 = stbi_load("./Enter a title.zip/chair1.jpg", &width9, &height9, &nrChannels9, 0);
    unsigned char *data10 = stbi_load("./Enter a title.zip/wall1.jpg", &width10, &height10, &nrChannels10, 0);
    unsigned char *data11 = stbi_load("./Enter a title.zip/win_right.jpg", &width11, &height11, &nrChannels11, 0);
    unsigned char *data12 = stbi_load("./Enter a title.zip/win_left.jpg", &width12, &height12, &nrChannels12, 0);
    unsigned char *data13 = stbi_load("./Enter a title.zip/glass_right.png", &width13, &height13, &nrChannels13, 0);
    unsigned char *data14 = stbi_load("./Enter a title.zip/glass_left.png", &width14, &height14, &nrChannels14, 0);


    unsigned int Texture0, Texture1, Texture2, Texture3, Texture4, Texture5,
    Texture6, Texture7, Texture8, Texture9, Texture10, Texture11, Texture12, Texture13, Texture14;
    glGenTextures(1, &Texture0);
    glGenTextures(1, &Texture1);
    glGenTextures(1, &Texture2);
    glGenTextures(1, &Texture3);
    glGenTextures(1, &Texture4);
    glGenTextures(1, &Texture5);
    glGenTextures(1, &Texture6);
    glGenTextures(1, &Texture7);
    glGenTextures(1, &Texture8);
    glGenTextures(1, &Texture9);
    glGenTextures(1, &Texture10);
    glGenTextures(1, &Texture11);
    glGenTextures(1, &Texture12);
    glGenTextures(1, &Texture13);
    glGenTextures(1, &Texture14);

	
	// Get a handle for our "myTextureSampler" uniform
	GLuint TextureID0  = glGetUniformLocation(programID, "texture0");
    GLuint TextureID1  = glGetUniformLocation(programID, "texture1");
    GLuint TextureID2  = glGetUniformLocation(programID, "texture2");
    GLuint TextureID3  = glGetUniformLocation(programID, "texture3");
    GLuint TextureID4  = glGetUniformLocation(programID, "texture4");
    GLuint TextureID5  = glGetUniformLocation(programID, "texture5");
    GLuint TextureID6  = glGetUniformLocation(programID, "texture6");
    GLuint TextureID7  = glGetUniformLocation(programID, "texture7");
    GLuint TextureID8  = glGetUniformLocation(programID, "texture8");
    GLuint TextureID9  = glGetUniformLocation(programID, "texture9");
    GLuint TextureID10  = glGetUniformLocation(programID, "texture10");
    GLuint TextureID11  = glGetUniformLocation(programID, "texture11");
    GLuint TextureID12  = glGetUniformLocation(programID, "texture12");
    GLuint TextureID13  = glGetUniformLocation(programID, "texture13");
    GLuint TextureID14  = glGetUniformLocation(programID, "texture14");
    

	// Read our .obj file
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals; // Won't be used at the moment.
    vector<int> texture_code_list;
	//bool res = loadOBJ("./Enter a title.zip/Enter a title.obj", vertices, uvs, normals);
    loadOBJWithMTL("./Enter a title.zip/Enter a title.obj", vertices, uvs, normals, texture_code_list);

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
    
    GLuint texturecodebuffer;
    glGenBuffers(1, &texturecodebuffer);
    glBindBuffer(GL_ARRAY_BUFFER, texturecodebuffer);
    glBufferData(GL_ARRAY_BUFFER, texture_code_list.size() * sizeof(int), &texture_code_list[0], GL_STATIC_DRAW);
    
    std::vector<glm::vec3> vertices_ATAT;
    std::vector<glm::vec2> uvs_ATAT;
    std::vector<glm::vec3> normals_ATAT;
    vector<int> texture_code_list_ATAT;
    loadOBJ("./ATAT/AtAt.obj", vertices_ATAT, uvs_ATAT, normals_ATAT);

    GLuint vertexbuffer_ATAT;
    glGenBuffers(1, &vertexbuffer_ATAT);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer_ATAT);
    glBufferData(GL_ARRAY_BUFFER, vertices_ATAT.size() * sizeof(glm::vec3), &vertices_ATAT[0], GL_STATIC_DRAW);
//
    GLuint uvbuffer_ATAT;
    glGenBuffers(1, &uvbuffer_ATAT);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer_ATAT);
    glBufferData(GL_ARRAY_BUFFER, uvs_ATAT.size() * sizeof(glm::vec2), &uvs_ATAT[0], GL_STATIC_DRAW);

    for (int i = 0; i<vertices_ATAT.size(); i++) {
        texture_code_list_ATAT.push_back(-1);
    }

    GLuint texturecodebuffer_ATAT;
    glGenBuffers(1, &texturecodebuffer_ATAT);
    glBindBuffer(GL_ARRAY_BUFFER, texturecodebuffer_ATAT);
    glBufferData(GL_ARRAY_BUFFER, texture_code_list_ATAT.size() * sizeof(int), &texture_code_list_ATAT[0], GL_STATIC_DRAW);
   
    vector<int> texture_code_list_Wall;
    static const GLfloat vertex_wall[] = {
       -20.0f, 20.0f, -10.0f, //TOP LEFT BACK
       20.0f, -20.0f, -10.0f, //BOTTOM RIGHT BACK
       -20.0f,  -20.0f, -10.0f, //BOTTOM LEFT BACK
        
        20.0f, -20.0f, -10.0f, //BOTTOM RIGHT BACK
        20.0f, 20.0f, -10.0f, //TOP RIGHT BACK
        -20.0f, 20.0f, -10.0f, //TOP LEFT BACK
        
        -20.0f,  -20.0f, 10.0f,//BOTTOM LEFT FRONT
        20.0f, -20.0f, 10.0f,//BOTTOM RIGHT FRONT
        -20.0f, 20.0f, 10.0f, //TOP LEFT FRONT
        
        -20.0f, 20.0f, 10.0f, //TOP LEFT FRONT
         20.0f, 20.0f, 10.0f, //TOP RIGHT FRONT
        20.0f, -20.0f, 10.0f, //BOTTOM RIGHT FRONT
         
        -20.0f,  -20.0f, -10.0f, //BOTTOM LEFT BACK
        20.0f, -20.0f, 10.0f, //BOTTOM RIGHT FRONT
        -20.0f,  -20.0f, 10.0f, //BOTTOM LEFT FRONT
        
        -20.0f,  -20.0f, -10.0f, //BOTTOM LEFT BACK
        20.0f, -20.0f, -10.0f, //BOTTOM RIGHT BACK
        20.0f, -20.0f, 10.0f, //BOTTOM RIGHT FRONT
        
        20.0f, 20.0f, -10.0f, //TOP RIGHT BACK
        20.0f, -20.0f, -10.0f, //BOTTOM RIGHT BACK
        20.0f, -20.0f, 10.0f,//BOTTOM RIGHT FRONT
        
        20.0f, 20.0f, -10.0f, //TOP RIGHT BACK
        20.0f, -20.0f, 10.0f,//BOTTOM RIGHT FRONT
        20.0f, 20.0f, 10.0f, //TOP RIGHT FRONT
        
        -20.0f, 20.0f, -10.0f, //TOP LEFT BACK
        -20.0f, 20.0f, 10.0f, //TOP LEFT FRONT
        20.0f, 20.0f, 10.0f, //TOP RIGHT FRONT
        
        -20.0f, 20.0f, -10.0f, //TOP LEFT BACK
        20.0f, 20.0f, -10.0f, //TOP RIGHT BACK
        20.0f, 20.0f, 10.0f, //TOP RIGHT FRONT
        
        -20.0f, 20.0f, -10.0f, //TOP LEFT BACK
        -20.0f,  -20.0f, -10.0f, //BOTTOM LEFT BACK
        -20.0f,  -20.0f, 10.0f, //BOTTOM LEFT FRONT
        
        -20.0f, 20.0f, -10.0f, //TOP LEFT BACK
        -20.0f,  -20.0f, 10.0f, //BOTTOM LEFT FRONT
        -20.0f, 20.0f, 10.0f, //TOP LEFT FRONT
        
        
    };
    for (int i = 0; i<12*3; i++) {
        texture_code_list_Wall.push_back(-2);
    }
    
    GLuint vertexbuffer_Wall;
    glGenBuffers(1, &vertexbuffer_Wall);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer_Wall);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_wall), vertex_wall, GL_STATIC_DRAW);
    
    GLuint texturecodebuffer_Wall;
    glGenBuffers(1, &texturecodebuffer_Wall);
    glBindBuffer(GL_ARRAY_BUFFER, texturecodebuffer_Wall);
    glBufferData(GL_ARRAY_BUFFER, texture_code_list_Wall.size() * sizeof(int), &texture_code_list_Wall[0], GL_STATIC_DRAW);

    
    // Create Texture that the disparity image will be save to:
    GLuint FramebufferName;
    glGenFramebuffers(1, &FramebufferName);
    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
    
    GLuint disparity_texture;
    createNewTexture(&disparity_texture, width, height);
    
    GLuint disparity_texture_max;
    createNewTexture(&disparity_texture_max, width, height);

    GLuint disparity_texture_min;
    createNewTexture(&disparity_texture_min, width, height);
        
    GLuint disparity_map;
    createNewTexture(&disparity_map, width, height);
    
    GLuint depth_map;
    createNewTexture(&depth_map, width, height);
    
    GLuint disparity_visual_map;
    createNewTexture(&disparity_visual_map, width, height);
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, disparity_texture, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, disparity_texture_max, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, disparity_texture_min, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, disparity_map, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT4, GL_TEXTURE_2D, depth_map, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT5, GL_TEXTURE_2D, disparity_visual_map, 0);

//    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, adaptive_grid_texture, 0);
    GLenum DrawBuffers[6] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3, GL_COLOR_ATTACHMENT4, GL_COLOR_ATTACHMENT5};
    glDrawBuffers(6, DrawBuffers);
    
    GLuint depthrenderbuffer;
    glGenRenderbuffers(1, &depthrenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        printf("Failed frame buffer 1");
        return 0;
    }
        
    
    // FBO for warped image
    GLuint FramebufferWarpedImage;
    glGenFramebuffers(1, &FramebufferWarpedImage);
    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferWarpedImage);
    
    GLuint warped_image;
    glGenTextures(1, &warped_image);
    glBindTexture(GL_TEXTURE_2D, warped_image);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2*width, 2*height, 0,GL_RGB, GL_FLOAT, 0); //MAC
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,GL_RGB, GL_FLOAT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, warped_image, 0);
    
    GLenum DrawBuffers1[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers1);
    
    GLuint depthrenderbuffer1;
    glGenRenderbuffers(1, &depthrenderbuffer1);
    glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer1);
//    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 2*width, 2*height);//MAC
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer1);
    
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        return 0;
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // FBO for warped image
    GLuint FramebufferResult;
    glGenFramebuffers(1, &FramebufferResult);
    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferResult);
    
    GLuint result_image;
    glGenTextures(1, &result_image);
    glBindTexture(GL_TEXTURE_2D, result_image);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,GL_RGB, GL_FLOAT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, result_image, 0);
    
    GLenum DrawBuffers2[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers2);
    
    GLuint depthrenderbuffer2;
    glGenRenderbuffers(1, &depthrenderbuffer2);
    glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer2);
//    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 2*width, 2*height);//MAC
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer2);
    
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        return 0;
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    
    int const grid_size = 8;

    static GLfloat g_quad_vertex_buffer_data[grid_size * grid_size * 3 * 2 * 4];
    int counter = 0;
    float step = 2.0f/grid_size;
    //Getting centers of all quads
    //TODO: This part needs to be in the Geometry processor for transform feed back
    for (float i = 0; i < grid_size; i++) {
        for (float j = 0; j < grid_size; j++){
            // 1 top-left
            g_quad_vertex_buffer_data[counter++] = (i / (float) grid_size) * 2.0f - 1.0f;
            g_quad_vertex_buffer_data[counter++] = (j / (float) grid_size) * 2.0f - 1.0f;
            g_quad_vertex_buffer_data[counter++] = 1.0f/grid_size;
            g_quad_vertex_buffer_data[counter++] = 0.0f;
            // 2 top-right
            g_quad_vertex_buffer_data[counter++] = (i / (float) grid_size) * 2.0f - 1.0f + step;
            g_quad_vertex_buffer_data[counter++] = (j / (float) grid_size) * 2.0f - 1.0f;
            g_quad_vertex_buffer_data[counter++] = 1.0f/grid_size;
            g_quad_vertex_buffer_data[counter++] = 0.0f;
            // 3 bottom-right
            g_quad_vertex_buffer_data[counter++] = (i / (float) grid_size) * 2.0f - 1.0f + step;
            g_quad_vertex_buffer_data[counter++] = (j / (float) grid_size) * 2.0f - 1.0f + step;
            g_quad_vertex_buffer_data[counter++] = 1.0f/grid_size;
            g_quad_vertex_buffer_data[counter++] = 0.0f;
            // 4 bottom-left
            g_quad_vertex_buffer_data[counter++] = (i / (float) grid_size) * 2.0f - 1.0f;
            g_quad_vertex_buffer_data[counter++] = (j / (float) grid_size) * 2.0f - 1.0f + step;
            g_quad_vertex_buffer_data[counter++] = 1.0f/grid_size;
            g_quad_vertex_buffer_data[counter++] = 0.0f;
            // 5 top-left
            g_quad_vertex_buffer_data[counter++] = (i / (float) grid_size) * 2.0f - 1.0f;
            g_quad_vertex_buffer_data[counter++] = (j / (float) grid_size) * 2.0f - 1.0f;
            g_quad_vertex_buffer_data[counter++] = 1.0f/grid_size;
            g_quad_vertex_buffer_data[counter++] = 0.0f;
            // 6 bottom-right
            g_quad_vertex_buffer_data[counter++] = (i / (float) grid_size) * 2.0f - 1.0f + step;
            g_quad_vertex_buffer_data[counter++] = (j / (float) grid_size) * 2.0f - 1.0f + step;
            g_quad_vertex_buffer_data[counter++] = 1.0f/grid_size;
            g_quad_vertex_buffer_data[counter++] = 0.0f;
        }
    }

    GLuint quad_vertexbuffer;
    glGenBuffers(1, &quad_vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);

//    GLuint adaptexID = glGetUniformLocation(programID, "adaptivegridTexture");
    
    glUseProgram(programTFID);
    
    static GLfloat g_vertex_buffer_data[grid_size * grid_size * 4];
    counter = 0;
    //Getting centers of all quads
    for (float i = 0; i < grid_size; i++) {
        for (float j = 0; j < grid_size; j++){
            g_vertex_buffer_data[counter++] = (i / (float) grid_size) * 2.0f - 1.0f + 1.0f/grid_size;
            g_vertex_buffer_data[counter++] = (j / (float) grid_size) * 2.0f - 1.0f + 1.0f/grid_size;
            g_vertex_buffer_data[counter++] = 1.0f/grid_size;
            g_vertex_buffer_data[counter++] = 1.0f;

        }
    }
    
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    
    
    // ID for all the textures
    glUseProgram(programID);
    GLuint texID = glGetUniformLocation(programID, "renderedTexture");
    GLuint disparity_map_ID = glGetUniformLocation(WarpingProgramID, "disparity_map");
    GLuint depth_map_ID = glGetUniformLocation(WarpingProgramID, "depth_map");
    
    // Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Texture0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width0, height0, 0, GL_RGB, GL_UNSIGNED_BYTE, data0);
    glGenerateMipmap(GL_TEXTURE_2D);
//    glUniform1i(TextureID0, 0);
    
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, Texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
    glGenerateMipmap(GL_TEXTURE_2D);
//    glUniform1i(TextureID1, 1);
    
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, Texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
    glGenerateMipmap(GL_TEXTURE_2D);
//    glUniform1i(TextureID2, 2);
    

    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, Texture3);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width3, height3, 0, GL_RGB, GL_UNSIGNED_BYTE, data3);
    glGenerateMipmap(GL_TEXTURE_2D);
//    glUniform1i(TextureID3, 3);
    
    // Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, Texture4);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width4, height4, 0, GL_RGB, GL_UNSIGNED_BYTE, data4);
    glGenerateMipmap(GL_TEXTURE_2D);
//    glUniform1i(TextureID4, 4);
    
    // Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, Texture5);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width5, height5, 0, GL_RGB, GL_UNSIGNED_BYTE, data5);
    glGenerateMipmap(GL_TEXTURE_2D);
//    glUniform1i(TextureID5, 5);

    glActiveTexture(GL_TEXTURE6);
    glBindTexture(GL_TEXTURE_2D, Texture6);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width6, height6, 0, GL_RGB, GL_UNSIGNED_BYTE, data6);
    glGenerateMipmap(GL_TEXTURE_2D);
//    glUniform1i(TextureID6, 6);

    glActiveTexture(GL_TEXTURE7);
    glBindTexture(GL_TEXTURE_2D, Texture7);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width7, height7, 0, GL_RGB, GL_UNSIGNED_BYTE, data7);
    glGenerateMipmap(GL_TEXTURE_2D);
//    glUniform1i(TextureID7, 7);

    glActiveTexture(GL_TEXTURE8);
    glBindTexture(GL_TEXTURE_2D, Texture8);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width8, height8, 0, GL_RGB, GL_UNSIGNED_BYTE, data8);
    glGenerateMipmap(GL_TEXTURE_2D);
//    glUniform1i(TextureID8, 8);
    
    // Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE9);
    glBindTexture(GL_TEXTURE_2D, Texture9);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width9, height9, 0, GL_RGB, GL_UNSIGNED_BYTE, data9);
    glGenerateMipmap(GL_TEXTURE_2D);
//    glUniform1i(TextureID9, 9);
    
    // Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE10);
    glBindTexture(GL_TEXTURE_2D, Texture10);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width10, height10, 0, GL_RGB, GL_UNSIGNED_BYTE, data10);
    glGenerateMipmap(GL_TEXTURE_2D);
//    glUniform1i(TextureID10, 10);
    
    // Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE11);
    glBindTexture(GL_TEXTURE_2D, Texture11);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width11, height11, 0, GL_RGB, GL_UNSIGNED_BYTE, data11);
    glGenerateMipmap(GL_TEXTURE_2D);
//    glUniform1i(TextureID11, 11);
    
    // Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE12);
    glBindTexture(GL_TEXTURE_2D, Texture12);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width12, height12, 0, GL_RGB, GL_UNSIGNED_BYTE, data12);
    glGenerateMipmap(GL_TEXTURE_2D);
//    glUniform1i(TextureID12, 12);
    
    // Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE13);
    glBindTexture(GL_TEXTURE_2D, Texture13);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width13, height13, 0, GL_RGB, GL_UNSIGNED_BYTE, data13);
    glGenerateMipmap(GL_TEXTURE_2D);
//    glUniform1i(TextureID13, 13);
    
    // Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE14);
    glBindTexture(GL_TEXTURE_2D, Texture14);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width14, height14, 0, GL_RGB, GL_UNSIGNED_BYTE, data14);
    glGenerateMipmap(GL_TEXTURE_2D);
//    glUniform1i(TextureID14, 14);

    
//    glUseProgram(programTFID);
//
//    int chosen_dimension = height/grid_size;
//    int lvl = floor(std::log2(chosen_dimension));
//    int num_level = lvl - 3;
////        printf("%u level to divide\n\n", lvl);
////        int num_level = (int) round(log2((float)height/(float)grid_size)) - 2;
//
//
////        printf("%u level to divide\n\n", num_level);
//
////        printf("%u buffer size\n\n", grid_size * grid_size * (int) pow(4,num_level));
//
//    int level = 0;
//
////        num_level = 2;
//
//    //Set vbo for the Transform Feedback
//    GLuint tbo;
//    glGenBuffers(1, &tbo);
//    glBindBuffer(GL_ARRAY_BUFFER, tbo);
//    glBufferData(GL_ARRAY_BUFFER, grid_size * grid_size * (int) pow(4,num_level) * 6 * sizeof(GLfloat), nullptr, GL_STATIC_READ);
////    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, tbo);

    
	do{
        // LOAD THE MODEL AND RENDER
        glUseProgram(programID);
        glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
        glViewport(0, 0, width, height);

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

		// Compute the MVP matrix from keyboard and mouse input
		computeMatricesFromInputs();
        int mode = getMode();
        int lod = getLOD();
        int kernel_size = getKernelSize();
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		glm::mat4 ModelMatrix = glm::mat4(1.0);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
        glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
        glUniformMatrix4fv(ProjectionMatrixID, 1, GL_FALSE, &ProjectionMatrix[0][0]);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture0);
        glTexSubImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width0, height0, 0, GL_RGB, GL_UNSIGNED_BYTE, data0);
		glUniform1i(TextureID0, 0);
        
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, Texture1);
        glTexSubImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
        glUniform1i(TextureID1, 1);
        
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, Texture2);
        glTexSubImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
        glUniform1i(TextureID2, 2);
        
 
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, Texture3);
        glTexSubImage2D(GL_TEXTURE_2D, 0, GL_RGB, width3, height3, 0, GL_RGB, GL_UNSIGNED_BYTE, data3);
        glUniform1i(TextureID3, 3);
        
        // Bind our texture in Texture Unit 0
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, Texture4);
        glTexSubImage2D(GL_TEXTURE_2D, 0, GL_RGB, width4, height4, 0, GL_RGB, GL_UNSIGNED_BYTE, data4);
        glUniform1i(TextureID4, 4);
        
        // Bind our texture in Texture Unit 0
        glActiveTexture(GL_TEXTURE5);
        glBindTexture(GL_TEXTURE_2D, Texture5);
        glTexSubImage2D(GL_TEXTURE_2D, 0, GL_RGB, width5, height5, 0, GL_RGB, GL_UNSIGNED_BYTE, data5);
        glUniform1i(TextureID5, 5);

        glActiveTexture(GL_TEXTURE6);
        glBindTexture(GL_TEXTURE_2D, Texture6);
        glTexSubImage2D(GL_TEXTURE_2D, 0, GL_RGB, width6, height6, 0, GL_RGB, GL_UNSIGNED_BYTE, data6);
        glUniform1i(TextureID6, 6);

        glActiveTexture(GL_TEXTURE7);
        glBindTexture(GL_TEXTURE_2D, Texture7);
        glTexSubImage2D(GL_TEXTURE_2D, 0, GL_RGB, width7, height7, 0, GL_RGB, GL_UNSIGNED_BYTE, data7);
        glUniform1i(TextureID7, 7);

        glActiveTexture(GL_TEXTURE8);
        glBindTexture(GL_TEXTURE_2D, Texture8);
        glTexSubImage2D(GL_TEXTURE_2D, 0, GL_RGB, width8, height8, 0, GL_RGB, GL_UNSIGNED_BYTE, data8);
        glUniform1i(TextureID8, 8);
        
        glActiveTexture(GL_TEXTURE9);
        glBindTexture(GL_TEXTURE_2D, Texture9);
        glTexSubImage2D(GL_TEXTURE_2D, 0, GL_RGB, width9, height9, 0, GL_RGB, GL_UNSIGNED_BYTE, data9);
        glUniform1i(TextureID9, 9);
        
        glActiveTexture(GL_TEXTURE10);
        glBindTexture(GL_TEXTURE_2D, Texture10);
        glTexSubImage2D(GL_TEXTURE_2D, 0, GL_RGB, width10, height10, 0, GL_RGB, GL_UNSIGNED_BYTE, data10);
        glUniform1i(TextureID10, 10);
        
        glActiveTexture(GL_TEXTURE11);
        glBindTexture(GL_TEXTURE_2D, Texture11);
        glTexSubImage2D(GL_TEXTURE_2D, 0, GL_RGB, width11, height11, 0, GL_RGB, GL_UNSIGNED_BYTE, data11);
        glUniform1i(TextureID11, 11);
        
        glActiveTexture(GL_TEXTURE12);
        glBindTexture(GL_TEXTURE_2D, Texture12);
        glTexSubImage2D(GL_TEXTURE_2D, 0, GL_RGB, width12, height12, 0, GL_RGB, GL_UNSIGNED_BYTE, data12);
        glUniform1i(TextureID12, 12);
        
        glActiveTexture(GL_TEXTURE13);
        glBindTexture(GL_TEXTURE_2D, Texture13);
        glTexSubImage2D(GL_TEXTURE_2D, 0, GL_RGB, width13, height13, 0, GL_RGB, GL_UNSIGNED_BYTE, data13);
        glUniform1i(TextureID13, 13);
        
        glActiveTexture(GL_TEXTURE14);
        glBindTexture(GL_TEXTURE_2D, Texture14);
        glTexSubImage2D(GL_TEXTURE_2D, 0, GL_RGB, width14, height14, 0, GL_RGB, GL_UNSIGNED_BYTE, data14);
        glUniform1i(TextureID14, 14);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			1,                                // attribute
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);
        
        // texture code
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, texturecodebuffer);
        glVertexAttribPointer(
            2,                                // attribute
            1,                                // size
            GL_INT,                          // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
        );

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer_ATAT);
        glVertexAttribPointer(
            0,                  // attribute
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        // 2nd attribute buffer : UVs
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer_ATAT);
        glVertexAttribPointer(
            1,                                // attribute
            2,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
        );

        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, texturecodebuffer_ATAT);
        glVertexAttribPointer(
            2,                                // attribute
            1,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
        );

        glDrawArrays(GL_TRIANGLES, 0, vertices_ATAT.size());
        
//        glUseProgram(WallProgramID);
//        glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
//        glViewport(0, 0, width, height);
        
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer_Wall);
        glVertexAttribPointer(
            0,                  // attribute
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );
        
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, texturecodebuffer_Wall);
        glVertexAttribPointer(
            2,                                // attribute
            1,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
        );
        
        glDrawArrays(GL_TRIANGLES, 0, 6 * 6);
        
        glUseProgram(programID);
        glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
        glViewport(0, 0, width, height);

        // MINMAX MIPMAP PROCESSING
        
        glBindTexture(GL_TEXTURE_2D, disparity_texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glGenerateMipmap(GL_TEXTURE_2D);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, disparity_texture, 0);
        
        glBindTexture(GL_TEXTURE_2D, disparity_texture_max);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        glBindTexture(GL_TEXTURE_2D, disparity_texture_min);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        glBindTexture(GL_TEXTURE_2D, disparity_map);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        for (int level = 1; level < 10; level++) {
            glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
            
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, disparity_texture, level);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, disparity_texture_max, level);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, disparity_texture_min, level);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, disparity_map, level);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT4, GL_TEXTURE_2D, depth_map, level);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT5, GL_TEXTURE_2D, disparity_visual_map, level);

            glViewport(0, 0, width / pow(2.0, level), height / pow(2.0, level));
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glUseProgram(MaxPyrProgramID);
            GLuint levelID = glGetUniformLocation(MaxPyrProgramID, "level");
            glUniform1i(levelID, level);
            
            GLuint kernel_size_ID = glGetUniformLocation(MaxPyrProgramID, "kernel_size");
            glUniform1i(kernel_size_ID, kernel_size);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, disparity_texture_max);
            GLuint TextureID_max = glGetUniformLocation(MaxPyrProgramID, "textureSamplerMax");
            glUniform1i(TextureID_max, 0);
            
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, disparity_texture_min);
            GLuint TextureID_min = glGetUniformLocation(MaxPyrProgramID, "textureSamplerMin");
            glUniform1i(TextureID_min, 1);
            
            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D, disparity_texture);
            GLuint TextureID_sampler = glGetUniformLocation(MaxPyrProgramID, "textureSampler");
            glUniform1i(TextureID_sampler, 2);

            // Draw the triangles !
            glEnableVertexAttribArray(3);
            glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
            glVertexAttribPointer(
                3,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                4,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*)0            // array buffer offset
            );
            glDrawArrays(GL_TRIANGLES, 0, grid_size * grid_size * 6);
            
            
            glBindTexture(GL_TEXTURE0, 0);
            glBindTexture(GL_TEXTURE1, 0);


        }
        
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, disparity_texture, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, disparity_texture_max, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, disparity_texture_min, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, disparity_map, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT4, GL_TEXTURE_2D, depth_map, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT5, GL_TEXTURE_2D, disparity_visual_map, 0);
        
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        

        //----------------------------------------------------------------------------------------------------------------------------------
        // Offscreen the adaptive grid
        //TRANSFORM FEEDBACK LOOPS
        
        glUseProgram(programTFID);
        
        glEnable(GL_RASTERIZER_DISCARD);
        
        int chosen_dimension = height/grid_size;
        int lvl = floor(std::log2(chosen_dimension));
        int num_level = lvl - 3;
        printf("%u level to divide\n\n", lvl);
//        int num_level = (int) round(log2((float)height/(float)grid_size)) - 2;


//        printf("%u level to divide\n\n", num_level);

//        printf("%u buffer size\n\n", grid_size * grid_size * (int) pow(4,num_level));

        int level = 0;

//        num_level = 2;

        //Set vbo for the Transform Feedback
        GLuint tbo;
        glGenBuffers(1, &tbo);
        glBindBuffer(GL_ARRAY_BUFFER, tbo);
        glBufferData(GL_ARRAY_BUFFER, grid_size * grid_size * (int) pow(4,num_level+1) * 6 * sizeof(GLfloat), nullptr, GL_STATIC_READ);
        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, tbo);
        glCopyBufferSubData(vbo, tbo,0,0,sizeof(g_vertex_buffer_data));
//        printf("%u TF buffer size\n\n", grid_size * grid_size * (int) pow(4,num_level));
        
        glBindBuffer(GL_ARRAY_BUFFER, tbo);
//        glBufferData(GL_ARRAY_BUFFER, grid_size * grid_size * (int) pow(4,num_level) * 6 * sizeof(GLfloat), nullptr, GL_STATIC_READ);
        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, tbo);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, disparity_texture_max);
        GLuint TextureID_max = glGetUniformLocation(programTFID, "maxTexture");
        glUniform1i(TextureID_max, 0);
        
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, disparity_texture_min);
        GLuint TextureID_min = glGetUniformLocation(programTFID, "minTexture");
        glUniform1i(TextureID_min, 1);
        
        
        GLuint primitives = grid_size * grid_size * 4 * 4;
        GLuint primitives_points = grid_size * grid_size * 4;
        GLuint primitives_mesh = grid_size * grid_size * 6;
        GLfloat data_points[grid_size * grid_size * (int) pow(4, num_level+2)];
        GLfloat data_final[grid_size * grid_size * (int) pow(4, num_level+2) * 6];
        
        
        //Set vbo for the input array
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            4,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );
        
        GLuint levelID = glGetUniformLocation(programTFID, "level_uniform");
        glUniform1i(levelID, level);
        
        GLuint num_levelID = glGetUniformLocation(programTFID, "num_level");
        glUniform1i(num_levelID, num_level);
        
        GLuint LodID = glGetUniformLocation(programTFID, "lod");
        glUniform1i(LodID, lod);
        
        GLuint query;

        GLuint new_vbo1;
        glGenBuffers(1, &new_vbo1);
        
        //TODO: find a way to make this into 1 to gridsize and collect all center
        // points from there. Then subdivide and recombined or subdivide and render
        // later.
        for (level = 0; level <= num_level; level++) {
            
            levelID = glGetUniformLocation(programTFID, "level_uniform");
            glUniform1i(levelID, level);
            
            
            glGenQueries(1, &query);
            glBeginQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, query);
            
            glBeginTransformFeedback(GL_POINTS);
            if(level == num_level){
                glDrawArrays(GL_POINTS, 0, grid_size * grid_size * (int) pow(4, num_level+1) * 6);
            } else {
                glDrawArrays(GL_POINTS, 0, primitives * 4);
            }
            glEndTransformFeedback();
            
            glEndQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN);
            
//            printf("%u primitives before TF level %u!\n\n", primitives, level);
            
//            GLuint prev_primitives = primitives;
            
            glGetQueryObjectuiv(query, GL_QUERY_RESULT, &primitives);
            
//            printf("%u primitives after TF level %u!\n\n", primitives, level);
            
            GLfloat data[primitives];
            if(level == num_level){
                glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, primitives*6, data);
            } else {
                glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, primitives*4, data);
            }
            
            glBindBuffer(GL_ARRAY_BUFFER, new_vbo1);
            glBufferData(GL_ARRAY_BUFFER, primitives * sizeof(GLfloat), data, GL_STATIC_DRAW);
            
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, new_vbo1);
            glVertexAttribPointer(
                0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                4,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*)0            // array buffer offset
            );
            
            
            if(level == num_level - 1){
//                data_points[primitives * (int)pow(4, level-1)];
                glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, primitives*4, data_points);
                primitives_points = primitives * 4;
            }
            
            if(level == num_level){
                glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, primitives * 6, data_final);
                primitives_mesh = primitives * 6;
            }
            

        }
       
        glFlush();

        glDisableVertexAttribArray(0);
        glDeleteBuffers(1, &new_vbo1);
        glDeleteBuffers(1, &tbo);
        
        GLuint new_vbo;
        glGenBuffers(1, &new_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, new_vbo);
        glBufferData(GL_ARRAY_BUFFER, primitives_mesh, data_final, GL_STATIC_DRAW);
        
        
        GLuint points_vbo;
        glGenBuffers(1, &points_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glBufferData(GL_ARRAY_BUFFER, primitives_points, data_points, GL_STATIC_DRAW);
        
        
    
        
        //---------------------------------------------------------------------------------------------------------------------------------
        // WARPING AND RENDERING
        
        glDisable(GL_RASTERIZER_DISCARD);
        
        GLuint color_ID = glGetUniformLocation(programRenderingID, "color");
        
        glUseProgram(WarpingProgramID);
        glBindFramebuffer(GL_FRAMEBUFFER, FramebufferWarpedImage);

        glClearColor(0.0f,0.0f,0.0f,1.0f);

        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//                    glViewport(0, 0, 2*width, 2*height);//MAC
        glViewport(0, 0, width, height);
        
        glDisable(GL_CULL_FACE);
        //glDisable(GL_BLEND);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, disparity_texture);
        GLuint og_image_ID = glGetUniformLocation(WarpingProgramID, "original_image");
        glUniform1i(og_image_ID, 0);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, disparity_map);
        glUniform1i(disparity_map_ID, 1);
        
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, depth_map);
        glUniform1i(depth_map_ID, 2);
        
        glEnableVertexAttribArray(0);
        
        glBindBuffer(GL_ARRAY_BUFFER, new_vbo);
        glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            4,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );
        glDrawArrays(GL_TRIANGLES, 0, primitives_mesh);
        
//        glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
//        glVertexAttribPointer(
//            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
//            4,                  // size
//            GL_FLOAT,           // type
//            GL_FALSE,           // normalized?
//            0,                  // stride
//            (void*)0            // array buffer offset
//        );
//        glDrawArrays(GL_TRIANGLES, 0, grid_size * grid_size * 6);
        
        
        glBindTexture(GL_TEXTURE0, 0);
        glBindTexture(GL_TEXTURE1, 0);
        
        glUseProgram(OGProgramID);
        glBindFramebuffer(GL_FRAMEBUFFER, FramebufferResult);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClearDepth(1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//                    glViewport(0, 0, 2*width, 2*height);//MAC
        glViewport(0, 0, width, height);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, disparity_texture);
        GLuint original_image_ID = glGetUniformLocation(OGProgramID, "original_image");
        glUniform1i(original_image_ID, 0);
        
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, warped_image);
        GLuint warped_image_ID = glGetUniformLocation(OGProgramID, "warped_image");
        glUniform1i(warped_image_ID, 1);

        glEnableVertexAttribArray(0);
        
        glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
        glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            4,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );
        glDrawArrays(GL_TRIANGLES, 0, grid_size * grid_size * 6);
        
        
        switch (mode) {
            case 0: //RESULTING IMAGE
                {
                    glUseProgram(WarpingProgramID);
                    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferWarpedImage);

                    glClearColor(0.0f,0.0f,0.0f,1.0f);

                    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//                    glViewport(0, 0, 2*width, 2*height);//MAC
                    glViewport(0, 0, width, height);
                    
                    glDisable(GL_CULL_FACE);
                    //glDisable(GL_BLEND);

                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, disparity_texture);
                    GLuint og_image_ID = glGetUniformLocation(WarpingProgramID, "original_image");
                    glUniform1i(og_image_ID, 0);

                    glActiveTexture(GL_TEXTURE1);
                    glBindTexture(GL_TEXTURE_2D, disparity_map);
                    glUniform1i(disparity_map_ID, 1);
                    
                    glActiveTexture(GL_TEXTURE2);
                    glBindTexture(GL_TEXTURE_2D, depth_map);
                    glUniform1i(depth_map_ID, 2);
                    
                    glEnableVertexAttribArray(0);
                    
                    glBindBuffer(GL_ARRAY_BUFFER, new_vbo);
                    glVertexAttribPointer(
                        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                        4,                  // size
                        GL_FLOAT,           // type
                        GL_FALSE,           // normalized?
                        0,                  // stride
                        (void*)0            // array buffer offset
                    );
                    glDrawArrays(GL_TRIANGLES, 0, primitives_mesh);
                    
            //        glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
            //        glVertexAttribPointer(
            //            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            //            4,                  // size
            //            GL_FLOAT,           // type
            //            GL_FALSE,           // normalized?
            //            0,                  // stride
            //            (void*)0            // array buffer offset
            //        );
            //        glDrawArrays(GL_TRIANGLES, 0, grid_size * grid_size * 6);
                    
                    
                    glBindTexture(GL_TEXTURE0, 0);
                    glBindTexture(GL_TEXTURE1, 0);
                    
                    glUseProgram(OGProgramID);
                    glBindFramebuffer(GL_FRAMEBUFFER, 0);
                    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                    glClearDepth(1.0);
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//                    glViewport(0, 0, 2*width, 2*height);//MAC
                    glViewport(0, 0, width, height);

                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, disparity_texture);
                    GLuint original_image_ID = glGetUniformLocation(OGProgramID, "original_image");
                    glUniform1i(original_image_ID, 0);
                    
                    glActiveTexture(GL_TEXTURE1);
                    glBindTexture(GL_TEXTURE_2D, warped_image);
                    GLuint warped_image_ID = glGetUniformLocation(OGProgramID, "warped_image");
                    glUniform1i(warped_image_ID, 1);

                    glEnableVertexAttribArray(0);
                    
                    glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
                    glVertexAttribPointer(
                        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                        4,                  // size
                        GL_FLOAT,           // type
                        GL_FALSE,           // normalized?
                        0,                  // stride
                        (void*)0            // array buffer offset
                    );
                    glDrawArrays(GL_TRIANGLES, 0, grid_size * grid_size * 6);
                    
                }
                break;
            case 1: //ORIGINAL IMAGE
                {
                    glUseProgram(PlainProgramID);
                    glBindFramebuffer(GL_FRAMEBUFFER, 0);

                    glClearColor(0.0f,0.0f,0.0f,1.0f);

                    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//                    glViewport(0, 0, 2*width, 2*height);//MAC
                    glViewport(0, 0, width, height);
                    
                    glDisable(GL_CULL_FACE);
                    //glDisable(GL_BLEND);

                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, disparity_texture);
                    GLuint og_image_ID = glGetUniformLocation(PlainProgramID, "original_image");
                    glUniform1i(og_image_ID, 0);
                    
                    GLuint lodID = glGetUniformLocation(PlainProgramID, "lod");
                    glUniform1i(lodID, 0);
                    
                    glEnableVertexAttribArray(0);
                    
                    glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
                    glVertexAttribPointer(
                        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                        4,                  // size
                        GL_FLOAT,           // type
                        GL_FALSE,           // normalized?
                        0,                  // stride
                        (void*)0            // array buffer offset
                    );
                    glDrawArrays(GL_TRIANGLES, 0, grid_size * grid_size * 6);
                    
                };
                break;
            case 2: //DEPTH MAP
                {
                    glUseProgram(PlainProgramID);
                    glBindFramebuffer(GL_FRAMEBUFFER, 0);

                    glClearColor(0.0f,0.0f,0.0f,1.0f);

                    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//                    glViewport(0, 0, 2*width, 2*height);//MAC
                    glViewport(0, 0, width, height);
                    
                    glDisable(GL_CULL_FACE);
                    //glDisable(GL_BLEND);

                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, depth_map);
                    GLuint og_image_ID = glGetUniformLocation(PlainProgramID, "original_image");
                    glUniform1i(og_image_ID, 0);
                    
                    GLuint lodID = glGetUniformLocation(PlainProgramID, "lod");
                    glUniform1i(lodID, 0);
                    
                    glEnableVertexAttribArray(0);
                    
                    glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
                    glVertexAttribPointer(
                        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                        4,                  // size
                        GL_FLOAT,           // type
                        GL_FALSE,           // normalized?
                        0,                  // stride
                        (void*)0            // array buffer offset
                    );
                    glDrawArrays(GL_TRIANGLES, 0, grid_size * grid_size * 6);
                };
                
                break;
            case 3: //DISPARITY MAP
                {
                    glUseProgram(PlainProgramID);
                    glBindFramebuffer(GL_FRAMEBUFFER, 0);

                    glClearColor(0.0f,0.0f,0.0f,1.0f);

                    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//                    glViewport(0, 0, 2*width, 2*height);//MAC
                    glViewport(0, 0, width, height);
                    
                    glDisable(GL_CULL_FACE);
                    //glDisable(GL_BLEND);

                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, disparity_visual_map);
                    GLuint og_image_ID = glGetUniformLocation(PlainProgramID, "original_image");
                    glUniform1i(og_image_ID, 0);
                    
                    GLuint lodID = glGetUniformLocation(PlainProgramID, "lod");
                    glUniform1i(lodID, 0);
                    
                    glEnableVertexAttribArray(0);
                    
                    glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
                    glVertexAttribPointer(
                        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                        4,                  // size
                        GL_FLOAT,           // type
                        GL_FALSE,           // normalized?
                        0,                  // stride
                        (void*)0            // array buffer offset
                    );
                    glDrawArrays(GL_TRIANGLES, 0, grid_size * grid_size * 6);
                };
                
                break;
            case 4: //MAX MIPMAP
                {
                    glUseProgram(PlainProgramID);
                    glBindFramebuffer(GL_FRAMEBUFFER, 0);

                    glClearColor(0.0f,0.0f,0.0f,1.0f);

                    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//                    glViewport(0, 0, 2*width, 2*height);//MAC
                    glViewport(0, 0, width, height);
                    
                    glDisable(GL_CULL_FACE);
                    //glDisable(GL_BLEND);

                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, disparity_texture_max);
                    GLuint og_image_ID = glGetUniformLocation(PlainProgramID, "original_image");
                    glUniform1i(og_image_ID, 0);
                    
                    GLuint lodID = glGetUniformLocation(PlainProgramID, "lod");
                    glUniform1i(lodID, lod);
                    
                    glEnableVertexAttribArray(0);
                    
                    glBindBuffer(GL_ARRAY_BUFFER, new_vbo);
                    glVertexAttribPointer(
                        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                        4,                  // size
                        GL_FLOAT,           // type
                        GL_FALSE,           // normalized?
                        0,                  // stride
                        (void*)0            // array buffer offset
                    );
                    glDrawArrays(GL_TRIANGLES, 0, primitives_mesh);
                };
                break;
            case 5: //MIN MIPMAP
                {
                    glUseProgram(PlainProgramID);
                    glBindFramebuffer(GL_FRAMEBUFFER, 0);

                    glClearColor(0.0f,0.0f,0.0f,1.0f);

                    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//                    glViewport(0, 0, 2*width, 2*height);//MAC
                    glViewport(0, 0, width, height);
                    
                    glDisable(GL_CULL_FACE);
                    //glDisable(GL_BLEND);

                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, disparity_texture_min);
                    GLuint og_image_ID = glGetUniformLocation(PlainProgramID, "original_image");
                    glUniform1i(og_image_ID, 0);
                    
                    GLuint lodID = glGetUniformLocation(PlainProgramID, "lod");
                    glUniform1i(lodID, lod);
                    
                    glEnableVertexAttribArray(0);
                    
                    glBindBuffer(GL_ARRAY_BUFFER, new_vbo);
                    glVertexAttribPointer(
                        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                        4,                  // size
                        GL_FLOAT,           // type
                        GL_FALSE,           // normalized?
                        0,                  // stride
                        (void*)0            // array buffer offset
                    );
                    glDrawArrays(GL_TRIANGLES, 0, primitives_mesh);
                };
                break;
            case 6: //ORIGINAL POINTS AND MESH
                {
                    glUseProgram(PlainProgramID);
                    glBindFramebuffer(GL_FRAMEBUFFER, 0);

                    glClearColor(0.0f,0.0f,0.0f,1.0f);

                    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//                    glViewport(0, 0, 2*width, 2*height);//MAC
                    glViewport(0, 0, width, height);
                    
                    glDisable(GL_CULL_FACE);
                    //glDisable(GL_BLEND);

                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, disparity_texture);
                    GLuint og_image_ID = glGetUniformLocation(PlainProgramID, "original_image");
                    glUniform1i(og_image_ID, 0);
                    
                    GLuint lodID = glGetUniformLocation(PlainProgramID, "lod");
                    glUniform1i(lodID, 0);
                    
                    glEnableVertexAttribArray(0);
                    
                    glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
                    glVertexAttribPointer(
                        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                        4,                  // size
                        GL_FLOAT,           // type
                        GL_FALSE,           // normalized?
                        0,                  // stride
                        (void*)0            // array buffer offset
                    );
                    glDrawArrays(GL_TRIANGLES, 0, grid_size * grid_size * 6);
                    // DISPLAY THE MESH DIVISION for vbo
                    
                    glUseProgram(programRenderingID);
                    glBindFramebuffer(GL_FRAMEBUFFER, 0);
                    glClear(GL_DEPTH_BUFFER_BIT);
//                    glViewport(0, 0, 2*width, 2*height);//MAC
                    glViewport(0, 0, width, height);
                    
                    color_ID = glGetUniformLocation(programRenderingID, "color");
                    glUniform3f(color_ID,0.0f, 1.0f, 0.0f);
                    
                    glEnableVertexAttribArray(0);
                    glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
                    glVertexAttribPointer(
                        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                        4,                  // size
                        GL_FLOAT,           // type
                        GL_FALSE,           // normalized?
                        0,                  // stride
                        (void*)0            // array buffer offset
                    );
            //
                    glLineWidth(0.5);
                    glDrawArrays(GL_LINE_STRIP_ADJACENCY, 0, grid_size * grid_size * 6);
                    
                    // DISPLAY THE POINTS FOR VBO
                    
                    glDisable(GL_RASTERIZER_DISCARD);
                    
                    glUseProgram(programRenderingID);
                    glBindFramebuffer(GL_FRAMEBUFFER, 0);
                    glClear(GL_DEPTH_BUFFER_BIT);
//                    glViewport(0, 0, 2*width, 2*height);//MAC
                    glViewport(0, 0, width, height);
                    
                    color_ID = glGetUniformLocation(programRenderingID, "color");
                    glUniform3f(color_ID,0.0f, 1.0f, 0.0f);
                    
                    glEnableVertexAttribArray(0);
                    glBindBuffer(GL_ARRAY_BUFFER, vbo);
            //        glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
                    glVertexAttribPointer(
                        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                        4,                  // size
                        GL_FLOAT,           // type
                        GL_FALSE,           // normalized?
                        0,                  // stride
                        (void*)0            // array buffer offset
                    );
            //
                    glPointSize(5);
                    glDrawArrays(GL_POINTS, 0, grid_size * grid_size * 6);
                };
                break;
            case 7: //SUBDIVIDIDED POINTS AND MESH
                {
                    
                    glDisable(GL_RASTERIZER_DISCARD);
                    
                    glUseProgram(PlainProgramID);
                    glBindFramebuffer(GL_FRAMEBUFFER, 0);

                    glClearColor(0.0f,0.0f,0.0f,1.0f);

                    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//                    glViewport(0, 0, 2*width, 2*height);//MAC
                    glViewport(0, 0, width, height);
                    
                    glDisable(GL_CULL_FACE);
                    //glDisable(GL_BLEND);

                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, disparity_texture);
                    GLuint og_image_ID = glGetUniformLocation(PlainProgramID, "original_image");
                    glUniform1i(og_image_ID, 0);
                    
                    GLuint lodID = glGetUniformLocation(PlainProgramID, "lod");
                    glUniform1i(lodID, 0);
                    
                    glEnableVertexAttribArray(0);
                    
                    glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
                    glVertexAttribPointer(
                        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                        4,                  // size
                        GL_FLOAT,           // type
                        GL_FALSE,           // normalized?
                        0,                  // stride
                        (void*)0            // array buffer offset
                    );
                    glDrawArrays(GL_TRIANGLES, 0, grid_size * grid_size * 6);
                    
                    glUseProgram(programRenderingID);
                    glBindFramebuffer(GL_FRAMEBUFFER, 0);
                    glClear(GL_DEPTH_BUFFER_BIT);
//                    glViewport(0, 0, 2*width, 2*height);//MAC
                    glViewport(0, 0, width, height);
                    
                    color_ID = glGetUniformLocation(programRenderingID, "color");
                    glUniform3f(color_ID,0.0f, 1.0f, 0.0f);
            //        glUniform1i(warped_image_ID, 1);
                    
                    glEnableVertexAttribArray(0);
                    glBindBuffer(GL_ARRAY_BUFFER, new_vbo);
                    glVertexAttribPointer(
                        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                        4,                  // size
                        GL_FLOAT,           // type
                        GL_FALSE,           // normalized?
                        0,                  // stride
                        (void*)0            // array buffer offset
                    );
            //
                    glLineWidth(0.5);
                    glDrawArrays(GL_LINE_STRIP_ADJACENCY, 0, primitives_mesh);
                     
                    
                    // DISPLAY THE POINTS FOR NEW VBO
                    
                    glDisable(GL_RASTERIZER_DISCARD);
                    
                    
                    glUseProgram(programRenderingID);
                    glBindFramebuffer(GL_FRAMEBUFFER, 0);
                    glClear(GL_DEPTH_BUFFER_BIT);
//                    glViewport(0, 0, 2*width, 2*height);//MAC
                    glViewport(0, 0, width, height);
                    
                    color_ID = glGetUniformLocation(programRenderingID, "color");
                    glUniform3f(color_ID,0.8f, 0.0f, 0.7f);
                    
                    glEnableVertexAttribArray(0);
                    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
                    glVertexAttribPointer(
                        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                        4,                  // size
                        GL_FLOAT,           // type
                        GL_FALSE,           // normalized?
                        0,                  // stride
                        (void*)0            // array buffer offset
                    );
            //
                    glPointSize(10);
                    glDrawArrays(GL_POINTS, 0, primitives_points);
                    
                };
                break;
            case 8:
                break;
            case 9:
            {
                glUseProgram(PlainProgramID);
                glBindFramebuffer(GL_FRAMEBUFFER, 0);

                glClearColor(0.0f,0.0f,0.0f,1.0f);

                glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//                glViewport(width, 0, width, height); // RIGHT DOWN MAC
                glViewport(width/2, 0, width/2, height/2); // RIGHT DOWN
                
                glDisable(GL_CULL_FACE);
                //glDisable(GL_BLEND);

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, result_image);
                og_image_ID = glGetUniformLocation(PlainProgramID, "original_image");
                glUniform1i(og_image_ID, 0);
                
                GLuint lodID = glGetUniformLocation(PlainProgramID, "lod");
                glUniform1i(lodID, 0);
                
                glEnableVertexAttribArray(0);
                
                glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
                glVertexAttribPointer(
                    0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                    4,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    0,                  // stride
                    (void*)0            // array buffer offset
                );
                
                glDrawArrays(GL_TRIANGLES, 0, grid_size * grid_size * 6);
                
                glUseProgram(PlainProgramID);
                glBindFramebuffer(GL_FRAMEBUFFER, 0);

                glClearColor(0.0f,0.0f,0.0f,1.0f);

//                glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//                glViewport(0, 0, width, height); // LEFT DOWN MAC
                glViewport(0, 0, width/2, height/2); // LEFT DOWN
                
                glDisable(GL_CULL_FACE);
                //glDisable(GL_BLEND);

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, disparity_texture);
                og_image_ID = glGetUniformLocation(PlainProgramID, "original_image");
                glUniform1i(og_image_ID, 0);
                
                lodID = glGetUniformLocation(PlainProgramID, "lod");
                glUniform1i(lodID, 0);
                
                glEnableVertexAttribArray(0);
                
                glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
                glVertexAttribPointer(
                    0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                    4,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    0,                  // stride
                    (void*)0            // array buffer offset
                );
                
                glDrawArrays(GL_TRIANGLES, 0, grid_size * grid_size * 6);
                
                glUseProgram(programRenderingID);
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
                glClear(GL_DEPTH_BUFFER_BIT);
                
                color_ID = glGetUniformLocation(programRenderingID, "color");
                glUniform3f(color_ID,0.0f, 1.0f, 0.0f);
        //        glUniform1i(warped_image_ID, 1);
                
                glEnableVertexAttribArray(0);
                glBindBuffer(GL_ARRAY_BUFFER, new_vbo);
                glVertexAttribPointer(
                    0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                    4,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    0,                  // stride
                    (void*)0            // array buffer offset
                );
        //
                glLineWidth(0.25);
                glDrawArrays(GL_LINE_STRIP_ADJACENCY, 0, primitives_mesh);
                 
                
                // DISPLAY THE POINTS FOR NEW VBO
                
                glDisable(GL_RASTERIZER_DISCARD);
                
                
                glUseProgram(programRenderingID);
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
                glClear(GL_DEPTH_BUFFER_BIT);
//                    glViewport(0, 0, 2*width, 2*height);//MAC
                
                color_ID = glGetUniformLocation(programRenderingID, "color");
                glUniform3f(color_ID,0.8f, 0.0f, 0.7f);
                
                glEnableVertexAttribArray(0);
                glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
                glVertexAttribPointer(
                    0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                    4,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    0,                  // stride
                    (void*)0            // array buffer offset
                );
        //
                glPointSize(2.5);
                glDrawArrays(GL_POINTS, 0, primitives_points);
                
                
                glUseProgram(PlainProgramID);
                glBindFramebuffer(GL_FRAMEBUFFER, 0);

                glClearColor(0.0f,0.0f,0.0f,1.0f);
//                glViewport(0, height, width, height); // LEFT UP MAC
                glViewport(0, height/2, width/2, height/2); // LEFT UP

//                glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                
                glDisable(GL_CULL_FACE);
                //glDisable(GL_BLEND);

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, depth_map);
                og_image_ID = glGetUniformLocation(PlainProgramID, "original_image");
                glUniform1i(og_image_ID, 0);
                
                lodID = glGetUniformLocation(PlainProgramID, "lod");
                glUniform1i(lodID, 0);
                
                glEnableVertexAttribArray(0);
                
                glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
                glVertexAttribPointer(
                    0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                    4,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    0,                  // stride
                    (void*)0            // array buffer offset
                );

                glDrawArrays(GL_TRIANGLES, 0, grid_size * grid_size * 6);
                
                glUseProgram(PlainProgramID);
                glBindFramebuffer(GL_FRAMEBUFFER, 0);

                glClearColor(0.0f,0.0f,0.0f,1.0f);
//                glViewport(width, height, width, height); // RIGHT UP MAC
                glViewport(width/2, height/2, width/2, height/2); // RIGHT UP

//                glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                
                glDisable(GL_CULL_FACE);
                //glDisable(GL_BLEND);

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, disparity_visual_map);
                og_image_ID = glGetUniformLocation(PlainProgramID, "original_image");
                glUniform1i(og_image_ID, 0);
                
                lodID = glGetUniformLocation(PlainProgramID, "lod");
                glUniform1i(lodID, 0);
                
                glEnableVertexAttribArray(0);
                
                glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
                glVertexAttribPointer(
                    0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                    4,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    0,                  // stride
                    (void*)0            // array buffer offset
                );

                glDrawArrays(GL_TRIANGLES, 0, grid_size * grid_size * 6);
                
            };
                break;
            default:
                break;
        }
                 
        glDisableVertexAttribArray(3);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glDeleteBuffers(1, &tbo);
        glDeleteBuffers(1, &new_vbo1);
        glDeleteBuffers(1, &new_vbo);
        glDeleteBuffers(1, &points_vbo);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
    glDeleteBuffers(1, &texturecodebuffer);
    glDeleteBuffers(1, &FramebufferName);
    glDeleteBuffers(1, &quad_vertexbuffer);
    glDeleteBuffers(1, &vbo);
    
    glDeleteProgram(programTFID);
    glDeleteProgram(programDrawQuadID);
    glDeleteProgram(programRenderingID);
	glDeleteProgram(programID);
    glDeleteProgram(MaxPyrProgramID);
    glDeleteProgram(WarpingProgramID);
    glDeleteProgram(OGProgramID);
    glDeleteProgram(MinPyrProgramID);
    glDeleteProgram(PlainProgramID);
    
    
	glDeleteTextures(1, &Texture0);
    glDeleteTextures(1, &Texture1);
    glDeleteTextures(1, &Texture2);
    glDeleteTextures(1, &Texture3);
    glDeleteTextures(1, &Texture4);
    glDeleteTextures(1, &Texture5);
    glDeleteTextures(1, &Texture6);
    glDeleteTextures(1, &Texture7);
    glDeleteTextures(1, &Texture8);
    glDeleteTextures(1, &Texture9);
    glDeleteTextures(1, &Texture10);
    glDeleteTextures(1, &Texture11);
    glDeleteTextures(1, &Texture12);
    glDeleteTextures(1, &Texture13);
    glDeleteTextures(1, &Texture14);
    glDeleteTextures(1, &texID);
    glDeleteTextures(1, &disparity_map_ID);
    glDeleteTextures(1, &disparity_texture);
    glDeleteTextures(1, &disparity_texture_min);
    glDeleteTextures(1, &disparity_texture_max);
    glDeleteTextures(1, &disparity_visual_map);
    glDeleteTextures(1, &depth_map);
    glDeleteTextures(1, &warped_image);
    glDeleteTextures(1, &result_image);
    
    stbi_image_free(data0);
    stbi_image_free(data1);
    stbi_image_free(data2);
    stbi_image_free(data3);
    stbi_image_free(data4);
    stbi_image_free(data5);
    stbi_image_free(data6);
    stbi_image_free(data7);
    stbi_image_free(data8);
    stbi_image_free(data9);
    stbi_image_free(data10);
    stbi_image_free(data11);
    stbi_image_free(data12);
    stbi_image_free(data13);
    stbi_image_free(data14);


	glDeleteVertexArrays(1, &VertexArrayID);

	glfwTerminate();

	return 0;
}


