#version 330 core
layout (location = 0) in vec4 aPos;
//in vec3 inValue;
out vec4 v_value;

void main()
{
//    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    v_value = aPos;
}
