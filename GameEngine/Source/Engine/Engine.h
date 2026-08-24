#pragma once

#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Random.h"
#include "Math/MathUtils.h"
#include "Math/Transform.h"
#include "StringUtils.h"

#include "Input.h"
#include "Renderer.h"
#include "EngineTime.h"
#include "Actor.h"
#include "Scene.h"
#include "File.h"
#include "Audio.h"
#include "Text.h"
#include "Texture.h"
#include "ParticleSystem.h"
#include "ResourceManager.h"
#include "Json.h"
#include "Factory.h"
#include "Physics/Physics.h"

#include "Game.h"

#include <iostream>
#include <vector>

namespace sr {
	class Engine {
	public:
		static Engine& Get() { static Engine engine{ Vector2{1920,1080} }; return engine; }

		bool Initialize();
		void Shutdown();

		void Update();

		Input& GetInput() { return m_input; }
		Renderer& GetRenderer() { return m_renderer; }
		Time& GetTime() { return m_time; }
		Audio& GetAudio() { return m_audio; }
		ParticleSystem& GetPS() { return m_particleSystem; }
		Physics& GetPhysics() { return m_physics; }

		void SetScreen(const Vector2& v) { m_screen = v; }
		const Vector2& GetScreen() const { return m_screen; }

		Engine(const Engine&) = delete;
		Engine& operator = (const Engine&) = delete;
	private:
		Engine(Vector2 v) : m_screen{ v } {};
		Engine() = default;
	private:
		Input m_input;
		Renderer m_renderer;
		Audio m_audio;
		ParticleSystem m_particleSystem;
		Physics m_physics;

		Time m_time;
		Vector2 m_screen{ 640,480 };

	};
}