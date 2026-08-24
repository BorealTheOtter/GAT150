#include "pch.h"
#include "Game.h"
#include "Scene.h"

namespace sr {
	void Game::Update(float dt, float width, float height){
		m_scene->Update(dt, width, height);
	}

	void Game::Draw(const Renderer& renderer){
		m_scene->Draw(renderer);
	}
}
