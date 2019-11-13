/*
@file Actor.cpp
*/
#include "Actor.h"
#include <algorithm>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\quaternion.hpp>

/*
アクターを初期化する

@param mesh  アクターとして表示するメッシュID
@param tex   メッシュに貼るテクスチャのID
@param hp    アクターの耐久力
@param pos   メッシュを表示する座標
@param rot   メッシュを表示する回転角度
@param scale メッシュを表示する大きさ
*/
void Actor::Initialize(int mesh, GLuint tex, int hp,
	const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale)
{
	//引数とメンバ変数の名前が同じの場合は、「this->」をつかう
	this->mesh = mesh;
	texture = tex;
	position = pos;
	rotation = rot;
	this->scale = scale;
	helth = hp;
}

/*
アクターを破棄する
*/
void Actor::Finalize()
{
	helth = 0;
}

/*
アクターを更新する

@param deltaTime 経過時間
*/
void Actor::Update(float deltaTime)
{
	//アクターの座標と衝突判定の位置を更新している
	position += velocity * deltaTime;
	colWorld.origin = colLocal.origin + position;
	colWorld.size = colLocal.size;
}

/*
利用可能なアクターを取得する

@param actorList 検索対象のアクターのリスト

@return 利用可能なアクターのポインタ
        利用可能なアクターが見つからなければnullptr
*/
Actor* FindAvailableActor(std::vector<Actor*>& actorList)
{
	//未使用のアクターを見つける
	for (auto& actor : actorList)
	{
		if (actor && actor->helth <= 0)
		{
			return actor;
		}
	}
	return nullptr;
}

/*
アクターの状態を更新する

@param actorList 更新するアクターのリスト
@param deltaTime 前回の更新からの経過時間
*/
void UpdateActorList(std::vector<Actor*>& actorList, float deltaTime)
{
	for (auto& actor : actorList)
	{
		if (actor && actor->helth > 0)
		{
			actor->Update(deltaTime);
		}
	}
}

/*
アクターを描画する

@param actorList 描画するアクターのリスト
@param shader    描画に使用するシェーダー・オブジェクト
@param meshList  描画に使用するメッシュリスト

事前にShader::Use(), Shader::SetViewProjectionMatrix()などの関数を実行しておくこと
*/
void RenderActorList(std::vector<Actor*>& actorList,
	Shader::Program& shader, MeshList& meshList)
{
	for (auto& actor : actorList)
	{
		if (actor && actor->helth > 0)
		{
			shader.BindTexture(0, actor->texture);
			shader.Draw(meshList.Get(actor->mesh),
				actor->position, actor->rotation, actor->scale);
		}
	}
}

/*
アクターリストを空にする

@param actorList 空にするアクターリスト
*/
void ClearActorList(std::vector<Actor*>& actorList)
{
	for (auto& actor : actorList)
	{
		//アクターを削除する
		delete actor;
	}
	actorList.clear();
	/*
	配列やstd::vectorなどにnewやmallocで作成したポインタを保持させている場合、
	それらを使い終わったときは必ずdeleteやfreeを実行してポインタが指すメモリを
	開放しなければならない。
	*/
}

/*
2つの直方体の衝突状態を調べる

@param lhs 直方体その1
@param rhs 直方体その2

@retval true  衝突している
@retval false 衝突していない
*/
bool DetectCollision(const Actor& lhs, const Actor& rhs)
{
	return
		lhs.colWorld.origin.x < rhs.colWorld.origin.x + rhs.colWorld.size.x &&
		lhs.colWorld.origin.x + lhs.colWorld.size.x > rhs.colWorld.origin.x &&
		lhs.colWorld.origin.y < rhs.colWorld.origin.y + rhs.colWorld.size.y &&
		lhs.colWorld.origin.y + lhs.colWorld.size.y > rhs.colWorld.origin.y &&
		lhs.colWorld.origin.z < rhs.colWorld.origin.z + rhs.colWorld.size.z &&
		lhs.colWorld.origin.z + lhs.colWorld.size.z > rhs.colWorld.origin.z;
}

/*
2つのグループ間で衝突判定を行う

@param va グループA
@param vb グループB
@param func A‐B間の衝突を処理する関数
*/
void DetectCollision(std::vector<Actor*>& va, std::vector<Actor*>& vb,
	CollisionHandlerType func)
{
	for (auto& a : va)
	{
		if (a->helth <= 0)
		{
			continue;
		}
		for (auto& b : vb)
		{
			if (b->helth <= 0)
			{
				continue;
			}
			if (DetectCollision(*a, *b))
			{
				func(*a, *b);
				if (a->helth <= 0)
				{
					break;
				}
			}
		}
	}
}

void CharactorCollision(Actor va, std::vector<Actor*>& vb,CollisionHandlerType func)
{
	for (auto& b : vb)
	{
		if (va.helth <= 0)
		{
			continue;
		}
		if (b->helth <= 0)
		{
			continue;
		}
		if (DetectCollision(va, *b))
		{
			func(va, *b);
			if (va.helth <= 0)
			{
				break;
			}
		}
	}
}

void ActorCollision(Actor va, Actor vb, CollisionHandlerType func)
{
	if (DetectCollision(va, vb))
	{
		func(va, vb);
	}
}
