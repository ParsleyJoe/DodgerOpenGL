#pragma once
#include <glm/glm.hpp>

class Shader
{
	int programID;

public:
	void LoadShaderFromFile(const char* vertexPath, const char* fragmentPath);
	void Use();
	void SetMatrix4(const char* name, glm::mat4& matrix);
	void SetVector3f(const char* name, glm::vec3& vec);
};