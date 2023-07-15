#include "syTitleScene.h"
#include "syPlayer.h"
#include "sySpriteRenderer.h"
#include "syObject.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syPlayer.h"
#include "sySpriteRenderer.h"
#include "syTransform.h"
#include "syResourceManager.h"
#include "syTexture.h"
#include "syBackGround.h"
#include "syApplication.h"
#include "syAnimator.h"

namespace sy
{
	TitleScene::TitleScene()
		: mVideo(nullptr)
	{
	}

	TitleScene::~TitleScene()
	{
	}

	void TitleScene::Initialize()
	{
		mVideo = object::Instantiate<Video>(eLayerType::Video);
		assert(mVideo);
		assert(mVideo->AddComponent<Animator>());
		mVideo->GetComponent<Transform>()->SetPosition(Vector2(Application::GetResolution()) / 2.f); // 중점 설정
		mVideo->SetSpeed(3.f); // 재생속도 3배 설정

		Animator* videoAnimator = mVideo->GetComponent<Animator>();
		assert(videoAnimator);
		videoAnimator->CreateAnimationFolder(L"TitleVideo", L"..\\Resources\\Video\\Title", Vector2::Zero, 0.033224f / mVideo->GetSpeed());
		videoAnimator->SetAffectedCamera(false);
		videoAnimator->PlayAnimation(L"TitleVideo", true);

		Scene::Initialize();
	}

	void TitleScene::Update()
	{
		Scene::Update();

		if (mVideo->GetComponent<Animator>()->IsComplete())
		{
			SceneManager::LoadScene(L"LevelSelectScene");
		}

		if (Input::GetKeyDown(eKeyCode::MOUSE_RBTN))
		{
			SceneManager::LoadScene(L"LevelSelectScene");
		}
	}

	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		//ShowSceneName(hdc, GetName(), L"Change to LevelSelectScene : Mouse LBTN");
	}
	void TitleScene::Enter()
	{
		Animator* videoAnimator = mVideo->GetComponent<Animator>();
		videoAnimator->PlayAnimation(L"TitleVideo", true);
	}

	void TitleScene::Exit()
	{
	}
}