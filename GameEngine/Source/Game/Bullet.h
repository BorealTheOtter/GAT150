#pragma once
#include "Actor.h"

struct BulletDesc : public sr::ActorDesc
{
	float speed = 200.0f;
};
class Bullet : public sr::Actor
{
public:
	Bullet() = default;
	Bullet(BulletDesc bd) :Actor{ bd }, m_speed{ bd.speed } {};
	Bullet(const sr::Transform& t) : Actor{ t } {}
	Bullet(const sr::Transform& t, const sr::Model& m) : Actor{ t, m } {}
	Bullet(const sr::Transform& t, const sr::Model& m, float s) : Actor{ t, m }, m_speed{ s } {}

	void Update(float dt, const float width, const float height) override;
private:
	float m_speed = 200.0f;
};
