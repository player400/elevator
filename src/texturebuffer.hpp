#pragma once

#include "utilities.hpp"

class TextureBuffer
{
    private:
        Texture texture;
        Buffer buffer;

    public:

        void rysuj()
        {
            texture.bind();
            //program->uzyj();

            buffer.wyslij();
            buffer.rysuj();

            buffer.czysc();
        }

        void ustaw_vertexy(float x1, float y1, float x2, float y2, float z, float u1, float v1, float u2, float v2)
        {
            buffer.vertex(x1, y1, z, 0, 0, 1, u1, v1);
            buffer.vertex(x2, y2, z, 0, 1, 0, u2, v2);
            buffer.vertex(x1, y2, z, 1, 0, 0, u1, v2);

            buffer.vertex(x1, y1, z, 0, 0, 1, u1, v1);
            buffer.vertex(x2, y1, z, 1, 0, 0, u2, v1);
            buffer.vertex(x2, y2, z, 0, 1, 0, u2, v2);
        }

        TextureBuffer(string texture_file_name):texture(texture_file_name)
        {
            return;
        }

        TextureBuffer(const TextureBuffer& texturebuffer) = delete;

        TextureBuffer(TextureBuffer&& texturebuffer):texture(move(texturebuffer.texture)), buffer(move(texturebuffer.buffer))
        {
            return;
        }
};
