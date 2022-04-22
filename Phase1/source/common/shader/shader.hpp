#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <iostream>

#include <glad/gl.h> 
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace our {

    class ShaderProgram {

    private:
        //Shader Program Handle
        GLuint program;

    public:
        void create();
        void destroy();

        ShaderProgram(){ program = 0; }
        //deleteing the copy constructor (to avoid assiging the same program to a different shader, instead we must begin)
        ShaderProgram( const ShaderProgram&) = delete;
        //also deleting the assignment operator
        ShaderProgram & operator=( const ShaderProgram&) = delete;
        ~ShaderProgram(){ destroy(); }

        bool attach(const std::string &filename, GLenum type) const;

        bool link() const;

        void use() { 
            //TODO: call opengl to use the program identified by this->program
            glUseProgram(this->program);
            //using this-> to indicate the program of the calling object
        }

        GLuint getUniformLocation(const std::string &name) {
            //TODO: call opengl to get the uniform location for the uniform defined by name from this->program
            return (glGetUniformLocation(this->program, name.c_str()));
            //glGetUniformLocation accepts constant pointer, so we must convert 'name' to c_str
        }

        void set(const std::string &uniform, GLfloat value) {
            //TODO: call opengl to set the value to the uniform defined by name
            glUniform1f(getUniformLocation(uniform), value);
            //glUniform binds the value to the uniform across the entire project
            // 1f means it accepts 1 float
        }

        void set(const std::string &uniform, glm::vec2 value) {
            //TODO: call opengl to set the value to the uniform defined by name
            glUniform2fv(getUniformLocation(uniform), 1, &value[0]);
            // 2fv means it accepts vec2 of type float
        }

        void set(const std::string &uniform, glm::vec3 value) {
            //TODO: call opengl to set the value to the uniform defined by name
            glUniform3fv(getUniformLocation(uniform), 1, &value[0]);
            // 3fv means it accepts vec3 of type float
        }

        void set(const std::string &uniform, glm::vec4 value) {
            //TODO: call opengl to set the value to the uniform defined by name
            glUniform4fv(getUniformLocation(uniform), 1, &value[0]);
            // 4fv means if accepts vec4 of type float
        }


        //TODO: Delete the copy constructor and assignment operator
        //AYMAN : DONE
        //Question: Why do we do this? Hint: Look at the deconstructor
            //We do this, off course, to prevent the footgun of the shallow copying 
            //Because ShaderProgram contains a handle to an object (GLuint program)
            //Doing ShaderProgram shp = anotherShaderProgram will copy only the GLuint
            //This is wrong, the GLuint is only a reference to an underlying object deep 
            //in GLFW bowels
    };

}

#endif