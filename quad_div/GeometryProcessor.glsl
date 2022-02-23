#version 330 core
// Preprocess Geometry Shader
layout (points) in;
layout(points, max_vertices = 2) out;

in vec2 v_value[];
out vec2 outValue;
//in float in_size;

//TODO: Check how close is the center to the origin (0,0), if it's closer than height/2 then 1 quad becomes 4 quads
//TODO: Emit these 4 quads centers back into the vertex shader.

void processVertex(vec4 position){
    vec4 point = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    vec4 origin = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    //TODO: make this a uniform later
    float offset = 0.125f * 0.25f;
    if(distance(origin, position) <= 0.1){
        point = position + vec4(-offset, -offset, 0.0, 1.0);
        outValue = point.xy;
        EmitVertex();
        EndPrimitive();
        point = position + vec4(-offset, offset, 0.0, 1.0);
        outValue = point.xy;
        EmitVertex();
        EndPrimitive();
        point = position + vec4(offset, -offset, 0.0, 1.0);
        outValue = point.xy;
        EmitVertex();
        EndPrimitive();
        point = position + vec4(offset, offset, 0.0, 1.0);
        outValue = point.xy;
        EmitVertex();
        EndPrimitive();
    } else {
        outValue = position.xy;
        EmitVertex();
        EndPrimitive();
        outValue = position.xy;
        EmitVertex();
        EndPrimitive();
        outValue = position.xy;
        EmitVertex();
        EndPrimitive();
        outValue = position.xy;
        EmitVertex();
        EndPrimitive();
    }
}

void main(){
    processVertex(vec4(v_value[0][0], v_value[0][1], 0.0f, 1.0f));
}
