#pragma once
#ifndef __BYTENOL_RUNNING_SANTA_PCH_H__
#define __BYTENOL_RUNNING_SANTA_PCH_H__

#include <iostream>
#include <vector>
#include <fstream>
#include <memory>
#include <algorithm>
#include <ranges>

#include <glad/glad.h>


using vertices_t = std::vector<float>;
using texel_t = float(*)[4];
using vec2_t = float(*)[2];
using vec3_t = float(*)[3];


// forward declarations and extended using
class InstancedRenderer;
class Texture;

using instanced_t = std::unique_ptr<InstancedRenderer>;
using texture_t = std::unique_ptr<Texture>;

#endif 
