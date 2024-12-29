#pragma once
#ifndef __BYTENOL_GL_RENDERER_H__
#define __BYTENOL_GL_RENDERER_H__

#include "pch.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Mat4.h"
#include "InstancedRenderer.h"
#include "Mesh.h"

class GLRenderer
{
private:
	static int width;
	static int height;

	FloorMesh floor;
	instanced_t floorRenderer = nullptr;
	texture_t spritesheet = nullptr;

public:
	GLRenderer(const int& w, const int& h);
	bool start();
	~GLRenderer();

private:
	GLFWwindow* window;

	struct Program {
		unsigned int id;
	} program;

	bool shouldClose = false;
	bool initWindow();
	bool init();
	bool onRender(float dt);
	bool onUpdate(float dt);
	bool onProcessEvent();

	bool initProgram(Program& program, const std::string & vSourcePath, const std::string & fSourcePath);

};

#endif 