#pragma once
#include <string>
#include <unordered_map>

#include "../vendor/glm/glm.hpp"

struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	std::string _filePath;
	
	std::unordered_map<std::string, int> _uniformLocationCache;

public:
	Shader(const std::string& filePath);
	~Shader();

	unsigned int _rendererID; // should be private

	void Bind() const;
	void Unbind() const;

	void SetUniform1i(const std::string name, int value);
	void SetUniform1iv(const std::string name, int value);
	void SetUniform1f(const std::string name, float value);
	void SetUniform4f(const std::string name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string name, const glm::mat4& matrix);

private:
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader,
		const std::string& fragmentShader);
	ShaderProgramSource ParseShader(const std::string& filepath);
	int GetUniformLocation(const std::string& name);

};






