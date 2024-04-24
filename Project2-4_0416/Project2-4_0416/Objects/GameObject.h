#pragma once

#include "../Utility/Vector2D.h"

class GameObject
{
protected:
	unsigned int color;
	Vector2D location;
	Vector2D box_size;

public:
	GameObject();
	virtual ~GameObject();

	virtual void Initialize();	//����������
	virtual void Update();		//�X�V����
	virtual void Draw() const;	//�`�揈��
	virtual void Finalize();	//�f�B�X�g���N�^

public:
	void SetLocation(Vector2D location);	//���W�ݒu
	Vector2D GetLocation() const;			//���W��Ԃ�
	Vector2D GetBoxSize() const;			//�傫����Ԃ�
	Vector2D Teleport();
};