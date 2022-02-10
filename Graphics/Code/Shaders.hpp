// HEADERS
#include <string.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

class BasicShader {
    
    public:
        
        GLuint VAO, VBO, shader;    
        void add_Shader(GLuint shader_prog, const char* shader_body, GLenum shader_type);
        
        void display_Triangle();
        void compile_Shader();
};