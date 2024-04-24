#pragma once

#define D_KEYCODE_MAX (256)

class InputControl
{
private:
	static char now_key[D_KEYCODE_MAX];	//今のフレームの入力値
	static char old_key[D_KEYCODE_MAX];	//前のフレームの入力値

public:
	static void Update();	//更新処理

	//キー入力取得処理
	static bool GetKey(int key_code);		//押しているキー
	static bool GetKeyDown(int key_code);	//押した瞬間
	static bool GetKeyUp(int key_code);		//離した瞬間

private:
	static bool CheckKeyCodeRange(int key_code);	//キー配列範囲チェック
};