#include "includes/Shader.h"

///This function receives the path of all the shaders, compiles them and links
///them into 'this' shader program
Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
    /// 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;

    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    /// ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        /// open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;

        /// read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        /// close file handlers
        vShaderFile.close();
        fShaderFile.close();
        /// convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    /// 2. compile shaders
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    ///Create a vertex Shader Object
    vertex = glCreateShader(GL_VERTEX_SHADER);

    ///Populate the object with the shader code
    glShaderSource(vertex, 1, &vShaderCode, NULL);

    ///Compile the shader
    glCompileShader(vertex);

    /// print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (success)
    {
        std::cout << "Vertex Shader compiled successfully" << std::endl;
    }
    else
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog
            << std::endl;
    }

    ///Same process for fragment shader.
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

    if (success)
    {
        std::cout << "Fragment Shader compiled successfully" << std::endl;
    }
    else
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog
            << std::endl;
    }

    ///Once the shaders are compiled link them into a shader program

    ///Create a shader program and link them to 'this' ID
    ID = glCreateProgram();

    ///Link the shaders, to the shader program
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    /// print linking errors if any
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (success)
    {
        std::cout << "Shader Program of ID " << ID << " was linked successfully"
            << std::endl;
    }
    else
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    ///Once the linking is done, delete the shader objects, we don't need them
    ///anymore
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

///Use this function to set 'this' shader as the current
///OpenGL shader
void Shader::use()
{
    glUseProgram(ID);
}

////////////////////Sets - Uniforms (GLSL)//////////////////////////////////////

void Shader::setBool(const std::string& name, bool value)
{
    int uniformLocation = glGetUniformLocation(ID, name.c_str());

    if (uniformLocation != -1)
    {
        glUniform1i(uniformLocation, (int)value);
    }
    else
    {
        std::cout << "Couldn't find uniform " << name << " in Shader program " << ID
            << std::endl;
    }

}

void Shader::setInt(const std::string& name, int value)
{
    int uniformLocation = glGetUniformLocation(ID, name.c_str());

    if (uniformLocation != -1)
    {
        glUniform1i(uniformLocation, value);
    }
    else
    {
        std::cout << "Couldn't find uniform " << name << " in Shader program " << ID
            << std::endl;
    }

}

void Shader::setFloat(const std::string& name, float value)
{
    int uniformLocation = glGetUniformLocation(ID, name.c_str());

    if (uniformLocation != -1)
    {
        glUniform1f(uniformLocation, value);
    }
    else
    {
        std::cout << "Couldn't find uniform " << name << " in Shader program " << ID
            << std::endl;
    }

}

void Shader::setMatrix4x4(const std::string& name, glm::mat4 value)
{
    int uniformLocation = glGetUniformLocation(ID, name.c_str());

    if (uniformLocation != -1)
    {
        glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
    }
    else
    {
        std::cout << "Couldn't find uniform " << name << " in Shader program " << ID
            << std::endl;
    }
}

void Shader::setVector3(const std::string& name, glm::vec3 value)
{
    int uniformLocation = glGetUniformLocation(ID, name.c_str());

    if (uniformLocation != -1)
    {
        glUniform3fv(uniformLocation, 1, glm::value_ptr(value));
    }
    else
    {
        std::cout << "Couldn't find uniform " << name << " in Shader program " << ID
            << std::endl;
    }
    
}