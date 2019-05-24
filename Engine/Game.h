#pragma once

namespace meow {

	class Game
	{
	public:
		Game() = default;
		virtual ~Game() = default;

		virtual void LoadGame() = 0;
	};

}
