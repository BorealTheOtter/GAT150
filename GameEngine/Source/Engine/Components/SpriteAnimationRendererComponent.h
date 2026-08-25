#pragma once
#include "SpriteRendererComponent.h"

namespace sr {
	class SpriteAnimationRendererComponent : public SpriteRendererComponent {
	public:
		CLASS_PROTOTYPE(SpriteAnimationRendererComponent);

		void Update(float dt) override;
		void Draw(const class Renderer& renderer) override;
		void Read(const json::value_t& value) override;

	private:
		float m_fps = 0;
		float m_frameTimer = 0;
		bool m_loop = true;

		unsigned int m_frame;
		res_t<class TexFrames> m_texFrames;
	};
}