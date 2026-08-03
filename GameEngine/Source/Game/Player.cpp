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
            BulletDesc bd;
            bd.name = "Bullet";
            bd.tag = "PlayerBullet";
            bd.model = assets::bulletModel;
            bd.transform = m_transform;
            bd.speed = 800.0f;
            bd.damping = 1.0f;
            bd.lifespan = 3.0f;

            Bullet* bullet = new Bullet(bd);
            m_scene->AddActor(bullet);

            sr::Engine::Get().GetAudio().PlaySound("shoot");
        }

            sr::Particle particle;
            particle.position = m_transform.pos;
            particle.rotation = m_transform.rotation + sr::RandomFloat(-20.0f, 20.0f);
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
