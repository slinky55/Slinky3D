/*
    MIT License

    Copyright (c) 2022 slinky55

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include <iostream>
#include <cstdint>
#include <array>
#include <random>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../common/Shader.hpp"
#include "../common/Camera.hpp"
#include "../common/CubeMesh.hpp"

// Not currently using textures
//#define STB_IMAGE_IMPLEMENTATION
//#include "../common/stb_image.h"

#include <Slinky/Particle/PWorld.hpp> // Slinky

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
constexpr uint32_t W_WIDTH { 800 };
constexpr uint32_t W_HEIGHT { 600 };

// camera
Camera camera { glm::vec3(0.0f, 5.f, 50.f) };
float lastX {W_WIDTH / 2.0f };
float lastY {W_HEIGHT / 2.0f };
bool firstMouse { true };

// timing
float deltaTime { 0.0f };	// time between current frame and last frame
float lastFrame { 0.0f };

int main()
{
    // random number generator
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(-5.f, 5.f);

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(W_WIDTH,
                                          W_HEIGHT,
                                          "Examples - Particles",
                                          nullptr,
                                          nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window,
                                   framebuffer_size_callback);
    glfwSetCursorPosCallback(window,
                             mouse_callback);
    glfwSetScrollCallback(window,
                          scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window,
                     GLFW_CURSOR,
                     GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader program
    // ------------------------------------
    Shader ourShader { "../examples/Particles/cube.vert",
                       "../examples/Particles/cube.frag" };

    CubeMesh mesh;

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use();

    // Physics stuff
    Slinky::PWorld world { {0.f, -3.f, 0.f} };

    auto const* currentParticle { world.CreateParticle({
        {0.f, 0.f, 0.f},
        25.f,
        0.1f,
        0.3f,
        0.9f
    })};

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        auto currentFrame { static_cast<float>(glfwGetTime()) };
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Destroy particles over 10 seconds old
/*        if (glfwGetTime() >= 10.f)
        {
            world.DestroyParticle(currentParticle);
            currentParticle = world.Particles().front().get();
        }*/

        for (std::size_t i { 0 }; i < 10; ++i)
        {
            auto particle { world.CreateParticle({
                 {0.f, 0.f, 0.f},
                 25.f,
                 0.1f,
                 0.3f,
                 0.9f
            })};
            particle->velocity = { dist(rd), dist(rd), dist(rd) };
        }

        world.Step(deltaTime);

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // activate shader
        ourShader.use();

        // projection matrix
        glm::mat4 projection {glm::perspective(
            glm::radians(camera.Zoom),
            (float)W_WIDTH / (float)W_HEIGHT,
            0.1f, 100.0f
        )};
        ourShader.setMat4("projection",
                          projection);

        // camera/view transformation
        glm::mat4 view { camera.GetViewMatrix() };
        ourShader.setMat4("view", view);

        for (auto const& particle : world.Particles())
        {
            // Model matrix
            glm::mat4 model { glm::mat4{1.0f} };
            model = glm::translate(model, {
                particle->position.x,
                particle->position.y,
                particle->position.z
            });
            model = glm::scale(model, glm::vec3{0.1f});

            ourShader.setMat4("model", model);

            // render cube
            glBindVertexArray(mesh.VAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    using enum CameraDir;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow*, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow*, double xposIn, double yposIn)
{
    float xpos { static_cast<float>(xposIn) };
    float ypos { static_cast<float>(yposIn) };

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset { xpos - lastX };
    float yoffset { lastY - ypos }; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow*, double, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

