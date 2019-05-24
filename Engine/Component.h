#pragma once

namespace meow {

	class GameObject;

	class Component
	{
	public:
		Component() = default;
		virtual ~Component() = default;

		virtual void Update() = 0;

		void AddToGameObject(GameObject* pGameObject);
		GameObject* GetGameObject() const { return m_pGameObject; }

	protected:
		GameObject* m_pGameObject;
	};

}