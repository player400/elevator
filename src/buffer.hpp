#pragma once
#include "utilities.hpp"

class Buffer
{
    private:
        vector <GLfloat> buffer;
        GLuint vao, vbo;
        int count=0;

        void atrybut(int index, int count_, int stride, long offset)
        {
            glVertexAttribPointer(index, count_, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*) (offset * sizeof(float)));
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

        void vertex(float x, float y, float z, float r, float g, float b, float u, float v)
        {
            buffer.push_back(x);
            buffer.push_back(y);
            buffer.push_back(z);
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
            atrybut(0, 3, 8, 0);
            atrybut(1, 3, 8, 3);
            atrybut(2, 2, 8, 6);
        }

        void rysuj()
        {
            bind();
            glDrawArrays(GL_TRIANGLES, 0, count);

//            for(int i=0; i<buffer.size(); i++)
//            {
//                //czyszczenie();
//                if(i%8==2)
//                {
//                    cout<<buffer[i]<<endl;
//                }
//
//            }
        }

        ~Buffer()
        {
            if(vao!=0)
            {
                glDeleteBuffers(1, &vbo);
                glDeleteVertexArrays(1, &vao);
            }
        }

        Buffer(const Buffer& buffer) = delete;

        Buffer(Buffer&& other):buffer(move(other.buffer))
        {
            count = other.count;
            vao = other.vao;
            vbo = other.vbo;
            other.vao=0;
            other.vbo=0;
        }
};
