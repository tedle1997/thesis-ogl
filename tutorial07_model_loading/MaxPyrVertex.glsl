#version 330 core
layout (location = 3) in vec3 aPos;
//layout (location = 1) in vec2 uv;
//uniform mat4 View;
//uniform mat4 Projection;
//uniform mat4 Model;
out vec2 UV;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    UV = (aPos.xy+vec2(1,1))/2.0;
}
