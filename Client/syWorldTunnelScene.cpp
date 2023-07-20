#include "syWorldTunnelScene.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syObject.h"
#include "syDefaultKirby.h"
#include "syTransform.h"
#include "syResourceManager.h"
#include "syApplication.h"
#include "syCamera.h"
#include "syAnimator.h"
#include "syWorldTunnel_BG.h"
#include "syPlayer.h"
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
	WorldTunnelScene::WorldTunnelScene()
		: mPlayer(nullptr)
	{
	}

	WorldTunnelScene::~WorldTunnelScene()
	{
	}

	void WorldTunnelScene::Initialize()
	{
		WorldTunnel_BG* Bg = object::Instantiate<WorldTunnel_BG>(eLayerType::BackGround);
		Vector2 vec = Vector2(Application::GetResolution()) / 2.f;
		vec.y /= 2.f;
		Bg->GetComponent<Transform>()->SetPosition(vec); // 중점 설정

		// 플레이어 설정
		mPlayer = object::Instantiate<DefaultKirby>(eLayerType::Player);
		Transform* PlayerTrans = mPlayer->GetComponent<Transform>();
		PlayerTrans->SetPosition(Vector2(275.f, 100.f));



		// 적 생성
		WaddleDee* waddleDee = object::Instantiate<WaddleDee>(eLayerType::Enemy);
		waddleDee->GetComponent<Transform>()->SetPosition(Vector2(100.f, 100.f));

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

		Scene::Initialize();
	}

	void WorldTunnelScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::MOUSE_RBTN))
		{
			SceneManager::LoadScene(L"EndingScene");
		}
	}

	void WorldTunnelScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void WorldTunnelScene::Enter()
	{
		// 카메라 설정 
		//Camera::SetTarget(nullptr);
		Camera::SetTarget(mPlayer);
	}

	void WorldTunnelScene::Exit()
	{
		// 카메라 설정 해제
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();
	}
}