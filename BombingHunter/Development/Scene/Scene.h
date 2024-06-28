#pragma once

#include <vector>
#include <string>
#include "../Objects/GameObject.h"

#define WINDOW_MAX_WIDTH (960)	//����ʃT�C�Y
#define WINDOW_MAX_HEIGHT (720)	//�c��ʃT�C�Y

class Scene
{
private:
	std::vector<GameObject*> objects;
	int BackgroundImage;	//�w�i�摜
	int BackgroundMusic;	//�w�i���y
	float PLocX;	//�v���C���[��x���W���擾����ϐ�
	float PLocY;	//�v���C���[��y���W���擾����ϐ�
	float ELocX;	//�G��x���W���擾����ϐ�
	float ELocY;	//�G��y���W���擾����ϐ�
	int enemy_spawn_rate;	//�G����������܂ł̃t���[���𐔂���ϐ�
	int bullet_spawn_rate;	//�e����������܂ł̃t���[���𐔂���ϐ�

public:
	Scene();
	~Scene();

	void Initialize();
	void Update();
	void Draw() const;
	void Finalize();

	//�����_���Ȑ��l�𐶐����鏈��
	int CreateRandNum(int r_num);

	//�G�𐶐����鏈��
	void EnemySpawn();
	//�{���𐶐����鏈��
	void BombSpawn();
	//�e�𐶐����鏈��
	void BulletSpawn();
	//�I�u�W�F�N�g���폜���鏈��
	void DeleteObject();
	

private:
	//�����蔻��`�F�b�N����
	void HitCheckObject(GameObject* a, GameObject* b);

	//�I�u�W�F�N�g��������
	template <class T>
	T* CreateObject(const Vector2D& location)
	{
		//�w�肵���N���X�𐶐�����
		T* new_instance = new T();
		//GameObject�N���X���p�����Ă��邩�m�F
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//�G���[�`�F�b�N
		if (new_object == nullptr)
		{
			delete new_instance;
			throw std::string("�Q�[���I�u�W�F�N�g����������܂���ł���");
		}

		//�������̐ݒ�
		new_object->SetLocation(location);
		
		//����������
		new_object->Initialize();
		

		//�I�u�W�F�N�g���X�g�ɒǉ�
		objects.push_back(new_object);

		//�C���X�^���X�̃|�C���^��ԋp
		return new_instance;
	}
};