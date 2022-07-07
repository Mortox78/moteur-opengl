#include <iostream>
#include <math.h>

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "Engine.hpp"
#include "Camera.hpp"
#include "mat.h"
#include "mat4.h"

using namespace LowRenderer;

Camera::Camera()
{
    posCam          = {0, 0, 0};
    rotCam          = {0, 0, 0};
    matCam          = Core::Maths::mat4::identity(4);
    matPerspective  = create_perspective_matrix(SCREEN_WIDTH, SCREEN_HEIGHT, 0.1, 100, 45);
    float aspect    = SCREEN_HEIGHT / SCREEN_WIDTH;
    matOrtho        = create_ortho_matrix(-1, 1, -aspect, aspect, 0.01, 100);
}

Camera::~Camera()
{

}

void Camera::manage_cam(GLFWwindow* window, const float& deltaTime)
{
    manage_cam_rotation(window, deltaTime);
    manage_cam_translation(window, deltaTime);

    // Change the camera's transformation matrix
    matCam = Core::Maths::mat4::CreateTRSMatrix({1.f, 1.f, 1.f}, rotCam, posCam);
    matCam = matCam.getReverseMatrix();
    glfwSetCursorPos(window, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}


void Camera::manage_cam_translation(GLFWwindow* window, const float& deltaTime)
{
    float forward = 0, strafe = 0, fly = 0, speed = deltaTime * CAM_TRANS_SPEED;

    // input
    if (glfwGetKey(window, GLFW_KEY_W))
        forward   += -0.025 * speed;
    if (glfwGetKey(window, GLFW_KEY_S))
        forward   += 0.025  * speed;
    if (glfwGetKey(window, GLFW_KEY_A))
        strafe    += -0.025 * speed;
    if (glfwGetKey(window, GLFW_KEY_D))
        strafe    += 0.025  * speed;
    if (glfwGetKey(window, GLFW_KEY_SPACE))
        fly       += 0.025  * speed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL))
        fly       += -0.025  * speed; 


    // change pos of camera
    double rotAngleY = (rotCam.y * M_PI) / 180.f;

    posCam.x += forward * sin(rotAngleY);
    posCam.z += forward * cos(rotAngleY);
    posCam.x += strafe  * cos(rotAngleY);
    posCam.z += strafe  * -sin(rotAngleY);
    posCam.y += fly;
}

void Camera::manage_cam_rotation(GLFWwindow* window, const float& deltaTime)
{
    if (!initialized)
    {
        initialized = true;
        return;
    }
    double xPos, yPos;

    glfwGetCursorPos(window, &xPos, &yPos);
    float speed = deltaTime * CAM_ROT_SPEED * MOUSE_SENSITIVITY;

    float yaw     = speed * ((SCREEN_WIDTH  / 2) - xPos);
    float pitch   = speed * ((SCREEN_HEIGHT / 2) - yPos);
    
    rotCam.x += pitch;
    rotCam.y += yaw;
    
    // limit vertical rotation
    if (rotCam.x > 89.f)
        rotCam.x = 89.f;
    else if (rotCam.x < -89.f)
        rotCam.x = -89.f;
}

Core::Maths::mat4 Camera::create_perspective_matrix(int width, int height, float near, float far, float fov)
{
    Core::Maths::mat4 matPerspective;

	float xmax, ymax, zmax;
	float aspect = (float)width/(float)height;
	ymax  = tanf((fov * M_PI) / 180.f);
	xmax  = ymax * aspect;
	zmax  = (far - near);

	matPerspective.accessor(0, 0) = xmax == 0 ? 1 : 1.f/xmax;
	matPerspective.accessor(1, 1) = ymax == 0 ? 1 : 1.f/ymax;
	matPerspective.accessor(2, 2) = zmax == 0 ? 1 : -((far + near) /zmax);
	matPerspective.accessor(2, 3) = zmax == 0 ? -((2.f * far) / zmax) : -((2.f * near * far) / zmax);
	matPerspective.accessor(3, 2) = -1.f;
	matPerspective.accessor(3, 3) = 0;

	return matPerspective;
}

Core::Maths::mat4 Camera::create_ortho_matrix(const float& right, const float&  left, const float&  top, const float&  bottom, const float&  far, const float&  near)
{
    Core::Maths::mat4 matOrtho = Core::Maths::mat4::identity(4);

	if (right - left != 0)
	{
		matOrtho.accessor(0, 0) = -2/(right - left);
		matOrtho.accessor(0, 3) = (right + left)/(right - left);
		matOrtho.accessor(0, 3) *= -1;
	}
	if (top - bottom != 0)
	{
		matOrtho.accessor(1, 1) = -2/(top - bottom);
		matOrtho.accessor(1, 3) = (top + bottom)/(top - bottom);
		matOrtho.accessor(1, 3) *= -1;
	}
	if (far - near != 0)
	{
		matOrtho.accessor(2, 2) = 2/(far - near);
		matOrtho.accessor(2, 3) = (far + near)/(far - near);
	}

	return matOrtho;
}