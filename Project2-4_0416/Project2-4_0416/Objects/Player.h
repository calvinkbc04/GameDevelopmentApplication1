#pragma once

#include "GameObject.h"

class Player : public GameObject
{
private:
	
public:
	Player();
	~Player() override;

	void Initialize() override;	//����������
	void Update() override;		//�X�V����
	void Draw() const override;	//�`�揈��
	void Finalize() override;	//�f�B�X�g���N�^


private:
	void Movement();	//�ړ�����
	Vector2D Teleport();
};