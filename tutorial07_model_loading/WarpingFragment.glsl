#version 330 core

layout(location = 0) out vec4 FragColor;
in vec2 tex_coord;
in vec4 original_pos_color;
in float disp;

uniform sampler2D original_image;

void main()
{
    FragColor = vec4(texture(original_image, tex_coord).rgb,1.0);
    //FragColor = vec3(0.5);
}

