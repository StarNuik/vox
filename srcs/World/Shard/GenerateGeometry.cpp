#include "Types.h"
#include "World/Shard.h"
#include "World/World.h"
#include "Render/VertexBuffers.h"
#include "Utilities/Profiler.h"

std::vector<float> Shard::GenerateBlock(World* w, const glm::ivec3 globalP, const glm::ivec3 localP) {
	std::vector<float> res = std::vector<float>();

	//? Right face
	if ((localP.x != 15 ? _blocks[localP.x + 1][localP.y][localP.z] : w->GetBlock(globalP + glm::ivec3(1, 0, 0))) == BlockType::Air) {
		float *buffer = VertexBuffers::GetBuffer(VertexBuffers::Right);
		res.reserve(48 * sizeof(float));
		res.insert(res.end(), buffer, buffer + 48);
	}
	//? Left face
	if ((localP.x != 0 ? _blocks[localP.x - 1][localP.y][localP.z] : w->GetBlock(globalP + glm::ivec3(-1, 0, 0))) == BlockType::Air) {
		float *buffer = VertexBuffers::GetBuffer(VertexBuffers::Left);
		res.reserve(48 * sizeof(float));
		res.insert(res.end(), buffer, buffer + 48);
	}
	//? Top face
	if ((localP.y != 15 ? _blocks[localP.x][localP.y + 1][localP.z] : w->GetBlock(globalP + glm::ivec3(0, 1, 0))) == BlockType::Air) {
		float *buffer = VertexBuffers::GetBuffer(VertexBuffers::Top);
		res.reserve(48 * sizeof(float));
		res.insert(res.end(), buffer, buffer + 48);
	}
	//? Bottom face
	if ((localP.y != 0 ? _blocks[localP.x][localP.y - 1][localP.z] : w->GetBlock(globalP + glm::ivec3(0, -1, 0))) == BlockType::Air) {
		float *buffer = VertexBuffers::GetBuffer(VertexBuffers::Bottom);
		res.reserve(48 * sizeof(float));
		res.insert(res.end(), buffer, buffer + 48);
	}
	//? Front face
	if ((localP.z != 15 ? _blocks[localP.x][localP.y][localP.z + 1] : w->GetBlock(globalP + glm::ivec3(0, 0, 1))) == BlockType::Air) {
		float *buffer = VertexBuffers::GetBuffer(VertexBuffers::Front);
		res.reserve(48 * sizeof(float));
		res.insert(res.end(), buffer, buffer + 48);
	}
	//? Back face
	if ((localP.z != 0 ? _blocks[localP.x][localP.y][localP.z - 1] : w->GetBlock(globalP + glm::ivec3(0, 0, -1))) == BlockType::Air) {
		float *buffer = VertexBuffers::GetBuffer(VertexBuffers::Back);
		res.reserve(48 * sizeof(float));
		res.insert(res.end(), buffer, buffer + 48);
	}
	return res;
}

std::vector<float> Shard::GenerateMultisideBlock(World* w, const glm::ivec3 globalBlockPos, const glm::ivec3 localBlockPos) {
	std::vector<float> res = std::vector<float>();

	//? Right face
	if (w->GetBlock(globalBlockPos + glm::ivec3(1, 0, 0)) == BlockType::Air) {
		float *buffer = VertexBuffers::GetBuffer(VertexBuffers::MultiRight);
		res.reserve(48 * sizeof(float));
		res.insert(res.end(), buffer, buffer + 48);
	}
	//? Left face
	if (w->GetBlock(globalBlockPos + glm::ivec3(-1, 0, 0)) == BlockType::Air) {
		float *buffer = VertexBuffers::GetBuffer(VertexBuffers::MultiLeft);
		res.reserve(48 * sizeof(float));
		res.insert(res.end(), buffer, buffer + 48);
	}
	//? Top face
	if (w->GetBlock(globalBlockPos + glm::ivec3(0, 1, 0)) == BlockType::Air) {
		float *buffer = VertexBuffers::GetBuffer(VertexBuffers::MultiTop);
		res.reserve(48 * sizeof(float));
		res.insert(res.end(), buffer, buffer + 48);
	}
	//? Bottom face
	if (w->GetBlock(globalBlockPos + glm::ivec3(0, -1, 0)) == BlockType::Air) {
		float *buffer = VertexBuffers::GetBuffer(VertexBuffers::MultiBottom);
		res.reserve(48 * sizeof(float));
		res.insert(res.end(), buffer, buffer + 48);
	}
	//? Front face
	if (w->GetBlock(globalBlockPos + glm::ivec3(0, 0, 1)) == BlockType::Air) {
		float *buffer = VertexBuffers::GetBuffer(VertexBuffers::MultiFront);
		res.reserve(48 * sizeof(float));
		res.insert(res.end(), buffer, buffer + 48);
	}
	//? Back face
	if (w->GetBlock(globalBlockPos + glm::ivec3(0, 0, -1)) == BlockType::Air) {
		float *buffer = VertexBuffers::GetBuffer(VertexBuffers::MultiBack);
		res.reserve(48 * sizeof(float));
		res.insert(res.end(), buffer, buffer + 48);
	}
	return res;
}

std::vector<float> Shard::GenerateFlower(World* w, glm::ivec3 globalBlockPos, const glm::ivec3 localBlockPos) {
	std::vector<float> res = std::vector<float>();
	float *buffer = VertexBuffers::GetBuffer(VertexBuffers::Flower);
	res.reserve(96 * sizeof(float));
	res.insert(res.end(), buffer, buffer + 48);
	return res;
}
