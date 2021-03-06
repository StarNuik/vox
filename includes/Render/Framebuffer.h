#pragma once

#include <glm/glm.hpp>

#include "Types.h"

class Framebuffer {
public:
	Framebuffer();
	~Framebuffer();
	void NewBloom(glm::ivec2 bufferSize);
	void NewColor(glm::ivec2 bufferSize);
	void NewShadow(glm::ivec2 bufferSize);
	void Bind();
	void Use();
	void Unbind();
	void Resize(glm::ivec2 newSize);
	Texture* GetColorTexture();
	Texture* GetColorTexture(int);
	Texture* GetDepthTexture();
	uint GetId();
private:
	bool _ready;
	uint _fbo;
	Texture* _color0;
	Texture* _color1;
	Texture* _depth;
};