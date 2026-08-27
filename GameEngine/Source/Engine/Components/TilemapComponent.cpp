#include "pch.h"
#include "TilemapComponent.h"
#include "Renderer/Tilemap.h"
#include "Physics/PhysicsBody.h"
#include "Engine.h"

namespace sr {
	FACTORY_REGISTER(TilemapComponent);

	TilemapComponent::TilemapComponent(const TilemapComponent& o)
	{
		m_tilemapName = o.m_tilemapName;
	}

	void TilemapComponent::Start()
	{
		m_tilemap = Resources().Get<Tilemap>(m_tilemapName, Engine::Get().GetRenderer());
	}
	void TilemapComponent::Draw(const Renderer& renderer)
	{
		//
	}
	void TilemapComponent::Read(const json::value_t& value)
	{
		RendererComponent::Read(value);
		JSON_READ_NAME_REQ(value, "tilemap_name", m_tilemapName);
	}
}