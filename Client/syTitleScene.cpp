#include "syTitleScene.h"
#include "syKirby.h"
#include "sySpriteRenderer.h"
#include "syObject.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syKirby.h"
#include "sySpriteRenderer.h"
#include "syTransform.h"
#include "syResourceManager.h"
#include "syTexture.h"
#include "syBackGround.h"
#include "syApplication.h"
#include "syAnimator.h"
#include "syCamera.h"

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
		Animator* videoAnimator = mVideo->AddComponent<Animator>();
		assert(videoAnimator);
		mVideo->GetComponent<Transform>()->SetPosition(Vector2(Application::GetResolution()) / 2.f); // ���� ����
		mVideo->SetSpeed(3.f); // ����ӵ� 3�� ����
		videoAnimator->CreateAnimationFolder(L"TitleVideo", L"..\\Resources\\Video\\Title", 0.033224f / mVideo->GetSpeed());
		videoAnimator->SetAffectedCamera(false);
		videoAnimator->PlayAnimation(L"TitleVideo", true);

		Scene::Initialize();
	}

	void TitleScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::MOUSE_RBTN))
		{
			SceneManager::LoadScene(L"LevelSelectScene");
		}
	}

	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void TitleScene::Enter()
	{
		// ī�޶� ���� 
		Camera::SetTarget(nullptr);

		Animator* videoAnimator = mVideo->GetComponent<Animator>();
		videoAnimator->PlayAnimation(L"TitleVideo", true);
	}

	void TitleScene::Exit()
	{
		// ī�޶� ���� ����
		Camera::SetTarget(nullptr);
	}
}