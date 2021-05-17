#include <iostream>

#include "../includes/glad.h"
#include "../includes/glm/glm.hpp"
#include "../includes/glm/gtc/type_ptr.hpp"
#include "../includes/glm/gtc/matrix_transform.hpp"

enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN,
    LEFT_SPIN,
    RIGHT_SPIN,
    UP_SPIN,
    DOWN_SPIN
};

enum Camera_Type
{
    ORTHOGRAPHIC,
    PERSPECTIVE
};

const float YAW                 = 270.0f;
const float PITCH               = 0.0f;
const float SPEED               = 2.5f;
const float ROTATION_SENSITIVTY = 20.0f;
const float FOV                 = 45.0f;
const float NEARCP              = 0.1f;
const float FARCP               = 100.0f;
const float WIDTH               = 800.0f;
const float HEIGHT              = 600.0f;
const glm::vec3 WORLD_UP        = glm::vec3(0.0f,1.0f,0.0f);

class Camera
{
    private:

        /// Camera Attributes
        glm::vec3 Position;
        glm::vec3 Front;
        glm::vec3 Up;
        glm::vec3 Right;
        glm::vec3 WorldUp;
        glm::vec3 Target;

        ///Field of vision
        float fZoom;

        ///Camera Settings
        Camera_Type type;
        float fNearClippingPlane;
        float fFarClippingPlane;
        float fWidth;
        float fHeight;

        ///Angles
        float fYaw;
        float fPitch;

        ///Movement and Rotation Speed
        float MovementSpeed;
        float RotationSensitivity;

        ///Private Functions
        void updateCameraVectors();

    public:

        ///Constructor
        Camera(glm::vec3 pos, glm::vec3 dir, glm::vec3 up);

        ///Public Functions
        glm::vec3 GetCameraPosition();
        glm::vec3 GetCameraFront();
        glm::mat4 GetViewMatrix();
        glm::mat4 GetProjectionMatrix();

        ///Function to get keyboard input and move the camera
        void MoveCamera(Camera_Movement direction, float deltaTime);


};


