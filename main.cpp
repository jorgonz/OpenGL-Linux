// C++ default I/O
#include <iostream>
//STB Image Loader 
#include "includes/stb_image.h"
//GLM
#include "includes/glm/glm.hpp"
#include "includes/glm/gtc/type_ptr.hpp"
#include "includes/glm/gtc/matrix_transform.hpp"
//OpenGL function loader
#include "includes/glad.h"
//Custom Classes
#include "includes/Shader.h"
#include "includes/Camera.h"
//GLFW
#include <GLFW/glfw3.h>

using namespace std;

/*
GLfloat vertices[] = {

    //Position            //Texture 
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
*/

/*
GLfloat vertices[] = {

    //Position           
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f, 
    -0.5f, -0.5f,  0.5f,

    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f, 
    -0.5f,  0.5f, -0.5f, 
};
*/

float verticesLightSource[] = {

    //Position            //Normal 
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

// camera
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

// Declare a camera
Camera camera(cameraPos, cameraFront, cameraUp);

// LightSource Position
glm::vec3 vc3LightSourcePos(1.0f, 0.0f, 1.0f);
glm::vec3 vc3LightSourceDir(-0.2f, -1.0f, -0.3f);

// Time between current and last frame
float deltaTime = 0.0f;
// TimeStamp of last Frame
float lastFrame = 0.0f;

// Flag for the current Scene
unsigned int currentSceneIndex = 0;
bool isEnterPressed = false;

void calcDeltaTime()
{
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

///This is the callback function for when the window gets resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    ///Just adjust the viewport to the new window size
    glViewport(0, 0, width, height);
}

///This is the function for Input
void ProcessInput(GLFWwindow* window)
{
    ///If the 'esc' key was pressed
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        ///Close the window
        glfwSetWindowShouldClose(window, true);
    }

    ////////////////////////////CAMERA CONTROLS////////////////////////////////////

    /////////////////////
    ///CAMERA POSITION////
    /////////////////////

    ///Move front and back
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.MoveCamera(FORWARD,deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.MoveCamera(BACKWARD,deltaTime);
    }

    ///Move left and right
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.MoveCamera(LEFT,deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.MoveCamera(RIGHT,deltaTime);
    }

    ///Move Up and Down
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        camera.MoveCamera(UP,deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        camera.MoveCamera(DOWN,deltaTime);
    }

///////////////////////////////////////////////////////////////////////////////

    ////////////////////
    //CAMERA ROTATION///
    ////////////////////

    ///Update new Yaw angle
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
       camera.MoveCamera(RIGHT_SPIN,deltaTime);
    }

    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        camera.MoveCamera(LEFT_SPIN,deltaTime);
    }

    ///Update new Pitch angle
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        camera.MoveCamera(UP_SPIN,deltaTime);
    }

    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {

        camera.MoveCamera(DOWN_SPIN,deltaTime);
    }

///////////////////////////////////////////////////////////////////////////////

    ////////////////////
    ///SCENE CONTROL////
    ////////////////////

    if(glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS && !isEnterPressed)
    {
        isEnterPressed = true;

        if(currentSceneIndex == 0)
        {
            currentSceneIndex = 1;
        }
        else if(currentSceneIndex == 1)
        {
            currentSceneIndex = 0;
        }
    }

    if(glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_RELEASE && isEnterPressed)
    {
        isEnterPressed = false;
    }

}

bool LoadTexture(string stextureNameWithFullPath, unsigned int& texture)
{
    //Load texture and store relevant info
    int width, height, nrChannels;
    unsigned char *data = stbi_load(stextureNameWithFullPath.c_str(), &width, &height, &nrChannels, 0);

    if(data == NULL)
    {
        cout << "LoadTexture: texture of name '" << stextureNameWithFullPath << "' didn't load" << endl;
        return false;
    }

    GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

    //Generate an OpenGL Texture Id
    //unsigned int texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //Populate Texture Id with data
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    //Free memory after you are done
    stbi_image_free(data);

    return true;
}

//Screen Resolution
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    ///Initialize GLFW
    if (glfwInit() == GLFW_TRUE)
    {
        cout << "GLFW initialized successfully" << endl;
    }
    else
    {
        cout << "Unable to initialize GLFW" << endl;
    }

    //Set GLFW version to 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    ///Create a window
    GLFWwindow* window = glfwCreateWindow(800, 600, "ModernOpenGL", NULL, NULL);
    if (window == NULL)
    {
        ///If it fails, end the program
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    ///Set the current context, the window we are currently working in.
    glfwMakeContextCurrent(window);

    ///Register 'framebuffer_size_callback' as the resize window callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "GLAD initialized successfully" << endl;
    }
    else
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    ///Set the initial viewport -- GL functions can only be called after GLAD has been loaded
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    ////////////////////////////COMPILE SHADERS///////////////////////////////////

    Shader shader("shaders/vertex.vert", "shaders/fragment.frag");
    Shader shaderLightSource("shaders/vertex.vert", "shaders/lightSource.frag");


    ///////////////////CREATION OF VAOs VBOs and EBOs//////////////////////////////

    //VAO-Vertex Array Object
    //VBO-Vertex Buffer Object
    //EBO-Element Buffer Object

    ///Generate VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    ///Generate VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    ///First Bind the VAO, so that all the configuration is saved in this VAO
    glBindVertexArray(VAO);

    ///Bind the VBO to GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    unsigned int DiffuseMapTextureId;
    LoadTexture("textures/container2.png", DiffuseMapTextureId);

    unsigned int SpecularMapTextureId;
    LoadTexture("textures/container2_specular.png", SpecularMapTextureId);

    ///Set the info of how the VBO must be read//

    //Populate the buffer with data
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Tell OpenGL how to read the Position data from the buffer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //Tell OpenGL how to read the Normal vertex data
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //Tell OpenGL how to read the texture vertex data
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //Setup VAO for the light source object
    unsigned int VBOLightSource;
    glGenBuffers(1, &VBOLightSource);
    unsigned int VAOLightSource;
    glGenVertexArrays(1, &VAOLightSource);
    glBindVertexArray(VAOLightSource);
    glBindBuffer(GL_ARRAY_BUFFER, VBOLightSource);
    glEnableVertexAttribArray(0);

    //Populate the buffer with data (position, color, texture coordinate)
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesLightSource), verticesLightSource, GL_STATIC_DRAW);

    //Tell OpenGL how to read the Position data from the buffer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //Tell OpenGL how to read the Normal vertex data
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    ///Draw in Wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    ///Draw in Fillmode, this is default.
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    //Enable Depth
    glEnable(GL_DEPTH_TEST);

    //Declare the ModelViewProjection Matrix for the vertex shader
    glm::mat4 modelviewproj = glm::mat4(1.0f);

    shader.use();
    
    //Set the Directional light position, color and intensity    
    shader.setVector3("directionalLights[0].direction", vc3LightSourceDir);
    shader.setVector3("directionalLights[0].ambientStrength", glm::vec3(0.1f, 0.1f, 0.1f));
    shader.setVector3("directionalLights[0].diffuseStrength", glm::vec3(0.25f, 0.25f, 0.25f));
    shader.setVector3("directionalLights[0].specularStrength", glm::vec3(0.5f, 0.5f, 0.5f));

    //Set the Point light position color, intensity and decay 
    shader.setVector3("pointLights[0].position", vc3LightSourcePos);
    shader.setVector3("pointLights[0].ambientStrength", glm::vec3(0.2f, 0.2f, 0.2f));
    shader.setVector3("pointLights[0].diffuseStrength", glm::vec3(0.5f, 0.5f, 0.5f));
    shader.setVector3("pointLights[0].specularStrength",glm::vec3(1.0f, 1.0f, 1.0f));
    shader.setFloat("pointLights[0].constantDecay", 1.0f);
    shader.setFloat("pointLights[0].linearDecay", 0.09f);
    shader.setFloat("pointLights[0].quadraticDecay", 0.032f);

    //Set the Spot light position, color, intensity, decay and cutoffAngle
    shader.setVector3("spotLights[0].ambientStrength", glm::vec3(0.1f, 0.1f, 0.1f));
    shader.setVector3("spotLights[0].diffuseStrength", glm::vec3(0.8f, 0.8f, 0.8f));
    shader.setVector3("spotLights[0].specularStrength",glm::vec3(1.0f, 1.0f, 1.0f));
    shader.setFloat("spotLights[0].constantDecay", 1.0f);
    shader.setFloat("spotLights[0].linearDecay", 0.09f);
    shader.setFloat("spotLights[0].quadraticDecay", 0.032f);
    shader.setFloat("spotLights[0].innerCutOffAngle", glm::cos(glm::radians(12.5f)));
    shader.setFloat("spotLights[0].outerCutOffAngle", glm::cos(glm::radians(17.5f)));

    //Set the cube object material
    shader.setInt("objectMaterial.ambientDiffuseMap", 0);
    shader.setInt("objectMaterial.specularMap", 1);
    shader.setFloat("objectMaterial.shininess", 32.0f);

    ///This is the render loop *While the window is open*
    while (!glfwWindowShouldClose(window))
    {
        ///Process user input
        ProcessInput(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ///Get time in between frames for camera transformations
        calcDeltaTime();
        
        shader.setVector3("vc3CameraPosition", camera.GetCameraPosition());

        ///Set background color
        if(currentSceneIndex == 0)
        {
            //Blue background color
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

            //Activate Directional and Point Lights
            shader.setInt("directionalLightsSize", 1);
            shader.setInt("pointLightsSize", 1);

            //Deactivate SpotLight
            shader.setInt("spotLightsSize", 0);
        }
        else if(currentSceneIndex == 1)
        {
            //Black background color
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

            //Activate SpotLight
            shader.setInt("spotLightsSize", 1);

            //Deactivate Directional and Point Lights
            shader.setInt("directionalLightsSize", 0);
            shader.setInt("pointLightsSize", 0);

            shader.setVector3("spotLights[0].position", camera.GetCameraPosition());
            shader.setVector3("spotLights[0].direction", camera.GetCameraFront());
        }

        //Draw Cube Container
        shader.use();
        glm::mat4 view = glm::mat4(1.0f);
        view = camera.GetViewMatrix();
        shader.setMatrix4x4("mx4View", view);

        glm::mat4 proj = glm::mat4(1.0f);
        proj = camera.GetProjectionMatrix();
        shader.setMatrix4x4("mx4Proj", proj);

        glm::mat4 model = glm::mat4(1.0f);
        //Rotate around the light source
        model = glm::translate(model, vc3LightSourcePos);
        model = glm::rotate(model, (float) glm::radians(glfwGetTime() * 60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::translate(model, -vc3LightSourcePos);
        //Rotate around its own axis
        model = glm::rotate(model, (float) glm::radians(glfwGetTime() * 60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        shader.setMatrix4x4("mx4Model", model);

        //Bind VAO for the Wood/Metal container, bind both the
        //Diffuse and Specular Map and Draw
        glBindVertexArray(VAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, DiffuseMapTextureId);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, SpecularMapTextureId);
        glDrawArrays(GL_TRIANGLES, 0 , 36);

        for(int i = 1; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader.setMatrix4x4("mx4Model", model);
            //Bind VAO for the Wood/Metal container, bind both the
            //Diffuse and Specular Map and Draw
            glBindVertexArray(VAO);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, DiffuseMapTextureId);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, SpecularMapTextureId);
            glDrawArrays(GL_TRIANGLES, 0 , 36);
        }

        //Draw Light Source
        if(currentSceneIndex == 0)
        {
            shaderLightSource.use();
            shaderLightSource.setMatrix4x4("mx4View", view);
            shaderLightSource.setMatrix4x4("mx4Proj", proj);
            glm::mat4 lightSourceModel = glm::mat4(1.0f);
            lightSourceModel = glm::translate(lightSourceModel, vc3LightSourcePos);
            lightSourceModel = glm::scale(lightSourceModel, glm::vec3(0.2f));
            shaderLightSource.setMatrix4x4("mx4Model", lightSourceModel);

            glBindVertexArray(VAOLightSource);
            glDrawArrays(GL_TRIANGLES, 0 , 36);
        }
        
        ///Swap the Front and Back buffer.
        glfwSwapBuffers(window);

        ///Poll CallBack Events
        glfwPollEvents();
    }

    ///Free resources when application ends.
    glfwTerminate();
    return 0;
}
