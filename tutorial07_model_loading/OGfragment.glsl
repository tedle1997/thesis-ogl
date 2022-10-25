#version 330 core

layout(location = 0) out vec3 FragColor;
in vec2 tex_coord;
in vec2 original_pos;

uniform sampler2D original_image;
uniform sampler2D warped_image;

void main()
{
    FragColor = vec3(texture(original_image, tex_coord).r,texture(warped_image, tex_coord).g,texture(warped_image, tex_coord).b);
//    FragColor = texture(warped_image, tex_coord).rgb;
    
//    FragColor = textureLod(original_image, tex_coord, 7).rgb;
//    FragColor = texture(original_image, tex_coord).rgb;
}

