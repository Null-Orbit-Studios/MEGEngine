#ifndef MEGENGINEPROJECT_VERTEX_H
#define MEGENGINEPROJECT_VERTEX_H

#include "MEGEngine/Common.hpp"

#include "MEGEngine/Math/Vec3.hpp"
#include "MEGEngine/Math/Vec2.hpp"


struct ENGINE_API Vertex {
    Vertex(Vec3 position, Vec3 normal, Vec3 colour, Vec2 texUV) : position(position), normal(normal), colour(colour), texUV(texUV) {};
    Vec3 position;
    Vec3 normal;
    Vec3 colour;
    Vec2 texUV;
};


#endif //MEGENGINEPROJECT_VERTEX_H