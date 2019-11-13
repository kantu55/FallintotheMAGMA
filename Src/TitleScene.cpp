/*
@file TitleScene.cpp
*/
#include "TitleScene.h"
#include <glm/gtc/matrix_transform.hpp>

/*
初期化
*/
bool TitleScene::Initialize()
{
	
	
	if (!meshList.Allocate())
	{
		return false;
	}
	progSimple.Reset(Shader::BuildFromFile("Res/Simple.vert", "Res/Simple.frag"));

	texLogo.Reset(Texture::LoadImage2D("Res/tga/TitleName.tga"));
	texBackground.Reset(Texture::LoadImage2D("Res/tga/Title.tga"));
	texStart_B.Reset(Texture::LoadImage2D("Res/tga/GameStart_B.tga"));
	texStart_Y.Reset(Texture::LoadImage2D("Res/tga/GameStart_Y.tga"));
	texOption_B.Reset(Texture::LoadImage2D("Res/tga/Option_B.tga"));
	texOption_Y.Reset(Texture::LoadImage2D("Res/tga/Option_Y.tga"));
	texSousaScene.Reset(Texture::LoadImage2D("Res/tga/sousa.tga"));
	texSousa_B.Reset(Texture::LoadImage2D("Res/tga/sousa_B.tga"));
	texSousa_Y.Reset(Texture::LoadImage2D("Res/tga/sousa_Y.tga"));
	texTutorial_B.Reset(Texture::LoadImage2D("Res/tga/tutorial_B.tga"));
	texTutorial_Y.Reset(Texture::LoadImage2D("Res/tga/tutorial_Y.tga"));
	texTutorial.Reset(Texture::LoadImage2D("Res/tga/tutorial_1.tga"));
	texEnemyTutorial.Reset(Texture::LoadImage2D("Res/tga/tutorial_2.tga"));
	texBulletTutorial.Reset(Texture::LoadImage2D("Res/tga/tutorial_3.tga"));
	audio.Initialize();
	Titlebgm = audio.Prepare("Res/Audio/Title.wav");
	Menubgm = audio.Prepare("Res/Audio/Menyu.wav");
	Enterbgm = audio.Prepare("Res/Audio/Option.wav");
	Titlebgm->Play();

	//一定時間入力を受け付けないようにする
	timer = 1.0f;
	isFinish = false;
	
	return true;
}

/*
入力の反映
*/
void TitleScene::ProcessInput()
{
	GLFWEW::Window& window = GLFWEW::Window::Instance();

	if (!isFinish && timer <= 0.0f)
	{
		if (state == State::tutorial)
		{
			if (window.IsKeyPressed(GLFW_KEY_ENTER))
			{
				Enterbgm->Play();
				timer = 0.2f;
				if (tutorial == Tutorial::rule)
				{
					tutorial = Tutorial::enemy;
				}
				else if (tutorial == Tutorial::enemy)
				{
					tutorial = Tutorial::bullet;
				}
				else
				{
					tutorial = Tutorial::rule;
					state = State::option;
				}
			}
		}
		if (state == State::option)
		{
			if (window.IsKeyPressed(GLFW_KEY_ESCAPE))
			{
				Enterbgm->Play();
				state = State::title;
			}
			if (window.IsKeyPressed(GLFW_KEY_DOWN))
			{
				Menubgm->Play();
				timer = 0.2f;
				o_SelectFlag += 1;
				if (o_SelectFlag >= 1)
				{
					o_SelectFlag = 1;
				}
			}
			else if (window.IsKeyPressed(GLFW_KEY_UP))
			{
				Menubgm->Play();
				timer = 0.2f;
				o_SelectFlag -= 1;
				if (o_SelectFlag <= 0)
				{
					o_SelectFlag = 0;
				}
			}
			if (window.IsKeyPressed(GLFW_KEY_ENTER) && o_SelectFlag == 0 && timer <= 0)
			{
				Enterbgm->Play();
				timer = 0.2f;
				state = State::tutorial;
			}
			else if (window.IsKeyPressed(GLFW_KEY_ENTER) && o_SelectFlag == 1)
			{
				Enterbgm->Play();
				timer = 0.2f;
				state = State::sousa;
			}
		}
		if (state == State::title)
		{
			if (window.IsKeyPressed(GLFW_KEY_DOWN))
			{
				Menubgm->Play();
				timer = 0.2f;
				SelectFlag += 1;
				if (SelectFlag >= 1)
				{
					SelectFlag = 1;
				}
			}
			else if (window.IsKeyPressed(GLFW_KEY_UP))
			{
				Menubgm->Play();
				timer = 0.2f;
				SelectFlag -= 1;
				if (SelectFlag <= 0)
				{
					SelectFlag = 0;
				}
			}
			//ENTERキーで終了
			if (window.IsKeyPressed(GLFW_KEY_ENTER) && SelectFlag == 0)
			{
				Enterbgm->Play();
				NextScene("MainGameScene");
				isFinish = true;
			}
			else if (window.IsKeyPressed(GLFW_KEY_ENTER) && SelectFlag == 1)
			{
				Enterbgm->Play();
				timer = 0.2f;
				state = State::option;
			}
		}
		if (state== State::sousa)
		{
			if (window.IsKeyPressed(GLFW_KEY_ESCAPE))
			{
				Menubgm->Play();
				timer = 0.2f;
				state = State::option;
			}
		}
		
	}
}

/*
状態の更新
*/
void TitleScene::Update()
{
	GLFWEW::Window& window = GLFWEW::Window::Instance();
	audio.Update();
	//経過時間だけ減らす
	if (timer > 0.0f)
	{
		timer -= window.DeltaTime();
	}
}

/*
描画
*/
void TitleScene::Render()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	//半透明合成機能を有効にする
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.1f, 0.3f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	meshList.BindVertexArray();

	progSimple.Use();

	//正射影で描画するように行列を設定
	const glm::mat4x4 matProj = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.0f, 500.0f);
	const glm::mat4x4 matView =
		glm::lookAt(glm::vec3(0, 0, 100), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	progSimple.SetViewProjectionMatrix(matProj * matView);

	
	if (state == State::title || state == State::option)
	{
		//背景とロゴをウィンドウを中心に描画
		progSimple.BindTexture(0, texBackground.Get());
		progSimple.Draw(meshList.Get(2),
			glm::vec3(400, 300, -1), glm::vec3(0), glm::vec3(400, 300, 1));
		progSimple.BindTexture(0, texLogo.Get());
		progSimple.Draw(meshList.Get(2),
			glm::vec3(400, 400, 0), glm::vec3(0), glm::vec3(200, 150, 1));
		if (state == State::title)
		{
			if (SelectFlag == 0)
			{
				progSimple.BindTexture(0, texStart_Y.Get());
				progSimple.Draw(meshList.Get(2),
					glm::vec3(400, 200, 0), glm::vec3(0), glm::vec3(100, 50, 1));
				progSimple.BindTexture(0, texOption_B.Get());
				progSimple.Draw(meshList.Get(2),
					glm::vec3(400, 100, 0), glm::vec3(0), glm::vec3(100, 50, 1));
			}
			else if (SelectFlag == 1)
			{
				progSimple.BindTexture(0, texStart_B.Get());
				progSimple.Draw(meshList.Get(2),
					glm::vec3(400, 200, 0), glm::vec3(0), glm::vec3(100, 50, 1));
				progSimple.BindTexture(0, texOption_Y.Get());
				progSimple.Draw(meshList.Get(2),
					glm::vec3(400, 100, 0), glm::vec3(0), glm::vec3(100, 50, 1));
			}
		}
		else if (state == State::option)
		{
			if (o_SelectFlag == 0)
			{
				progSimple.BindTexture(0, texTutorial_Y.Get());
				progSimple.Draw(meshList.Get(2),
					glm::vec3(400, 200, 0), glm::vec3(0), glm::vec3(100, 50, 1));
				progSimple.BindTexture(0, texSousa_B.Get());
				progSimple.Draw(meshList.Get(2),
					glm::vec3(400, 100, 0), glm::vec3(0), glm::vec3(100, 50, 1));
			}
			else if (o_SelectFlag == 1)
			{
				progSimple.BindTexture(0, texTutorial_B.Get());
				progSimple.Draw(meshList.Get(2),
					glm::vec3(400, 200, 0), glm::vec3(0), glm::vec3(100, 50, 1));
				progSimple.BindTexture(0, texSousa_Y.Get());
				progSimple.Draw(meshList.Get(2),
					glm::vec3(400, 100, 0), glm::vec3(0), glm::vec3(100, 50, 1));
			}
		}
	}
	else if (state == State::sousa)
	{
		progSimple.BindTexture(0, texSousaScene.Get());
		progSimple.Draw(meshList.Get(2),
			glm::vec3(400, 300, -1), glm::vec3(0), glm::vec3(400, 300, 1));
	}
	else if (state == State::tutorial)
	{
		if (tutorial == Tutorial::rule)
		{
			progSimple.BindTexture(0, texTutorial.Get());
			progSimple.Draw(meshList.Get(2),
				glm::vec3(400, 300, -1), glm::vec3(0), glm::vec3(400, 300, 1));
		}
		else if (tutorial == Tutorial::enemy)
		{
			progSimple.BindTexture(0, texEnemyTutorial.Get());
			progSimple.Draw(meshList.Get(2),
				glm::vec3(400, 300, -1), glm::vec3(0), glm::vec3(400, 300, 1));
		}
		else if (tutorial == Tutorial::bullet)
		{
			progSimple.BindTexture(0, texBulletTutorial.Get());
			progSimple.Draw(meshList.Get(2),
				glm::vec3(400, 300, -1), glm::vec3(0), glm::vec3(400, 300, 1));
		}
	}
}

/*
終了
*/
void TitleScene::Finalize()
{
	Titlebgm->Stop();
}

/*
タイトル画面が終わったかどうか調べる

@retval true  終わった
@retval false 終わっていない
*/
bool TitleScene::IsFinish() const
{
	return isFinish;
}