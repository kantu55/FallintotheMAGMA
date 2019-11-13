#pragma once
/*
@file MainGameScene.h
*/
#ifndef MAINGAMESCENE_H_INCLUDED
#define MAINGAMESCENE_H_INCLUDED
#include "GLFWEW.h"
#include "Texture.h"
#include "Shader.h"
#include "MeshList.h"
#include "Scene.h"
#include "Actor.h"
#include "Audio.h"
#include <vector>
#include <random>


class PlayerActor : public Actor
{
public:
	virtual ~PlayerActor() = default;
	virtual void Update(float deltaTime) override;
};

class GuestActor : public Actor
{
public:
	virtual ~GuestActor() = default;
	virtual void Update(float deltaTime) override;
};

class ZombieActor : public Actor
{
public:
	virtual ~ZombieActor() = default;
	virtual void Update(float deltaTime) override;

	float baseSpeed = 1.0f;
};

class ObjectActor : public Actor
{
public:
	virtual ~ObjectActor() = default;
	virtual void Update(float deltaTime) override;
};

class FloorActor : public Actor
{
public:
	virtual ~FloorActor() = default;
	//virtual void Update(float deltaTime) override;
};

/*
プレイヤーから発射される弾のアクター
*/
class EnemyBulletActor : public Actor
{
public:
	virtual ~EnemyBulletActor() = default;
	virtual void Update(float deltaTime) override;
};

/*
プレイヤーから発射される弾のアクター
*/
class BulletActor : public Actor
{
public:
	virtual ~BulletActor() = default;
	virtual void Update(float deltaTime) override;
};

/*
メインゲーム画面
*/
class MainGameScene : public Scene
{
public:
	MainGameScene() = default;
	virtual ~MainGameScene() = default;

	virtual bool Initialize() override;    //画面の表示に必要なデータを準備する
	virtual void ProcessInput() override;  //入力を受けて内部状態を設定する
	virtual void Update() override;        //プログラムの状態を更新する
	virtual void Render() override;        //モデルの表示などを行う
	virtual void Finalize() override;      //Initialize関数で準備したデータを破棄する
	void RenderLoad();
	float BulletLoad(Actor*, Actor, float);
	void FixCollision(Actor&, Actor&);

private:
	MeshList meshList;

	Texture::Image2D texId;
	Texture::Image2D texId2;
	Texture::Image2D texHuman;
	Texture::Image2D texGround;
	Texture::Image2D texBullet;
	Texture::Image2D texMagma;
	Texture::Image2D texZombie;
	
	//情報表示用テクスチャ
	Texture::Image2D texPlayerWin;
	Texture::Image2D texGuestWin;
	Texture::Image2D texNumber[10];
	Texture::Image2D texNum;
	Texture::Image2D texReload;
	Texture::Image2D texBord;
	Texture::Image2D texStan;
	Texture::Image2D texPouse;
	Texture::Image2D texPlayer;
	Texture::Image2D texGuest;
	Texture::Image2D texDirPlayer;
	Texture::Image2D texDirGuest;
	Texture::Image2D texTitle_B;
	Texture::Image2D texTitle_Y;
	Texture::Image2D texRetry_B;
	Texture::Image2D texRetry_Y;


	Shader::Program progSimple;
	Shader::Program progLighting;
	Shader::Program progLightingGuest;
	Shader::LightList lights;
	
	Audio::EngineRef audio = Audio::Engine::Instance();
	Audio::SoundPtr Mainbgm;
	Audio::SoundPtr Bulletbgm;
	Audio::SoundPtr Stanbgm;
	Audio::SoundPtr Hitbgm;
	Audio::SoundPtr Overbgm;
	Audio::SoundPtr Enterbgm;
	Audio::SoundPtr Menubgm;

	float angleY = 0;
	float mMaxForwardpeed;

	int viewHeight = 1280;
	int viewWidth = 720;
	
	//プレイヤーのカメラ位置と注視点
	glm::vec3 viewPos;
	glm::vec3 targetPos;
	glm::vec3 viewoffset;
	glm::vec3 targetoffset;
	glm::vec3 vCamera;
	glm::vec3 vTraget;
	glm::vec3 vCameraTraget;
	glm::vec3 vTragetoffset;
	glm::vec3 cameraVelocity;
	glm::vec3 TragetVelocity;

	//ゲストのカメラ位置と注視点
	glm::vec3 g_viewPos;
	glm::vec3 g_targetPos;
	glm::vec3 g_viewoffset;
	glm::vec3 g_targetoffset;
	glm::vec3 g_vCamera;
	glm::vec3 g_vTraget;
	glm::vec3 g_vCameraTraget;
	glm::vec3 g_vTragetoffset;
	glm::vec3 g_cameraVelocity;
	glm::vec3 g_TragetVelocity;

	glm::vec3 p_Min;
	glm::vec3 p_Max;
	glm::vec3 h_Min;
	glm::vec3 h_Max;
	glm::vec3 f_Max;
	glm::vec3 f_Min;

	glm::vec3 FirePos= glm::vec3(0,1.0f,0);

	glm::vec3 mousePos;
	glm::vec2 mouseAngles;

	glm::vec3 enemyPos[4] = 
	{
		glm::vec3(-10,0,-10),
		glm::vec3(-10,0,10),
		glm::vec3(10,0,-10),
		glm::vec3(10,0,10)
	};
	glm::vec3 enemyRot[4] =
	{
		glm::vec3(0),
		glm::vec3(0),
		glm::vec3(0),
		glm::vec3(0)
	};
	
	double mousex;
	double mousey;
	

	//プレイヤー
	PlayerActor player;
	std::vector<Actor*> myplayer;
	GuestActor guest;
	ZombieActor zombie;
	ZombieActor* zombies;
	ZombieActor* zombies2[4];
	std::vector<Actor*> enemies;
	
	//床
	Actor floor;
	Actor deathFloor;
	Actor house;
	Actor playerDirection;
	glm::vec3 p_dir;
	glm::vec3 p_dirOffset;
	glm::vec3 p_dirVeloctiy;
	glm::vec3 p_dirTarget;
	Actor guestDirection;
	glm::vec3 g_dir;
	glm::vec3 g_dirOffset;
	glm::vec3 g_dirVeloctiy;
	glm::vec3 g_dirTarget;

	//弾
	std::vector<Actor*> playerBullets;
	std::vector<Actor*> guestBullets;
	std::vector<Actor*> enemyBullets;
	
	std::mt19937 random;

	//ゲーム状態
	//列挙型
	enum class State
	{
		play,        //通常プレイ中
		pouse,
		stageClear,  //ステージクリア
		gameOver,    //ゲームオーバー
	};
	State state = State::play;
	enum class GameOver
	{
		title,
		retry
	};
	GameOver over = GameOver::title;

	bool jumpFlg = false;
	int jump = 0;
	float Gravity = 1.2f;  //重力
	float jumpPower = 0;
	float accel = 0;
	float jumpTime;
	float interval = 0;
	float gameinterval = 0;
	float guestinterval = 0;
	float playerStan = 0;
	float guestStan = 0;
	const float speed = 30.0f; //弾の移動速度(m/秒)
	const float enemyBulletSpeed = 20.0f;
	float playerBulletTimer = 0;
	float guestBulletTimer = 0;
	float zombieBulletTimer = 0;
	float enemySpeed = 1.0f; //ゾンビの移動速度
	int popCount = 4; //同時に発生するゾンビの最大数
	int enemyTotal = 4; //敵の総数
	int enemyLeft = 4;  //未登場の敵の数。敵を出現させるたびに減少していく
	int tutorialFlag = 0;
	float tutorialTimer = 0;
};

#endif //MAINGAMESCENE_H_INCLUDED