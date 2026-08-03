#pragma once
#include "Actor.h"

struct PlayerDesc : public sr::ActorDesc 
{
	float speed = 200.0f;
};
	class Player : public sr::Actor
	{
	public:
		Player() = default;
		Player(const PlayerDesc& pd) : Actor{ pd }, m_speed{ pd.speed } {};
		Player(const sr::Transform& t) : Actor{ t } {}
		Player(const sr::Transform& t, const sr::Model& m) : Actor{ t, m } {}
		Player(const sr::Transform& t, const sr::Model& m, float s) : Actor{ t, m }, m_speed{s} {}

		void Update(float dt, const float width, const float height) override;

		void OnCollision(Actor* other) override;
	private:
		float m_speed = 200.0f;
	};