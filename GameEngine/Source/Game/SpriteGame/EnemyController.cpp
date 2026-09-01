#include "EnemyController.h"

#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorComponent.h"

#include "Engine.h"

FACTORY_REGISTER(EnemyController)

void EnemyController::Start(){
	Actor::Start();

	m_physComponent = GetComponent<sr::PhysicsComponent>();
	assert(m_physComponent);
	m_rendererComponent = GetComponent<sr::SpriteAnimatorComponent>();
	assert(m_rendererComponent);
}

void EnemyController::Update(float dt, const float width, const float height){
	float dir = 0.0f;
	sr::Vector2 vel = m_physComponent->GetVelocity();

	auto player = m_scene->GetActorByName<Actor>("Proto_Player");
	if (player) {
		sr::Vector2 pos = m_physComponent->GetPosition();
		sr::Vector2 playerPos = player->GetTransform().pos;

		if (playerPos.x < pos.x) dir = -1.0f;
		else dir = 1.0f;
		}


	if (dir != 0.0f) {
		vel.x = dir * 200.0f;
		m_rendererComponent->Play("run");
		m_rendererComponent->SetFlipH(dir < 0.0f);
	}
	else {
		m_rendererComponent->Play("idle");
	}
	
	m_physComponent->SetVelocity(vel);

	Actor::Update(dt, width, height);
}

void EnemyController::OnCollision(sr::Actor * o){

}

void EnemyController::Read(const sr::json::value_t & value){
	Actor::Read(value);
}
