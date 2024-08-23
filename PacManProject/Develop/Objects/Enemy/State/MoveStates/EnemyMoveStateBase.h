#pragma once
#include "../Enum/EnemyMoveState.h"

/// <summary>
/// �G�̈ړ���Ԃ̃x�[�X�N���X
/// </summary>
class EnemyMoveStateBase
{
protected:
	//�G���
	class EnemyBase* enemy;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="e">�G�̏��</param>
	EnemyMoveStateBase(class EnemyBase* e) : enemy(e)
	{
	}

	//�f�X�g���N�^
	virtual ~EnemyMoveStateBase() = default;

public:
	//�����������֐�
	virtual void Initialize() = 0;

	//�I�������֐�
	virtual void Finalize() = 0;

	//�X�V�����֐�
	virtual void Update() = 0;

	//�`�揈���֐�
	virtual void Draw() const = 0;

	//�ړ���Ԃ̎擾
	virtual eEnemyMoveState GetState() const = 0;
};