#include "PlayerController.h"

#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorComponent.h"

#include "Engine.h"

FACTORY_REGISTER(PlayerController)

void PlayerController::Start(){
	Actor::Start();

	m_physComponent = GetComponent<sr::PhysicsComponent>();
	assert(m_physComponent);
	m_rendererComponent = GetComponent<sr::SpriteAnimatorComponent>();
	assert(m_rendererComponent);
}

void PlayerController::Update(float dt, const float width, const float height){
	float dir = 0.0f;
	sr::Vector2 vel = m_physComponent->GetVelocity();

	
	if (sr::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) dir = -1.0f;
	if (sr::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) dir = 1.0f;

	if (sr::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
		vel.y -= 800.0f;
	}


	if (dir != 0.0f) {
		vel.x = dir * 300.0f;
		m_rendererComponent->Play("run");
		m_rendererComponent->SetFlipH(dir < 0.0f);
	}
	else {
		m_rendererComponent->Play("idle");
	}
	
	m_physComponent->SetVelocity(vel);

	sr::Engine::Get().GetRenderer().SetCamera(m_physComponent->GetPosition());

	Actor::Update(dt, width, height);
}

void PlayerController::OnCollision(sr::Actor * o){

}

void PlayerController::Read(const sr::json::value_t & value){
	CharacterBase::Read(value);
}
