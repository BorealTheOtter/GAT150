#include "pch.h"
#include "Renderer.h"
#include "Texture.h"
#include "MathUtils.h"
#include <SDL3/SDL.h>

#include <iostream>

namespace sr
{
    bool Renderer::Initialize(const char* name, int width, int height)
    {
		m_width = width;
		m_height = height;

        SDL_Init(SDL_INIT_VIDEO);

        if (!TTF_Init()) {
            std::cerr << "TTF_Init Error: " << SDL_GetError() << std::endl;
            return false;
        }

        m_window = SDL_CreateWindow(name, width, height, 0);
        if (m_window == nullptr) {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return false;
        }

        m_renderer = SDL_CreateRenderer(m_window, NULL);
        if (m_renderer == nullptr) {
            std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            return false;
        }

		SDL_SetRenderVSync(m_renderer, 1);

        return true;
    }

    void Renderer::SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const
    {
        SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
    }

    void Renderer::SetColor(float r, float g, float b, float a) const
    {
		SDL_SetRenderDrawColorFloat(m_renderer, r, g, b, a);
    }

    void Renderer::SetColor(const Vector3& v, float a) const
    {
        SDL_SetRenderDrawColorFloat(m_renderer, v.r, v.g, v.b, a);
    }

	void Renderer::Clear() const
	{
		SDL_RenderClear(m_renderer);
	}

    void Renderer::DrawPoint(float x, float y) const
    {
        SDL_RenderPoint(m_renderer, x, y);
    }

    void Renderer::DrawFillRect(float x, float y, float width, float height) const
    {
        SDL_FRect rect{ x, y, width, height };
        SDL_RenderFillRect(m_renderer, &rect);
    }

    void Renderer::DrawRect(float x, float y, float width, float height) const
    {
		SDL_FRect rect{ x, y, width, height };
		SDL_RenderRect(m_renderer, &rect);
	
    }

    void Renderer::DrawLine(float x1, float y1, float x2, float y2) const
    {
		SDL_RenderLine( m_renderer, x1, y1, x2, y2 );
    }

    void Renderer::DrawModel(const Model& m, const Transform& t) const
    {
        for (auto mesh : m.GetMeshes()) {


            SetColor(mesh.GetColor());

            auto& points = mesh.GetPoints();

            for (size_t i = 0; i + 1 < points.size(); i++)
            {
                Vector2 v1 = points[i];
                Vector2 v2 = points[i + 1];

                v1 *= t.scale;
                v2 *= t.scale;

                v1 = v1.Rotate(t.rotation * math::DEG_TO_RAD);
                v2 = v2.Rotate(t.rotation * math::DEG_TO_RAD);


                v1 += t.pos;
                v2 += t.pos;

                DrawLine(v1.x, v1.y, v2.x, v2.y);
            }

        }
    }

    void Renderer::DrawTexture(Texture* texture, float x, float y)
    {
        Vector2 size = texture->GetSize();

            SDL_FRect destRect;
        destRect.x = x;
        destRect.y = y;
        destRect.w = texture->GetSize().x;
        destRect.h = texture->GetSize().y;

        // https://wiki.libsdl.org/SDL3/SDL_RenderTexture
        SDL_RenderTexture(m_renderer, texture->m_texture, NULL, &destRect);
    }



    void Renderer::Present() const
    {
        SDL_RenderPresent(m_renderer);
    }

    void Renderer::DebugText(float x, float y, const char* text) const
    {
        SDL_RenderDebugText(m_renderer, x, y, text);
    }

    void Renderer::Quit() const
    {
        TTF_Quit();
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }
   
}
