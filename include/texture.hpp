#pragma once

class Texture2D
{
public:
	unsigned int ID;
	unsigned int width, height;
	unsigned int internalFormat; // format of texture object
	unsigned int imageFormat; // format of loaded image

	// texture config
	unsigned int wrap_s;
	unsigned int wrap_t;
	unsigned int filterMin;
	unsigned int filterMax;

	Texture2D();
	void Generate(unsigned int width, unsigned int height, unsigned char* data);

	void Bind() const;
};