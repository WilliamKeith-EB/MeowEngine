#include "pch.h"
#pragma comment(lib, "xinput.lib")

#include <vld.h>
#include <SDL.h>
#include "Engine.h"
#include "DigDugGame.h"

#pragma warning( push )
#pragma warning(disable : 4100)
int main(int argc, char* argv[]) {
#pragma warning( pop )

	meow::Engine engine{};
	DigDugGame* pGame = new DigDugGame{};

	engine.Run(pGame);

	delete pGame;

	return 0;
}