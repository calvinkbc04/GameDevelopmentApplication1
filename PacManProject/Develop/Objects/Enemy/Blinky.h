#pragma once

#include "EnemyBase/EnemyBase.h"

class Blinky : public EnemyBase
{
protected:

	std::vector<int> move_animation;		// �ړ��̃A�j���[�V����
	std::vector<int> dead_animation;		// ���S�̃A�j���[�V����
	Vector2D velocity;					// �ړ���
	eEnemyState enemy_state;			// �G�̏��
	eEnemyMoveState now_direction;			// ���ݐi�s�������
	float animation_time;				// �A�j���[�V��������
	int animation_count;				// �A�j���[�V�����Y��
	int state_time;				// ��Ԏ���
	int state_count;			// ��ԓY��
	Vector2D turf_location;			// �꒣��̈ʒu
	Player* player_instance;		// �v���C���[�̏������ϐ�

public:
	Blinky();
	virtual ~Blinky();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

	/// <summary>
	/// �����蔻��ʒm����
	/// </summary>
	/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

public:
	eEnemyState GetEnemyState() const;

protected:
	void GetPlayerInstance(Player*);
	Vector2D SetNearTargetPanel();
	void Movement(float);
	virtual void HouseMovement(float);
	virtual void RestMovement(float);
	virtual void ChaseMovement(float);
	virtual void ScaredMovement(float);
	void DeathMovement(float);

	void AnimationControl(float delta_second);
};