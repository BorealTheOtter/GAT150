#pragma once
#include "Actor.h"

struct EnemyDesc : public sr::ActorDesc
{
	float speed = 200.0f;
};
class Enemy : public sr::Actor
{
public:
	Enemy() = default;
	Enemy(EnemyDesc ed) :Actor{ ed }, m_speed{ ed.speed } {};

	void OnCollision(Actor* other) override;

	void Update(float dt, const float width, const float height) override;
private:
	float m_speed = 200.0f;
};