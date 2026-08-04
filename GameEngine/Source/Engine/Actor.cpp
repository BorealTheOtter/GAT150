#include "pch.h"
#include "Actor.h"
#include "Renderer.h"
#include "MathUtils.h"

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

	}
	float Actor::GetRadius() const
	{
			return m_model.get()->GetRadius() * m_transform.scale * 0.6f;
	}
}