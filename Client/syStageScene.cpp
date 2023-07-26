#include "syStageScene.h"
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

#include "syWaddleDee.h"
#include "syBlockin.h"
#include "syCrimp.h"
#include "syHotHead.h"
#include "syHotHead_Fire.h"
#include "syIce.h"
#include "sySirKibble.h"

#include "syGround.h"

namespace sy
{
	StageScene::StageScene()
	{
	}

	StageScene::~StageScene()
	{
	}

	void StageScene::Initialize()
	{
		// ��׶��� ����
		Texture* tex = ResourceManager::Load<Texture>(L"World1_Backgrounds", L"..\\Resources\\Map\\World1_Backgrounds.bmp"); // �̹��� ����

		BackGround* Bg = object::Instantiate<BackGround>(eLayerType::BackGround);
		Bg->GetComponent<Transform>()->SetPosition(Vector2(tex->GetWidth() / 2 - 2, tex->GetHeight() / 2 - 2)); // ���� ����

		SpriteRenderer* BgRenderer = Bg->AddComponent<SpriteRenderer>();		
		BgRenderer->SetAffectedCamera(false);
		BgRenderer->SetTexture(tex);

		// �������� ����
		tex = ResourceManager::Load<Texture>(L"Stage1", L"..\\Resources\\Map\\Stage1.bmp"); // �̹��� ����
		ForeGround* Fg = object::Instantiate<ForeGround>(eLayerType::ForeGround);
		Fg->GetComponent<Transform>()->SetPosition(Vector2(tex->GetWidth() / 2, tex->GetHeight() / 2)); // ���� ����

		SpriteRenderer* FgRenderer = Fg->AddComponent<SpriteRenderer>();
		FgRenderer->SetAffectedCamera(true);
		FgRenderer->SetTexture(tex);

		// �� ����
		WaddleDee* waddleDee = object::Instantiate<WaddleDee>(eLayerType::Enemy);
		waddleDee->GetComponent<Transform>()->SetPosition(Vector2(100.f, 100.f));
		//col = waddleDee->GetComponent<Collider>();
		//col->SetSize(Vector2(50.f, 50.f));

		Blockin* Block = object::Instantiate<Blockin>(eLayerType::Enemy);
		Block->GetComponent<Transform>()->SetPosition(Vector2(150.f, 100.f));

		Crimp* flower = object::Instantiate<Crimp>(eLayerType::Enemy);
		flower->GetComponent<Transform>()->SetPosition(Vector2(200.f, 100.f));

		HotHead* hotHead = object::Instantiate<HotHead>(eLayerType::Enemy);
		hotHead->GetComponent<Transform>()->SetPosition(Vector2(250.f, 100.f));

		Ice* ice = object::Instantiate<Ice>(eLayerType::Enemy);
		ice->GetComponent<Transform>()->SetPosition(Vector2(300.f, 100.f));

		SirKibble* sirkibble = object::Instantiate<SirKibble>(eLayerType::Enemy);
		sirkibble->GetComponent<Transform>()->SetPosition(Vector2(350.f, 100.f));

		Ground* ground = object::Instantiate<Ground>(eLayerType::Enemy);

		// ������ ��� ������Ʈ �ʱ�ȭ 
		Scene::Initialize();
	}

	void StageScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::MOUSE_RBTN))
		{
			SceneManager::LoadScene(L"EndingScene");
		}
	}

	void StageScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void StageScene::Enter()
	{
		// �÷��̾� ����
		Player* player = SceneManager::GetPlayer();
		Transform* playerTrans = player->GetComponent<Transform>();
		playerTrans->SetPosition(Vector2(275.f, 100.f));
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
			playerAni->PlayAnimation(L"DefaultKirby_Right_Drop", false);
		}

		player->GetComponent<Rigidbody>()->SetGround(false);

		// ī�޶� ���� 
		Camera::SetTarget(player);

		// ���̾� �浹 ����
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Enemy, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Effect, true);
	}

	void StageScene::Exit()
	{
		// ī�޶� ���� ����
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();
	}
}