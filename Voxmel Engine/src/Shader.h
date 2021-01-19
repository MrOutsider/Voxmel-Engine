#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	void create(const char* vertexPath, const char* fragmentPath);
	// Use/Activate the shader
	void use();
	void destroy();
	// Utility uniform functions
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;

private:
	// The program ID
	uint32_t ID;
};

#endif // !SHADER_H