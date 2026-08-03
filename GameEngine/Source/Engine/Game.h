#pragma once
#include "Scene.h"

namespace sr {

	class Game
	{
	public:
		Game() = default;
		Game(Scene* scene) : m_scene{ scene } {};

		virtual bool Initialize() { return true; }
		virtual bool Shutdown() { return true; }

		virtual void Update(float dt, float width, float height);
		virtual void Draw(const class Renderer& renderer);

		void SetScene(Scene* scene) { m_scene = scene; }
	protected:
		Scene* m_scene = nullptr;


	};
}