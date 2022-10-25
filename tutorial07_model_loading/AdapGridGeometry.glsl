#version 330 core
layout (points) in;
layout (line_strip, max_vertices = 6) out;

in vec4 v_value[];
out vec4 outValue;

void draw_quads(vec4 position)
{
    float offset = position.z;
    outValue = vec4(position.x - offset, position.y + offset, 1.0, 1.0);    // 1 top-left
    EmitVertex();
    outValue = vec4(position.x + offset, position.y + offset, 1.0, 1.0);    // 2 top-right
    EmitVertex();
    outValue = vec4(position.x + offset, position.y - offset, 1.0, 1.0);    // 3 bottom-right
    EmitVertex();
    outValue = vec4(position.x - offset, position.y - offset, 1.0, 1.0);    // 4 bottom-left
    EmitVertex();
    outValue = vec4(position.x - offset, position.y + offset, 1.0, 1.0);    // 5 top-left
    EmitVertex();
    outValue = vec4(position.x + offset, position.y - offset, 1.0, 1.0);    // 6 bottom-right
    EmitVertex();
    EndPrimitive();
}

void main() {
    draw_quads(vec4(v_value[0][0], v_value[0][1], v_value[0][2], 1.0f));
} 
