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
	Enemy(const sr::Transform& t) : Actor{ t } {}
	Enemy(const sr::Transform& t, const sr::Model& m) : Actor{ t, m } {}
	Enemy(const sr::Transform& t, const sr::Model& m, float s) : Actor{ t, m }, m_speed{ s } {}

	void OnCollision(Actor* other) override;

	void Update(float dt, const float width, const float height) override;
private:
	float m_speed = 200.0f;
};