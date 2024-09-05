#include <Novice.h>

const char kWindowTitle[] = "6001_タイトル";

const int kWindowWidth = 1280; // 横幅
const int kWindowHeight = 720; // 縦幅

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// シーン
	enum Scene { Title, Stage, GameClear, GameOver };

	//// サウンド
	//enum Sound { TitleBGM, StageBGM, GameClearBGM, GameOverBGM };


	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);


	// シーン
	Scene scene = Title;
	
	//// テクスチャ読み込み
	//int titleTex = Novice::LoadTexture("./Resources/images/title.png"); //タイトル画面
	//int gameClearTex = Novice::LoadTexture("./Resources/images/GameClear.png"); //ゲームクリア画面
	//int gameOverTex = Novice::LoadTexture("./Resources/images/GameOver.png"); //ゲームオーバー画面


	//// サウンド
	//Sound sound = TitleBGM;
	//// サウンド読み込み
	//int soundTitle = Novice::LoadAudio("./Resources/sounds/title.mp3"); //タイトル
	//int soundStage = Novice::LoadAudio("./Resources/sounds/stage.mp3"); //ステージ
	//int soundGameClear = Novice::LoadAudio("./Resources/sounds/clear.mp3"); //クリア
	//int soundGameOver = Novice::LoadAudio("./Resources/sounds/gameover.mp3"); //ゲームオーバー
	//// サウンド初期化
	//int soundTitleP = -1; // タイトル
	//int soundStageP = -1; // ステージ
	//int soundGameClearP = -1; // クリア
	//int soundGameOverP = -1; // ゲームオーバー


	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

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

		////----------↓サウンドの処理↓------------------------------------------------------------------------------
		//switch (sound) {
		//	// タイトル //
		//case TitleBGM:
		//	Novice::StopAudio(soundGameOverP);
		//	Novice::StopAudio(soundGameClearP);
		//	if (Novice::IsPlayingAudio(soundTitleP) == false || soundTitleP == -1) {
		//		soundTitleP = Novice::PlayAudio(soundTitle, true, 1.0f);
		//	}
		//	break;

		//	// ステージ //
		//case StageBGM:
		//	Novice::StopAudio(soundTitleP);
		//	if (Novice::IsPlayingAudio(soundStageP) == false || soundStageP == -1) {
		//		soundStageP = Novice::PlayAudio(soundStage, true, 1.0f);
		//	}
		//	break;

		//	// ゲームクリア //
		//case GameClearBGM:
		//	Novice::StopAudio(soundStageP);
		//	if (Novice::IsPlayingAudio(soundGameClearP) == false || soundGameClearP == -1) {
		//		soundGameClearP = Novice::PlayAudio(soundGameClear, false, 1.0f);
		//	}
		//	break;

		//	// ゲームオーバー //
		//case GameOverBGM:
		//	Novice::StopAudio(soundStageP);
		//	if (Novice::IsPlayingAudio(soundGameOverP) == false || soundGameOverP == -1) {
		//		soundGameOverP = Novice::PlayAudio(soundGameOver, false, 1.0f);
		//	}
		//	break;

		//}
		////----------サウンドの処理終了-------------------------------------------------------------------------------


		//----------↓各シーンの描画処理↓---------------------------------------------------------------------------
		switch (scene) {

		case Title: // タイトル //
			// 背景
			//Novice::DrawSprite(0, 0, titleTex, 1, 1, 0.0f, WHITE);
			Novice::ScreenPrintf(kWindowWidth / 2, kWindowHeight / 2, "PUSH SPACE");

			break;
		//----------タイトルの描画処理終了---------------------------------------------------------------------------

		case Stage: // ステージ //
			// 背景
			//

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
