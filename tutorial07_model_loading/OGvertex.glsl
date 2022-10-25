#version 330 core

layout (location = 0) in vec4 aPos;
out vec2 tex_coord;

uniform sampler2D original_image;

void main()
{
    tex_coord = aPos.xy * 0.5 + 0.5;
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    
}
