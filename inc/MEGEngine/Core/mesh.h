#ifndef MESH_H
#define MESH_H

#include <vector>

#include "MEGEngine/common.h"
#include "MEGEngine/Core/vao.h"
#include "MEGEngine/Core/vertex.h"
#include "MEGEngine/Core/texture.h"


class ENGINE_API Mesh {
public:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
	void bind();
	size_t numIndices();

private:
	VAO vao;

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
};



#endif //MESH_H