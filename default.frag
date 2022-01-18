#version 330 core

// pa
out vec4 FragColor;

// vertex color from the vertex shader
in vec3 color;

// texture coordinates from the vertex shader
in vec2 texCoord;

// texture unit reference that is passed in the main class
uniform sampler2D tex0;


void main()
{
	FragColor = texture(tex0, texCoord);
}