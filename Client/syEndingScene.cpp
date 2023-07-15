#include "syEndingScene.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syObject.h"
#include "sySpriteRenderer.h"
#include "syKirby.h"
#include "syTransform.h"
#include "syResourceManager.h"
#include "syTexture.h"
#include "syBackGround.h"
#include "syApplication.h"
#include "syAnimator.h"
#include "syCamera.h"

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
		Animator* videoAnimator = mVideo->AddComponent<Animator>();
		assert(videoAnimator);
		mVideo->GetComponent<Transform>()->SetPosition(Vector2(Application::GetResolution()) / 2.f); // ���� ����
		mVideo->SetSpeed(5.f); // ����ӵ� 5�� ����
		videoAnimator->CreateAnimationFolder(L"EndingVideo", L"..\\Resources\\Video\\Ending", 0.0444931f / mVideo->GetSpeed());
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
	}

	void EndingScene::Enter()
	{
		// ī�޶� ���� 
		Camera::SetTarget(nullptr);

		Animator* videoAnimator = mVideo->GetComponent<Animator>();
		videoAnimator->PlayAnimation(L"EndingVideo", false);
	}

	void EndingScene::Exit()
	{
		// ī�޶� ���� ����
		Camera::SetTarget(nullptr);
	}
}