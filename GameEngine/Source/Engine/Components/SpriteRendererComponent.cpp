#include "SpriteRendererComponent.h"
#include "Engine.h"

namespace sr {

	FACTORY_REGISTER(SpriteRendererComponent);

	void SpriteRendererComponent::Draw(const Renderer& renderer){
		renderer.DrawTexture(*m_texture, GetOwner()->GetTransform());
	}

	void SpriteRendererComponent::Read(const json::value_t& value){
		
		Object::Read(value);

		std::string textureName;
		JSON_READ_NAME(value, "texture", textureName);

		if (!textureName.empty()) {
			m_texture = Resources().Get<Texture>(textureName, Engine::Get().GetRenderer());
		}
	}
}
