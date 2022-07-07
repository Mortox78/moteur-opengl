#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "vec3.h"
#include "mat4.h"

#define MOUSE_SENSITIVITY 0.1f
#define CAM_ROT_SPEED 50.f
#define CAM_TRANS_SPEED 150.f

namespace LowRenderer
{
    class Camera
    {
        private:
            // The camera won't rotate at the first frame if the user try to move his mouse
            bool initialized = false;


            void manage_cam_translation(GLFWwindow* window, const float& deltaTime);
            void manage_cam_rotation(GLFWwindow* window, const float& deltaTime);


        public:
            Camera();
            ~Camera();

            Core::Maths::vec3 posCam;
            Core::Maths::vec3 rotCam;
            Core::Maths::mat4 matCam;
            Core::Maths::mat4 matPerspective;
            Core::Maths::mat4 matOrtho;

            void manage_cam(GLFWwindow* window, const float& deltaTime);
            Core::Maths::mat4 create_perspective_matrix(int width, int height, float near, float far, float fov);
            Core::Maths::mat4 create_ortho_matrix(const float& right, const float&  left, const float&  top, const float&  bottom, const float&  far, const float&  near);
    };
}