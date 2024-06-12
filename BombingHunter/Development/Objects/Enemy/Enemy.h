#pragma once

#include "../GameObject.h"

#define ANIM_MIN (2)
#define ANIM_MAX (5)
#define FLOOR_PATH (600.0f)		//���̂��ʒu���W
#define FLY_PATH_1 (300.0f)		//��ԓG�̂��ʒu���W�P
#define FLY_PATH_2 (450.0f)		//��ԓG�̂��ʒu���W�Q

class Enemy : public GameObject
{
private:
	int animation[5];		//�A�j���[�V�����摜
	int animation_count;	//�A�j���[�V��������
	int image_num;			//��������������ϐ�
	Vector2D direction;		//�i�s����

	//���ׂĂ�Enemy�̉摜�̕ϐ�
	int E_Box[ANIM_MIN];
	int E_Fly[ANIM_MIN];
	int E_Metal[ANIM_MAX];
	int Harpy[ANIM_MIN];

public:
	Enemy();
	~Enemy();

	//����������
	virtual void Initialize() override;
	//�X�V����
	virtual void Update() override;
	//�`�揈��
	virtual void Draw() const override;
	//�I������
	virtual void Finalize() override;
	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	//�ړ�����
	void Movement();
	//�A�j���[�V��������
	void AnimationControl();
	//��������Enemy���擾���鏈��
	void GetSpawnEnemy();

public:

	//���ׂĂ�Enemy�̉摜�̓ǂݍ��ݏ���
	void LoadImages();

	//���ׂĂ�Enemy�̉摜�̍폜����
	void UnloadImages();
};