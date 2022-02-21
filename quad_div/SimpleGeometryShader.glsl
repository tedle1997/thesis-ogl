#version 330 core
layout (points) in;
layout (line_strip, max_vertices = 6) out;


void build_house(vec4 position)
{    
    float unit_width = 0.0625f;
    float unit_height = 0.0625f;

    //fColor = vec4(gs_in[0].color, 1.0f); // gs_in[0] since there's only one input vertex
    gl_Position = position + vec4(-unit_width,  unit_height, 0.0, 0.0);    // 1 top-left
    EmitVertex();
    gl_Position = position + vec4( unit_width,  unit_height, 0.0, 0.0);    // 2 top-right
    EmitVertex();
    gl_Position = position + vec4( unit_width, -unit_height, 0.0, 0.0);    // 3 bottom-right
    EmitVertex();
    gl_Position = position + vec4(-unit_width, -unit_height, 0.0, 0.0);    // 4 bottom-left   
    EmitVertex();   
    gl_Position = position + vec4(-unit_width,  unit_height, 0.0, 0.0);    // 5 top-left
    EmitVertex();
    gl_Position = position + vec4( unit_width, -unit_height, 0.0, 0.0);    // 6 bottom-right
    EmitVertex();
    EndPrimitive(); 
}

void main() {    
    build_house(gl_in[0].gl_Position);
} 