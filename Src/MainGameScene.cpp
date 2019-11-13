/*
file MainGameScene.cpp
*/

#include "MainGameScene.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include<math.h>

/*
プレイヤーの状態を更新する

@param deltaTime 経過時間
*/
void PlayerActor::Update(float deltaTime)
{
	//プレイヤーが死んでいたら、地面に倒れる(-90度になる)まで「倒れ具合」を大きくしていく
	if (helth <= 0)
	{
		rotation.x -= glm::radians(45.0f) * deltaTime;
		if (rotation.x < glm::radians(-90.0f))
		{
			rotation.x = glm::radians(-90.0f);
		}
	}
	
	//常に必要な処理は基底クラスだけ書いておく
	Actor::Update(deltaTime);
}

void GuestActor::Update(float deltaTime)
{
	if (helth <= 0)
	{
		rotation.x += glm::radians(45.0f) * deltaTime;
		if (rotation.x > glm::radians(90.0f))
		{
			rotation.x = glm::radians(90.0f);
		}
	}
	
	Actor::Update(deltaTime);
}

void ZombieActor::Update(float deltaTime)
{
	const glm::mat4 e_VelocityRotY =
		glm::rotate(glm::mat4(1), rotation.y, glm::vec3(0, 1, 0));
	float e_rightSpeed = 0.0f;
	e_rightSpeed -= 1.0f;
	const float speed = 5.0f;
	velocity = e_VelocityRotY * glm::vec4(e_rightSpeed, 0, 0, 1);
	velocity = glm::normalize(velocity);
	velocity *= speed;
	//e_rightSpeed = glm::normalize(e_rightSpeed);
	e_rightSpeed *= speed / 2;
	goalVec += e_rightSpeed * deltaTime;
	if (goalVec <= -10)
	{
		goalVec = 0;
		rotation.y -= glm::radians(90.0f);
	}
	
	
	
	Actor::Update(deltaTime);
}

void EnemyBulletActor::Update(float deltaTime)
{
	//マップの広さを20cm × 20cmとして、弾がその範囲を超えたら消えるようにする
	const float mapSize = 20;
	for (size_t i = 0; i < 3; ++i)
	{
		if (position[i] < -mapSize || position[i] > mapSize)
		{
			helth = 0;
			break;
		}
	}
	Actor::Update(deltaTime);
}

/*
プレイヤーの弾の状態を更新する
*/
void BulletActor::Update(float deltaTime)
{
	//マップの広さを20cm × 20cmとして、弾がその範囲を超えたら消えるようにする
	const float mapSize = 20;
	for (size_t i = 0; i < 3; ++i)
	{
		if (position[i] < -mapSize || position[i] > mapSize)
		{
			helth = 0;
			break;
		}
	}
	Actor::Update(deltaTime);
}

void ObjectActor::Update(float deltaTime)
{
	Actor::Update(deltaTime);
}

float MainGameScene::BulletLoad(Actor* bullet, Actor charctor ,float speed)
{
	const float deltaTime = (float)GLFWEW::Window::Instance().DeltaTime();
	const int meshId = 3; //弾のメッシュID
	const glm::mat4 matRotY =
		glm::rotate(glm::mat4(1), charctor.rotation.y, glm::vec3(0, 1, 0));
	bullet->Initialize(meshId, texBullet.Get(), 1,
		charctor.position + FirePos, charctor.rotation, glm::vec3(2));
	bullet->velocity = matRotY * glm::vec4(0, 0, -speed, 1);
	bullet->colLocal =
	{ glm::vec3(-0.75f), glm::vec3(3) };
	return 10.5f;
}

//衝突したら、すり抜けないようにする
/*
@param ch  キャラクター(player,guest,enemy)
@param obj オブジェクト(floor,bullet...)
*/
void MainGameScene::FixCollision(Actor& ch, Actor& obj)
{
	//Maxは直方体の右上を指す
	//Minは直方体の左下を指す
	ch.colMax = ch.colWorld.origin + ch.colWorld.size;
	ch.colMin = ch.colWorld.origin;
	obj.colMax = obj.colWorld.origin + obj.colWorld.size;
	obj.colMin = obj.colWorld.origin;

	//objとchの差を計算する
	float dx1 = obj.colMin.x - ch.colMax.x;
	float dx2 = obj.colMax.x - ch.colMin.x;
	float dy1 = obj.colMin.y - ch.colMax.y;
	float dy2 = obj.colMax.y - ch.colMin.y;
	float dz1 = obj.colMin.z - ch.colMax.z;
	float dz2 = obj.colMax.z - ch.colMin.z;

	// 絶対値が小さい方をセットする
	float dx = (glm::abs(dx1) < glm::abs(dx2)) ? dx1 : dx2;
	float dy = (glm::abs(dy1) < glm::abs(dy2)) ? dy1 : dy2;
	float dz = (glm::abs(dz1) < glm::abs(dz2)) ? dz1 : dz2;

	// x/y/zのうち最も差が小さいほうで位置を調整
	if (glm::abs(dx) <= glm::abs(dy) &&
		glm::abs(dx) <= glm::abs(dz))
	{
		ch.position.x += dx;
	}
	else if (glm::abs(dz) <= glm::abs(dx) &&
		glm::abs(dz) <= glm::abs(dy))
	{
		ch.position.z += dz;
	}
	else if (glm::abs(dy) <= glm::abs(dx) &&
		glm::abs(dy) <= glm::abs(dz))
	{
		ch.position.y += dy;
	}
}

/*
初期化
*/
bool MainGameScene::Initialize()
{
	random.seed(std::random_device()());

	if (!meshList.Allocate())
	{
		return false;
	}
	progSimple.Reset(Shader::BuildFromFile("Res/Simple.vert", "Res/Simple.frag"));
	progLighting.Reset(Shader::BuildFromFile("Res/FragmentLighting.vert", "Res/FragmentLighting.frag"));
	
	//テクスチャを作成する
	const int imageWidth = 8;  //
	const int imageHeight = 8; //
	const uint32_t B = 0xff'00'00'00; //
	const uint32_t W = 0xff'ff'ff'ff; //
	const uint32_t imageData[imageWidth * imageHeight] =
	{
		W, W, B, W, W, W, W, W,
		W, W, B, W, W, W, W, W,
		W, W, B, W, W, W, W, W,
		B, B, B, B, B, B, B, B,
		W, W, W, W, W, W, B, W,
		W, W, W, W, W, W, B, W,
		W, W, W, W, W, W, B, W,
		B, B, B, B, B, B, B, B,
	};

	const uint32_t imageData2[imageWidth * imageHeight] =
	{
		W, W, W, W, W, W, W, W,
		B, B, B, B, B, B, B, B,
		W, W, W, W, W, W, W, W,
		B, B, B, B, B, B, B, B,
		W, W, W, W, W, W, W, W,
		B, B, B, B, B, B, B, B,
		W, W, W, W, W, W, W, W,
		B, B, B, B, B, B, B, B,
	};

	texHuman.Reset(Texture::LoadImage2D("Res/tga/Human.tga"));
	texGround.Reset(Texture::LoadImage2D("Res/tga/kon.tga"));
	texBullet.Reset(Texture::LoadImage2D("Res/tga/Bullet2.tga"));
	texMagma.Reset(Texture::LoadImage2D("Res/tga/magma.tga"));
	texZombie.Reset(Texture::LoadImage2D("Res/tga/Zombie.tga"));
	texBord.Reset(Texture::LoadImage2D("Res/tga/bord.tga"));
	
	//情報表示用テクスチャを読み込む
	for (int i = 0; i < 10; i++)
	{
		//ナンバーを読み込む
		const std::string filename =
			std::string("Res/tga/Num_") + (char)('0' + i) + ".tga";
		texNumber[i].Reset(Texture::LoadImage2D(filename.c_str()));
	}
	texNum.Reset(Texture::LoadImage2D("Res/tga/Num.tga"));
	texPlayerWin.Reset(Texture::LoadImage2D("Res/tga/1P_win.tga"));
	texGuestWin.Reset(Texture::LoadImage2D("Res/tga/2P_win.tga"));
	texReload.Reset(Texture::LoadImage2D("Res/tga/reload.tga"));
	texStan.Reset(Texture::LoadImage2D("Res/tga/stan.tga"));
	texPouse.Reset(Texture::LoadImage2D("Res/tga/pouse.tga"));
	texPlayer.Reset(Texture::LoadImage2D("Res/tga/1P.tga"));
	texGuest.Reset(Texture::LoadImage2D("Res/tga/2P.tga"));
	texDirPlayer.Reset(Texture::LoadImage2D("Res/tga/playerdirection.tga"));
	texDirGuest.Reset(Texture::LoadImage2D("Res/tga/guestdirection.tga"));
	texTitle_B.Reset(Texture::LoadImage2D("Res/tga/title_B.tga"));
	texTitle_Y.Reset(Texture::LoadImage2D("Res/tga/title_Y.tga"));
	texRetry_B.Reset(Texture::LoadImage2D("Res/tga/retry_B.tga"));
	texRetry_Y.Reset(Texture::LoadImage2D("Res/tga/retry_Y.tga"));
	Mainbgm = audio.Prepare("Res/Audio/Main.wav");
	Bulletbgm = audio.Prepare("Res/Audio/PlayerShot.xwm");
	Overbgm = audio.Prepare("Res/Audio/Over.wav");
	Menubgm = audio.Prepare("Res/Audio/Menyu.wav");
	Enterbgm = audio.Prepare("Res/Audio/Option.wav");
	Hitbgm = audio.Prepare("Res/Audio/Hit.wav");
	Stanbgm = audio.Prepare("Res/Audio/Stan.wav");
	Mainbgm->Play();

	//ライトの設定
	lights.ambient.color = glm::vec3(0.1f, 0.01f, 0.2f);  //環境光の色
	lights.directional.direction = glm::normalize(glm::vec3(5, -2, -2));  //指向性ライト
	lights.directional.color = glm::vec3(1.0, 1.0f, 1.0f); //指向性ライトの色

	lights.point.position[0] = glm::vec3(0, -1, 0);
	lights.point.color[0] = glm::vec3(1.0f, 0.8f, 0.4f) * 200.0f;
	
	
	const glm::vec3 tmpSpotLightDir = glm::normalize(glm::vec3(-1, -2, -3));
	lights.spot.dirAndCutoff[0] = glm::vec4(tmpSpotLightDir, std::cos(glm::radians(20.0f)));
	lights.spot.posAndInnerCutOff[0] = glm::vec4(0, 6, 0, std::cos(glm::radians(15.0f)));
	lights.spot.color[0] = glm::vec3(0.4f, 0.8f, 1.0f) * 200.0f;

	player.Initialize(0, texHuman.Get(), 10,
		glm::vec3(0, 0, 5), glm::vec3(0,0,0), glm::vec3(1));
	player.colLocal =
	{
		glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(1.0f, 1.7f, 1.0f)
	};
	guest.Initialize(0, texHuman.Get(), 10,
		glm::vec3(0, 0, -5), glm::vec3(0), glm::vec3(1));
	guest.colLocal =
	{
		glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(1.0f, 1.7f, 1.0f)
	};
	floor.Initialize(1, texGround.Get(), 1,
		glm::vec3(0, 0, 0), glm::vec3(0), glm::vec3(1,3,1));
	floor.colLocal=
	{
		glm::vec3(-9.5f,0.0f,-9.5f), glm::vec3(19.0f, 0.1f, 19.0f)
	};
	deathFloor.Initialize(1, texMagma.Get(), 1,
		glm::vec3(0, -1.5f, 0), glm::vec3(0), glm::vec3(4, 1, 4));
	deathFloor.colLocal =
	{
		glm::vec3(-40.0f,0.0f,-40.0f), glm::vec3(80.0f, 0.1f, 80.0f)
	};
	playerDirection.Initialize(1, texDirPlayer.Get(), 1,
		glm::vec3(0),glm::vec3(0), glm::vec3(1));
	guestDirection.Initialize(1, texDirGuest.Get(), 1,
		glm::vec3(0), glm::vec3(0), glm::vec3(1));
	playerDirection.position = player.position + p_dirOffset;
	playerBullets.resize(128);
	for (auto& bullet : playerBullets)
	{
		bullet = new BulletActor;
	}
	guestBullets.resize(128);
	for (auto& g_bullet : guestBullets)
	{
		g_bullet = new BulletActor;
	}
	enemies.resize(128);
	for (auto& enemy : enemies)
	{
		enemy = new ZombieActor;
	}
	enemyBullets.resize(128);
	for (auto& e_Bullet : enemyBullets)
	{
		e_Bullet = new BulletActor;
	}

	enemyRot[0].y = glm::radians(180.0f);
	enemyRot[1].y = glm::radians(-90.0f);
	enemyRot[2].y = glm::radians(90.0f);
	enemyRot[3].y = glm::radians(0.0f);
	for (int i = 0; i < popCount; i++)
	{
		zombies = (ZombieActor*)FindAvailableActor(enemies);
		if (zombies)
		{
			zombies->Initialize(0, texZombie.Get(), 8,
				enemyPos[i], enemyRot[i], glm::vec3(1));
			zombies->colLocal =
			{
				glm::vec3(-0.5f, 0, -0.5f), glm::vec3(1, 1.8f, 1)
			};
			zombies->velocity = glm::vec3(0);
			std::uniform_real_distribution<float> BulletIntaval(2, 5);
			zombies->bulletTimer = BulletIntaval(random);
			zombies->baseSpeed = enemySpeed;
			zombies2[i] = zombies;
		}
	}
	gameinterval = 3.0f;
	viewoffset = glm::vec3(0, 50, 10);
	return true;
}


/*
入力の反映
*/
void MainGameScene::ProcessInput()
{
	const float deltaTime = (float)GLFWEW::Window::Instance().DeltaTime();
	GLFWEW::Window& window = GLFWEW::Window::Instance();
	if (state == State::play)
	{
		const glm::mat4 pVelocityRotY = 
			glm::rotate(glm::mat4(1), player.rotation.y, glm::vec3(0, 1, 0));
		const glm::mat4 gVelocityRotY =
			glm::rotate(glm::mat4(1), guest.rotation.y, glm::vec3(0, 1, 0));
		float pforwardSpeed = 0.0f;
		float prightSpeed = 0.0f;
		float gforwardSpeed = 0.0f;
		float grightSpeed = 0.0f;
		
		player.velocity = glm::vec3(0);
		guest.velocity = glm::vec3(0);
		if (playerStan > 0)
		{
			player.velocity.x = player.velocity.y = player.velocity.z = 0;
		}
		else
		{
			if (!window.IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
			{
				if (window.IsKeyPressed(GLFW_KEY_A))
				{
					player.rotation.y += glm::radians(90.0f) * deltaTime;
				}
				else if (window.IsKeyPressed(GLFW_KEY_D))
				{
					player.rotation.y -= glm::radians(90.0f) * deltaTime;
				}
			}
			else
			{
				if (window.IsKeyPressed(GLFW_KEY_A))
				{
					prightSpeed -= 1.0f;
				}
				else if (window.IsKeyPressed(GLFW_KEY_D))
				{
					prightSpeed += 1.0f;
				}
				
			}
			if (window.IsKeyPressed(GLFW_KEY_W))
			{
				pforwardSpeed -= 1;
			}
			else if (window.IsKeyPressed(GLFW_KEY_S))
			{
				pforwardSpeed += 1;
			}
			if (pforwardSpeed < 0 || pforwardSpeed > 0)
			{
				if (window.IsKeyPressed(GLFW_KEY_LEFT_SHIFT) && window.IsKeyPressed(GLFW_KEY_S))
				{
					/*
					std::atan...移動ベクトルから向きを計算するための関数
					向きをY,Xのベクトルを指定すると、そのベクトルの向きをラジアンの値で
					返してくれる
					*/
					player.rotation.y = std::atan2(-player.rotation.y, 180.0f);
					player.rotation.y -= glm::radians(180.0f);
				}

				const float speed = 10.0f;
				player.velocity = pVelocityRotY * glm::vec4(0, 0, pforwardSpeed, 1);
				player.velocity = glm::normalize(player.velocity);
				player.velocity *= speed;
			}
			if (prightSpeed < 0 || prightSpeed > 0)
			{
				const float speed = 5.0f;
				player.velocity = pVelocityRotY * glm::vec4(prightSpeed, 0, 0, 1);
				player.velocity = glm::normalize(player.velocity);
				player.velocity *= speed;
			}
		}
		if (guestStan > 0)
		{
			guest.velocity.x = guest.velocity.y = guest.velocity.z = 0;
		}
		else
		{
			if (!window.IsKeyPressed(GLFW_KEY_RIGHT_SHIFT))
			{
				if (window.IsKeyPressed(GLFW_KEY_J))
				{
					guest.rotation.y += glm::radians(90.0f) * deltaTime;
				}
				else if (window.IsKeyPressed(GLFW_KEY_L))
				{
					guest.rotation.y -= glm::radians(90.0f) * deltaTime;
				}
			}
			else
			{
				if (window.IsKeyPressed(GLFW_KEY_J))
				{
					grightSpeed -= 1.0f;
				}
				else if (window.IsKeyPressed(GLFW_KEY_L))
				{
					grightSpeed += 1.0f;
				}
			}

			if (window.IsKeyPressed(GLFW_KEY_I))
			{
				gforwardSpeed -= 1;
			}
			else if (window.IsKeyPressed(GLFW_KEY_K))
			{
				gforwardSpeed += 1;
			}
			

			if (gforwardSpeed < 0 || gforwardSpeed > 0)
			{
				if (window.IsKeyPressed(GLFW_KEY_RIGHT_SHIFT) && window.IsKeyPressed(GLFW_KEY_K))
				{
					/*
					std::atan...移動ベクトルから向きを計算するための関数
					向きをY,Xのベクトルを指定すると、そのベクトルの向きをラジアンの値で
					返してくれる
					*/
					guest.rotation.y = std::atan2(-guest.rotation.y, 180.0f);
					guest.rotation.y -= glm::radians(180.0f);
				}

				const float speed = 10.0f;
				guest.velocity = gVelocityRotY * glm::vec4(0, 0, -gforwardSpeed, 1);
				guest.velocity = glm::normalize(guest.velocity);
				guest.velocity *= speed;
			}
			if (grightSpeed < 0 || grightSpeed > 0)
			{
				const float speed = 5.0f;
				guest.velocity = gVelocityRotY * glm::vec4(-grightSpeed, 0, 0, 1);
				guest.velocity = glm::normalize(guest.velocity);
				guest.velocity *= speed;
			}

		}
		if (window.IsKeyPressed(GLFW_KEY_ESCAPE))
		{
			state = State::pouse;
		}
		//ショットボタンが押されていなければ方向転換
		
	
		if (gameinterval > 0) return;
		else
		{
			gameinterval = 0.0f;
		}
		//ショットボタンが押されていたら弾を発射
		if (window.IsKeyPressed(GLFW_KEY_SPACE))
		{
			if (playerBulletTimer <= 0)
			{
				Actor* p_Bullet = FindAvailableActor(playerBullets);
				if (p_Bullet)
				{
					Bulletbgm->Play();
					playerBulletTimer = BulletLoad(p_Bullet, player, speed);
				}
				else
				{
					playerBulletTimer = 0.0f;
				}
			}
		}
		if (window.IsKeyPressed(GLFW_KEY_ENTER))
		{
			if (guestBulletTimer <= 0)
			{
				Actor* g_Bullet = FindAvailableActor(guestBullets);
				if (g_Bullet)
				{
					Bulletbgm->Play();
					guestBulletTimer = BulletLoad(g_Bullet, guest, -speed);
				}
			}
		}
	}
	else if (state == State::pouse)
	{
		if (window.IsKeyPressed(GLFW_KEY_ESCAPE))
		{
			state = State::play;
		}
	}
	else if(state == State::stageClear || state == State::gameOver)
	{
		player.velocity.x = player.velocity.y = player.velocity.z = 0;
		guest.velocity.x = guest.velocity.y = guest.velocity.z = 0;
		if (window.IsKeyPressed(GLFW_KEY_LEFT))
		{
			Menubgm->Play();
			over = GameOver::title;
		}
		if (window.IsKeyPressed(GLFW_KEY_RIGHT))
		{
			Menubgm->Play();
			over = GameOver::retry;
		}
		if (window.IsKeyPressed(GLFW_KEY_ENTER) && gameinterval <= 0)
		{
			Enterbgm->Play();
			if (over == GameOver::title)
			{
				gameinterval = 0.0f;
				NextScene("TitleScene");
			}
			else if (over == GameOver::retry)
			{
				gameinterval = 0.0f;
				NextScene("MainGameScene");
			}
		}
	}
}

/*
状態の更新
*/
void MainGameScene::Update()
{
	if (state == State::pouse)
	{
		return;
	}
	const float deltaTime = (float)GLFWEW::Window::Instance().DeltaTime();

	player.velocity.y -= Gravity;
	guest.velocity.y -= Gravity;
	
	//マップの前後左右15㎝の範囲で出現ポイントを決め、そこを中心として前後左右5mの範囲に出現
	for (int i = 0; i < 4; i++)
	{
		if (zombies2[i])
		{
			if (zombies2[i]->bulletTimer <= 0)
			{
				Actor* e_Bullet = FindAvailableActor(enemyBullets);
				if (e_Bullet)
				{
					const int meshId = 3; //弾のメッシュID
					const glm::mat4 matRotY =
						glm::rotate(glm::mat4(1), zombies2[i]->rotation.y, glm::vec3(0, 1, 0));
					e_Bullet->Initialize(meshId, texBord.Get(), 1,
						zombies2[i]->position + FirePos, zombies2[i]->rotation, glm::vec3(2));
					e_Bullet->velocity = matRotY * glm::vec4(0, 0, -enemyBulletSpeed, 1);
					e_Bullet->colLocal =
					{ glm::vec3(-0.5f), glm::vec3(1) };
					std::uniform_real_distribution<float> BulletIntaval(2, 5);
					zombies2[i]->bulletTimer = BulletIntaval(random);
				}
			}
		}
	}
	

	

	/*
	「[&](Actor&, Actor&){ ~ }」の部分は「無名関数」あるいは「ラムタ式」と呼ばれる
	関数を定義しなくても、必要な場所に直接関数の内容を描くことが出来る
	*/
	DetectCollision(playerBullets, guestBullets, [&](Actor& p_bullet, Actor& g_bullet)
	{
		FixCollision(p_bullet, g_bullet);
	});

	CharactorCollision(player, guestBullets, [&](Actor& charctor, Actor& bullet)
	{
		Stanbgm->Play();
		bullet.helth = 0;
		playerStan += 3.0f;
	});

	CharactorCollision(player, enemyBullets, [&](Actor& charctor, Actor& bullet)
	{
		FixCollision(player, bullet);
	});
	CharactorCollision(guest, enemyBullets, [&](Actor& charctor, Actor& bullet)
	{
		FixCollision(guest, bullet);
	});

	CharactorCollision(guest, playerBullets, [&](Actor& charctor, Actor& bullet)
	{
		Stanbgm->Play();
		bullet.helth = 0;
		guestStan += 3.0f;
	});

	ActorCollision(player, guest, [&](Actor& charctor, Actor& bullet)
	{
		FixCollision(player, guest);
	});
	
	ActorCollision(player, floor, [&](Actor& charctor, Actor& ground)
	{
		FixCollision(player, floor);
	});
	
	ActorCollision(guest, floor, [&](Actor& charctor, Actor& ground)
	{
		FixCollision(guest, floor);
	});
	ActorCollision(player, deathFloor, [&](Actor& charctor, Actor& obj)
	{
		FixCollision(player, deathFloor);
		player.helth = 0;
	});
	ActorCollision(guest, deathFloor, [&](Actor& charctor, Actor& obj)
	{
		FixCollision(guest, deathFloor);
		guest.helth = 0;
	});

	//ステージクリア判定
	if (state == State::play && guest.helth <= 0)
	{
		Overbgm->Play();
		gameinterval = 1.0f;
		state = State::stageClear;
	}

	//ゲームオーバー判定
	if (state == State::play && player.helth <= 0)
	{
		Overbgm->Play();
		gameinterval = 1.0f;
		state = State::gameOver;
	}

	if (state == State::play)
	{
		gameinterval -= deltaTime;
	}

	if (player.helth <= 0 || guest.helth <= 0)
	{
		gameinterval -= deltaTime;
	}

	//プレイヤーの弾の発射タイマーを更新
	if (playerBulletTimer > 0)
	{
		playerBulletTimer -= deltaTime;
	}
	if (guestBulletTimer > 0)
	{
		guestBulletTimer -= deltaTime;
	}
	for (int i = 0; i < 4; i++)
	{
		if (zombies2[i]->bulletTimer > 0)
		{
			zombies2[i]->bulletTimer -= deltaTime;
		}
	}
	
	if (playerStan > 0)
	{
		playerStan -= deltaTime;
	}
	if (guestStan > 0)
	{
		guestStan -= deltaTime;
	}

	playerDirection.rotation.x = guestDirection.rotation.x = glm::radians(-90.0f);

	const glm::mat4 PlayerDirRotY = glm::rotate(glm::mat4(1), player.rotation.y, glm::vec3(0, 1, 0));
	p_dir = playerDirection.position - player.position;       //曲がる前プレイヤーと矢印間のベクトル
	p_dirTarget = PlayerDirRotY * glm::vec4(0, 0.2f, -1, 1);  //曲がった後のプレイヤーと矢印間ベクトル
	p_dirVeloctiy = p_dirTarget - p_dir;                      //曲がる前と曲がった後のベクトル
	p_dir += p_dirVeloctiy;                                   //その差分進める
	playerDirection.position = player.position + p_dir;       //矢印の位置を調整
	playerDirection.rotation.y = player.rotation.y + glm::radians(180.0f);

	const glm::mat4 GuestDirRotY = glm::rotate(glm::mat4(1), guest.rotation.y, glm::vec3(0, 1, 0));
	g_dir = guestDirection.position - guest.position;
	g_dirTarget = GuestDirRotY * glm::vec4(0, 0.2f, 1, 1);
	g_dirVeloctiy = g_dirTarget - g_dir;
	g_dir += g_dirVeloctiy;
	guestDirection.position = guest.position + g_dir;
	guestDirection.rotation.y = guest.rotation.y;

	//ゾンビの状態を更新
	UpdateActorList(enemies, deltaTime);
	UpdateActorList(enemyBullets, deltaTime);
	//プレイヤーの弾の状態を更新
	UpdateActorList(playerBullets, deltaTime);
	UpdateActorList(guestBullets, deltaTime);
	player.Update(deltaTime);
	guest.Update(deltaTime);
	floor.Update(deltaTime);
	deathFloor.Update(deltaTime);
}

void MainGameScene::RenderLoad()
{
	progLighting.SetLightList(lights);
	meshList.BindVertexArray();
	//プレイヤー
	progLighting.BindTexture(0, player.texture);
	progLighting.Draw(meshList.Get(player.mesh),
		player.position, player.rotation, player.scale);
	//ゲスト
	progLighting.Draw(meshList.Get(guest.mesh),
		guest.position, guest.rotation, guest.scale);
	//地面
	progLighting.BindTexture(0, floor.texture);
	progLighting.Draw(meshList.Get(floor.mesh),
		floor.position, floor.rotation, floor.scale);
	//マグマ
	progLighting.BindTexture(0, deathFloor.texture);
	progLighting.Draw(meshList.Get(floor.mesh),
		deathFloor.position, deathFloor.rotation, deathFloor.scale);

	progLighting.BindTexture(0, playerDirection.texture);
	progLighting.Draw(meshList.Get(2),
		playerDirection.position, playerDirection.rotation,
		playerDirection.scale);
	progLighting.BindTexture(0, guestDirection.texture);
	progLighting.Draw(meshList.Get(2),
		guestDirection.position, guestDirection.rotation,
		guestDirection.scale);
	//プレイヤーの弾
	RenderActorList(playerBullets,progLighting, meshList);
	//ゲストの弾
	RenderActorList(guestBullets, progLighting, meshList);
	RenderActorList(enemyBullets, progLighting, meshList);
	RenderActorList(enemies, progLighting, meshList);


}

/*
描画
*/
void MainGameScene::Render()
{
	GLFWEW::Window& window = GLFWEW::Window::Instance();
	const float deltaTime = (float)window.DeltaTime();

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1f, 0.3f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	{
		progLighting.Use();

		//座標変換行列を作成してシェーダーに転送する
		const glm::mat4x4 matProj =
			//透視投影を行うための座標変換行列(プロジェクション変換)を作成している
			/*
			引数１・・・Y軸方向の視野角度
			引数２・・・X軸方向の視野角度を決めるための比率
			引数３・・・奥行きの描画範囲を設定する
			引数４・・・引数３と同じ
			*/
			glm::perspective(glm::radians(90.0f), 640.0f / 360.0f, 0.1f, 500.0f);

		const glm::mat4x4 matView =
			//ワールド座標系からビュー座標系への変換行列を作成している
			/*
			引数１・・・視点の座標
			引数２・・・注視点の座標
			引数３・・・視点の上方向のベクトル
			*/
			glm::lookAt(glm::vec3(0, 15, 2), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));

		progLighting.SetViewProjectionMatrix(matProj * matView);

		RenderLoad();
	}

	

	{
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		progSimple.Use();

		//正射影で描画するように行列を設定
		const glm::mat4x4 matProj = glm::ortho(
			-400.0f, 400.0f, -300.0f, 300.0f, 1.0f, 500.0f);
		const glm::mat2x4 matView = glm::lookAt(
			glm::vec3(0, 0, 100), glm::vec3(0), glm::vec3(0, 1, 0));
		progSimple.SetViewProjectionMatrix(matProj * matView);

		const Mesh planeMeshId = meshList.Get(2);
		progSimple.BindTexture(0, texPlayer.Get());
		progSimple.Draw(planeMeshId,
			glm::vec3(-350, -170, 0), glm::vec3(0), glm::vec3(32, 32, 1));
		progSimple.BindTexture(0, texGuest.Get());
		progSimple.Draw(planeMeshId,
			glm::vec3(350, -170, 0), glm::vec3(0), glm::vec3(32, 32, 1));
		progSimple.BindTexture(0, texReload.Get());
		progSimple.Draw(planeMeshId,
			glm::vec3(-330, -220, 0), glm::vec3(0), glm::vec3(64, 64, 1));
		progSimple.Draw(planeMeshId,
			glm::vec3(270, -220, 0), glm::vec3(0), glm::vec3(64, 64, 1));
		int maxReloadDigits = 2;
		int tmpPlayerReload = playerBulletTimer;
		for (int i = 0; i < maxReloadDigits; i++)
		{
			const int posX = -282 + 32 * (maxReloadDigits - i);;
			const int number = tmpPlayerReload % 10;
			tmpPlayerReload /= 10;
			progSimple.BindTexture(0, texNumber[number].Get());
			progSimple.Draw(planeMeshId,
				glm::vec3(posX, -215, 0), glm::vec3(0), glm::vec3(32, 32, 1));
		}
		int tmpGuestReload = guestBulletTimer;
		for (int i = 0; i < maxReloadDigits; i++)
		{
			const int posX = 310 + 32 * (maxReloadDigits - i);;
			const int number = tmpGuestReload % 10;
			tmpGuestReload /= 10;
			progSimple.BindTexture(0, texNumber[number].Get());
			progSimple.Draw(planeMeshId,
				glm::vec3(posX, -215, 0), glm::vec3(0), glm::vec3(32, 32, 1));
		}
		progSimple.BindTexture(0, texStan.Get());
		progSimple.Draw(planeMeshId,
			glm::vec3(-330, -270, 0), glm::vec3(0), glm::vec3(64, 64, 1));
		progSimple.Draw(planeMeshId,
			glm::vec3(270, -270, 0), glm::vec3(0), glm::vec3(64, 64, 1));
		{
			int tmpStan = playerStan;
			const int posX = -250;
			const int number = tmpStan;
			tmpStan /= 10;
			progSimple.BindTexture(0, texNumber[number].Get());
			progSimple.Draw(planeMeshId,
				glm::vec3(posX, -265, 0), glm::vec3(0), glm::vec3(32, 32, 1));
		}
		
		{
			int tmpGuestStan = guestStan;
			const int posX = 342;
			const int number = tmpGuestStan;
			tmpGuestStan /= 10;
			progSimple.BindTexture(0, texNumber[number].Get());
			progSimple.Draw(planeMeshId,
				glm::vec3(posX, -265, 0), glm::vec3(0), glm::vec3(32, 32, 1));
		}
		
		

		//ステージクリア・ゲームオーバー表示
		if (state == State::stageClear || state == State::gameOver)
		{
			if (over == GameOver::title)
			{
				progSimple.BindTexture(0, texTitle_Y.Get());
				progSimple.Draw(planeMeshId,
					glm::vec3(-60, -60, 0), glm::vec3(0), glm::vec3(60, 60, 1));
				progSimple.BindTexture(0, texRetry_B.Get());
				progSimple.Draw(planeMeshId,
					glm::vec3(60, -60, 0), glm::vec3(0), glm::vec3(60, 60, 1));
			}
			else if (over == GameOver::retry)
			{
				progSimple.BindTexture(0, texTitle_B.Get());
				progSimple.Draw(planeMeshId,
					glm::vec3(-60,-60,0), glm::vec3(0), glm::vec3(60, 60, 1));
				progSimple.BindTexture(0, texRetry_Y.Get());
				progSimple.Draw(planeMeshId,
					glm::vec3(60, -60, 0), glm::vec3(0), glm::vec3(60, 60, 1));
			}
			
		}
		if (state == State::stageClear)
		{
			progSimple.BindTexture(0, texPlayerWin.Get());
			progSimple.Draw(planeMeshId,
				glm::vec3(0,60,0), glm::vec3(0), glm::vec3(120, 120, 1));
		}
		else if (state == State::gameOver)
		{
			progSimple.BindTexture(0, texGuestWin.Get());
			progSimple.Draw(planeMeshId,
				glm::vec3(0, 60, 0), glm::vec3(0), glm::vec3(120, 120, 1));
		}
		else if (state == State::pouse)
		{
			//progSimple.BindTexture(0, texPouse.Get());
			//progSimple.Draw(planeMeshId,
			//	glm::vec3(0), glm::vec3(0), glm::vec3(150, 150, 1));
		}
	}
	progLighting.BindTexture(0, 0);
}

/*
終了
*/
void MainGameScene::Finalize()
{
	Mainbgm->Stop();
	Bulletbgm->Stop();
	Overbgm->Stop();
	ClearActorList(playerBullets);
	ClearActorList(guestBullets);
	ClearActorList(enemies);
}