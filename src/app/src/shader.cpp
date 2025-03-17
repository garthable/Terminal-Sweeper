#include "shader.hpp"
#include <fstream>
#include "log.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace sha
{

void readShaderScript(const char* fileName, std::string& output)
{
    std::ifstream in(fileName, std::ios::binary);
    if (!in)
    {
        throw std::runtime_error("Failed to open file!");
    }
    in.seekg(0, std::ios::end);
    output.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&output[0], output.size());
    in.close();
}

void compileErrors(uint32_t shader, const char* type)
{
	// Stores status of compilation
	GLint hasCompiled;
	// Character array to store error message in
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            LOG_ERROR("SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog);
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            LOG_ERROR("SHADER_LINKING_ERROR for:" << type << "\n" << infoLog);
		}
	}
}

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	// Read vertexFile and fragmentFile and store the strings
	std::string vertexCode;
    readShaderScript(vertexPath, vertexCode);
	std::string fragmentCode;
    readShaderScript(fragmentPath, fragmentCode);

	// Convert the shader source strings into character arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);
	// Checks if Shader compiled succesfully
	compileErrors(vertexShader, "VERTEX");

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(fragmentShader);
	// Checks if Shader compiled succesfully
	compileErrors(fragmentShader, "FRAGMENT");

	// Create Shader Program Object and get its reference
	m_Id = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(m_Id, vertexShader);
	glAttachShader(m_Id, fragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(m_Id);
	// Checks if Shaders linked succesfully
	compileErrors(m_Id, "PROGRAM");

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
	glDeleteProgram(m_Id);
}

void Shader::use()
{
    glUseProgram(m_Id);
}

}

