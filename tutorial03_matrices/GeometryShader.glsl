
#version 330 core
layout(points) in;
layout(triangle_strip, max_vertices = 3) out;

in float[] geoValue;
out float outValue;

//TODO: Check how close is the center to the origin (0,0), if it's closer than height/2 then 1 quad becomes 4 quads
//TODO: Emit these 4 quads centers back into the vertex shader.
//
//void processVertex(vec4 position){
//    vec4 origin = vec4(0.0f);
//    //TODO: make this a uniform later
//    float offset = 0.125f * 0.25f;
//    if(distance(origin, position) <= 0.5){
//        gl_Position = position + vec4(-offset, -offset,0.0,1.0);
//        EmitVertex();
//        EndPrimitive();
//        gl_Position = position + vec4(-offset, offset,0.0,1.0);
//        EmitVertex();
//        EndPrimitive();
//        gl_Position = position + vec4(offset, -offset,0.0,1.0);
//        EmitVertex();
//        EndPrimitive();
//        gl_Position = position + vec4(offset, offset,0.0,1.0);
//        EmitVertex();
//        EndPrimitive();
//    }
//}

void main(){
    for (int i = 0; i < 3; i++) {
        outValue = geoValue[0] + i;
        EmitVertex();
    }
    EndPrimitive();
}
