#include <GL/glew.h>
#include <GLFW/glfw3.h>

class BasicWindow {
    private:
        GLint WIDTH, HEIGHT;
    public:
        BasicWindow(GLint width=800, GLint height=600);
        void set_Window_Size(GLint width, GLint height) ;
        int display();

        GLint get_Window_Width() const { return WIDTH; } 
        GLint get_Window_Height() const { return HEIGHT; }

        

};