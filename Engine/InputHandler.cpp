#include "pch.h"
#include "InputHandler.h"



meow::InputHandler::InputHandler()
	: m_MaxNrOfControllers{ 4 }
	, m_pCurrentStates {} {

	m_pCurrentStates = new XINPUT_STATE[m_MaxNrOfControllers]{};
}

meow::InputHandler::~InputHandler() {

	delete[] m_pCurrentStates;
}

bool meow::InputHandler::ProcessInput() {

	ZeroMemory(m_pCurrentStates, sizeof(XINPUT_STATE) * m_MaxNrOfControllers);

	m_NrOfConnectedControllers = 0;
	for (int i{}; i < m_MaxNrOfControllers; ++i) {

		if (XInputGetState(i, &m_pCurrentStates[i]) == ERROR_SUCCESS) {

			++m_NrOfConnectedControllers;
		}
	}

	SDL_Event e;
	while (SDL_PollEvent(&e)) {

		switch (e.type) {

		case SDL_QUIT:
			return false;

		case SDL_KEYDOWN:
		case SDL_KEYUP:
		case SDL_MOUSEMOTION:
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEWHEEL:
			;
		}
	}

	return true;
}
