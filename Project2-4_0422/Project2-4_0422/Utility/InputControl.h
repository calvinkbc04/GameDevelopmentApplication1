#pragma once

#define D_KEYCODE_MAX (256)

class InputControl
{
private:
	static char now_key[D_KEYCODE_MAX];	//���̃t���[���̓��͒l
	static char old_key[D_KEYCODE_MAX];	//�O�̃t���[���̓��͒l

public:
	static void Update();	//�X�V����

	//�L�[���͎擾����
	static bool GetKey(int key_code);		//�����Ă���L�[
	static bool GetKeyDown(int key_code);	//�������u��
	static bool GetKeyUp(int key_code);		//�������u��

private:
	static bool CheckKeyCodeRange(int key_code);	//�L�[�z��͈̓`�F�b�N
};