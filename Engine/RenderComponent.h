#pragma once
#include "Texture2D.h"

#define RenderComponentIndex unsigned int

namespace meow {

	class GameObject;

	class RenderComponent_Internal final
	{
		friend class Renderer;
	public:
		explicit RenderComponent_Internal(Texture2D* pTexture);
		~RenderComponent_Internal() = default;

		void AddToGameObject(GameObject* pGameObject);
		void Render();

		void* operator new(size_t size);
		void operator delete(void* ptr);
	private:
		Texture2D* m_pTexture;
		GameObject* m_pGameObject;

	};

	class RenderComponent final {

		friend class GameObject;
		friend class Renderer;

	public:
		explicit RenderComponent(Texture2D* pTexture);
		~RenderComponent() = default;

		void AddToGameObject(GameObject* pGameObject);
		GameObject* GetGameObject() const { return m_pGameObject; }
	private:
		GameObject* m_pGameObject;
		RenderComponentIndex m_RenderComponentIndex;
		RenderComponent_Internal* m_pRenderComponent;

		void SetRenderComponentIndex(RenderComponentIndex index);
	};

}
