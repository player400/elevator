#pragma once

#include "utilities.hpp"

class ShaderProgram
{
    private:

        GLuint program;

        GLuint zbuduj_shader(const string& code, GLenum type, const char* name)
        {
            GLuint shader = glCreateShader(type);

            const char* source = code.c_str();

            glShaderSource(shader, 1, &source, NULL);
            glCompileShader(shader);

            int status;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
            if(status==0)
            {
                char error[1024];
                int length;
                glGetShaderInfoLog(shader, 1024, &length, error);
                cout<<"COMPILATION FAILED BECAUSE: "<<error<<"||| IN SHADER: "<<name<<endl;
                exit(2);
            }

            return shader;
        }

    public:

        void uzyj()
        {
            glUseProgram(program);
        }


        ShaderProgram(const string& vertex, const string& fragment)
        {
            GLuint vert=zbuduj_shader(vertex, GL_VERTEX_SHADER, "vertex");
            GLuint frag=zbuduj_shader(fragment, GL_FRAGMENT_SHADER, "fragment");

            program = glCreateProgram();

            glAttachShader(program, vert);
            glAttachShader(program, frag);
            glLinkProgram(program);

            int status;
            glGetProgramiv(program, GL_LINK_STATUS, &status);
            if(status==0)
            {
                cout<<"LINK FAILED"<<endl;
                exit(2);
            }


            glDeleteShader(vert);
            glDeleteShader(frag);
        }

};
