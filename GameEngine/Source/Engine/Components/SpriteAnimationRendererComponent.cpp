#include "pch.h"
#include "SpriteAnimationRendererComponent.h"

#include "Engine.h"
#include "Renderer/TexFrames.h"

namespace sr {
	FACTORY_REGISTER(SpriteAnimationRendererComponent);

	void SpriteAnimationRendererComponent::Update(float dt)
	{
		m_frameTimer += dt;
		float frameTime = 1.0f / m_fps;
		while (m_frameTimer >= frameTime) {
			
			m_frame++;

			if (m_loop) { 
				m_frame = m_frame % m_texFrames->GetTotalFrames(); 
			} else {
				if (m_frame >= m_texFrames->GetTotalFrames() - 1) {
					m_frame = m_texFrames->GetTotalFrames() - 1;
				}
			}

			m_frameTimer -= frameTime;
		}

		
	}

	void SpriteAnimationRendererComponent::Draw(const Renderer& renderer)
	{
		if (!m_texFrames) return;

		auto transform = GetOwner()->GetTransform();

		renderer.DrawTexture(*m_texFrames->GetTexture(), m_texFrames->GetFrameRect(m_frame), transform);
	}
	void SpriteAnimationRendererComponent::Read(const json::value_t& value)
	{
		RendererComponent::Read(value);

		sr::json::Read(value, "fps", m_fps, true);
		JSON_READ_NAME(value, "loop", m_loop);

		std::string texFrameName;
		JSON_READ_NAME_REQ(value, "tex_frames", texFrameName);

		if (!texFrameName.empty()) {
			m_texFrames = Resources().Get<TexFrames>(texFrameName, Engine::Get().GetRenderer());
		}
	}
}