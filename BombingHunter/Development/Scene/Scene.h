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
	float PLocX;	//�v���C���[��x���W���擾����ϐ�
	float PLocY;	//�v���C���[��y���W���擾����ϐ�
	float ELocX;	//�G��x���W���擾����ϐ�
	float ELocY;	//�G��y���W���擾����ϐ�

public:
	Scene();
	~Scene();

	void Initialize();
	void Update();
	void Draw() const;
	void Finalize();

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