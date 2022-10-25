#version 330 core

layout(location = 0) out vec3 FragColor;
uniform vec3 color;

void main()
{
//    FragColor = vec3(0.0, 1.0, 0.0);
    FragColor = color;
    
}
