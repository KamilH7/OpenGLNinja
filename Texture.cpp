#include"Texture.h"

// Constructor for the Texture class. 
// It takes image file path as an input, from which it creates a texture object and saves it to the designated texture unit

Texture::Texture(const char* imagePath, GLenum texType, GLenum textureUnit, GLenum format, GLenum pixelType)
{
	// Initialize texture type variable
	type = texType;

	// Create the variables into which stbi_load() function will save the image info
	int widthImg, heightImg, numColCh;
	// unlike GL, STB reads the texture from the topleft corner to the bottom right corner so it has to be flipped vertically
	stbi_set_flip_vertically_on_load(true);
	// Tells STB to read the image file and save its contents as bytes, it also initializes previously created variables with data
	unsigned char* bytes = stbi_load(imagePath, &widthImg, &heightImg, &numColCh, 0);

	// Generate a texture object
	glGenTextures(1, &ID);
	// Tell GL which texture unit we're working with
	glActiveTexture(textureUnit);
	
	Bind();

	//GL_NEAREST, GL_LINEAR
	// Settings for scaling the texture down
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// Settings for scaling the texture up
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER
	// Settings for filling the texture vertically
	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	// Settings for filling the texture horizontally
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Assign all the data to the gl texture object
	glTexImage2D(type, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
	// Generate MipMaps which are smaller resolution version of the image, used when texture is far away
	glGenerateMipmap(type);
	// Tell stb to get rid of the image data
	stbi_image_free(bytes);

	Unbind();
}

void Texture::texUnit(ShaderProgram& shader, const char* uniform, GLuint unit)
{
	// Gets the location of the uniform
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	// Shader needs to be activated before changing the value of a uniform
	shader.Activate();
	// Sets the value of the uniform
	glUniform1i(texUni, unit);
}

void Texture::Bind()
{
	glBindTexture(type, ID);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}