#include <Novice.h>
#include "Vector2.h"
#include "Module.h"
//#include "Player.h"
#include <stdlib.h>
#include <stdio.h>

#define ROWS 100 // 最大行
#define COLS 100 // 最大列


const char kWindowTitle[] = "学籍番号";

void LoadMap(const char *filename,int map[ROWS][COLS],int *rowCount);
void Collision(Info &info);

Player* player_ = new Player();

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 640, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	int BlockSize = 16;

	Player player =
	{
		{60,60},
		{0,0},
		{0.0f,0.0f},
		{0.0f,-0.8f},
		0,
		3,
		false
	};

	CornerPosition postion =
	{
		{player.pos.x - BlockSize / 2 - 2, player.pos.y - BlockSize / 2 - 2},
		{player.pos.x + BlockSize / 2 - 2, player.pos.y - BlockSize / 2 - 2},
		{player.pos.x - BlockSize / 2 - 2, player.pos.y + BlockSize / 2 - 2},
		{player.pos.x + BlockSize / 2 - 2, player.pos.y + BlockSize / 2 - 2},

	};

	int map[ROWS][COLS];
	int rowCount;

	//mapに情報を格納
	LoadMap("./Resource/MapData.txt",map, &rowCount);

	/*player_->Initialize();*/
	
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		player.speed = 0;

		player.prePos.x = player.pos.x;
		player.prePos.y = player.pos.y;

		if (keys[DIK_D]) {

			postion.topLeft.x = (postion.topLeft.x - player.speed);
			postion.bottomLeft.x = (postion.bottomLeft.x - player.speed);
			postion.topRight.x = (postion.topRight.x - player.speed);
			postion.bottomRight.x = (postion.bottomRight.x - player.speed);

			if (map[(int)postion.topRight.y / BlockSize][(int)postion.topRight.x / BlockSize] == 0 &&
				map[(int)postion.bottomRight.y / BlockSize][(int)postion.bottomRight.x / BlockSize] == 0) {

				player.speed += player.tempSpeed;
				player.pos.x += player.speed;

			}
			else if (map[(int)postion.topRight.y / BlockSize][(int)postion.topRight.x / BlockSize] == 1 &&
				map[(int)postion.bottomRight.y / BlockSize][(int)postion.bottomRight.x / BlockSize] == 1) {

				player.speed -= player.tempSpeed + 0.25f;
				player.pos.x += player.speed;
				
			}

			postion.topLeft.x = (postion.topLeft.x + player.speed);
			postion.bottomLeft.x = (postion.bottomLeft.x + player.speed);
			postion.topRight.x = (postion.topRight.x + player.speed);
			postion.bottomRight.x = (postion.bottomRight.x + player.speed);
		}

		if (keys[DIK_A]) {
			postion.topLeft.x = (postion.topLeft.x + player.speed);
			postion.bottomLeft.x = (postion.bottomLeft.x + player.speed);
			postion.topRight.x = (postion.topRight.x + player.speed);
			postion.bottomRight.x = (postion.bottomRight.x + player.speed);

			if (map[(int)postion.topLeft.y / BlockSize][(int)postion.topLeft.x / BlockSize] == 0 &&
				map[(int)postion.bottomLeft.y / BlockSize][(int)postion.bottomLeft.x / BlockSize] == 0) {

				player.speed += player.tempSpeed;
				player.pos.x -= player.speed;

			}
			else if (map[(int)postion.topLeft.y / BlockSize][(int)postion.topLeft.x / BlockSize] == 1 &&
				map[(int)postion.bottomLeft.y / BlockSize][(int)postion.bottomLeft.x / BlockSize] == 1) {

				player.speed -= player.tempSpeed + 0.25f;
				player.pos.x -= player.speed;

			}

			postion.topLeft.x = (postion.topLeft.x - player.speed);
			postion.bottomLeft.x = (postion.bottomLeft.x - player.speed);
			postion.topRight.x = (postion.topRight.x - player.speed);
			postion.bottomRight.x = (postion.bottomRight.x - player.speed);
		}

		player.tempSpeed = 5;

		if (keys[DIK_SPACE]) {

			player.JumpFlag = true;
			player.velocity.y -= 17.0f;

		}

		//上当たり判定
		if (player.JumpFlag) {

			postion.topLeft.y = (postion.topLeft.y - player.speed);
			postion.bottomLeft.y = (postion.bottomLeft.y - player.speed);
			postion.topRight.y = (postion.topRight.y - player.speed);
			postion.bottomRight.y = (postion.bottomRight.y - player.speed);

			if (map[(int)postion.topLeft.y / BlockSize][(int)postion.topLeft.x / BlockSize] == 0 &&
				map[(int)postion.topRight.y / BlockSize][(int)postion.topRight.x / BlockSize] == 0) {

				


			}
			else if (map[(int)postion.topLeft.y / BlockSize][(int)postion.topLeft.x / BlockSize] == 1 &&
				map[(int)postion.topRight.y / BlockSize][(int)postion.topRight.x / BlockSize] == 1) {

				player.velocity.y += 17.0f;

			}

			player.velocity.x += player.acceleration.x;
			player.velocity.y += player.acceleration.y;

			player.pos.x += player.velocity.x;
			player.pos.y += player.velocity.y;

		}
		else {
			postion.topLeft.y = (postion.topLeft.y + player.speed);
			postion.bottomLeft.y = (postion.bottomLeft.y + player.speed);
			postion.topRight.y = (postion.topRight.y + player.speed);
			postion.bottomRight.y = (postion.bottomRight.y + player.speed);

			if (map[(int)postion.bottomLeft.y / BlockSize][(int)postion.bottomLeft.x / BlockSize] == 0 &&
				map[(int)postion.bottomRight.y / BlockSize][(int)postion.bottomRight.x / BlockSize] == 0) {

				player.pos.y += 17.0f;


			}
			else if (map[(int)postion.topLeft.y / BlockSize + 5][(int)postion.topLeft.x / BlockSize] == 1 &&
				map[(int)postion.topRight.y / BlockSize + 5][(int)postion.topRight.x / BlockSize] == 1) {

				player.pos.y += 0.0f;

			}

			postion.topLeft.y = (postion.topLeft.y - player.speed);
			postion.bottomLeft.y = (postion.bottomLeft.y - player.speed);
			postion.topRight.y = (postion.topRight.y - player.speed);
			postion.bottomRight.y = (postion.bottomRight.y - player.speed);
		}

		

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		//描画
		for (int i = 0; i < rowCount; i++) {
			for (int j = 0; j < COLS; j++) {

				if (map[i][j] == kBlock) {

					Novice::DrawBox(j * 16, i * 16, 16, 16, 0.0f, WHITE,kFillModeSolid);

				}

			}
		}

		Novice::DrawEllipse((int)player.pos.x, (int)player.pos.y, 8, 8, 0.0, WHITE, kFillModeSolid);
		
		Novice::DrawEllipse((int)postion.topLeft.x, (int)postion.topLeft.y, 4, 4, 0.0, RED, kFillModeSolid);
		Novice::DrawEllipse((int)postion.topRight.x, (int)postion.topRight.y, 4, 4, 0.0, RED, kFillModeSolid);
		Novice::DrawEllipse((int)postion.bottomLeft.x, (int)postion.bottomLeft.y, 4, 4, 0.0, RED, kFillModeSolid);
		Novice::DrawEllipse((int)postion.bottomRight.x, (int)postion.bottomRight.y, 4, 4, 0.0, RED, kFillModeSolid);


		Novice::ScreenPrintf(150, 400, "upeerleft = [%d]", postion.topLeft.x);
		Novice::ScreenPrintf(280, 400, "[%d]", postion.topLeft.y);
		Novice::ScreenPrintf(400, 400, "upeerrigth = [%d]", postion.topRight.x);
		Novice::ScreenPrintf(580, 400, "[%d]", postion.topRight.y);
		Novice::ScreenPrintf(150, 450, "lowerleft = [%d]", postion.bottomLeft.x);
		Novice::ScreenPrintf(280, 450, "[%d]", postion.bottomLeft.y);
		Novice::ScreenPrintf(400, 450, "lowerleft = [%d]", postion.bottomRight.x);
		Novice::ScreenPrintf(580, 450, "[%d]", postion.bottomRight.y);

		/// 
		/// ↑描画処理ここまで
		///
		
		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

void LoadMap(const char* filename,int map[ROWS][COLS], int* rowCount) {

	FILE* mapFile;
	int row = 0, col = 0;
	errno_t err;
	char buffer[1024];
	char* context = NULL;

	//ファイルを開く
	err = fopen_s(&mapFile,filename, "r");
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

//void Collision(Info &info)
//{
//
//
//
//}
