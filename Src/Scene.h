#pragma once
/*
@file Scene.h
*/
#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED
#include<string>

/*
シーンの基底クラス
*/
class Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;

	//派生クラスで必ず定義しなければならない
	virtual bool Initialize() = 0;
	virtual void ProcessInput() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Finalize() = 0;

	//シーン切り替え用の関数
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
