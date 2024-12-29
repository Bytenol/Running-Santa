#pragma once
#ifndef __BYTENOL_RUNNING_SANTA_INSTANCED_RENDERER_H__
#define __BYTENOL_RUNNING_SANTA_INSTANCED_RENDERER_H__

#include "pch.h"


instanced_t createInstancedRenderer(unsigned bufferSize, const void* bufferData, unsigned instancedSize, const void* instancedData);

texture_t createTexture(const char* path, int req_comp);


class Texture
{
	friend texture_t createTexture(const char* path, int req_comp);

public:
	Texture() = default;
	void bind(int textureShaderLocation);

private:
	int width;
	int height;
	int channel;
	unsigned char* imgData;
	int texture_loc = 0;
	unsigned int tbo;

	static int unit;
};


class InstancedRenderer
{
	friend instanced_t createInstancedRenderer(unsigned bufferSize, const void* bufferData, unsigned instancedSize, const void* instancedData);

	using val_it = std::vector<float>::iterator;
	unsigned int vao;
	unsigned int buffer[2];
	unsigned bufferSize;
	unsigned instancedSize;


public:
	vertices_t bufferData;
	vertices_t instancedData;

    InstancedRenderer() = default;
	InstancedRenderer(unsigned bufferSize, unsigned instancedSize);
	void setVertexBuffer(unsigned size, const void* data);
	void setInstancedBuffer(unsigned size, const void* data);
	void render();
	~InstancedRenderer();
};


#endif 
