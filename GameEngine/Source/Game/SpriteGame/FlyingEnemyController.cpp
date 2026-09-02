#include "FlyingEnemyController.h"

#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorComponent.h"

#include "Engine.h"

FACTORY_REGISTER(FlyingEnemyController)

void FlyingEnemyController::Start(){
	Actor::Start();

	m_physComponent = GetComponent<sr::PhysicsComponent>();
	assert(m_physComponent);
	m_rendererComponent = GetComponent<sr::SpriteAnimatorComponent>();
	assert(m_rendererComponent);
}

void FlyingEnemyController::Update(float dt, const float width, const float height){
	sr::Vector2 vel = m_physComponent->GetVelocity();

	auto player = m_scene->GetActorByName<Actor>("Proto_Player");
	if (player) {
		sr::Vector2 pos = m_physComponent->GetPosition();
		sr::Vector2 playerPos = player->GetTransform().pos;

		sr::Vector2 dir = playerPos - pos;

		

		//if (playerPos.x < pos.x) dir = -1.0f;
		//else dir = 1.0f;
		m_rendererComponent->SetFlipH(dir.x < 0.0f);
		m_physComponent->ApplyForce(dir.Normalize() * 800.0f);
		}

	Actor::Update(dt, width, height);
}

void FlyingEnemyController::OnCollision(sr::Actor * o){

}

void FlyingEnemyController::Read(const sr::json::value_t & value){
	CharacterBase::Read(value);
}
