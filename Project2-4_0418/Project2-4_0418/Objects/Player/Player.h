#pragma once

#include "../GameObject.h"

class Player : public GameObject
{
private:
	Vector2D velocity;	//�ړ����x

public:
	Player();
	virtual ~Player();

	virtual void Initialize();	//����������
	virtual void Update();		//�X�V����
	virtual void Draw() const;	//�`�揈��
	virtual void Finalize();	//�f�B�X�g���N�^


private:
	void Movement();	//�ړ�����
};