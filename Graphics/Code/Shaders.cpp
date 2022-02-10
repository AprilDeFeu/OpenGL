// HEADERS
#include <string.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
// CLASS
#include "Shaders.hpp"

// Vertex shader; resize smaller
static const char *vShader = "                       \n\
#version 330                                         \n\
                                                     \n\
layout (location = 0) in vec3 pos;                   \n\
                                                     \n\
void main() {                                        \n\
    gl_Position = vec4(0.4 * pos.x, 0.4 * pos.y, 0.4 * pos.z, 1.0);    \n\
}";

// Fragment shader; color triangle dark purple
static const char *fShader = "                       \n\
#version 330                                         \n\
                                                     \n\
out vec4 color;                                      \n\
                                                     \n\
void main() {                                        \n\
    color = vec4(0.3, 0.0, 0.3, 1.0);                \n\
}";

void BasicShader::display_Triangle() {
    // Define vertices relative to the width and height of window
    GLfloat vertices [] = { 
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };
    
    // Create one vertex array object, as we only have one triangle
    glGenVertexArrays(1, &VAO);
    // Bind the vertex array object
    glBindVertexArray(VAO);

    // Create vertex buffer object
    glGenBuffers(1, &VBO);
    // Bind the vertex buffer object, choosing array buffer as target
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Connect buffer array to GL buffer using 'vertices' to draw
    // a static triangle over the current window.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // Set attribute pointers. Arguments:
    /* - GLuint: Layout index 
     * - GLint: Number of values
     * - GLenum: Type of values
     * - GLboolean: Whether to normalize values or not
     * - GLsizei:  In case of packed data, choose skip factor
     * - Pointer: Whether to buffer or now
     */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    // Disable VAO
    glEnableVertexAttribArray(0);
    // Unbind VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

}

void BasicShader::add_Shader(GLuint shader_prog, const char* shader_body, GLenum shader_type){
    // Create shader of type shader_type
    GLuint created_shader = glCreateShader(shader_type);
    // Point to shader body to use as code
    const GLchar *shader_code[1];
    shader_code[0] = shader_body; 
    // Get size of shader_body
    GLint code_size[1];
    code_size[0] = strlen(shader_body); 
    // Set shader data
    glShaderSource(created_shader, 1, shader_code, code_size);
    glCompileShader(created_shader);

    // Container for result and error of computations
    GLint result = 0;
    GLchar error_Log[2048] = { 0 };

    // Verify shader for errors
    glGetShaderiv(created_shader, GL_COMPILE_STATUS, &result);
    
    // In case of error, log it in container 
    if (!result) {
        glGetShaderInfoLog(shader, sizeof(error_Log), NULL, error_Log);
        printf("Error compiling %d shader:\n '%s'\n",shader_type, error_Log);
        return;
    }

    // If successful, attach shader
    glAttachShader(shader_prog, created_shader);

}

void BasicShader::compile_Shader() {
    shader = glCreateProgram();
    // Verify shader initialization
    if (!shader) {
        printf("Shader failure.\nCheck the header definitions.\n");
        return;
    }
    // Add shaders to program
    add_Shader(shader, vShader, GL_VERTEX_SHADER);
    add_Shader(shader, fShader, GL_FRAGMENT_SHADER);

    // Container for result and error of computations
    GLint result = 0;
    GLchar error_Log[2048] = { 0 };

    // Create executables in GPU for shaders
    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    
    // In case of error, log it in container 
    if (!result) {
        glGetProgramInfoLog(shader, sizeof(error_Log), NULL, error_Log);
        printf("Error linking program for BasicShader:\n '%s'\n", error_Log);
        return;
    }

    // Validate whether shader is valid in context of program
    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shader, sizeof(error_Log), NULL, error_Log);
        printf("Error validating program for BasicShader:\n '%s'\n", error_Log);
        return;
    }
}