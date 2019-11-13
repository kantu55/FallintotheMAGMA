#pragma once
/*
@file Actor.h
*/
#ifndef ACTOR_H_INCLUDED
#define ACTOR_H_INCLUDED
#include <GL\glew.h>
#include "Shader.h"
#include "MeshList.h"
#include <glm\vec3.hpp>
#include <vector>
#include <functional>

/*
直方体
*/
struct Rect
{
	glm::vec3 origin;
	glm::vec3 size;
};

/*
シーンに配置するオブジェクト
*/
class Actor
{
public:
	Actor() = default;
	//virtual...仮想関数。サブクラスに実装された、メンバ関数が実行されています。
	virtual ~Actor() = default;

	void Initialize(int mesh, GLuint tex, int hp,
		const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale);
	void Finalize();
	//敵やプレイヤーなど役割によって更新関数を切り替えられるようにする
	virtual void Update(float deltaTime);
	
public:
	int mesh = 0;
	GLuint texture = 0;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	
	glm::vec3 velocity;
	glm::vec3 GetForward;

	float mfowardSpeed;
	float mangularSpeed;
	float goalVec = 0;
	float bulletTimer = 0;
	
	
	int helth = 0;
	
	Rect colLocal;
	Rect colWorld;
	glm::vec3 colMax;
	glm::vec3 colMin;


	glm::vec3 viewoffset;
	glm::vec3 targetoffset;
	glm::vec3 vCamera;
	glm::vec3 vTraget;
	glm::vec3 vCameraTraget;
	glm::vec3 vTragetoffset;
	glm::vec3 cameraVelocity;
	glm::vec3 TragetVelocity;
};

/*
Actor配列の範囲を指定するのではなく、
std::vector<Actor*>型の参照を指定している。
*/
Actor* FindAvailableActor(std::vector<Actor*>&);
void UpdateActorList(std::vector<Actor*>&, float);
void RenderActorList(std::vector<Actor*>&, Shader::Program&, MeshList&);
void ClearActorList(std::vector<Actor*>&);
using CollisionHandlerType = std::function<void(Actor&, Actor&)>;
bool DetectCollision(const Actor&, const Actor&);
void DetectCollision(
	std::vector<Actor*>&, std::vector<Actor*>&, CollisionHandlerType);
void CharactorCollision(Actor, std::vector<Actor*>&, CollisionHandlerType);
void ActorCollision(Actor, Actor, CollisionHandlerType);

#endif // !ACTOR_H_INCLUDED


