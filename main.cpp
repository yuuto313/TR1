#include <Novice.h>

const char kWindowTitle[] = "LE2B_04_オザワ_ユウト";

enum Scene {
	sound1,
	sound2,
	sound3,
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Scene scene = sound1;

	int sound[3] = {Novice::LoadAudio("./Resources/1.mp3"),
	                Novice::LoadAudio("./Resources/2.mp3"),
	                Novice::LoadAudio("./Resources/3.mp3")
	};

	int vh[3] = { -1,0,0 };

	float volume[3] = { 0.0f,0.0f,0.0f };

	float soundTimer[3] = {120.f,120.f,0.f};



	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

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

		case sound1:


			volume[0] += 0.001f;

			if (volume[0] >= 0.3f) {
				volume[0] = 0.3f;
				soundTimer[0]--;
			}

			if (soundTimer[0] <= 0.f) {
				//ボリュームを少しずつ下げる
				volume[0] -= 0.005f;
				if (volume[0] <= 0.f) {
					volume[0] = 0.f;
					//次の音楽へ
					vh[1] = -1;
					scene = sound2;

				}

			}

			Novice::SetAudioVolume(vh[0], volume[0]);

			break;
		case sound2:

			volume[1] += 0.002f;

			if (volume[1] >= 1.0f) {
				volume[1] = 1.f;
				soundTimer[1]--;
			}

			if (soundTimer[1] <= 0.f) {
				//タイマーが0以下になったらボリュームを下げる
				volume[1] -= 0.007f;
				if (volume[1] <= 0.3f) {
					volume[1] = 0.3f;
					//次の音楽へ
					vh[2] = -1;
					scene = sound3;
				}
			}

			Novice::SetAudioVolume(vh[1], volume[1]);

			break;
		case sound3:

			volume[1] -= 0.001f;
			if (volume[1] <= 0.f) {
				//ボリュームが0になったら止める
				volume[1] = 0.f;
			}

			volume[2] += 0.002f;
			if (volume[2] >= 1.0f) {
				volume[2] = 1.0f;
			}
			Novice::SetAudioVolume(vh[1], volume[1]);

			Novice::SetAudioVolume(vh[2], volume[2]);
		}
	

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///


		if (Novice::IsPlayingAudio(vh[0] == 0) || vh[0] == -1) {
			vh[0] = Novice::PlayAudio(sound[0], false, volume[0]);

		}
		else if (volume[0] <= 0 && soundTimer[0] == 0) {
			Novice::StopAudio(vh[0]);
		}


		if (Novice::IsPlayingAudio(vh[1] == 0) || vh[1] == -1) {
			vh[1] = Novice::PlayAudio(sound[1], false, volume[1]);
		}
		else if (volume[1] <= 0 && soundTimer[1] == 0) {
			Novice::StopAudio(vh[1]);
		}
	
		if (Novice::IsPlayingAudio(vh[2] == 0) || vh[2] == -1) {
			vh[2] = Novice::PlayAudio(sound[2], false, volume[2]);
		}

		

	
		Novice::ScreenPrintf(0, 0, "%f", soundTimer[0]);
		Novice::ScreenPrintf(0, 20, "%f", volume[0]);

		Novice::ScreenPrintf(0, 50, "%f", soundTimer[1]);
		Novice::ScreenPrintf(0, 70, "%f", volume[1]);

		Novice::ScreenPrintf(0, 100, "%f", volume[2]);

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
