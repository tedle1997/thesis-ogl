#version 330 core

layout (location = 0) in vec4 aPos;
//layout (location = 0) in vec3 aPos;
out vec2 tex_coord;
out vec4 original_pos_color;

uniform sampler2D original_image;
uniform sampler2D disparity_map;

void main()
{
    tex_coord = aPos.xy * 0.5 + vec2(0.5, 0.5);
    float disparity  = texture(disparity_map, tex_coord).x;
//    original_pos_color = texture(original_image, tex_coord);
    gl_Position = vec4(aPos.x + disparity, aPos.y, aPos.z, 1.0);
    
//    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    
}
