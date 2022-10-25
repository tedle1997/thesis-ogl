#version 330 core

uniform sampler2D textureSampler;
uniform sampler2D textureSamplerMax;
uniform sampler2D textureSamplerMin;
uniform sampler2D textureSamplerMap;

uniform int level;
uniform int kernel_size;

in vec2 UV;

//layout(location = 0) out vec3 disparity_texture;
layout(location = 1) out vec3 color_max;
layout(location = 2) out vec3 color_min;
//layout(location = 3) out vec3 disparity_map;


void main()
{
   
    vec2 pixelSize = vec2(1.0)/textureSize(textureSampler, level);
    
    int kernel = kernel_size;

    color_max = vec3(-1000.0);
    color_min = vec3(1000.0);

    for(int i = -kernel; i<=kernel; i++){
        for(int j = -kernel; j<=kernel; j++){
            vec4 rgb_level_max = textureLod(textureSamplerMax,UV + vec2(i,j) * pixelSize, level-1);
            vec4 rgb_level_min = textureLod(textureSamplerMin,UV + vec2(i,j) * pixelSize, level-1);
            color_max = vec3(max(color_max.x,rgb_level_max.x));
            color_min = vec3(min(color_min.x,rgb_level_min.x));
        }
    }
//    color = textureLod(textureSampler,UV, 0).xyz;
//    disparity_texture = texture(textureSampler, UV).rgb;
//    disparity_map = texture(textureSamplerMap, UV).rgb;
}
