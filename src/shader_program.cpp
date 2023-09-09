#include "shader_program.h"

void ShaderProgram::compileShader(unsigned int &shader, ShaderType type, const std::string& code) {
    const char* charCode = code.c_str();
    switch(type){
        case ShaderType::eVertex:
            shader = glCreateShader(GL_VERTEX_SHADER);
            break;
        case ShaderType::eFragment:
            shader = glCreateShader(GL_FRAGMENT_SHADER);
            break;
        case ShaderType::eGeometry:
            shader = glCreateShader(GL_GEOMETRY_SHADER);
            break;
    }
    glShaderSource(shader, 1, &charCode, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &mSuccess);
    if(!mSuccess) {
        glGetShaderInfoLog(shader, 512, NULL, mInfoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << mInfoLog << std::endl;
        std::cout << "TYPE=" << type << std::endl;
    }
}

void ShaderProgram::linkProgram() {
    glAttachShader(ID, mVertex);
    glAttachShader(ID, mFragment);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &mSuccess);
    if(!mSuccess){
        glGetProgramInfoLog(ID, 512, NULL, mInfoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << mInfoLog << std::endl;
    }
}

void ShaderProgram::addShaders(bool bGeometry){
    compileShader(mVertex, ShaderType::eVertex, mVertexCode);
    compileShader(mFragment, ShaderType::eFragment, mFragmentCode);
    if(bGeometry)
        compileShader(mGeometry, ShaderType::eGeometry, mGeometryCode);
    linkProgram();
    glDeleteShader(mVertex);
    glDeleteShader(mFragment);
    if(bGeometry)
        glDeleteShader(mGeometry);
}

ShaderProgram::ShaderProgram(const std::string& shaderCode, const std::string& fragmentCode) {
    ID = glCreateProgram();
    addShaders(false);
}

ShaderProgram::ShaderProgram(const std::string& shaderCode, const std::string& fragmentCode,
                             const std::string& geometryCode) {
    ID = glCreateProgram();
    addShaders(true);
}

ShaderProgram::~ShaderProgram(){
    glDeleteProgram(ID);
}

void ShaderProgram::use() const {
    glUseProgram(ID);
}

void ShaderProgram::setBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void ShaderProgram::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void ShaderProgram::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void ShaderProgram::setVector2f(const std::string& name, float x, float y) const {
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void ShaderProgram::setVector2f(const std::string& name, const glm::vec2& value) const {
    glUniform2f(glGetUniformLocation(ID, name.c_str()), value.x, value.y);
}

void ShaderProgram::setVector3f(const std::string& name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void ShaderProgram::setVector3f(const std::string& name, const glm::vec3& value) const {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
}

void ShaderProgram::setVector4f(const std::string& name, float x, float y, float z, float w) const {
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void ShaderProgram::setVector4f(const std::string& name, const glm::vec4& value) const {
    glUniform4f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z, value.w);
}

void ShaderProgram::setMat4(const std::string& name, glm::mat4 value) const{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}