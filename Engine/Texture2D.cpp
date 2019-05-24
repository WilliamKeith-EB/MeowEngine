#include "pch.h"
#include "Texture2D.h"


meow::Texture2D::Texture2D(const std::string& path)
{
	SDL_Surface* pSurface = IMG_Load(path.c_str());

	if (pSurface == nullptr)
	{
		LOGGER.LogError(SDL_GetError());
		return;
	}

	m_Dimensions.x = float(pSurface->w);
	m_Dimensions.y = float(pSurface->h);

	GLenum pixelFormat{ GL_RGB };
	switch (pSurface->format->BytesPerPixel)
	{
	case 3:
		if (pSurface->format->Rmask == 0x000000ff)
		{
			pixelFormat = GL_RGB;
		}
		else
		{
			pixelFormat = GL_BGR;
		}
		break;
	case 4:
		if (pSurface->format->Rmask == 0x000000ff)
		{
			pixelFormat = GL_RGBA;
		}
		else
		{
			pixelFormat = GL_BGRA;
		}
		break;
	default:
		LOGGER.LogError("Unknown pixel format, " + std::string(SDL_GetError()));
		return;
	}

	glGenTextures(1, &m_Id);
	glBindTexture(GL_TEXTURE_2D, m_Id);

	GLenum e = glGetError();
	if (e != GL_NO_ERROR)
	{
		LOGGER.LogError("Error binding textures");
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pSurface->w, pSurface->h, 0, pixelFormat, GL_UNSIGNED_BYTE, pSurface->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	SDL_FreeSurface(pSurface);
}


meow::Texture2D::~Texture2D() {

	SDL_DestroyTexture(m_pTexture);
}

void meow::Texture2D::Render(const glm::mat4x4& transformationMatrix) {

	glPushMatrix();

	// do transformation
	glMultMatrixf(&transformationMatrix[0].x);

	// Determine texture coordinates
	float textLeft{ 0.0f };
	float textRight{ 1.0f };
	float textTop{ 0.0f };
	float textBottom{ 1.0f };
	
	// Determine vertex coordinates
	float vertexLeft{ 0.0f };
	float vertexBottom{ 0.0f};
	float vertexRight{ m_Dimensions.x };
	float vertexTop{ m_Dimensions.y };
	
	// Tell openGL which texture we will use
	glBindTexture(GL_TEXTURE_2D, m_Id);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	// Draw
	glEnable(GL_TEXTURE_2D);
	{
		glBegin(GL_QUADS);
		{
			glTexCoord2f(textLeft, textBottom);
			glVertex2f(vertexLeft, vertexBottom);

			glTexCoord2f(textLeft, textTop);
			glVertex2f(vertexLeft, vertexTop);

			glTexCoord2f(textRight, textTop);
			glVertex2f(vertexRight, vertexTop);

			glTexCoord2f(textRight, textBottom);
			glVertex2f(vertexRight, vertexBottom);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}
