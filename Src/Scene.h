#pragma once
/*
@file Scene.h
*/
#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED
#include<string>

/*
�V�[���̊��N���X
*/
class Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;

	//�h���N���X�ŕK����`���Ȃ���΂Ȃ�Ȃ�
	virtual bool Initialize() = 0;
	virtual void ProcessInput() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Finalize() = 0;

	//�V�[���؂�ւ��p�̊֐�
	const std::string& NextScene() const
	{
		return nextscene;
	}
	void NextScene(const char* name)
	{
		nextscene = name;
	}

private:
	std::string nextscene;
};

#endif // !SCENE_H_INCLUDED
