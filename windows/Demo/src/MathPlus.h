#pragma once

#include <random>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

inline vec3 VectorMultiple(mat4 mat, vec3 vec)
{
    return vec3(
        mat[0].x * vec.x + mat[0].y * vec.y + mat[0].z * vec.z + mat[0].w + mat[3].x,
        mat[1].x * vec.x + mat[1].y * vec.y + mat[1].z * vec.z + mat[1].w + mat[3].y,
        mat[2].x * vec.x + mat[2].y * vec.y + mat[2].z * vec.z + mat[2].w + mat[3].z
    );
}

template<typename T>
inline T Random(T min, T max)
{   }

template<>
inline float Random<float>(float min, float max)
{
    std::random_device rd;
    std::mt19937_64 rng(rd());

    std::uniform_real_distribution<float> dist1(min, max);
    return dist1(rng);
}

template<>
inline int Random<int>(int min, int max)
{
    std::random_device rd;
    std::mt19937_64 rng(rd());

    std::uniform_int_distribution<int> dist1(min, max);
    return dist1(rng);
}