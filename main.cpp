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
//#include "includes/Shader.h"
#include "includes/Camera.h"
#include "includes/Model.h"
//GLFW
#include <GLFW/glfw3.h>

using namespace std;

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

    //Set the Directional light position, color and intensity
    shader.use();
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
    shader.setInt("objectMaterial.diffuseMap0", 0);
    shader.setInt("objectMaterial.specularMap0", 1);
    shader.setFloat("objectMaterial.shininess", 32.0f);

    //Load Models
    Model backpackmodel("models/backpack/backpack.obj");

    ///This is the render loop *While the window is open*
    while (!glfwWindowShouldClose(window))
    {
        ///Process user input
        ProcessInput(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ///Get time in between frames for camera transformations
        calcDeltaTime();
        
        shader.use();
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

        shader.use();
        glm::mat4 view = glm::mat4(1.0f);
        view = camera.GetViewMatrix();
        shader.setMatrix4x4("mx4View", view);

        glm::mat4 proj = glm::mat4(1.0f);
        proj = camera.GetProjectionMatrix();
        shader.setMatrix4x4("mx4Proj", proj);

        glm::mat4 model = glm::mat4(1.0f);
        shader.setMatrix4x4("mx4Model", model);

        backpackmodel.Draw(shader);

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
