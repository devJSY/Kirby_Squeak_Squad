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


namespace sy
{
	WorldTunnelScene::WorldTunnelScene()
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
		Bg->GetComponent<Transform>()->SetPosition(vec); // ���� ����

		Scene::Initialize();
	}

	void WorldTunnelScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::MOUSE_LBTN))
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
		// �÷��̾� ����
		Player* player = SceneManager::GetPlayer();
		Transform* playerTrans = player->GetComponent<Transform>();
		playerTrans->SetPosition(Vector2(275.f, 100.f));
		Animator* playerAni = player->GetComponent<Animator>();
		playerAni->SetAffectedCamera(true);
		Collider* playerCol = player->GetComponent<Collider>();
		playerCol->SetAffectedCamera(true);
		player->SetPlayerMode(ePlayerMode::LevelMode);

		// ī�޶� ���� 
		//Camera::SetTarget(nullptr);
		Camera::SetTarget(player);

		// ���̾� �浹 ����
		CollisionManager::CollisionLayerCheck(eLayerType::Enemy, eLayerType::Effect, true);
	}

	void WorldTunnelScene::Exit()
	{
		// ī�޶� ���� ����
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();
	}
}