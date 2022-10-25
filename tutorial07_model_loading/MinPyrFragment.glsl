#version 330 core

uniform sampler2D textureSampler;
uniform int level;

in vec2 UV;

layout(location = 0) out vec3 color_min;


void main()
{
    vec2 pixelSize = vec2(1.0)/textureSize(textureSampler, level-1);
    
    int kernel = 2;

    color_min = vec3(1.0);

    for(int i = -kernel; i<=kernel; i++){
        for(int j = -kernel; j<=kernel; j++){
            vec4 disparity_min = textureLod(textureSampler,UV + vec2(i,j) * pixelSize, level-1);
            color_min = vec3(min(color_min.x,disparity_min.x));
        }
    }
}
