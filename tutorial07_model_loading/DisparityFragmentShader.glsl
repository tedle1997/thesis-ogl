#version 330 core

flat in int texture_code;

// Interpolated values from the vertex shaders
in vec2 UV;
in vec3 depth_image;

layout(location = 0) out vec3 color;
layout(location = 1) out vec3 color_max;
layout(location = 2) out vec3 color_min;
layout(location = 3) out vec3 disparity_map;
layout(location = 4) out vec3 depth_map;
layout(location = 5) out vec3 disp_visual;
//out vec3 color;

// Values that stay constant for the whole mesh.
//uniform sampler2D myTextureSampler;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform sampler2D texture4;
uniform sampler2D texture5;
uniform sampler2D texture6;
uniform sampler2D texture7;
uniform sampler2D texture8;
uniform sampler2D texture9;
uniform sampler2D texture10;
uniform sampler2D texture11;
uniform sampler2D texture12;
uniform sampler2D texture13;
uniform sampler2D texture14;

void main(){

    // Output color = color of the texture at the specified UV
    //color = texture( myTextureSampler, UV ).rgb;
    // color = vec3(1.0f, 1.0f, 1.0f);
    switch (texture_code) {
        case -2:
            color = vec3(1.0);
            break;
        case -1:
            color = vec3(0.6);
            break;
        case 0:
            color = texture(texture0, UV ).rgb;
            break;
        case 1:
            color = texture(texture1, UV ).rgb;
            break;
        case 2:
            color = texture(texture2, UV ).rgb;
            break;
        case 3:
            color = texture(texture3, UV ).rgb;
            break;
        case 4:
            color = texture(texture4, UV ).rgb;
            break;
        case 5:
            color = texture(texture5, UV ).rgb;
            break;
        case 6:
            color = texture(texture6, UV ).rgb;
            break;
        case 7:
            color = texture(texture7, UV ).rgb;
            break;
        case 8:
            color = texture(texture8, UV ).rgb;
            break;
        case 9:
            color = texture(texture9, UV ).rgb;
            break;
        case 10:
            color = texture(texture10, UV ).rgb;
            break;
        case 11:
            color = texture(texture11, UV ).rgb;
            break;
        case 12:
            color = texture(texture12, UV ).rgb;
            break;
        case 13:
            color = texture(texture13, UV ).rgb;
            break;
        case 14:
            color = texture(texture14, UV ).rgb;
            break;

    }
//    depth_image = depth_image/depth_image.w
    float IPD = 0.065;
    float IPD_scale = 0.5;
    float screen_width = 0.4;
    float focal = 0.5;
    
    float separation = IPD/screen_width * IPD_scale;
    
    float disparity = separation * (1-(focal/depth_image.x));

//    vec3 color_disparity = vec3(0.0);
////    if(disparity > IPD * IPD_scale) disparity = IPD * IPD_scale;
////    if(disparity < -IPD * IPD_scale) disparity = -IPD * IPD_scale;
//    color_disparity.r = max(-disparity * 20, 0.0) * 10;
//    color_disparity.g = max(disparity * 20, 0.0) * 10;
//
//    color.rg = vec2(color_disparity);
//    disparity_map = vec3(depth_image.x * 0.1);
//    disparity_map = color;
    
    disparity_map = vec3(disparity);
    color_max = vec3(disparity * 25);
    color_min = vec3(disparity * 25);
    depth_map = vec3(depth_image.x * 0.1);
    
    vec3 color_disparity = vec3(0.0);
    float disparity_1 = separation * (1-(focal/(0.15*depth_image.x)));
    vec3 color_temp = color;
    color_disparity.r = max(-disparity_1, 0.0) * 20;
    color_disparity.g = max(disparity_1, 0.0) * 20;
    color_temp.rg = vec2(color_disparity);
    disp_visual.rg = vec2(color_disparity);
    
}
