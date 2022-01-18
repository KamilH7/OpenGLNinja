#version 330 core

//position
layout (location = 0) in vec3 aPos;
//color
layout (location = 1) in vec3 aColor;
//texture coordinate
layout (location = 2) in vec2 aTex;

out vec3 currentPosition;
out vec3 color;
out vec2 texCoord;

//matrix data
uniform mat4 modelMatrix;
uniform mat4 camMatrix;

void main()
{
	//applies the model matrix to the current position
	currentPosition = vec3( modelMatrix * vec4(aPos,1.0f));

	// passes the vertex color data to the fragment shader
	color = aColor;

	// calculates and passes the vertex text cord data to the fragment shader;
	texCoord = mat2(0.0, -1.0, 1.0, 0.0) * aTex;

	// calculates and passes the position of the vertices
	gl_Position = camMatrix * vec4(currentPosition ,1.0);
}