#version 330 core
layout (points) in;
layout (line_strip, max_vertices = 6) out;

void draw_quads(vec4 position)
{
    float offset = position.z;
//    position.z = 0.0f;

    //fColor = vec4(gs_in[0].color, 1.0f); // gs_in[0] since there's only one input vertex
    gl_Position = vec4(position.x - offset, position.y + offset, 0.0, 1.0);    // 1 top-left
    EmitVertex();
    gl_Position = vec4(position.x + offset, position.y + offset, 0.0, 1.0);    // 2 top-right
    EmitVertex();
    gl_Position = vec4(position.x + offset, position.y - offset, 0.0, 1.0);    // 3 bottom-right
    EmitVertex();
    gl_Position = vec4(position.x - offset, position.y - offset, 0.0, 1.0);    // 4 bottom-left
    EmitVertex();
    gl_Position = vec4(position.x - offset, position.y + offset, 0.0, 1.0);    // 5 top-left
    EmitVertex();
    gl_Position = vec4(position.x + offset, position.y - offset, 0.0, 1.0);    // 6 bottom-right
    EmitVertex();
    EndPrimitive();
}

void main() {
    draw_quads(gl_in[0].gl_Position);
} 
