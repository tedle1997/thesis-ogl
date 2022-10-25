#version 330 core

layout(location = 0) out vec3 FragColor;
in vec2 tex_coord;
in vec2 original_pos;

uniform sampler2D original_image;
uniform int lod;

void main()
{
    FragColor = textureLod(original_image, tex_coord, lod).rgb;
}
