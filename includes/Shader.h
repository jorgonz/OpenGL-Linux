#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../includes/glad.h"
#include "../includes/glm/glm.hpp"
#include "../includes/glm/gtc/type_ptr.hpp"
#include "../includes/glm/gtc/matrix_transform.hpp"


class Shader
{
private:

    ///The ID of this Shader Program
    unsigned int ID;

public:

    ///Constructor
    Shader(const GLchar*, const GLchar*);

    ///Setters - *GLSL uniforms*
    void setBool(const std::string& name, bool value);
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);
    void setMatrix4x4(const std::string& name, glm::mat4 value);
    void setVector3(const std::string& name, glm::vec3 value);

    ///Use this function to set 'this' shader as the current
    ///OpenGL shader
    void use();

};
