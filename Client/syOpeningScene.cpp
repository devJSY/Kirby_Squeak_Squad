#include "syOpeningScene.h"
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
	OpeningScene::OpeningScene()
		: mVideo(nullptr)
	{
	}

	OpeningScene::~OpeningScene()
	{
	}

	void OpeningScene::Initialize()
	{
		mVideo = object::Instantiate<Video>(eLayerType::Video);
		assert(mVideo);
		assert(mVideo->AddComponent<Animator>());
		mVideo->GetComponent<Transform>()->SetPosition(Vector2(Application::GetResolution()) / 2.f); // 중점 설정
		mVideo->SetSpeed(3.f); // 재생속도 3배 설정

		Animator* videoAnimator = mVideo->GetComponent<Animator>();
		assert(videoAnimator);
		videoAnimator->CreateAnimationFolder(L"OpeningVideo", L"..\\Resources\\Video\\Opening", Vector2::Zero, 0.03196546f / mVideo->GetSpeed());
		videoAnimator->SetAffectedCamera(false);
		videoAnimator->PlayAnimation(L"OpeningVideo", false);

		Scene::Initialize();
	}

	void OpeningScene::Update()
	{
		Scene::Update();

		if (mVideo->GetComponent<Animator>()->IsComplete())
		{
			SceneManager::LoadScene(L"TitleScene");
		}

		if (Input::GetKeyDown(eKeyCode::MOUSE_RBTN))
		{
			SceneManager::LoadScene(L"TitleScene");
		}

	}

	void OpeningScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		//ShowSceneName(hdc, GetName(), L"Change to TitleScene : Mouse LBTN");
	}

	void OpeningScene::Enter()
	{
		Animator* videoAnimator = mVideo->GetComponent<Animator>();
		videoAnimator->PlayAnimation(L"OpeningVideo", false);
	}

	void OpeningScene::Exit()
	{
	}
}