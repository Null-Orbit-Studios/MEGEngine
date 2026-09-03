#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <sstream>

#include "MEGEngine/Common.hpp"
#include "MEGEngine/Core/Settings.hpp"



std::string get_file_contents(const char* filename);

class ENGINE_API Shader {
public:
	unsigned int ID();
	Shader(const char* vertexFile = (settings.graphics().shaderDirectory+"/defaultLit/defaultLit.vert").c_str(), const char* fragmentFile = (settings.graphics().shaderDirectory+"/defaultLit/defaultLit.frag").c_str());

	void activate();
	void del();

	template<typename T>
	void setUniform(const char* name, const T& value);

private:
	unsigned int _id;
	void compileErrors(unsigned int shader, const char* type);
};


#endif //SHADER_H
