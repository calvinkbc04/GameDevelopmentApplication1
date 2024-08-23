#pragma once
#include "../EnemyMoveStateBase.h"

class MoveRightState : public EnemyMoveStateBase
{
public:
	//�R���X�g���N�^
	MoveRightState(class Enemy* e);

	//�f�X�g���N�^
	virtual ~MoveRightState();

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