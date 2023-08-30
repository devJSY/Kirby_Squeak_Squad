#include "syLevel1_Stage1Scene.h"
#include "syObject.h"
#include "syGameObject.h"
#include "sySpriteRenderer.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syTransform.h"
#include "syResourceManager.h"
#include "syTexture.h"
#include "syBackGround.h"
#include "syApplication.h"
#include "syCamera.h"
#include "syForeGround.h"
#include "syAnimator.h"
#include "syPlayer.h"
#include "syCollider.h"
#include "syCollisionManager.h"
#include "syRigidbody.h"
#include "sySound.h"
#include "syResourceManager.h"
#include "syPortalUI.h"
#include "syAbilityItem.h"
#include "syMixItem.h"
#include "syInventory.h"
#include "syDefaultKirby.h"
#include "syFireKirby.h"
#include "syIceKirby.h"
#include "syCutterKirby.h"
#include "syTornadoKirby.h"
#include "syNinjaKirby.h"
#include "sySparkKirby.h"
#include "syWheelKirby.h"
#include "sySwordKirby.h"

#include "syWaddleDee.h"
#include "syHotHead.h"
#include "syHotHead_Fire.h"
#include "sySparky.h"

namespace sy
{
	Level1_Stage1Scene::Level1_Stage1Scene()
		: mPixelBG(nullptr)
	{
	}

	Level1_Stage1Scene::~Level1_Stage1Scene()
	{
	}

	void Level1_Stage1Scene::Initialize()
	{
		// �� ����
		WaddleDee* waddleDee = object::Instantiate<WaddleDee>(eLayerType::Enemy);
		waddleDee->GetComponent<Transform>()->SetPosition(Vector2(430.f, 120.f));

		WaddleDee* waddleDee2 = object::Instantiate<WaddleDee>(eLayerType::Enemy);
		waddleDee2->GetComponent<Transform>()->SetPosition(Vector2(620.f, 120.f));

		WaddleDee* waddleDee3 = object::Instantiate<WaddleDee>(eLayerType::Enemy);
		waddleDee3->GetComponent<Transform>()->SetPosition(Vector2(1350.f, 100.f));

		HotHead* hotHead = object::Instantiate<HotHead>(eLayerType::Enemy);
		hotHead->GetComponent<Transform>()->SetPosition(Vector2(1050.f, 100.f));

		Sparky* sparky = object::Instantiate<Sparky>(eLayerType::Enemy);
		sparky->GetComponent<Transform>()->SetPosition(Vector2(1470.f, 120.f));


		// ��׶��� ����
		Texture* tex = ResourceManager::Load<Texture>(L"World1_Backgrounds", L"..\\Resources\\Map\\Stage\\World1_Backgrounds.png"); // �̹��� ����

		BackGround* Bg = object::Instantiate<BackGround>(eLayerType::BackGround);
		Bg->GetComponent<Transform>()->SetPosition(Vector2(tex->GetWidth() / 2 - 2, tex->GetHeight() / 2 - 2)); // ���� ����

		SpriteRenderer* BgRenderer = Bg->AddComponent<SpriteRenderer>();		
		BgRenderer->SetAffectedCamera(true);
		BgRenderer->SetTexture(tex);
		BgRenderer->SetCameraSpeedRatio(Vector2(6.f, 1.f));

		// �������� ����
		tex = ResourceManager::Load<Texture>(L"Stage1", L"..\\Resources\\Map\\Foreground\\Stage1.bmp"); // �̹��� ����
		ForeGround* Fg = object::Instantiate<ForeGround>(eLayerType::ForeGround);
		Fg->GetComponent<Transform>()->SetPosition(Vector2(tex->GetWidth() / 2, tex->GetHeight() / 2)); // ���� ����

		SpriteRenderer* FgRenderer = Fg->AddComponent<SpriteRenderer>();
		FgRenderer->SetAffectedCamera(true);
		FgRenderer->SetTexture(tex);

		// �ȼ� �̹��� �ε�
		Texture* Pixeltex = ResourceManager::Load<Texture>(L"Stage1_Pixel"
			, L"..\\Resources\\Map\\Foreground\\Stage1_Pixel.bmp");

		mPixelBG = object::Instantiate<BackGround>(eLayerType::Pixel);
		mPixelBG->GetComponent<Transform>()->SetPosition(Vector2(Pixeltex->GetWidth() / 2, Pixeltex->GetHeight() / 2)); // ���� ����

		SpriteRenderer* PixelBgRenderer = mPixelBG->AddComponent<SpriteRenderer>();
		PixelBgRenderer->SetAffectedCamera(true);
		PixelBgRenderer->SetTexture(Pixeltex);
		PixelBgRenderer->SetRenderTrig(false);

		// Portal
		PortalUI* portalUI = object::Instantiate<PortalUI>(eLayerType::Portal);
		portalUI->GetComponent<Transform>()->SetPosition(Vector2(1548.f, 118.f)); 
		// Sound Load
		ResourceManager::Load<Sound>(L"Stage1BGMSound", L"..\\Resources\\Sound\\Theme\\Stage1BGM.wav");

		// ������ ��� ������Ʈ �ʱ�ȭ 
		Scene::Initialize();
	}

	void Level1_Stage1Scene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::MOUSE_MBTN))
		{
			SceneManager::LoadScene(L"Level1_Stage2Scene");
		}

		if (Input::GetKeyDown(eKeyCode::T))
		{
			SpriteRenderer* PixelBgRenderer = mPixelBG->GetComponent<SpriteRenderer>();

			if (PixelBgRenderer->GetRenderTrig())
				PixelBgRenderer->SetRenderTrig(false);
			else
				PixelBgRenderer->SetRenderTrig(true);
		}

		// �ӽ� �� ����
		if (Input::GetKeyDown(eKeyCode::R))
		{
			Player* player = SceneManager::GetPlayer();
			Transform* playerTrans = player->GetComponent<Transform>();

			Vector2 pos = playerTrans->GetPosition();
			pos.x += 50.f;

			//AbilityItem* item = new AbilityItem(eAbilityType::Fire);
			//item->GetComponent<Transform>()->SetPosition(pos);
			//object::ActiveSceneAddGameObject(eLayerType::AbilityItem, item);
			//pos.x += 50.f;

			//AbilityItem* item2 = new AbilityItem(eAbilityType::Ice);
			//item2->GetComponent<Transform>()->SetPosition(pos);
			//object::ActiveSceneAddGameObject(eLayerType::AbilityItem, item2);
			//pos.x += 50.f;

			//AbilityItem* item3 = new AbilityItem(eAbilityType::Cutter);
			//item3->GetComponent<Transform>()->SetPosition(pos);
			//object::ActiveSceneAddGameObject(eLayerType::AbilityItem, item3);
			//pos.x += 50.f;

			//AbilityItem* item4 = new AbilityItem(eAbilityType::Tornado);
			//item4->GetComponent<Transform>()->SetPosition(pos);
			//object::ActiveSceneAddGameObject(eLayerType::AbilityItem, item4);
			//pos.x += 50.f;

			//AbilityItem* item5 = new AbilityItem(eAbilityType::Ninja);
			//item5->GetComponent<Transform>()->SetPosition(pos);
			//object::ActiveSceneAddGameObject(eLayerType::AbilityItem, item5);
			//pos.x += 50.f;

			//AbilityItem* item6 = new AbilityItem(eAbilityType::Spark);
			//item6->GetComponent<Transform>()->SetPosition(pos);
			//object::ActiveSceneAddGameObject(eLayerType::AbilityItem, item6);

			//WaddleDee* waddleDee = object::Instantiate<WaddleDee>(eLayerType::Enemy);
			//waddleDee->GetComponent<Transform>()->SetPosition(pos);
			//waddleDee->Initialize();

			//pos.x += 10.f;
			//HotHead* hotHead = object::Instantiate<HotHead>(eLayerType::Enemy);
			//hotHead->GetComponent<Transform>()->SetPosition(pos);
			//hotHead->Initialize();

			//pos.x += 10.f;
			//Blockin* blockin = object::Instantiate<Blockin>(eLayerType::Enemy);
			//blockin->GetComponent<Transform>()->SetPosition(pos);
			//blockin->Initialize();

			//pos.x += 10.f;
			//SirKibble* sirKibble = object::Instantiate<SirKibble>(eLayerType::Enemy);
			//sirKibble->GetComponent<Transform>()->SetPosition(pos);
			//sirKibble->Initialize();

			//pos.x += 10.f;
			//Crimp* crimp = object::Instantiate<Crimp>(eLayerType::Enemy);
			//crimp->GetComponent<Transform>()->SetPosition(pos);
			//crimp->Initialize();
		}



	}

	void Level1_Stage1Scene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void Level1_Stage1Scene::Enter()
	{
		// �÷��̾� ����
		Player* player = SceneManager::GetPlayer();
		Transform* playerTrans = player->GetComponent<Transform>();
		playerTrans->SetPosition(Vector2(30.f, 100.f));
		Animator* playerAni = player->GetComponent<Animator>();
		playerAni->SetAffectedCamera(true);
		Collider* playerCol = player->GetComponent<Collider>();
		playerCol->SetAffectedCamera(true);
		//playerCol->SetSize(Vector2(50.f, 50.f));
		player->SetPlayerMode(ePlayerMode::PlayMode);
		playerTrans->SetDirection(eDirection::RIGHT);

		// �÷��̾� Ÿ�Կ����� ���� ���� 
		eAbilityType playerType = player->GetAbilityType();
		if (playerType == eAbilityType::Normal)
		{
			DefaultKirby* defaultKirby = dynamic_cast<DefaultKirby*>(player->GetActiveKirby());
			defaultKirby->SetKirbyState(eDefaultKirbyState::Turn);
			playerAni->PlayAnimation(L"DefaultKirby_Right_Turn", false);
		}
		else if (playerType == eAbilityType::Fire)
		{
			FireKirby* fireKirby = dynamic_cast<FireKirby*>(player->GetActiveKirby());
			fireKirby->SetKirbyState(eFireKirbyState::Turn);
			playerAni->PlayAnimation(L"FireKirby_Right_Turn", false);
		}
		else if (playerType == eAbilityType::Ice)
		{
			IceKirby* iceKirby = dynamic_cast<IceKirby*>(player->GetActiveKirby());
			iceKirby->SetKirbyState(eIceKirbyState::Turn);
			playerAni->PlayAnimation(L"IceKirby_Right_Turn", false);
		}
		else if (playerType == eAbilityType::Cutter)
		{
			CutterKirby* cutterKirby = dynamic_cast<CutterKirby*>(player->GetActiveKirby());
			cutterKirby->SetKirbyState(eCutterKirbyState::Turn);
			playerAni->PlayAnimation(L"CutterKirby_Right_Turn", false);
		}
		else if (playerType == eAbilityType::Tornado)
		{
			TornadoKirby* tornadoKirby = dynamic_cast<TornadoKirby*>(player->GetActiveKirby());
			tornadoKirby->SetKirbyState(eTornadoKirbyState::Turn);
			playerAni->PlayAnimation(L"TornadoKirby_Right_Turn", false);
		}
		else if (playerType == eAbilityType::Ninja)
		{
			NinjaKirby* ninjaKirby = dynamic_cast<NinjaKirby*>(player->GetActiveKirby());
			ninjaKirby->SetKirbyState(eNinjaKirbyState::Turn);
			playerAni->PlayAnimation(L"NinjaKirby_Right_Turn", false);
		}
		else if (playerType == eAbilityType::Spark)
		{
			SparkKirby* sparkKirby = dynamic_cast<SparkKirby*>(player->GetActiveKirby());
			sparkKirby->SetKirbyState(eSparkKirbyState::Turn);
			playerAni->PlayAnimation(L"SparkKirby_Right_Turn", false);
		}
		//else if (playerType == eAbilityType::Wheel)
		//{
		//	WheelKirby* wheelKirby = dynamic_cast<WheelKirby*>(player->GetActiveKirby());
		//	wheelKirby->SetKirbyState(eWheelKirbyState::Turn);
		//	playerAni->PlayAnimation(L"WheelKirby_Right_Turn", false);
		//}
		else if (playerType == eAbilityType::Sword)
		{
			SwordKirby* swordKirby = dynamic_cast<SwordKirby*>(player->GetActiveKirby());
			swordKirby->SetKirbyState(eSwordKirbyState::Turn);
			playerAni->PlayAnimation(L"SwordKirby_Right_Turn", false);
		}

		player->GetComponent<Rigidbody>()->SetGround(false);

		// ī�޶� ���� 
		Camera::SetTarget(player);
		Camera::SetCameraLimit(Vector2(1588.f, 207.f));
		Camera::Pause(1.f, RGB(255, 255, 255));
		Camera::fadeIn(1.f, RGB(255, 255, 255));

		// ���̾� �浹 ����
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Enemy, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Effect, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Portal, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::AbilityItem, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Enemy, eLayerType::Effect, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Enemy, eLayerType::Enemy, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Effect, eLayerType::AbilityItem, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Effect, eLayerType::Effect, true);

		// ����� ���
		ResourceManager::Find<Sound>(L"Stage1BGMSound")->Play(true);
	}

	void Level1_Stage1Scene::Exit()
	{
		// ����� ����
		ResourceManager::AllSoundStop();

		// ī�޶� ���� ����
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();
	}
}