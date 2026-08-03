#pragma once
#include "Font.h"

struct SDL_Texture;

namespace sr {
	class Renderer;
	struct Vector3;

	class Text {
	public:
		Text() = default;
		Text(Font* font) : m_font{ font } {}
		~Text();

		bool Create(Renderer& renderer, const std::string& text, const Vector3& color);
		void Draw(Renderer& renderer, float x, float y);

	private:
		Font* m_font{ nullptr };
		SDL_Texture* m_texture{ nullptr };
	};
 }