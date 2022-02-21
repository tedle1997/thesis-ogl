#version 330 core
layout (location = 0) in vec2 aPos;
uniform mat4 View;
uniform mat4 Projection;
uniform mat4 Model;

void main()
{
    gl_Position =  vec4(aPos.x, aPos.y, 0.0, 1.0); 
}