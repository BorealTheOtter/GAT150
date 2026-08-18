#include "Player.h"
#include "Bullet.h"
#include "Assets.h"
#include "SpaceGame.h"
#include "../Engine/Engine.h"

void Player::Update(float dt, const float width, const float height)
{
    {
        sr::Vector2 thrust = { 0.0f, 0.0f };

        float drag = 10.0f;
        if (sr::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_W)) { thrust.y -= m_speed; };
        if (sr::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_S)) { thrust.y += m_speed; };

        if (sr::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) { thrust.x -= m_speed; };
        if (sr::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) { thrust.x += m_speed; };

        sr::Vector2 direction = sr::Engine::Get().GetInput().GetMousePos() - m_transform.pos;
        float rotation = direction.Angle();
        SetRotation(rotation * sr::math::RAD_TO_DEG);

        AddVelocity(thrust * dt);

        if (sr::Engine::Get().GetInput().GetMousePressed(sr::Engine::Get().GetInput().LEFT)) {
            sr::Vector2 b_offset = sr::Vector2{ 1.0f, 0.0f }.Rotate(m_transform.rot * sr::math::DEG_TO_RAD) * 15.0f;

            auto bullet = sr::Factory::Instance().Create<Bullet>("Proto_Bullet");
            bullet->SetTransform(m_transform);
            bullet->SetPosition(bullet->GetTransform().pos + b_offset);
            m_scene->AddActor(std::move(bullet));

            sr::Engine::Get().GetAudio().PlaySound("shoot");
        }

        sr::Vector2 offset = sr::Vector2{ 1.0f, 0.0f }.Rotate(m_transform.rot * sr::math::DEG_TO_RAD) * -15.0f;

            sr::Particle particle;
            particle.position = m_transform.pos + offset;
            particle.rotation = m_transform.rot + sr::RandomFloat(-20.0f, 20.0f);
            particle.color = { sr::RandomFloat(0.9803921569f, 1.0f), sr::RandomFloat(0.1176470588f, 0.9215686275f), 0.1176470588f };
            particle.lifespan = sr::RandomFloat(0.5f, 1.5f);
            particle.active = true;
            particle.velocity = sr::Vector2{ 1.0f,0.0f }.Rotate(particle.rotation * sr::math::DEG_TO_RAD) * sr::RandomFloat(-200.0f, 0.0f);

            sr::Engine::Get().GetPS().AddParticle(particle);
 

        Actor::Update(dt, width, height);
    }

    
}

void Player::OnCollision(Actor* other) {
    if (other->GetTag() == "EnemyShip") {
        SetDestroyed();
        
        for (int i = 0; i < 100; i++)
        {
            sr::Particle particle;
            particle.position = m_transform.pos;
            particle.color = { sr::RandomFloat(0.9803921569f, 1.0f), sr::RandomFloat(0.1176470588f, 0.9215686275f), 0.1176470588f };
            particle.lifespan = sr::RandomFloat(0.5f, 2.0f);
            particle.velocity = { sr::RandomFloat(-600.0f, 600.0f), sr::RandomFloat(-600.0f, 600.0f) };

            sr::Engine::Get().GetPS().AddParticle(particle);
        }
        sr::Engine::Get().GetAudio().PlaySound("explosion");
        ((SpaceGame*)m_scene->GetGame())->SetGameState(SpaceGame::GameState::Dead);
    }
}

void Player::Read(const sr::json::value_t& value)
{
    Actor::Read(value);
    JSON_READ_NAME(value, "speed", m_speed);
}
