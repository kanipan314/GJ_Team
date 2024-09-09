#include "Player.h"

void Player::Initialize()
{
	position_ = { 100,100 };
	prePostion_ = { 0.0 };
	speed_ = 0.0f;
	tempSpeed_ = 15.0f;
}

void Player::Update()
{
	CornerPosition Corner = {
		{position_.x + position_.x / 2.0f - 2.0f,position_.y + position_.y / 2.0f - 2.0f},
		{position_.x - position_.x / 2.0f - 2.0f,position_.y + position_.y / 2.0f - 2.0f},
		{position_.x + position_.x / 2.0f - 2.0f,position_.y - position_.y / 2.0f - 2.0f},
		{position_.x - position_.x / 2.0f - 2.0f,position_.y - position_.y / 2.0f - 2.0f}
	};

	speed_ = 0;

	prePostion_.x = position_.x;
	prePostion_.y = position_.y;

}

void Player::Draw()
{
	Novice::DrawEllipse((int)Corner_.topLeft.x, (int)Corner_.topLeft.y, 2, 2, 0.0f, GREEN, kFillModeSolid);
	Novice::DrawBox((int)position_.x, (int)position_.y, 16, 16, 0.0f, RED,kFillModeSolid);

}

void Player::MoveD()
{
	Corner_.topRight.x = (Corner_.topRight.x + speed_);
	Corner_.bottomRight.x = (Corner_.bottomRight.x + speed_);
	if (map_[(int)Corner_.topRight.y / 16][(int)Corner_.topRight.x / 16] == kBlank &&
		map_[(int)Corner_.bottomRight.y / 16][(int)Corner_.bottomRight.x / 16] == kBlank) {

		speed_ += tempSpeed_;
		position_.x += speed_;
	}
	else {
		position_.x -= speed_;
	}


}

void Player::MoveA()
{
	Corner_.topLeft.x = (Corner_.topLeft.x + speed_);
	Corner_.bottomLeft.x = (Corner_.bottomLeft.x + speed_);
	if (map_[(int)Corner_.topLeft.y / 16][(int)Corner_.topLeft.x / 16] == kBlank &&
		map_[(int)Corner_.bottomLeft.y / 16][(int)Corner_.bottomLeft.x / 16] == kBlank) {
		position_.x -= speed_;
	}
	else {
		position_.x += speed_;
	}

}

void Player::MoveSpace()
{



}

void Player::SetMapChip(const char* filename, int map[ROWS][COLS], int* rowCount)
{

	FILE* mapFile;
	int row = 0, col = 0;
	errno_t err;
	char buffer[1024];
	char* context = NULL;

	//ファイルを開く
	err = fopen_s(&mapFile, filename, "r");
	if (mapFile == NULL) {
		printf("ファイルエラー");
		return;
	}

	//ファイルの読み込み

	while (fgets(buffer, sizeof(buffer), mapFile) && row < ROWS) {
		col = 0;
		char* token = strtok_s(buffer, ",", &context);
		while (token != NULL && col < COLS) {
			map[row][col] = atoi(token);  // トークンを整数に変換して配列に格納
			token = strtok_s(NULL, ",", &context);
			col++;
		}
		row++;
	}

	fclose(mapFile);
	*rowCount = row;

}
