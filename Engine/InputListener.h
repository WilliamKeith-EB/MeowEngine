#pragma once

namespace meow {

	class InputListener
	{
	public:
		InputListener(int controllerNumber = -1);
		~InputListener();

	protected:
		int m_ControllerNumber; // -1 is listening to all controllers
	};
}