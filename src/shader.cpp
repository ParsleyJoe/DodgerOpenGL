#include <shader.hpp>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

const char* const defaultVertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos, 1.0);\n"
"}\n";

const char* const defaultFramentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n";

bool checkCompileErrors(unsigned int shader, std::string type)
{
	std::transform(type.begin(), type.end(), type.begin(),
		[](char c) { return std::toupper(c);} );

	bool result = true;

	if (type != "PROGRAM")
	{
		int success;
		char infoLog[512];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::" << type << "::COMPILATION_FAILED\n" << infoLog << std::endl;
			result = false;
		}
	}
	else if (type == "PROGRAM")
	{
		int success;
		char infoLog[512];
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::" << type << "::LINKING_FAILED\n" << infoLog << std::endl;
		}
	}

	return result;
}

void Shader::LoadShaderFromFile(const char* vertexPath, const char* fragmentPath)
{
	const char* vertexCode;
	const char* fragmentCode;
	std::ifstream vertexFile, fragmentFile;
	std::string vertexStr, fragmentStr;


	if (vertexPath == nullptr || fragmentPath == nullptr)
	{
		vertexCode = defaultVertexShaderSource;
		fragmentCode = defaultFramentShaderSource;
	}
	else
	{
		vertexFile.open(vertexPath);
		fragmentFile.open(fragmentPath);

		if (!vertexFile.is_open())
		{
			std::cout << "Failed to open VertexShader File: " << vertexPath << std::endl;
		}
		if (!fragmentFile.is_open())
		{
			std::cout << "Failed to open FragmentShader File: " << fragmentPath << std::endl;
		}

		std::stringstream vertexStream, fragmentStream;
		vertexStream << vertexFile.rdbuf();
		fragmentStream << fragmentFile.rdbuf();

		vertexStr = vertexStream.str();
		fragmentStr = fragmentStream.str();

		vertexCode = vertexStr.c_str();
		fragmentCode = fragmentStr.c_str();
	}

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexCode, NULL);
	glCompileShader(vertexShader);
	checkCompileErrors(vertexShader, "vertex");

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentCode, NULL);
	glCompileShader(fragmentShader);
	if (!checkCompileErrors(fragmentShader, "fragment"))
	{
		std::cout << "SHADER::FRAGMENT::STOPPING_SHADER_COMPILATION\n";
		return;
	}

	this->programID = glCreateProgram();
	glAttachShader(this->programID, vertexShader);
	glAttachShader(this->programID, fragmentShader);
	glLinkProgram(this->programID);
	checkCompileErrors(this->programID, "program");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Use()
{
	glUseProgram(this->programID);
}

void Shader::SetMatrix4(const char* name, glm::mat4& matrix)
{
	this->Use();
	glUniformMatrix4fv(glGetUniformLocation(this->programID, name), 1, false, glm::value_ptr(matrix));
}

void Shader::SetVector3f(const char* name, glm::vec3& vec)
{
	this->Use();
	glUniform3f(glGetUniformLocation(this->programID, name), vec.x, vec.y, vec.z);
}