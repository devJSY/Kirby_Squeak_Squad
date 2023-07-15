#include "syEndingScene.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syObject.h"
#include "sySpriteRenderer.h"
#include "syPlayer.h"
#include "syTransform.h"
#include "syResourceManager.h"
#include "syTexture.h"
#include "syBackGround.h"
#include "syApplication.h"
#include "syAnimator.h"

namespace sy
{
	EndingScene::EndingScene()
		: mVideo(nullptr)
	{
	}

	EndingScene::~EndingScene()
	{
	}

	void EndingScene::Initialize()
	{
		mVideo = object::Instantiate<Video>(eLayerType::Video);
		assert(mVideo);
		assert(mVideo->AddComponent<Animator>());
		mVideo->GetComponent<Transform>()->SetPosition(Vector2(Application::GetResolution()) / 2.f); // 중점 설정
		mVideo->SetSpeed(5.f); // 재생속도 5배 설정

		Animator* videoAnimator = mVideo->GetComponent<Animator>();
		assert(videoAnimator);
		videoAnimator->CreateAnimationFolder(L"EndingVideo", L"..\\Resources\\Video\\Ending", Vector2::Zero, 0.0444931f / mVideo->GetSpeed());
		videoAnimator->SetAffectedCamera(false);
		videoAnimator->PlayAnimation(L"EndingVideo", true);

		Scene::Initialize();
	}

	void EndingScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::MOUSE_RBTN))
		{
			SceneManager::LoadScene(L"OpeningScene");
		}
	}

	void EndingScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		//ShowSceneName(hdc, GetName(), L"Change to OpeningScene : Mouse LBTN");
	}

	void EndingScene::Enter()
	{
		Animator* videoAnimator = mVideo->GetComponent<Animator>();
		videoAnimator->PlayAnimation(L"EndingVideo", false);
	}

	void EndingScene::Exit()
	{
	}
}