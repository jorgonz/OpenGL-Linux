#include "includes/Camera.h"

Camera::Camera(glm::vec3 pos, glm::vec3 dir, glm::vec3 up)
{
    Position = pos;
    Up = up;
    Front = dir;

    type = PERSPECTIVE;

    fYaw = YAW;
    fPitch = PITCH;
    fZoom = FOV;

    MovementSpeed = SPEED;
    RotationSensitivity = ROTATION_SENSITIVTY;
    WorldUp = WORLD_UP;

    fNearClippingPlane = NEARCP;
    fFarClippingPlane = FARCP;

    fWidth = WIDTH;
    fHeight = HEIGHT;

    updateCameraVectors();
}

///Whenever the camera's position
///changes we must update the corresponding
///vectors
void Camera::updateCameraVectors()
{
    ///Calculate the new Front vector
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(fYaw)) * cos(glm::radians(fPitch));
    newFront.y = sin(glm::radians(fPitch));
    newFront.z = sin(glm::radians(fYaw)) * cos(glm::radians(fPitch));

    Front = normalize(newFront);

    ///Also re-calculate the Right and Up vector
    Right = normalize(cross(Front, WorldUp));
    Up    = normalize(cross(Right, Front));

    Target = Position + Front;
    
}

void Camera::MoveCamera(Camera_Movement direction, float deltaTime)
{
    float fCameraSpeed = MovementSpeed * deltaTime;
    float fCameraRotationSpeed = fCameraSpeed * RotationSensitivity;

    switch(direction)
    {
        case FORWARD:
            Position += Front * fCameraSpeed;
            break;
        case BACKWARD:
            Position -= Front * fCameraSpeed;    
            break;
        case LEFT:
            Position -= Right * fCameraSpeed;
            break;
        case RIGHT:
            Position += Right * fCameraSpeed;
            break;
        case UP:
            Position += WorldUp * fCameraSpeed;
            break;
        case DOWN:
            Position -= WorldUp * fCameraSpeed;
            break;
        case LEFT_SPIN:
            fYaw -= fCameraRotationSpeed;
            updateCameraVectors();
            break;
        case RIGHT_SPIN:
            fYaw += fCameraRotationSpeed;
            updateCameraVectors();
            break;
        case UP_SPIN:
            fPitch += fCameraRotationSpeed;
            updateCameraVectors();
            break;
        case DOWN_SPIN:
            fPitch -= fCameraRotationSpeed;
            updateCameraVectors();
            break;
    }
}

///This function returns the corresponding lookAt
///matrix for the shader pipeline
glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(Position, Position + Front, Up);
}

///This function returns the corresponding Projection
///matrix of this camera for the vertex shader
glm::mat4 Camera::GetProjectionMatrix()
{
    if(type == PERSPECTIVE)
    {
       return glm::perspective(glm::radians(FOV), (float)fWidth/(float)fHeight,
                          fNearClippingPlane, fFarClippingPlane);
    }
    else if(type == ORTHOGRAPHIC)
    {
        return glm::ortho(0.0f, fWidth, 0.0f, fHeight, fNearClippingPlane,
              fFarClippingPlane);
    }

    return glm::mat4();
}