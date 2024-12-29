#include "Mesh.h"


vertices_t planeVertexData{
    -0.5, -0.5, 0.5, 0.0, 0.0, 0.0, 0.0, 1.0, // Bottom-left
    0.5, -0.5, 0.5, 1.0, 0.0, 0.0, 0.0, 1.0, // Bottom-right
    0.5, 0.5, 0.5, 1.0, 1.0, 0.0, 0.0, 1.0, // Top-right
    -0.5, -0.5, 0.5, 0.0, 0.0, 0.0, 0.0, 1.0, // Bottom-left
    0.5, 0.5, 0.5, 1.0, 1.0, 0.0, 0.0, 1.0, // Top-right
    -0.5, 0.5, 0.5, 0.0, 1.0, 0.0, 0.0, 1.0, // Top-left
};


vertices_t cubeVertexData{
    // front
    -0.5, -0.5, 0.5, 0.0, 0.0, 0.0, 0.0, 1.0, // Bottom-left
    0.5, -0.5, 0.5, 1.0, 0.0, 0.0, 0.0, 1.0, // Bottom-right
    0.5, 0.5, 0.5, 1.0, 1.0, 0.0, 0.0, 1.0, // Top-right
    -0.5, -0.5, 0.5, 0.0, 0.0, 0.0, 0.0, 1.0, // Bottom-left
    0.5, 0.5, 0.5, 1.0, 1.0, 0.0, 0.0, 1.0, // Top-right
    -0.5, 0.5, 0.5, 0.0, 1.0, 0.0, 0.0, 1.0, // Top-left
    // Back face
    -0.5, -0.5, -0.5, 0.0, 0.0, 0.0, 0.0, -1.0, // Bottom-left
    -0.5, 0.5, -0.5, 0.0, 1.0, 0.0, 0.0, -1.0, // Top-left
    0.5, 0.5, -0.5, 1.0, 1.0, 0.0, 0.0, -1.0, // Top-right
    -0.5, -0.5, -0.5, 0.0, 0.0, 0.0, 0.0, -1.0, // Bottom-left
    0.5, 0.5, -0.5, 1.0, 1.0, 0.0, 0.0, -1.0, // Top-right
    0.5, -0.5, -0.5, 1.0, 0.0, 0.0, 0.0, -1.0, // Bottom-right
    // Top face
    -0.5, 0.5, -0.5, 0.0, 0.0, 0.0, 1.0, 0.0, // Bottom-left
    -0.5, 0.5, 0.5, 0.0, 1.0, 0.0, 1.0, 0.0, // Top-left
    0.5, 0.5, 0.5, 1.0, 1.0, 0.0, 1.0, 0.0, // Top-right
    -0.5, 0.5, -0.5, 0.0, 0.0, 0.0, 1.0, 0.0, // Bottom-left
    0.5, 0.5, 0.5, 1.0, 1.0, 0.0, 1.0, 0.0, // Top-right
    0.5, 0.5, -0.5, 1.0, 0.0, 0.0, 1.0, 0.0, // Bottom-right
    // Bottom face
    -0.5, -0.5, -0.5, 0.0, 0.0, 0.0, -1.0, 0.0, // Bottom-left
    0.5, -0.5, 0.5, 1.0, 1.0, 0.0, -1.0, 0.0, // Top-right
    -0.5, -0.5, 0.5, 0.0, 1.0, 0.0, -1.0, 0.0, // Top-left
    -0.5, -0.5, -0.5, 0.0, 0.0, 0.0, -1.0, 0.0, // Bottom-left
    0.5, -0.5, -0.5, 1.0, 0.0, 0.0, -1.0, 0.0, // Bottom-right
    0.5, -0.5, 0.5, 1.0, 1.0, 0.0, -1.0, 0.0, // Top-right
    // Right face
    0.5, -0.5, -0.5, 0.0, 0.0, 1.0, 0.0, 0.0, // Bottom-left
    0.5, 0.5, -0.5, 1.0, 0.0, 1.0, 0.0, 0.0, // Top-left
    0.5, 0.5, 0.5, 1.0, 1.0, 1.0, 0.0, 0.0, // Top-right
    0.5, -0.5, -0.5, 0.0, 0.0, 1.0, 0.0, 0.0, // Bottom-left
    0.5, 0.5, 0.5, 1.0, 1.0, 1.0, 0.0, 0.0, // Top-right
    0.5, -0.5, 0.5, 0.0, 1.0, 1.0, 0.0, 0.0, // Bottom-right
    // Left face
    -0.5, -0.5, -0.5, 0.0, 0.0, -1.0, 0.0, 0.0, // Bottom-left
    -0.5, -0.5, 0.5, 1.0, 0.0, -1.0, 0.0, 0.0, // Bottom-right
    -0.5, 0.5, 0.5, 1.0, 1.0, -1.0, 0.0, 0.0, // Top-right
    -0.5, -0.5, -0.5, 0.0, 0.0, -1.0, 0.0, 0.0, // Bottom-left
    -0.5, 0.5, 0.5, 1.0, 1.0, -1.0, 0.0, 0.0, // Top-right
    -0.5, 0.5, -0.5, 0.0, 1.0, -1.0, 0.0, 0.0, // Top-left
};


vertices_t transformVertexData(const vertices_t& data, texel_t texel, vec3_t translation, vec3_t scale)
{
    const float tx = (*texel)[0] / 640.0f;
    const float ty = (*texel)[1] / 1664.0f;
    const float tw = ((*texel)[0] + (*texel)[2]) / 640.0f;
    const float th = ((*texel)[1] + (*texel)[3]) / 1664.0f;
    const int stride = 8;

    vertices_t vertexData{ data.cbegin(), data.cend() };

    for (size_t i = 0; i < vertexData.size(); i += stride) {
        vertexData[i] = vertexData[i] * (*scale)[0] + (*translation)[0];
        vertexData[i + 1] = vertexData[i + 1] * (*scale)[1] + (*translation)[1];
        vertexData[i + 2] = vertexData[i + 2] * (*scale)[2] + (*translation)[2];
        // texel
        vertexData[i + 3] = (vertexData[i + 3] == 0.0f ? tx : tw);
        vertexData[i + 4] = (vertexData[i + 4] == 0.0f ? ty : th);
    }

    return vertexData;
}

vertices_t getVertexData(SpriteType type)
{
    float scale[3]{ 1, 1, 1 };
    float translation[3]{ 0, 0, 0 };
    float texel[4]{ 0, 0, 64, 64 };

    switch (type) {
    case SpriteType::STAR:
        texel[0] = 7 * 64;
        return transformVertexData(planeVertexData, &texel, &translation, &scale);
    case SpriteType::SMOKE:
        texel[0] = 3 * 64;
        return transformVertexData(planeVertexData, &texel, &translation, &scale);
    case SpriteType::SHIELD:
        texel[0] = 4 * 64;
        return transformVertexData(planeVertexData, &texel, &translation, &scale);
    case SpriteType::QUESTION:
        texel[0] = 5 * 64;
        return transformVertexData(planeVertexData, &texel, &translation, &scale);
    case SpriteType::AIRPLANE:
        texel[0] = 6 * 64;
        return transformVertexData(planeVertexData, &texel, &translation, &scale);
    case SpriteType::SNAIL:
        texel[0] = 2 * 64;
        return transformVertexData(planeVertexData, &texel, &translation, &scale);
    case SpriteType::COIN:
        texel[0] = 64;
        texel[1] = 164;
        scale[0] = scale[1] = scale[2] = 0.4f;
        return transformVertexData(planeVertexData, &texel, &translation, &scale);
    default:
        return transformVertexData(cubeVertexData, &texel, &translation, &scale);
    }
}


void FloorMesh::init()
{
    float texel[4]{ 64.0f, 0.0f, 64.0f, 64.0f };
    float trans[3]{ 0.0f, 0.0f, 0.0f };
    float scale[3]{ maxColumn, 0.1f, 1.0f };
    vertices_t position;
    auto floorData = transformVertexData(cubeVertexData, &texel, &trans, &scale);
    auto lastIt = position.insert(position.begin(), floorData.begin(), floorData.end());

    // pole data
    texel[0] = 0;
    texel[1] = 164;

    scale[0] = 0.1f;
    scale[1] = scale[0];
    scale[2] = 1.0f;
    trans[0] = -maxColumn * 0.5f;
    trans[1] = 1.0f;
    auto poleData = transformVertexData(cubeVertexData, &texel, &trans, &scale);
    lastIt = position.insert(position.begin(), poleData.begin(), poleData.end());

    trans[0] = maxColumn * 0.5f;
    poleData = transformVertexData(cubeVertexData, &texel, &trans, &scale);
    lastIt = position.insert(position.begin(), poleData.begin(), poleData.end());

    trans[1] = 0.5f;
    scale[1] = 1.0f;
    scale[2] = scale[0];

    poleData = transformVertexData(cubeVertexData, &texel, &trans, &scale);
    lastIt = position.insert(lastIt, poleData.begin(), poleData.end());

    trans[0] = -maxColumn * 0.5f;
    poleData = transformVertexData(cubeVertexData, &texel, &trans, &scale);
    lastIt = position.insert(lastIt, poleData.begin(), poleData.end());

    instancedData.clear();
    for (int z = 0; z <= 50; z++) {
        instancedData.push_back(0.0f);
        instancedData.push_back(-1.0f);
        instancedData.push_back(-z);
    }

    renderer = createInstancedRenderer(position.size() * sizeof(float), position.data(), instancedData.size() * sizeof(float), instancedData.data());
}

void FloorMesh::update(const float& dt, const float& speed)
{
    for (size_t i = 0; i < instancedData.size(); i += 3) {
        auto& posZ = instancedData[i + 2];
        posZ += speed * dt;
        if (posZ > 0.5f) {
            posZ = -50.0f;
        }
    }
    renderer->setInstancedBuffer(instancedData.size() * sizeof(float), instancedData.data());
}

void FloorMesh::render()
{
    renderer->render();
}


instanced_t Obstacle::cubeRenderer = nullptr;
instanced_t Obstacle::starRenderer = nullptr;
instanced_t Obstacle::snailRenderer = nullptr;
instanced_t Obstacle::shieldRenderer = nullptr;
instanced_t Obstacle::smokeRenderer = nullptr;
instanced_t Obstacle::airplaneRenderer = nullptr;


void Obstacle::init()
{
    size_t i = 0;

    auto data = getVertexData(SpriteType::CUBE);
    cubeRenderer = createInstancedRenderer(data.size() * sizeof(float), data.data(), 60 * sizeof(float), nullptr);
    cubeRenderer->instancedData.clear();
    for (i = 0; i < 20; i++) {
        cubeRenderer->instancedData.push_back(0);
        cubeRenderer->instancedData.push_back(-0.5f);
        cubeRenderer->instancedData.push_back(-INFINITY);
    }
    cubeRenderer->instancedData[0] = -2;
    cubeRenderer->instancedData[2] = -10.0f;
    cubeRenderer->instancedData[3] = -1;
    cubeRenderer->instancedData[5] = -10.0f;

    data = getVertexData(SpriteType::STAR);
    starRenderer = createInstancedRenderer(data.size() * sizeof(float), data.data(), 3 * sizeof(float), nullptr);
    starRenderer->instancedData = { 0, -0.5f, -INFINITY };

    data = getVertexData(SpriteType::SNAIL);
    snailRenderer = createInstancedRenderer(data.size() * sizeof(float), data.data(), 3 * sizeof(float), nullptr);
    snailRenderer->instancedData = { 0, -0.5f, -INFINITY };

    data = getVertexData(SpriteType::SMOKE);
    smokeRenderer = createInstancedRenderer(data.size() * sizeof(float), data.data(), 3 * sizeof(float), nullptr);
    smokeRenderer->instancedData = { 1, -0.5f, -INFINITY };

    data = getVertexData(SpriteType::SHIELD);
    shieldRenderer = createInstancedRenderer(data.size() * sizeof(float), data.data(), 3 * sizeof(float), nullptr);
    shieldRenderer->instancedData = { 0, -0.5f, -INFINITY };

    data = getVertexData(SpriteType::AIRPLANE);
    airplaneRenderer = createInstancedRenderer(data.size() * sizeof(float), data.data(), 3 * sizeof(float), nullptr);
    airplaneRenderer->instancedData = { 2, -0.5f, -INFINITY };
}


void Obstacle::update(const float& dt, const float& speed)
{
    auto updateObstacle = [&speed, &dt](instanced_t& instanced, void(*ptr)(float& px, float& py, float& pz)) -> void {
        for (size_t i = 0; i < instanced->instancedData.size(); i += 3)
        {
            auto& posX = instanced->instancedData[i];
            auto posY = instanced->instancedData[i + 1];
            auto& posZ = instanced->instancedData[i + 2];
            if (!std::isfinite(posZ)) continue;
            posZ += speed * dt;
            if (ptr) ptr(posX, posY, posZ);
        }
        instanced->setInstancedBuffer(instanced->instancedData.size() * sizeof(float),
            instanced->instancedData.data());
    };

    updateObstacle(cubeRenderer, nullptr);
    updateObstacle(starRenderer, nullptr);
    updateObstacle(snailRenderer, nullptr);
    updateObstacle(smokeRenderer, nullptr);
    updateObstacle(shieldRenderer, nullptr);
    updateObstacle(airplaneRenderer, nullptr);
}


void Obstacle::render()
{
    cubeRenderer->render();
    starRenderer->render();
    snailRenderer->render();
    smokeRenderer->render();
    shieldRenderer->render();
    airplaneRenderer->render();
}

