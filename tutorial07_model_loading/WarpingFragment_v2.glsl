#version 330 core

layout(location = 0) out vec3 FragColor;
in vec2 out_tex_coord;
in vec4 original_pos_color;

uniform sampler2D original_image;

void main()
{
    FragColor = texture(original_image, out_tex_coord).rgb;
}

