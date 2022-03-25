#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

#include <vendor/glad/include/glad/gl.h> 
#include <vendor/glm/glm.hpp>
#include <vendor/glm/gtc/type_ptr.hpp>

namespace our {

    class ShaderProgram {

    private:
        //Shader Program Handle
        GLuint program;

    public:
        void create();
        void destroy();

        ShaderProgram(){ program = 0; }
        ShaderProgram( const ShaderProgram&) = delete;
        ShaderProgram & operator=( const ShaderProgram&) = delete;
        ~ShaderProgram(){ destroy(); }

        bool attach(const std::string &filename, GLenum type) const;

        bool link() const;

        void use() { 
            //TODO: call opengl to use the program identified by this->program
            glUseProgram(this->program);
        }

        GLuint getUniformLocation(const std::string &name) {
            //TODO: call opengl to get the uniform location for the uniform defined by name from this->program
            return (glGetUniformLocation(this->program, name.c_str()));
        }

        void set(const std::string &uniform, GLfloat value) {
            //TODO: call opengl to set the value to the uniform defined by name
            glUniform1f(getUniformLocation(uniform), value);
        }

        void set(const std::string &uniform, glm::vec2 value) {
            //TODO: call opengl to set the value to the uniform defined by name
            glUniform2fv(getUniformLocation(uniform), 1, &value[0]);
        }

        void set(const std::string &uniform, glm::vec3 value) {
            //TODO: call opengl to set the value to the uniform defined by name
            glUniform2fv(getUniformLocation(uniform), 1, &value[0]);
        }

        void set(const std::string &uniform, glm::vec4 value) {
            //TODO: call opengl to set the value to the uniform defined by name
            glUniform2fv(getUniformLocation(uniform), 1, &value[0]);
        }


        //TODO: Delete the copy constructor and assignment operator
        //AYMAN : DONE
        //Question: Why do we do this? Hint: Look at the deconstructor
    };

}

#endif