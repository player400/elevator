#pragma once
#include "utilities.hpp"

class Buffer
{
    private:
        vector <GLfloat> buffer;
        GLuint vao, vbo;
        int count=0;

        void atrybut(int index, int count, int stride, long offset)
        {
            glVertexAttribPointer(index, count, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*) (offset * sizeof(float)));
            glEnableVertexAttribArray(index);
        }

    public:

        void bind()
        {
            glBindVertexArray(vao);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
        }

        void czysc()
        {
            buffer.clear();
            count=0;
        }

        void vertex(float x, float y, float r, float g, float b, float u, float v)
        {
            buffer.push_back(x);
            buffer.push_back(y);
            buffer.push_back(r);
            buffer.push_back(g);
            buffer.push_back(b);
            buffer.push_back(u);
            buffer.push_back(v);
            count++;
        }

        void wyslij()
        {
            bind();
            glBufferData(GL_ARRAY_BUFFER, buffer.size()*sizeof(float), buffer.data(), GL_DYNAMIC_DRAW);
        }

        Buffer()
        {
            glGenVertexArrays(1, &vao);
            glGenBuffers(1, &vbo);


            bind();
            atrybut(0, 2, 7, 0);
            atrybut(1, 3, 7, 2);
            atrybut(2, 2, 7, 5);
        }

        void rysuj()
        {
            bind();
            glDrawArrays(GL_TRIANGLES, 0, count);
        }

};
