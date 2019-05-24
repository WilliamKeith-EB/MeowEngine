#ifndef PCH_H
#define PCH_H

// TODO: add headers that you want to pre-compile here
#include <stdio.h>
#include <iostream>
#include <tchar.h>
#include <vector>
#include <string>
#include <assert.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// OpenGL libs
#pragma comment (lib,"opengl32.lib")
#pragma comment (lib,"Glu32.lib")

#pragma comment(lib, "xinput.lib")

#include <SDL.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>
#include <SDL_image.h>
#include <SDL_ttf.h> 
#include <SDL_mixer.h> 

#include <Xinput.h>

#include "Locator.h"
#include "SceneManager.h"
#include "Time.h"
#include "Logger.h"
#include "InputHandler.h"
#include "Scene.h"
#include "GameObject.h"
#include "Components.h"
#include "StackAllocator.h"
#include "ConfigLoader.h"
#include "Texture2D.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#pragma warning(pop)

#endif //PCH_H
