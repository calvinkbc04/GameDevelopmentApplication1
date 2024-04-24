#pragma once

/*
��Βl�ɕϊ�
�����̐��l���Βl�ɕϊ�����e���v���[�g�֐�

�����@�FT value�@ �ϊ�����l
�߂�l�FT	�ϊ���̒l
*/
template <typename T>
T Abs(T value)
{
	T result;

	if (value > 0)
	{
		result = value;
	}
	else
	{
		result = -value;
	}

	return result;
}


/*
�ő�l��Ԃ��e���v���[�g�֐�
�����Ŏw�肳�ꂽ��̒l�̍ő�l��Ԃ�

�����@�FTa, Tb�@�v�Z�p�f�[�^
�߂�l�FT�@�ő�l
*/
template <typename T>
T Max(T a, T b)
{
	T result;

	if (a < b)
	{
		result = b;
	}
	else
	{
		result = a;
	}

	return result;
}


/*
�ŏ��l��Ԃ��e���v���[�g�֐�
�����Ŏw�肳�ꂽ��̒l�̍ŏ��l��Ԃ�

�����@�FTa, Tb�@�v�Z�p�f�[�^
�߂�l�FT�@�ŏ��l
*/
template <typename T>
T Min(T a, T b)
{
	T result;

	if (a > b)
	{
		result = b;
	}
	else
	{
		result = a;
	}

	return result;
}