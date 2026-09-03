#include "EnemyController.h"

#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorComponent.h"

#include "Damager.h"

#include "Engine.h"

FACTORY_REGISTER(EnemyController)

void EnemyController::Start(){
	CharacterBase::Start();

	m_physComponent = GetComponent<sr::PhysicsComponent>();
	assert(m_physComponent);
	m_rendererComponent = GetComponent<sr::SpriteAnimatorComponent>();
	assert(m_rendererComponent);
}

void EnemyController::Update(float dt, const float width, const float height){
	float dir = 0.0f;
	sr::Vector2 vel = m_physComponent->GetVelocity();

	switch (m_state)
	{
	case CharacterBase::State::Move:
	{
		auto player = m_scene->GetActorByName<Actor>("Proto_Player");
		if (player) {
			sr::Vector2 pos = m_physComponent->GetPosition();
			sr::Vector2 playerPos = player->GetTransform().pos;

			if (playerPos.x < pos.x) dir = -1.0f;
			else dir = 1.0f;
		}


		if (dir != 0.0f) {
			vel.x = dir * 100.0f;
			m_rendererComponent->Play("run");
			m_rendererComponent->SetFlipH(dir < 0.0f);
		}
		else {
			m_rendererComponent->Play("idle");
		}

	}
	case CharacterBase::State::Attack:
		break;
	case CharacterBase::State::Hit:
	{
		if (m_rendererComponent->IsDone()) {
			m_state = State::Move;
			m_rendererComponent->Play("idle");
		}
		break;
	}
	case CharacterBase::State::Death:
		SetDestroyed();
		break;
	default:
		break;
	}

	m_physComponent->SetVelocity(vel);

CharacterBase::Update(dt, width, height);
}

void EnemyController::OnCollision(sr::Actor * o){
	if (sr::EqualsIgnoreCase(o->GetTag(), "PlayerDamager")) {


		m_state = State::Hit;
		m_rendererComponent->Play("hit");
		Damager* damager = dynamic_cast<Damager*>(o);
		if (damager) {
			m_health -= damager->GetDamage();
		}
		else {
			m_health -= 1.0f;
		}

		if (m_health <= 0) {
			m_state = State::Death;
		}
		o->SetDestroyed();
	}
}

void EnemyController::Read(const sr::json::value_t & value){
	CharacterBase::Read(value);
}
