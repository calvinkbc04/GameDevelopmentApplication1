#pragma once

#include "../Utility/Vector2D.h"

class GameObject
{
protected:
	unsigned int color;	//�F
	Vector2D location;	//���W
	Vector2D box_size;	//�傫��

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
};