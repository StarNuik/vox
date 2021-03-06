#include <GL/glew.h>

#include "Types.h"
#include "Render/ShadowRenderer.h"
#include "Render/RenderModel.h"
#include "Render/Camera.h"
#include "Render/GLRenderer.h"
#include "Render/Shader.h"
#include "Engine/Game.h"
#include "World/ResourceLoader.h"
#include "Player/Player.h"
#include "World/ResourceLoader.h"
#include "Render/Framebuffer.h"
#include "Render/Texture.h"
#include "Render/Geometry.h"
#include "Render/Material.h"

ShadowRenderer::ShadowRenderer() {
	_shadowFbo = new Framebuffer();
};

void ShadowRenderer::Init(Game* game) {
	_game = game;
	_shader = game->GetResources()->GetShader("Shadow Renderer");
	_player = _game->GetPlayer();
	
	_shadowFbo->NewShadow(glm::ivec2(SHADOWMAP_SIDE, SHADOWMAP_SIDE));	
};

ShadowRenderer::~ShadowRenderer() {
	delete _shadowFbo;
}

void ShadowRenderer::PrepareData(float sunAngle) {
	glm::quat rotation = glm::quat(glm::vec3(glm::radians(sunAngle), 0.f, 0.f));
	glm::vec3 sunDir = glm::vec3(0.f, 0.f, 1.f) * rotation;

	glm::vec3 playerPos = _player->GetPosition();
	_view = glm::lookAt(playerPos + sunDir, playerPos, glm::vec3(0.f, 1.f, 0.f));
	_projection = glm::ortho(-128.f, 128.f, -128.f, 128.f, -128.f, 128.f);
	_lightSpace = _projection * _view;
}

void ShadowRenderer::Render(std::vector<RenderModel*>& rendered) {
	glViewport(0, 0, SHADOWMAP_SIDE, SHADOWMAP_SIDE);

	glEnable(GL_DEPTH_TEST);
	// glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	_shadowFbo->Use();
	glClear(GL_DEPTH_BUFFER_BIT);
	_shader->Use();
	_shader->SetInt("diffuse", 0);
	glActiveTexture(GL_TEXTURE0);
	Material* lastMaterial = nullptr;
	for (RenderModel* model : rendered) {
		model->GetGeometry()->Use();
		Material* material = model->GetMaterial();
		if (material != lastMaterial) {
			glBindTexture(GL_TEXTURE_2D, material->GetDiffuseId());
			lastMaterial = material;
		}
		_shader->SetMatrix4("lightMVP", _lightSpace * model->GetModelMatrix());
		glDrawArrays(GL_TRIANGLES, 0, model->GetPolygonCount() * 3);
	}

	glm::ivec2 winSize = _game->GetRenderer()->GetWindowSize();
	glViewport(0, 0, winSize.x, winSize.y);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
};

void ShadowRenderer::ApplyMap(Shader* shader) {
	glActiveTexture(TEXTURE_SLOT);
	_shadowFbo->GetDepthTexture()->Use();
	shader->SetInt("shadowMap", TEXTURE_SLOT - GL_TEXTURE0);
};

void ShadowRenderer::ApplyLightSpace(Shader* shader) {
	shader->SetMatrix4("lightSpace", _lightSpace);
};

void ShadowRenderer::ApplySelf(Shader* shader) {
	glActiveTexture(TEXTURE_SLOT);
	_shadowFbo->GetDepthTexture()->Use();
	shader->SetInt("shadowMap", TEXTURE_SLOT - GL_TEXTURE0);
	shader->SetMatrix4("lightSpace", _lightSpace);
};

glm::mat4 ShadowRenderer::GetLightSpace() {return _lightSpace;};
