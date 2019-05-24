#pragma once
#include <string>

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#pragma warning(pop)

struct SDL_Texture;

namespace meow {

	class Texture2D
	{
	public:
		explicit Texture2D(const std::string& path);
		virtual ~Texture2D();

		virtual void Render(const glm::mat4x4& transformationMatrix);
		const glm::vec2& GetDimensions() const { return m_Dimensions; }

	protected:
		SDL_Texture* m_pTexture;
		glm::vec2 m_Dimensions;
		GLuint m_Id;
	};
}
