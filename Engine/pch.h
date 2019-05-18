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

#include "Locator.h"
#include "SceneManager.h"
#include "Time.h"
#include "Logger.h"
#include "InputHandler.h"
#include "Scene.h"
#include "GameObject.h"
#include "Components.h"
#include "StackAllocator.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#pragma warning(pop)

#endif //PCH_H
