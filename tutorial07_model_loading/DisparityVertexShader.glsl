#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in int t_code;


// Output data ; will be interpolated for each fragment.
flat out int texture_code;
out vec2 UV;
out vec3 depth_image;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main(){

    // Output position of the vertex, in clip space : MVP * position
    gl_Position =  MVP * vec4(vertexPosition_modelspace,1);
    
    vec4 new_position = ViewMatrix * ModelMatrix * vec4(vertexPosition_modelspace,1);
    new_position /= new_position.w;
    depth_image = vec3(new_position.z);
    depth_image = -1.0*(depth_image);
    UV = vertexUV;
    texture_code = t_code;
}
