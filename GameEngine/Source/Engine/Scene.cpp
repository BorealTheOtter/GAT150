#include "pch.h"
#include "Scene.h"

namespace sr {
	
	void Scene::AddActor(std::unique_ptr<Actor> actor) {
		actor->m_scene = this;
		m_pendingActors.push_back(std::move(actor));
	}

	void Scene::ClearActors()
	{
		m_actors.clear();
	}

	void Scene::Update(float dt,float width, float height)
	{
		for (auto& actor : m_actors)
		{
			actor->Update(dt, width, height);
		}

		std::erase_if(m_actors, [](auto& actor) {return actor->m_destroyed; });

		//m_actors.insert(m_actors.end(), m_pendingActors.begin(), m_pendingActors.end());

		for (auto& actor : m_pendingActors) {
			m_actors.push_back(std::move(actor));
		}

		m_pendingActors.clear();

		UpdateCollisions();
	}

	void Scene::Draw(const Renderer& renderer)
	{
		for (auto& actor : m_actors)
		{
			actor->Draw(renderer);
		}


	}
	void Scene::UpdateCollisions()
	{
		for (auto& actorA : m_actors) {
			for (auto& actorB : m_actors) {
				if (actorA == actorB || actorA->m_destroyed || actorB->m_destroyed) continue;
				
				float distance = (actorA->GetTransform().pos - actorB->GetTransform().pos).Length();
				if (distance <= actorA->GetRadius() + actorB->GetRadius()) {
					actorA->OnCollision(actorB.get());
					actorB->OnCollision(actorA.get());
				}
			}
		}
	}
}
