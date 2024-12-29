#include "InstancedRenderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

int Texture::unit = 0;

InstancedRenderer::InstancedRenderer(unsigned bufferSize, unsigned instancedSize)
{
    this->bufferSize = bufferSize;
    this->instancedSize = instancedSize;
}

void InstancedRenderer::setVertexBuffer(unsigned size, const void* data)
{
    bufferSize = size;
    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void InstancedRenderer::setInstancedBuffer(unsigned size, const void* data)
{
    instancedSize = size;
    glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void InstancedRenderer::render()
{
    glBindVertexArray(vao);
    glDrawArraysInstanced(GL_TRIANGLES, 0, bufferSize / 8, instancedSize / 3);
    glBindVertexArray(0);
}

InstancedRenderer::~InstancedRenderer()
{
    glDeleteBuffers(2, buffer);
    glDeleteVertexArrays(1, &vao);
}


instanced_t createInstancedRenderer(unsigned bufferSize, const void* bufferData, unsigned instancedSize, const void* instancedData)
{
    instanced_t ref{ new InstancedRenderer(bufferSize, instancedSize) };

    glGenVertexArrays(1, &ref->vao);
    glGenBuffers(2, ref->buffer);

    glBindVertexArray(ref->vao);

    glBindBuffer(GL_ARRAY_BUFFER, ref->buffer[0]);
    glBufferData(GL_ARRAY_BUFFER, bufferSize, bufferData, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0 * sizeof(float)));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, ref->buffer[1]);
    glBufferData(GL_ARRAY_BUFFER, instancedSize, instancedData, GL_STREAM_DRAW);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)(0));
    glEnableVertexAttribArray(3);
    glVertexAttribDivisor(3, 1);

    glBindVertexArray(0);

    return ref;
}

texture_t createTexture(const char* path, int req_comp)
{
    texture_t texture{ new Texture() };
    texture->imgData = stbi_load(path, &texture->width, &texture->height, &texture->channel, req_comp);
    if (!texture->imgData) {
        std::cerr << "Failed to load texture:: " << stbi_failure_reason() << std::endl;
        return nullptr;
    }

    texture->texture_loc = Texture::unit++;

    glGenTextures(1, &texture->tbo);
    glBindTexture(GL_TEXTURE_2D, texture->tbo);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->imgData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
}

void Texture::bind(int textureShaderLocation)
{
    glActiveTexture(GL_TEXTURE0 + texture_loc);
    glBindTexture(GL_TEXTURE_2D, tbo);
    glUniform1i(textureShaderLocation, texture_loc);
}
