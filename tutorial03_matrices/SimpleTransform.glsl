#version 330 core
// VERTEX SHADER

in float inValue;
out float geoValue;

// Input vertex data, different for all executions of this shader.
// layout(location = 0) in vec3 vertexPosition_modelspace;
//in float inValue;
//out float outValue;

// Values that stay constant for the whole mesh.
// uniform mat4 MVP;

void main(){

	// Output position of the vertex, in clip space : MVP * position
	// gl_Position =  vec4(vertexPosition_modelspace,1);
    // outValue = sqrt(inValue);
    geoValue = sqrt(inValue);

}

