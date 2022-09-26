#pragma once
#include "utilities.hpp"

class Texture
{
    private:
        int width;
        int height;
        GLuint texture;

    public:

        void bind()
        {
            glBindTexture(GL_TEXTURE_2D, texture);
        }

        Texture(const string& path)
        {
            glGenTextures(1, &texture);
            bind();
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

            int channels;
            unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 3);

            if(!data)
            {
                cout<<"TXT ERROR"<< path<<endl;
                exit(3);
            }

            glPixelStorei(GL_PACK_ALIGNMENT, 1);
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }

};
