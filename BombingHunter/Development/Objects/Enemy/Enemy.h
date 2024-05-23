#pragma once

#include "../GameObject.h"

#define ANIM_MIN (2)
#define ANIM_MAX (5)

class Enemy : public GameObject
{
private:
	int animation[5];		//�A�j���[�V�����摜
	int animation_count;	//�A�j���[�V��������
	Vector2D direction;		//�i�s����

	

	//���ׂĂ�Enemy�̉摜�̕ϐ�
	int E_Box[ANIM_MIN];
	int E_Fly[ANIM_MIN];
	int E_Metal[ANIM_MAX];
	int E_Harpy[ANIM_MIN];

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