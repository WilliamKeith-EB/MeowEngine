#pragma once
#include <Xinput.h>

class InputHandler {

public:
	InputHandler() = default;
	virtual ~InputHandler() = default;

	InputHandler(const InputHandler& other) = delete;
	InputHandler(InputHandler&& other) noexcept = delete;
	InputHandler operator=(const InputHandler& other) = delete;
	InputHandler operator=(InputHandler&& other) noexcept = delete;

	virtual bool ProcessInput();

protected:
	XINPUT_STATE m_CurrentState{};
};

