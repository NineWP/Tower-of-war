#pragma once
#include "Monsters.h"
using namespace sf;
int createBackGround(VertexArray& rVA, IntRect arena);
Monsters* createHorde(int numMonsters, IntRect arena);