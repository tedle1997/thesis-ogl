#version 330 core
// Preprocess Geometry Shader
layout (points) in;
layout(points, max_vertices = 4) out;

uniform float inv_width;
uniform float inv_height;

in vec3 v_value[];
out vec3 outValue;
//in float in_size;

//TODO: Check how close is the center to the origin (0,0), if it's closer than height/2 then 1 quad becomes 4 quads
//TODO: Emit these 4 quads centers back into the vertex shader.

void processVertex(vec4 position){
    vec4 origin = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    //TODO: make this a uniform later
    float offset = position.z * 0.25f;
    if(distance(origin, position) <= 0.5){
        position.z = 0.0f;
//        point = position + vec4(-offset, -offset, 0.0, 0.0);
        outValue = vec3(position.x - offset, position.y - offset, offset);
        EmitVertex();
//        EndPrimitive();
//        point = position + vec4(-offset, offset, 0.0, 0.0);
        outValue = vec3(position.x - offset, position.y + offset, offset);
        EmitVertex();
//        EndPrimitive();
//        point = position + vec4(offset, -offset, 0.0, 0.0);
        outValue = vec3(position.x + offset, position.y - offset, offset);
        EmitVertex();
//        EndPrimitive();
//        point = position + vec4(offset, offset, 0.0, 0.0);
        outValue = vec3(position.x + offset, position.y + offset, offset);
        EmitVertex();
        EndPrimitive();
    } else {
        outValue = position.xyz;
        EmitVertex();
//        EndPrimitive();
//        outValue = position.xy;
//        EmitVertex();
////        EndPrimitive();
//        outValue = position.xy;
//        EmitVertex();
////        EndPrimitive();
//        outValue = position.xy;
//        EmitVertex();
        EndPrimitive();
    }
//    outValue = position.xyz;
//    EmitVertex();
//    EndPrimitive();
}

void main(){
    processVertex(vec4(v_value[0][0], v_value[0][1], v_value[0][2], 1.0f));
}
