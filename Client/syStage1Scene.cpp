#include "syStage1Scene.h"
#include "syDefaultKirby.h"
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

#include "syWaddleDee.h"
#include "syHotHead.h"
#include "syHotHead_Fire.h"

#include "syBlockin.h"
#include "sySirKibble.h"
#include "syCrimp.h"

#include "syBlock.h"

namespace sy
{
	Stage1Scene::Stage1Scene()
		: mPixelBG(nullptr)
	{
	}

	Stage1Scene::~Stage1Scene()
	{
	}

	void Stage1Scene::Initialize()
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

	void Stage1Scene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::MOUSE_RBTN))
		{
			SceneManager::LoadScene(L"Stage2Scene");
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
		if (Input::GetKeyDown(eKeyCode::MOUSE_LBTN))
		{
			Player* player = SceneManager::GetPlayer();
			Transform* playerTrans = player->GetComponent<Transform>();

			Vector2 pos = playerTrans->GetPosition();
			pos.x += 50.f;
			pos.y -= 50.f;

			WaddleDee* waddleDee = object::Instantiate<WaddleDee>(eLayerType::Enemy);
			waddleDee->GetComponent<Transform>()->SetPosition(pos);
			waddleDee->Initialize();

			pos.x += 10.f;
			HotHead* hotHead = object::Instantiate<HotHead>(eLayerType::Enemy);
			hotHead->GetComponent<Transform>()->SetPosition(pos);
			hotHead->Initialize();

			pos.x += 10.f;
			Blockin* blockin = object::Instantiate<Blockin>(eLayerType::Enemy);
			blockin->GetComponent<Transform>()->SetPosition(pos);
			blockin->Initialize();

			pos.x += 10.f;
			SirKibble* sirKibble = object::Instantiate<SirKibble>(eLayerType::Enemy);
			sirKibble->GetComponent<Transform>()->SetPosition(pos);
			sirKibble->Initialize();

			pos.x += 10.f;
			Crimp* crimp = object::Instantiate<Crimp>(eLayerType::Enemy);
			crimp->GetComponent<Transform>()->SetPosition(pos);
			crimp->Initialize();

			pos.y += 50.f;
			Block* block = object::Instantiate<Block>(eLayerType::Block);
			block->GetComponent<Transform>()->SetPosition(pos);
			block->Initialize();
		}



	}

	void Stage1Scene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void Stage1Scene::Enter()
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
			DefaultKirby* defaultKirby = dynamic_cast<DefaultKirby*>(player);
			defaultKirby->SetKirbyState(eDefaultKirbyState::Turn);
			playerAni->PlayAnimation(L"DefaultKirby_Right_Turn", false);
		}

		player->GetComponent<Rigidbody>()->SetGround(false);

		// ī�޶� ���� 
		Camera::SetTarget(player);
		Camera::SetCameraLimit(Vector2(1588.f, 207.f));

		// ���̾� �浹 ����
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Enemy, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Effect, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Portal, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Block, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Effect, eLayerType::Block, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Enemy, eLayerType::Effect, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Enemy, eLayerType::Block, true);

		// ����� ����
		ResourceManager::Find<Sound>(L"StageSelectSound")->Stop(true);
		// ����� ���
		ResourceManager::Find<Sound>(L"Stage1BGMSound")->Play(true);
	}

	void Stage1Scene::Exit()
	{
		// ī�޶� ���� ����
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();

		// ����� ���
		ResourceManager::Find<Sound>(L"Stage1BGMSound")->Stop(true);
	}
}