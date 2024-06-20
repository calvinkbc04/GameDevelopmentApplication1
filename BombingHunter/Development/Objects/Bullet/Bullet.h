#pragma once

#include "../GameObject.h"


class Bullet : public GameObject
{
	int animation[4];		//�A�j���[�V�����摜
	int animation_count;	//�A�j���[�V��������
	int bullet_rate;
	int flip_flag;			//���]�t���O
	Vector2D direction;		//�i�s����

public:
	Bullet();
	~Bullet();

	virtual void Initialize() override;		//����������
	virtual void Update() override;			//�X�V����
	virtual void Draw() const override;		//�`�揈��
	virtual void Finalize() override;		//�I��������

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;
	//�I�u�W�F�N�g�^�C�v���擾���鏈��
	float GetObjectType();

private:
	//�ړ�����
	void Movement();
	//�A�j���[�V��������
	void AnimationControl();

private:

	//���ׂĂ�Enemy�̉摜�̓ǂݍ��ݏ���
	void LoadImages();
	//���ׂĂ�Enemy�̉摜�̍폜����
	void UnloadImages();

public:

	bool CheckTypeAndFrameCnt();
};