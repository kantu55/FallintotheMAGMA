/*
@file Main.cpp
*/

//https://github.com/tn-mai/OpenGL3D2018

#include "GLFWEW.h"
#include "TitleScene.h"
#include "MainGameScene.h"
#include <vector>


/*
メッシュ配列
const Mesh meshList[] = 
{
	{ GL_TRIANGLES, 21, (const GLvoid*)0, 0},//木
	{ GL_TRIANGLES, 42, (const GLvoid*)(21 * sizeof(GLushort)), 8},//家
	{ GL_TRIANGLES, 30, (const GLvoid*)(63 * sizeof(GLushort)), 24 },
	{ GL_TRIANGLES, 102, (const GLvoid*)(93 * sizeof(GLushort)), 32 },
};
*/

MeshList meshList;

/*
エントリーポイント
*/

int main()
{
	GLFWEW::Window& window = GLFWEW::Window::Instance();
	if (!window.Init(1280, 720, "OpenGL Tutorial"))
	{
		return 1;
	}
	Audio::EngineRef audio = Audio::Engine::Instance();
	if (!audio.Initialize())
	{
		return 1;
	}
	
	Scene* pScene = new TitleScene;
	if (!pScene || !pScene->Initialize())
	{
		delete pScene;
		return 1;
	}

	
	//メインループ
	window.InitTimer();
	while (!window.ShouldClose())
	{
		window.UpdateTimer();
		
		pScene->ProcessInput();
		pScene->Update();
		pScene->Render();
		if (!pScene->NextScene().empty())
		{
			const std::string sceneName =
				pScene->NextScene();
			pScene->Finalize();
			delete pScene;
			pScene = nullptr;
			if (sceneName == "TitleScene")
			{
				pScene = new TitleScene;
			}
			else if (sceneName == "MainGameScene")
			{
				pScene = new MainGameScene;
			}
			if (!pScene || !pScene->Initialize())
			{
				break;
			}
		}
		window.SwapBuffers();
	}
	if (pScene)
	{
		pScene->Finalize();
		delete pScene;
	}
	return 0;
}