#include "Render/Objects.h"
#include "Engine/Locator.hpp"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include "Types.h"

std::vector<float> ReadGeometry(std::string path) {
	//? Code copied from https://github.com/syoyo/tinyobjloader

	std::vector<float> res;

	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn;
	std::string err;

	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str());
	if (!warn.empty()) {
		Locator::getLogger()->LogWarning("[ReadGeometry]\n" + warn);
	}
	if (!err.empty()) {
		Locator::getLogger()->LogError("[ReadGeometry]\n" + err);
	}
	if (!ret) {
		Locator::getLogger()->LogError("[ReadGeometry]\nError");
		exit(1);
	}
	size_t index_offset = 0;
	for (size_t f = 0; f < shapes[0].mesh.num_face_vertices.size(); f++) {
		int fv = shapes[0].mesh.num_face_vertices[f];

		// Loop over vertices in the face.
		for (size_t v = 0; v < fv; v++) {
			// access to vertex
			tinyobj::index_t idx = shapes[0].mesh.indices[index_offset + v];
			res.push_back(attrib.vertices [3 * idx.vertex_index   + 0]);
			res.push_back(attrib.vertices [3 * idx.vertex_index   + 1]);
			res.push_back(attrib.vertices [3 * idx.vertex_index   + 2]);
			res.push_back(attrib.normals  [3 * idx.normal_index   + 0]);
			res.push_back(attrib.normals  [3 * idx.normal_index   + 1]);
			res.push_back(attrib.normals  [3 * idx.normal_index   + 2]);
			res.push_back(attrib.texcoords[2 * idx.texcoord_index + 0]);
			res.push_back(attrib.texcoords[2 * idx.texcoord_index + 1]);
		}
		index_offset += fv;
	}
	return res;
}

#include <stdio.h>
Geometry::Geometry(std::string path) {
	const int numOfFloats = 8;

	std::vector<float> buffer = ReadGeometry(path);
	_polygonCount = buffer.size() / 8;
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);

	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numOfFloats * 3 * _polygonCount, &buffer[0], GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, numOfFloats * sizeof(float), nullptr);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, numOfFloats * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, numOfFloats * sizeof(float), (void*)(6 * sizeof(float)));
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	Locator::getLogger()->LogSuccess("[Geometry::Geomtry]\nLoaded: " + path);
}

Geometry::~Geometry() {
	glDeleteBuffers(1, &_vbo);
	glDeleteVertexArrays(1, &_vao);
};

uint Geometry::GetPolygonCount() {
	return _polygonCount;
}

void Geometry::Use() {
	glBindVertexArray(_vao);
}