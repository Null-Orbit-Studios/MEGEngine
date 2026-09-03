#ifndef MESH_H
#define MESH_H

#include <vector>

#include "MEGEngine/Common.hpp"
#include "MEGEngine/Renderer/VAO.hpp"
#include "MEGEngine/Renderer/Vertex.hpp"
#include "MEGEngine/Renderer/Texture.hpp"


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