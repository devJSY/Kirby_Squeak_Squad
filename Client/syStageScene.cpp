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

#include "syWaddleDee.h"
#include "syBlockEnemy.h"
#include "syFlower.h"
#include "syHotHead.h"
#include "syHotHead_Fire.h"
#include "syIce.h"
#include "sySirKibble.h"

namespace sy
{
	StageScene::StageScene()
		: mPlayer(nullptr)
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


		// �÷��̾� ����
		mPlayer = object::Instantiate<DefaultKirby>(eLayerType::Player);	
		Transform* PlayerTrans = mPlayer->GetComponent<Transform>();	
		PlayerTrans->SetPosition(Vector2(275.f, 100.f));
		Collider* col = mPlayer->AddComponent<Collider>();
		col->SetSize(Vector2(50.f, 50.f));

		// �� ����
		WaddleDee* waddleDee = object::Instantiate<WaddleDee>(eLayerType::Enemy);
		waddleDee->GetComponent<Transform>()->SetPosition(Vector2(100.f, 100.f));
		col = waddleDee->AddComponent<Collider>();
		col->SetSize(Vector2(50.f, 50.f));

		BlockEnemy* Block = object::Instantiate<BlockEnemy>(eLayerType::Enemy);
		Block->GetComponent<Transform>()->SetPosition(Vector2(150.f, 100.f));

		Flower* flower = object::Instantiate<Flower>(eLayerType::Enemy);
		flower->GetComponent<Transform>()->SetPosition(Vector2(200.f, 100.f));

		HotHead* hotHead = object::Instantiate<HotHead>(eLayerType::Enemy);
		hotHead->GetComponent<Transform>()->SetPosition(Vector2(250.f, 100.f));

		Ice* ice = object::Instantiate<Ice>(eLayerType::Enemy);
		ice->GetComponent<Transform>()->SetPosition(Vector2(300.f, 100.f));

		SirKibble* sirkibble = object::Instantiate<SirKibble>(eLayerType::Enemy);
		sirkibble->GetComponent<Transform>()->SetPosition(Vector2(350.f, 100.f));

		// ������ ��� ������Ʈ �ʱ�ȭ 
		Scene::Initialize();
	}

	void StageScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::MOUSE_RBTN))
		{
			SceneManager::LoadScene(L"WorldTunnelScene");
		}
	}

	void StageScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void StageScene::Enter()
	{
		// ī�޶� ���� 
		Camera::SetTarget(mPlayer);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Enemy, true);
	}

	void StageScene::Exit()
	{
		// ī�޶� ���� ����
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();
	}
}