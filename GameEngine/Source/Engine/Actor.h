#pragma once

#include <string>
#include <memory>


#include "Transform.h"
#include "Model.h"


namespace sr
{
	class Scene;

	struct ActorDesc 
	{
		Transform transform{ Vector2{0, 0}, 0, 1 };
		Vector2 velocity{ 0,0 };
		float damping = 0.0f;
		std::shared_ptr<Model> model;
		std::string name;
		std::string tag;
		float lifespan{ -1.0f };
	};

	class Actor
	{
	public:
		Actor() = default;
		Actor(const ActorDesc& ad) : m_transform{ ad.transform }, m_velocity{ ad.velocity }, m_model{ ad.model }, m_name{ ad.name }, m_tag{ ad.tag }, m_damping{ ad.damping }, m_lifespan{ ad.lifespan } {};

		virtual void Update(float dt, const float width, const float height);
		virtual void Draw(const class Renderer& renderer) const;

		virtual void OnCollision(Actor* other) {}

		const Transform& GetTransform() const { return m_transform; }

		void SetPosition(const Vector2& pos) { m_transform.pos = pos; }
		void SetRotation(float rotation) { m_transform.rotation = rotation; }
		void SetScale(float scale) { m_transform.scale = scale; }

		const Vector2& GetVelocity() const { return m_velocity; }
		void SetVelocity(const Vector2& velocity) { m_velocity = velocity; }
		void AddVelocity(const Vector2& velocity) { m_velocity += velocity; }
		
		const std::string& GetName() const { return m_name; }
		const std::string& GetTag() const { return m_tag; }

		Scene* GetScene() { return m_scene; }

		float GetRadius() const;

		void SetDestroyed(bool destroy = true) { m_destroyed = destroy; }
		bool GetDestroyed() const { return m_destroyed; }

		friend Scene;

	protected:
		std::string m_name;
		std::string m_tag;

		Transform m_transform;
		Vector2 m_velocity{ 0,0 };
		float m_damping = 0.0f;
		float m_lifespan = -1.0f;

		bool m_destroyed = false;

		std::shared_ptr<Model> m_model;
		Scene* m_scene = nullptr;
	};
}