#version 330 core
// Preprocess Geometry Shader
layout (points) in;
layout(points, max_vertices = 24) out;

uniform sampler2D maxTexture;
uniform sampler2D minTexture;

uniform int level_uniform;
uniform int num_level;
uniform int grid_size;
uniform int lod;

in vec4 v_value[];
out vec4 outValue;

float minmax_thresh = 0.5 * pow(0.1,lod);

void outputQuad(vec4 position){
    float offset = position.z;
    outValue = vec4(position.x - offset, position.y - offset, offset, 1.0);    // 1 top-left
    EmitVertex();
    EndPrimitive();
    outValue = vec4(position.x + offset, position.y - offset, offset, 1.0);    // 2 top-right
    EmitVertex();
    EndPrimitive();
    outValue = vec4(position.x + offset, position.y + offset, offset, 1.0);    // 3 bottom-right
    EmitVertex();
    EndPrimitive();
    outValue = vec4(position.x - offset, position.y + offset, offset, 1.0);    // 4 bottom-left
    EmitVertex();
    EndPrimitive();
    outValue = vec4(position.x - offset, position.y - offset, offset, 1.0);    // 5 top-left
    EmitVertex();
    EndPrimitive();
    outValue = vec4(position.x + offset, position.y + offset, offset, 1.0);    // 6 bottom-right
    EmitVertex();
    EndPrimitive();
}

void div4Vertex(vec4 position, float minmax_diff, float minmax_thresh){
    
    float offset = position.z * 0.5;
    float orignal_offset = position.z;
    
    if(minmax_diff >= minmax_thresh){
        if(num_level == level_uniform){
            outputQuad(vec4(position.x - offset, position.y - offset, offset, 1.0f));
            outputQuad(vec4(position.x - offset, position.y + offset , offset, 1.0f));
            outputQuad(vec4(position.x + offset, position.y - offset, offset, 1.0f));
            outputQuad(vec4(position.x + offset, position.y + offset, offset, 1.0f));
        } else {
            outValue = vec4(position.x - offset, position.y - offset, offset, 1.0f);
            EmitVertex();
            EndPrimitive();
            outValue = vec4(position.x - offset, position.y + offset , offset, 1.0f);
            EmitVertex();
            EndPrimitive();
            outValue = vec4(position.x + offset, position.y - offset, offset, 1.0f);
            EmitVertex();
            EndPrimitive();
            outValue = vec4(position.x + offset, position.y + offset, offset, 1.0f);
            EmitVertex();
            EndPrimitive();
        }
    }
    else {
        outValue = position;
        EmitVertex();
        EndPrimitive();
    }
}

void processVertex(vec4 position){
    
    float minmax_diff = abs(textureLod(maxTexture, (position.xy) * 0.5 + vec2(0.5,0.5), level_uniform).x
                            - textureLod(minTexture, (position.xy) * 0.5  + vec2(0.5,0.5), level_uniform).x);
    
    if(level_uniform < num_level){
        div4Vertex(position, minmax_diff, minmax_thresh);
    } else {
        outputQuad(position);
    }
}

void main(){
    processVertex(vec4(v_value[0][0], v_value[0][1], v_value[0][2], 1.0));
}
