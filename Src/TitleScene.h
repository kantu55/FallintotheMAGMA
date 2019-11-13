#pragma once
/*
@file TitleScene.h
*/
#ifndef TITLESCENE_H_INCLUDED
#define TITLESCENE_H_INCLUDED
#include "GLFWEW.h"
#include "Texture.h"
#include "Shader.h"
#include "MeshList.h"
#include "Scene.h"
#include "Audio.h"

/*
�^�C�g�����
*/
class TitleScene : public Scene
{
public:
	TitleScene() = default;
	virtual ~TitleScene() = default;

	virtual bool Initialize() override;
	virtual void ProcessInput() override;  //���͂��󂯂ē�����Ԃ�ݒ肷��
	virtual void Update() override;        //�v���O�����̏�Ԃ��X�V����
	virtual void Render() override;        //���f���̕\���Ȃǂ��s��
	virtual void Finalize() override;      //Initialize�֐��ŏ��������f�[�^��j������

	bool IsFinish() const;

private:
	MeshList meshList;

	Texture::Image2D texLogo;
	Texture::Image2D texBackground;
	Texture::Image2D texStart_B;
	Texture::Image2D texOption_B;
	Texture::Image2D texStart_Y;
	Texture::Image2D texOption_Y;
	Texture::Image2D texSousaScene;
	Texture::Image2D texSousa_B;
	Texture::Image2D texSousa_Y;
	Texture::Image2D texTutorial_B;
	Texture::Image2D texTutorial_Y;
	Texture::Image2D texTutorial;
	Texture::Image2D texEnemyTutorial;
	Texture::Image2D texBulletTutorial;

	Shader::Program progSimple;

	Audio::SoundPtr Titlebgm;
	Audio::SoundPtr Enterbgm;
	Audio::SoundPtr Menubgm;
	Audio::SoundPtr Startbgm;
	Audio::EngineRef audio = Audio::Engine::Instance();
	enum class State
	{
		title,
		option,
		sousa,
		tutorial
	};
	State state = State::title;
	enum class Tutorial
	{
		rule,
		enemy,
		bullet
	};
	Tutorial tutorial;

	int SelectFlag;
	int o_SelectFlag;
	float timer;
	bool isFinish;
	bool OpsionFlag = false;
};

#endif // !TITLESCENE_H_INCLUDED


