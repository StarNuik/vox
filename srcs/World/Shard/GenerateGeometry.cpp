#include "Types.h"
#include "World/Shard.h"
#include "World/World.h"
#include "Render/VertexBuffers.h"
#include "Utilities/Profiler.h"

#include "World/Block.h"

void Shard::AddSide(std::vector<float>& res, glm::ivec3 local, glm::ivec3 global, glm::ivec3 offset, VertexBuffers::BufferType side, World* w) {
	Block block;
	local += offset;
	if (local.x > 15 or local.y > 15 or local.z > 15 or local.x < 0 or local.y < 0 or local.z < 0)
		block = w->GetBlock(global + offset);
	else
		block = _blocks[local.x][local.y][local.z];
	if (block.IsTransparent() or block.IsFlower()) {
		float *buffer = VertexBuffers::GetBuffer(side);
		res.reserve(48 * sizeof(float));
		res.insert(res.end(), buffer, buffer + 48);
	}
};

void Shard::AddSideTransparent(std::vector<float>& res, glm::ivec3 local, glm::ivec3 global, glm::ivec3 offset, VertexBuffers::BufferType side, World* w, Block b) {
	Block block;
	local += offset;
	if (local.x > 15 or local.y > 15 or local.z > 15 or local.x < 0 or local.y < 0 or local.z < 0)
		block = w->GetBlock(global + offset);
	else
		block = _blocks[local.x][local.y][local.z];
	if (block.IsTransparent() and block != b) {
		std::vector<float> buffer;
		buffer = VertexBuffers::GetVectorBuffer(side);
		res.insert(res.end(), buffer.begin(), buffer.end());
	}
};

void Shard::AddSideWater(std::vector<float>& res, glm::ivec3 local, glm::ivec3 global, glm::ivec3 offset, VertexBuffers::BufferType side, VertexBuffers::BufferType sideLow, World* w) {
	Block block;
	Block upBlock;

	local += offset;
	if (local.x > 15 or local.y > 15 or local.z > 15 or local.x < 0 or local.y < 0 or local.z < 0)
		block = w->GetBlock(global + offset);
	else
		block = _blocks[local.x][local.y][local.z];
	local += -offset + glm::ivec3(0, 1, 0);
	if (local.y > 15)
		upBlock = w->GetBlock(global + offset);
	else
		upBlock = _blocks[local.x][local.y][local.z];
	if ((block.IsTransparent() or block.IsFlower()) and !block.IsWater()) {
		std::vector<float> buffer;
		if (upBlock.IsWater()) {
			buffer = VertexBuffers::GetVectorBuffer(side);
			res.insert(res.end(), buffer.begin(), buffer.end());
		} else {
			buffer = VertexBuffers::GetVectorBuffer(sideLow);
			res.insert(res.end(), buffer.begin(), buffer.end());
		}
	}
};

std::vector<float> Shard::GenerateWater(World* w, const glm::ivec3 globalP, const glm::ivec3 localP) {
	std::vector<float> res = std::vector<float>();

	AddSideWater(res, localP, globalP, glm::ivec3(1, 0, 0), VertexBuffers::Right, VertexBuffers::WaterRight, w);
	AddSideWater(res, localP, globalP, glm::ivec3(-1, 0, 0), VertexBuffers::Left, VertexBuffers::WaterLeft, w);
	AddSideWater(res, localP, globalP, glm::ivec3(0, 1, 0), VertexBuffers::Top, VertexBuffers::WaterTop, w);
	AddSideWater(res, localP, globalP, glm::ivec3(0, 0, 1), VertexBuffers::Front, VertexBuffers::WaterFront, w);
	AddSideWater(res, localP, globalP, glm::ivec3(0, 0, -1), VertexBuffers::Back, VertexBuffers::WaterBack, w);
	AddSideTransparent(res, localP, globalP, glm::ivec3(0, -1, 0), VertexBuffers::Bottom, w, Block::Water);

	res.shrink_to_fit();
	return res;
}

std::vector<float> Shard::GenerateTransparent(World* w, const glm::ivec3 globalP, const glm::ivec3 localP, const Block block) {
	std::vector<float> res = std::vector<float>();

	AddSideTransparent(res, localP, globalP, glm::ivec3(1, 0, 0), VertexBuffers::Right, w, block);
	AddSideTransparent(res, localP, globalP, glm::ivec3(-1, 0, 0), VertexBuffers::Left, w, block);
	AddSideTransparent(res, localP, globalP, glm::ivec3(0, 1, 0), VertexBuffers::Top, w, block);
	AddSideTransparent(res, localP, globalP, glm::ivec3(0, -1, 0), VertexBuffers::Bottom, w, block);
	AddSideTransparent(res, localP, globalP, glm::ivec3(0, 0, 1), VertexBuffers::Front, w, block);
	AddSideTransparent(res, localP, globalP, glm::ivec3(0, 0, -1), VertexBuffers::Back, w, block);

	res.shrink_to_fit();
	return res;
}

std::vector<float> Shard::GenerateBlock(World* w, const glm::ivec3 globalP, const glm::ivec3 localP) {
	std::vector<float> res = std::vector<float>();

	AddSide(res, localP, globalP, glm::ivec3(1, 0, 0), VertexBuffers::Right, w);
	AddSide(res, localP, globalP, glm::ivec3(-1, 0, 0), VertexBuffers::Left, w);
	AddSide(res, localP, globalP, glm::ivec3(0, 1, 0), VertexBuffers::Top, w);
	AddSide(res, localP, globalP, glm::ivec3(0, -1, 0), VertexBuffers::Bottom, w);
	AddSide(res, localP, globalP, glm::ivec3(0, 0, 1), VertexBuffers::Front, w);
	AddSide(res, localP, globalP, glm::ivec3(0, 0, -1), VertexBuffers::Back, w);
	return res;
}

std::vector<float> Shard::GenerateMultisideBlock(World* w, const glm::ivec3 globalBlockPos, const glm::ivec3 localBlockPos) {
	std::vector<float> res = std::vector<float>();

	AddSide(res, localBlockPos, globalBlockPos, glm::ivec3(1, 0, 0), VertexBuffers::MultiRight, w);
	AddSide(res, localBlockPos, globalBlockPos, glm::ivec3(-1, 0, 0), VertexBuffers::MultiLeft, w);
	AddSide(res, localBlockPos, globalBlockPos, glm::ivec3(0, 1, 0), VertexBuffers::MultiTop, w);
	AddSide(res, localBlockPos, globalBlockPos, glm::ivec3(0, -1, 0), VertexBuffers::MultiBottom, w);
	AddSide(res, localBlockPos, globalBlockPos, glm::ivec3(0, 0, 1), VertexBuffers::MultiFront, w);
	AddSide(res, localBlockPos, globalBlockPos, glm::ivec3(0, 0, -1), VertexBuffers::MultiBack, w);
	return res;
}

std::vector<float> Shard::GenerateFlower() {
	// std::vector<float> res = std::vector<float>();
	// float *buffer = VertexBuffers::GetBuffer(VertexBuffers::Flower);
	// res.reserve(96 * sizeof(float));
	// res.insert(res.end(), buffer, buffer + 96);
	return VertexBuffers::GetVectorBuffer(VertexBuffers::Flower);
}

std::vector<float> Shard::GenerateCactus() {
	// std::vector<float> res = std::vector<float>();
	// float *buffer = VertexBuffers::GetBuffer(VertexBuffers::Cactus);
	// res.reserve(288 * sizeof(float));
	// res.insert(res.end(), buffer, buffer + 288);
	return VertexBuffers::GetVectorBuffer(VertexBuffers::Cactus);
}
