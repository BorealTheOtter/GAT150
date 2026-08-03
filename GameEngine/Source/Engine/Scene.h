#pragma once
#include <vector>
#include <string>

#include "Actor.h"

namespace sr {
	
	class Scene {
	public:
		void AddActor(Actor* actor);

		void ClearActors();

		void Update(float dt, float width, float height);
		void Draw(const class Renderer& renderer);

		template<typename T>
		T* GetActorByName(const std::string& name);

		void SetGame(class Game* game) { m_game = game; }
		class Game* GetGame() { return m_game; }

	private:
		void UpdateCollisions();
		
	private:
		std::vector<Actor*> m_actors;
		std::vector<Actor*> m_pendingActors;

		class Game* m_game = nullptr;

	};
	
	template<typename T>
	inline T* Scene::GetActorByName(const std::string& name)
	{
		for (auto actor : m_actors) 
		{
			T* actorT = dynamic_cast<T*>(actor);
			if (actorT && actorT->m_name == name) {
				return actorT;
			}
		}
		return nullptr;
	}
}