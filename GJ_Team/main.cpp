#include <Novice.h>
#include "Vector2.h"
#include "Module.h"
//#include "Player.h"
#include <stdlib.h>
#include <stdio.h>
#include "imgui.h"

#define ROWS 100 // 最大行
#define COLS 100 // 最大列


const char kWindowTitle[] = "学籍番号";

void LoadMap(const char* filename, int map[ROWS][COLS], int* rowCount);
void Collision(Info& info);

// シーン
enum Scene { Title, Stage, GameClear, GameOver };

// サウンド
enum Sound { TitleBGM, StageBGM, GameClearBGM, GameOverBGM };

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// シーン
	Scene scene = Title;

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
		{0,0},
		{0,0},
		{0,0},
		{0,0}
	};

	postion.itiTopLeft = { (int)postion.topLeft.x / BlockSize,(int)postion.topLeft.y / BlockSize };
	postion.itiTopRight = { (int)postion.topRight.x / BlockSize,(int)postion.topRight.y / BlockSize };
	postion.itiBottomLeft = { (int)postion.bottomLeft.x / BlockSize ,(int)postion.bottomLeft.y / BlockSize };
	postion.itiBottomRight = { (int)postion.bottomRight.x / BlockSize ,(int)postion.bottomRight.y / BlockSize };

	//マップサイズ
	int map[ROWS][COLS];
	int rowCount;

	//タイトル移動
	int moveText = 0;

	//テクスチャ関連
	int BlockTexture = Novice::LoadTexture("./Resource/Block.png");
	int Toumei = Novice::LoadTexture("./Resource/transparent.png");
	int Title_background = Novice::LoadTexture("./Resource/Title.png");
	int Title_text = Novice::LoadTexture("./Resource/TitleText.png");

	//mapに情報を格納
	LoadMap("./Resource/MapData.txt", map, &rowCount);

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

		switch (scene) {
			//--------------------------------------------------------------------------------------------------------
		case Title: // タイトル //
			// 音
			//sound = TitleBGM;
			
			moveText -= 15;

			if (moveText <= -1280) {
				moveText = 1280;
			}

			// Enterを押したらステージへ
			if (scene == Title && keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				scene = Stage;
				// 各変数の初期化
				//
				//
			}

			break;
			//----------タイトルの更新終了------------------------------------------------------------------------------


		case Stage: // ステージ // 

			// 音
			//sound = StageBGM;

			// プレイ中の処理
			//
			//
			//

#pragma region プレイヤーの移動処理

			player.speed = 0;

			player.prePos.x = player.pos.x;
			player.prePos.y = player.pos.y;

			if (keys[DIK_D]) {

				postion.topLeft.x = postion.topLeft.x - player.speed;
				postion.bottomLeft.x = postion.bottomLeft.x - player.speed;
				postion.topRight.x = postion.topRight.x - player.speed;
				postion.bottomRight.x = postion.bottomRight.x - player.speed;

				if (map[(int)postion.topRight.y / BlockSize][(int)postion.topRight.x / BlockSize] == 0 ||
					map[(int)postion.bottomRight.y / BlockSize][(int)postion.bottomRight.x / BlockSize] == 0) {

					player.speed += player.tempSpeed;
					player.pos.x += player.speed;

				}
				else if (map[(int)postion.topRight.y / BlockSize][(int)postion.topRight.x / BlockSize] == 1 &&
					map[(int)postion.bottomRight.y / BlockSize][(int)postion.bottomRight.x / BlockSize] == 1) {

					player.speed -= player.tempSpeed + 0.25f;
					player.pos.x += player.speed;

				}

				postion.topLeft.x = postion.topLeft.x + player.speed;
				postion.bottomLeft.x = postion.bottomLeft.x + player.speed;
				postion.topRight.x = postion.topRight.x + player.speed;
				postion.bottomRight.x = postion.bottomRight.x + player.speed;
			}

			if (keys[DIK_A]) {
				postion.topLeft.x = postion.topLeft.x + player.speed;
				postion.bottomLeft.x = postion.bottomLeft.x + player.speed;
				postion.topRight.x = postion.topRight.x + player.speed;
				postion.bottomRight.x = postion.bottomRight.x + player.speed;

				if (map[(int)postion.topLeft.y / BlockSize][(int)postion.topLeft.x / BlockSize] == 0 ||
					map[(int)postion.bottomLeft.y / BlockSize][(int)postion.bottomLeft.x / BlockSize] == 0) {

					player.speed += player.tempSpeed;
					player.pos.x -= player.speed;

				}
				else if (map[(int)postion.topLeft.y / BlockSize][(int)postion.topLeft.x / BlockSize] == 1 &&
					map[(int)postion.bottomLeft.y / BlockSize][(int)postion.bottomLeft.x / BlockSize] == 1) {

					player.speed -= player.tempSpeed + 0.25f;
					player.pos.x -= player.speed;

				}

				postion.topLeft.x = postion.topLeft.x - player.speed;
				postion.bottomLeft.x = postion.bottomLeft.x - player.speed;
				postion.topRight.x = postion.topRight.x - player.speed;
				postion.bottomRight.x = postion.bottomRight.x - player.speed;
			}

			player.tempSpeed = 5;

			if (map[(int)postion.bottomLeft.y / BlockSize][(int)postion.bottomLeft.x / BlockSize] == 0 &&
				map[(int)postion.bottomRight.y / BlockSize][(int)postion.bottomRight.x / BlockSize] == 0) {

				player.JumpFlag = 0;

			}

			//重力
			if (map[(int)postion.bottomLeft.y / BlockSize][(int)postion.bottomLeft.x / BlockSize] == 0 &&
				map[(int)postion.bottomRight.y / BlockSize][(int)postion.bottomRight.x / BlockSize] == 0) {

				player.speed = -3.8f;
				player.pos.y -= player.speed;

				postion.topLeft.y = postion.topLeft.y - player.speed;
				postion.bottomLeft.y = postion.bottomLeft.y - player.speed;
				postion.topRight.y = postion.topRight.y - player.speed;
				postion.bottomRight.y = postion.bottomRight.y - player.speed;
			}

			//ジャンプ
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] &&
				(map[(int)postion.bottomLeft.y / BlockSize][(int)postion.bottomLeft.x / BlockSize] == 1 ||
					map[(int)postion.bottomRight.y / BlockSize][(int)postion.bottomRight.x / BlockSize] == 1)) {

				player.velocity.y = 15.0f;
				player.JumpFlag = 1;

			}
			if (player.JumpFlag == 1) {
				player.velocity.y += player.acceleration.y;

				if (player.velocity.y >= 15.0f) {
					player.velocity.y = 15.0f;
				}

				postion.topLeft.y = postion.topLeft.y - player.velocity.y;
				postion.topRight.y = postion.topRight.y - player.velocity.y;
				postion.bottomLeft.y = postion.bottomLeft.y - player.velocity.y;
				postion.bottomRight.y = postion.bottomRight.y - player.velocity.y;

				if (map[(int)postion.topLeft.y / BlockSize][(int)postion.topLeft.x / BlockSize] == 1 ||
					map[(int)postion.topRight.y / BlockSize][(int)postion.topRight.x / BlockSize] == 1) {


					player.pos.y += player.velocity.y;
				}
				/*else if (map[(int)postion.bottomLeft.y / BlockSize][(int)postion.bottomLeft.x / BlockSize] == 0 &&
					map[(int)postion.bottomRight.y / BlockSize][(int)postion.bottomRight.x / BlockSize] == 0) {

					player.velocity.y = 0;
					player.JumpFlag = false;
					player.pos.y -= player.velocity.y;

				}*/

				postion.topLeft.y = postion.topLeft.y + player.velocity.y;
				postion.topRight.y = postion.topRight.y + player.velocity.y;
				postion.bottomLeft.y = postion.bottomLeft.y + player.velocity.y;
				postion.bottomRight.y = postion.bottomRight.y + player.velocity.y;
			}
#pragma endregion

#pragma region 敵の処理



#pragma endregion


#pragma region ライトの処理

			


#pragma endregion


			break;
			//----------ステージの更新終了------------------------------------------------------------------------------


		case GameClear: // ゲームクリア //
			//音
			//sound = GameClearBGM;

			// Enterを押したらタイトルへ
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				scene = Title;
			}

			break;
			//----------ゲームクリアの更新終了--------------------------------------------------------------------------


		case GameOver: // ゲームオーバー //
			//音
			//sound = GameOverBGM;

			// Enterを押したらタイトルへ
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				scene = Title;
			}

			break;
			//----------ゲームオーバーの更新終了------------------------------------------------------------------------

		}



		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		TitleText

		switch (scene) {

		case Title: // タイトル //
			// 背景
			//Novice::DrawSprite(0, 0, titleTex, 1, 1, 0.0f, WHITE);
		
			Novice::DrawSprite(0, 0, Title_background, 1, 1, 0.0f, WHITE);
			Novice::DrawSprite(moveText, 106, Title_text, 1, 1, 0.0f, WHITE);

			break;
			//----------タイトルの描画処理終了---------------------------------------------------------------------------

		case Stage: // ステージ //
			// 背景
			//

#pragma region map描画

			//描画
			for (int i = 0; i < rowCount; i++) {
				for (int j = 0; j < COLS; j++) {

					if (map[j][i] == kBlock) {

						Novice::DrawSprite(16 * i, 16 * j, BlockTexture, 1, 1, 0.0f, WHITE);

					}

					Novice::DrawBox(16 * i, 16 * j, 16, 16, 0.0f, WHITE, kFillModeWireFrame);

				}
			}

#pragma endregion

#pragma region 敵の描画



#pragma endregion

#pragma region ライトの描画

			Novice::DrawBox(0, 0, 1280, 720, 0.0, BLACK, kFillModeSolid);
			Novice::SetBlendMode(BlendMode::kBlendModeNormal);

			Novice::DrawSprite((int)(player.pos.x / 2), (int)( player.pos.y / 2), Toumei, 1, 1, 0.0f, WHITE);

#pragma endregion

#pragma region プレイヤー描画

			Novice::DrawEllipse((int)player.pos.x, (int)player.pos.y, 8, 8, 0.0, RED, kFillModeSolid);

			Novice::DrawEllipse(postion.itiTopLeft.x, postion.itiTopLeft.y, 4, 4, 0.0, RED, kFillModeSolid);
			Novice::DrawEllipse(postion.itiTopRight.x, postion.itiTopRight.y, 4, 4, 0.0, RED, kFillModeSolid);
			Novice::DrawEllipse(postion.itiBottomLeft.x, postion.itiBottomLeft.y, 4, 4, 0.0, RED, kFillModeSolid);
			Novice::DrawEllipse(postion.itiBottomRight.x, postion.itiBottomRight.y, 4, 4, 0.0, RED, kFillModeSolid);


#pragma endregion



			// その他描画
			//
			//

			break;
			//----------ステージの描画処理終了---------------------------------------------------------------------------

		case GameClear: // ゲームクリア //
			// 背景
			//Novice::DrawSprite(0, 0, gameClearTex, 1, 1, 0.0f, WHITE);

			break;
			//----------ゲームクリアの描画処理終了-----------------------------------------------------------------------



		case GameOver: // ゲームオーバー //
			// 背景
			//Novice::DrawSprite(0, 0, gameOverTex, 1, 1, 0.0f, WHITE);

			break;
			//----------ゲームオーバーの描画処理終了----------------------------------------------------------------------

		}

		

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

void LoadMap(const char* filename, int map[ROWS][COLS], int* rowCount) {

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

//void Collision(Info &info)
//{
//
//
//
//}
