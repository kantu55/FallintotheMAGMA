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
タイトル画面
*/
class TitleScene : public Scene
{
public:
	TitleScene() = default;
	virtual ~TitleScene() = default;

	virtual bool Initialize() override;
	virtual void ProcessInput() override;  //入力を受けて内部状態を設定する
	virtual void Update() override;        //プログラムの状態を更新する
	virtual void Render() override;        //モデルの表示などを行う
	virtual void Finalize() override;      //Initialize関数で準備したデータを破棄する

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


