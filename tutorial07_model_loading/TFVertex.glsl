#version 330 core
// Preprocess Vertex Shader
layout (location = 0) in vec4 aPos;
//in float in_size;
//out float g_size;
in vec4 inValue;
out vec4 v_value;

void main(){
//    gl_Position = vec4(inValue[0], inValue[1], 0.0f, 1.0f);
//    g_size = in_size;
    v_value = aPos;
}
