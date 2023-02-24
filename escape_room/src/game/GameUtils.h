#pragma once

#include "game/Game.h"
#include "game/game_object/GameObject.h"
#define MAX_PICK_DIST 2.5f

bool CheckDistanceLimit(GameObject& ob1, GameObject& ob2);

void DrawTime();

std::string TwoDigitsFormat(unsigned int n);