// HEADERS
#include <stdio.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "Window.hpp"
#include "Shaders.hpp"

// CLASS CONSTRUCTOR
BasicWindow::BasicWindow(GLint width, GLint height) {
    set_Window_Size(width, height);
}

// FUNCTIONS

void BasicWindow::set_Window_Size(GLint width, GLint height) {
    WIDTH = width; 
    HEIGHT = height;
}

int BasicWindow::display() {
    // INITIALIZE GLFW

    if (!glfwInit()) { 
        // Initialization fails
        printf("GLFW Initialization Failure\nPerhaps the headers are wrong for this Operating System.\nMake sure to include GLEW and GLFW correctly, accordingly.\n");
        glfwTerminate();
        return 1;
    }
    // SETUP GLFW WINDOW PROPERTIES

    // Set OpenGL version used
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Core profile implies no backwards compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // However, we allow for forward compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // Pointer to test window 
    // (Recall: Pointers store the memory address of some variable, which can be redefined to that of another variable.)
    GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);
    // Verify window creation
    if (!mainWindow) {
        printf("GLFW Window Creation Failure\nCheck OpenGL version and make sure it is declared with correct compatibility to GLFW.\n");
        glfwTerminate();
        return 1;
    }

    // GET BUFFER SIZE INFORMATION
    int buffer_Width, buffer_Height;
    // (Recall: References are aliases for some variable, and cannot be changed.)
    glfwGetFramebufferSize(mainWindow, &buffer_Width, &buffer_Height);
    // Set contet for GLEW to used
    glfwMakeContextCurrent(mainWindow);
    // Allow modern extension features
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)  {
        printf("GLEW Initialization Failure, Destroying window.\nVerify GLEW is included correctly into the project.\n");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    // SETUP VIEWPORT SIZE
    glViewport(0,0, buffer_Width, buffer_Height);

    // SHADERS SETUP
    // ('tg' is short for triangle)
    BasicShader tg;
    tg.display_Triangle();
    tg.compile_Shader();

    

    // QUIT WHEN WINDOW CLOSES
    while(!glfwWindowShouldClose(mainWindow)) {
        // Get & Handle user input events
        glfwPollEvents();

        // Clear window
        glClearColor(0.99f, 0.98f, 0.89f, 0.8);
        glClear(GL_COLOR_BUFFER_BIT);
        // Add triangle 
        glUseProgram(tg.shader);
        glBindVertexArray(tg.VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glUseProgram(0);
        // Switch window buffer
        glfwSwapBuffers(mainWindow);

    }

    return 0;
}