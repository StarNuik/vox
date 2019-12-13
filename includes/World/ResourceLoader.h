#pragma once

#include <unordered_map>
#include <string>

#include "Types.h"
// #include "Render/Objects.h"
// #include "World/World.h"

// class VertexBuffers;

class ResourceLoader {
public:
	ResourceLoader();
	~ResourceLoader();
	Shader* GetShader(std::string);
	Texture* GetTexture(BlockType);
	Geometry* GetGeometry(std::string);
	// Block* GetBlock(BlockType);
private:
	void LoadShaders();
	void LoadTextures();
	void LoadGeometries();
	// void LoadBlocks();
	std::unordered_map<std::string, Shader*> _shaders;
	std::unordered_map<uint, Texture*> _textures;
	std::unordered_map<std::string, Geometry*> _geometries;
	// std::unordered_map<uint, Block*> _blocks;
	VertexBuffers _vbs();
};