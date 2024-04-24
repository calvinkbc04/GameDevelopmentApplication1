#pragma once

#include "../Utility/Vector2D.h"

class Player
{
private:
	Vector2D location;
	Vector2D direction;
	float radius;

public:
	Player();
	Player(float x, float y);
	Player(Vector2D location);
	~Player();

	void Update();		//�X�V����
	void Draw() const;	//�`�揈��

	void SetLocation(float x, float y);		//���W�ݒu
	void SetLocation(Vector2D location);	//���W�ݒu
	Vector2D GetLocation() const;			//���W�擾
	float GetRadius();						//�傫��

private:
	void Movement();	//�ړ�����
};