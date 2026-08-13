#include "pch.h"
#include "Actor.h"
#include "Renderer.h"
#include "MathUtils.h"
#include "Texture.h"
#include "Engine.h"

namespace sr
{
	void Actor::Update(float dt, const float width, const float height)
	{
		if (m_lifespan != -1.0f) {
			if (m_destroyed) {
				m_lifespan = 0.0f;
			}
			m_lifespan -= dt;
			m_destroyed = (m_lifespan <= 0.0f);
		}

		m_transform.pos += (m_velocity * dt);
		m_velocity *= (1.0f / (1.0f + m_damping * dt));

		m_transform.pos.x = math::Wrap(m_transform.pos.x, 0.0f, width);
		m_transform.pos.y = math::Wrap(m_transform.pos.y, 0.0f, height);
	}

	void Actor::Draw(const Renderer& renderer) const {
		
		if (m_model) {
			renderer.DrawModel(*m_model, m_transform);
		}
		if (m_texture) {
			renderer.DrawTexture(*m_texture, m_transform);
		}

	}
	float Actor::GetRadius() const
	{
			if(m_model) return m_model.get()->GetRadius() * m_transform.scale * 0.6f;
			if (m_texture) return (m_texture->GetSize().Length() * 0.5f) * 0.6f;

			return 0.0f;
	}
	void Actor::Read(const json::value_t& value)
	{
		Object::Read(value);
		
		std::string textureName;
		JSON_READ_NAME(value, "texture", textureName);
		
		if (!textureName.empty()) {
			m_texture = Resources().Get<Texture>(textureName, Engine::Get().GetRenderer());
		}
		JSON_READ_NAME(value, "tag", m_tag);
		JSON_READ_NAME(value, "lifespan", m_lifespan);
		JSON_READ_NAME(value, "damping", m_damping);

		if (JSON_HAS_NAME(value, "transform")) {
		m_transform.Read(JSON_GET_NAME(value, "transform"));
		}

	}
}