#include "Shader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Renderer.h"


Shader::Shader(const std::string& filePath)
	: _filePath(filePath), _rendererID(0)
{
    ShaderProgramSource shaderSource = ParseShader(filePath);
    _rendererID = CreateShader(shaderSource.VertexSource, shaderSource.FragmentSource);

}
Shader::~Shader() {
    glDeleteProgram(_rendererID);
}


void Shader::Bind() const
{
    glUseProgram(_rendererID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath) {
    std::cout << filepath << std::endl;;
    std::ifstream stream(filepath);

    enum class ShaderType {
        None = -1,
        Vertex = 0,
        Fragment = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::None;
    /**/
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::Vertex;
            }
            else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::Fragment;
            }
        }
        else {
            ss[(int)type] << line << '\n';
        }

    }
    return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* scr = source.c_str();
    glShaderSource(id, 1, &scr, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)_malloca(length * sizeof(char));

        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "failed to compile shader! " << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader,
    const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}

void Shader::SetUniform1i(const std::string name, int value) {
    glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform1iv(const std::string name, int value) {
    //auto loc = glGetUniformLocation(shader, );
}

void Shader::SetUniform1f(const std::string name, float value) {
    glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform4f(const std::string name, float v0, float v1, float v2, float v3)
{
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniformMat4f(const std::string name, const glm::mat4& matrix)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

int Shader::GetUniformLocation(const std::string& name)
{
    if (_uniformLocationCache.find(name) != _uniformLocationCache.end()) {
        return _uniformLocationCache[name];
    }
    int location = glGetUniformLocation(_rendererID, name.c_str());
    if (location == -1) {
        //std::cout << "uniform: " << name << " does not exist!" << std::endl;
    }
    else _uniformLocationCache[name] = location;
    return location;
}