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
�v���C���[���甭�˂����e�̃A�N�^�[
*/
class EnemyBulletActor : public Actor
{
public:
	virtual ~EnemyBulletActor() = default;
	virtual void Update(float deltaTime) override;
};

/*
�v���C���[���甭�˂����e�̃A�N�^�[
*/
class BulletActor : public Actor
{
public:
	virtual ~BulletActor() = default;
	virtual void Update(float deltaTime) override;
};

/*
���C���Q�[�����
*/
class MainGameScene : public Scene
{
public:
	MainGameScene() = default;
	virtual ~MainGameScene() = default;

	virtual bool Initialize() override;    //��ʂ̕\���ɕK�v�ȃf�[�^����������
	virtual void ProcessInput() override;  //���͂��󂯂ē�����Ԃ�ݒ肷��
	virtual void Update() override;        //�v���O�����̏�Ԃ��X�V����
	virtual void Render() override;        //���f���̕\���Ȃǂ��s��
	virtual void Finalize() override;      //Initialize�֐��ŏ��������f�[�^��j������
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
	
	//���\���p�e�N�X�`��
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
	
	//�v���C���[�̃J�����ʒu�ƒ����_
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

	//�Q�X�g�̃J�����ʒu�ƒ����_
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
	

	//�v���C���[
	PlayerActor player;
	std::vector<Actor*> myplayer;
	GuestActor guest;
	ZombieActor zombie;
	ZombieActor* zombies;
	ZombieActor* zombies2[4];
	std::vector<Actor*> enemies;
	
	//��
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

	//�e
	std::vector<Actor*> playerBullets;
	std::vector<Actor*> guestBullets;
	std::vector<Actor*> enemyBullets;
	
	std::mt19937 random;

	//�Q�[�����
	//�񋓌^
	enum class State
	{
		play,        //�ʏ�v���C��
		pouse,
		stageClear,  //�X�e�[�W�N���A
		gameOver,    //�Q�[���I�[�o�[
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
	float Gravity = 1.2f;  //�d��
	float jumpPower = 0;
	float accel = 0;
	float jumpTime;
	float interval = 0;
	float gameinterval = 0;
	float guestinterval = 0;
	float playerStan = 0;
	float guestStan = 0;
	const float speed = 30.0f; //�e�̈ړ����x(m/�b)
	const float enemyBulletSpeed = 20.0f;
	float playerBulletTimer = 0;
	float guestBulletTimer = 0;
	float zombieBulletTimer = 0;
	float enemySpeed = 1.0f; //�]���r�̈ړ����x
	int popCount = 4; //�����ɔ�������]���r�̍ő吔
	int enemyTotal = 4; //�G�̑���
	int enemyLeft = 4;  //���o��̓G�̐��B�G���o�������邽�тɌ������Ă���
	int tutorialFlag = 0;
	float tutorialTimer = 0;
};

#endif //MAINGAMESCENE_H_INCLUDED