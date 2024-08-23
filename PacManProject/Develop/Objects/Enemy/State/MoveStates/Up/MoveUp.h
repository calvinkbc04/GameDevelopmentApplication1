#pragma once
#include "../EnemyMoveStateBase.h"

class MoveUpState : public EnemyMoveStateBase
{
public:
	//�R���X�g���N�^
	MoveUpState(class Enemy* e);

	//�f�X�g���N�^
	virtual ~MoveUpState();

public:
	//����������
	virtual void Initialize() override;

	//�I������
	virtual void Finalize() override;

	//�X�V����
	virtual void Update() override;

	//�`�揈��
	virtual void Draw() const override;

	//���݂̃X�e�[�g�����擾����
	virtual eEnemyMoveState GetState() const override;
};