#include "pch.h"
#include "InputHandler.h"

bool meow::InputHandler::ProcessInput() {

	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);

	SDL_Event e;
	while (SDL_PollEvent(&e)) {

		if (e.type == SDL_QUIT) {

			return false;
		}

		// other events
	}

	return true;
}
