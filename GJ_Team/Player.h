#pragma once
#include "Vector2.h"
#include "Module.h"
#include <Novice.h>
#include <stdlib.h>
#include <stdio.h>

class Player
{
public:

	void Initialize();

	void Update();

	void Draw();

	void MoveD();

	void MoveA();

	void MoveSpace();

	void SetMapChip(const char* filename, int map[ROWS][COLS], int* rowCount);

private:

	int map_[ROWS][COLS];

	Vector2 position_;
	Vector2 prePostion_;
	Vector2 velocity_;
	float speed_;
	float tempSpeed_;

	CornerPosition Corner_ = {};

};

