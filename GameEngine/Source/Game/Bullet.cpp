#include "Bullet.h"
#include "Engine.h"

void Bullet::Update(float dt, const float width, const float height)
{
	sr::Vector2 forward{ 1.0f, 0.0f };
	sr::Vector2 velocity = forward.Rotate(m_transform.rot * sr::math::DEG_TO_RAD) * m_speed;

	//SetVelocity(velocity);

	Actor::Update(dt, width, height);
}

void Bullet::Read(const sr::json::value_t& value)
	{
		Actor::Read(value);
		JSON_READ_NAME(value, "speed", m_speed);
	}
