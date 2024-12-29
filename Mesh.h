#pragma once
#ifndef __BYTENOL_RUNNING_SANTA_MESH_H__
#define __BYTENOL_RUNNING_SANTA_MESH_H__

#include <functional>

#include "pch.h"
#include "InstancedRenderer.h"

extern vertices_t planeVertexData, cubeVertexData;

enum class SpriteType
{
	STAR,
	COIN,
	QUESTION,
	SMOKE,
	SHIELD,
	SNAIL,
	AIRPLANE,
	CUBE
};

vertices_t transformVertexData(const vertices_t& data, texel_t texel, vec3_t translation, vec3_t scale);

vertices_t getVertexData(SpriteType type);


class Obstacle
{
public:
	static void init();
	static void update(const float& dt, const float& speed);
	static void render();

private:
	static instanced_t cubeRenderer;
	static instanced_t starRenderer;
	static instanced_t coinRenderer;
	static instanced_t snailRenderer;
	static instanced_t smokeRenderer;
	static instanced_t shieldRenderer;
	static instanced_t airplaneRenderer;
};


class FloorMesh
{
public:
	void init();
	void update(const float& dt, const float& speed);
	void render();
private:
	instanced_t renderer;
	vertices_t instancedData;

	static const int maxColumn = 6;
};

#endif 