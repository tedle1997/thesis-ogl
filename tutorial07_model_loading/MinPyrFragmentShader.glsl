#version 330 core

#define PI 3.1415926538

uniform sampler2D textureSampler;
uniform int level;

in vec2 UV;
out vec3 color;

void main()
{
   
    vec2 pixelSize = vec2(1.0)/textureSize(textureSampler, level-1);
    
    int kernel = 2;

    color = vec3(0.0);
    float min_val = 1.0;

    for(int i = -kernel; i<=kernel; i++){
        for(int j = -kernel; j<=kernel; j++){
            vec4 rgb_level = textureLod(textureSampler,UV + vec2(i,j) * pixelSize, level-1);
            min_val = min(min_val,rgb_level);
        }
    }
    color = vec3(min_val);
}

