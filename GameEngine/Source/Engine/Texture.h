#pragma once
#include "Vector2.h"

#include <SDL3_image/SDL_image.h>
#include <string>
#include <iostream>

struct SDL_Texture;

namespace sr {
	class Texture
	{
	public:
		Texture() = default;
		~Texture();

		bool Load(const std::string& filename, class Renderer& renderer);

		Vector2 GetSize();

		

	private:
		friend class Renderer;
		SDL_Texture* m_texture{ nullptr };
	};
}