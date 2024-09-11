#pragma once
#include "Vector2.h"

#define ROWS 100 // 最大行
#define COLS 100 // 最大列


struct CornerPosition
{
	Vector2  topLeft;
	Vector2  topRight;
	Vector2  bottomLeft;
	Vector2  bottomRight;

	Vector2I itiTopLeft;
	Vector2I itiTopRight;
	Vector2I itiBottomLeft;
	Vector2I itiBottomRight;

};

struct Player {
	Vector2 pos;
	Vector2 prePos;
	Vector2 velocity;
	Vector2 acceleration;
	float speed;
	float tempSpeed; 
	bool JumpFlag;
};

struct Info
{

	bool upFlag;
	bool bottomFlag;
	bool wallFlag;

};

enum BlockType {

	kBlank,
	kBlock,
};
