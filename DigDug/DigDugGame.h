#pragma once
#include "Game.h"
#include  "MainScene.h"
#include "Locator.h"
#include "SceneManager.h"

class DigDugGame : public Game {

public:

	void LoadGame() override {

		MainScene* mainScene = new MainScene{};

		SCENEMANAGER.AddScene(mainScene);
		SCENEMANAGER.SetSceneActive("Main");
	}
};