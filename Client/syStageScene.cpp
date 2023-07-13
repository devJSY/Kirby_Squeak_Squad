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
		BgRenderer->SetTexture(ResourceManager::Load<Texture>(L"Stage1", L"..\\Resources\\Map\\Stage1.bmp")); // 이미지 설정
		BgRenderer->SetBmpRGB(255, 0, 255); // 마젠타 색상
		BgRenderer->SetAffectCamera(true);
		//Bg->GetComponent<Transform>()->SetPosition(Vector2(Application::GetResolution()) / 2.f); // 중점 설정
		


		Player* player = object::Instantiate<Player>(eLayerType::Player);
		assert(player);
		assert(player->AddComponent<SpriteRenderer>());
		SpriteRenderer* playerRenderer = player->GetComponent<SpriteRenderer>();
		assert(playerRenderer);
		playerRenderer->SetTexture(ResourceManager::Load<Texture>(L"sword_kirby_change", L"..\\Resources\\Kirby\\SwordKirby\\sword kirby change.png")); // 이미지 설정
		playerRenderer->SetAffectCamera(true);

		//Camera::SetTarget(player); //오브젝트생성은 씬진입시 해야함 여기서 설정한 오브젝트가 다른씬에 영향을 줘선안됨

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