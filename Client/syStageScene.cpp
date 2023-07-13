#include "syStageScene.h"
#include "syPlayer.h"
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
		BackGround* Bg = object::Instantiate<BackGround>(eLayerType::BackGround);
		assert(Bg);
		assert(Bg->AddComponent<SpriteRenderer>());
		SpriteRenderer* BgRenderer = Bg->GetComponent<SpriteRenderer>();
		assert(BgRenderer);
		BgRenderer->SetTexture(ResourceManager::Load<Texture>(L"Stage1", L"..\\Resources\\Map\\Stage1.bmp")); // �̹��� ����
		BgRenderer->SetBmpRGB(255, 0, 255); // ����Ÿ ����
		BgRenderer->SetAffectCamera(true);
		//Bg->GetComponent<Transform>()->SetPosition(Vector2(Application::GetResolution()) / 2.f); // ���� ����
		


		Player* player = object::Instantiate<Player>(eLayerType::Player);
		assert(player);
		assert(player->AddComponent<SpriteRenderer>());
		SpriteRenderer* playerRenderer = player->GetComponent<SpriteRenderer>();
		assert(playerRenderer);
		playerRenderer->SetTexture(ResourceManager::Load<Texture>(L"sword_kirby_change", L"..\\Resources\\Kirby\\SwordKirby\\sword kirby change.png")); // �̹��� ����
		playerRenderer->SetAffectCamera(true);

		//Camera::SetTarget(player); //������Ʈ������ �����Խ� �ؾ��� ���⼭ ������ ������Ʈ�� �ٸ����� ������ �༱�ȵ�

		Scene::Initialize();
	}

	void StageScene::Update()
	{
		Scene::Update();
		if (Input::GetKeyDown(eKeyCode::R) || Input::GetKeyDown(eKeyCode::MOUSE_LBTN))
		{
			SceneManager::LoadScene(L"WorldTunnelScene");
		}
	}

	void StageScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		ShowSceneName(hdc, GetName(), L"Change to WorldTunnelScene : R or Mouse LBTN");
	}
}