#pragma once

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

namespace meow {

	class InputListener;

	class InputHandler {

	public:
		InputHandler();
		virtual ~InputHandler();

		InputHandler(const InputHandler& other) = delete;
		InputHandler(InputHandler&& other) noexcept = delete;
		InputHandler operator=(const InputHandler& other) = delete;
		InputHandler operator=(InputHandler&& other) noexcept = delete;

		virtual bool ProcessInput();

		int GetNumberOfConnectedControllers() const { return m_NrOfConnectedControllers; }
		const glm::vec2& GetMousePosition() const { return m_MousePosition; }

	protected:
		const int m_MaxNrOfControllers;
		XINPUT_STATE* m_pCurrentStates;
		int m_NrOfConnectedControllers;
		glm::vec2 m_MousePosition;
	};
}