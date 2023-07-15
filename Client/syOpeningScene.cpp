#include "syOpeningScene.h"
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
	OpeningScene::OpeningScene()
		: mVideo(nullptr)
	{
	}

	OpeningScene::~OpeningScene()
	{
	}

	void OpeningScene::Initialize()
	{
		// ���� ����
		mVideo = object::Instantiate<Video>(eLayerType::Video);
		assert(mVideo);
		Animator* videoAnimator = mVideo->AddComponent<Animator>();
		assert(videoAnimator);
		mVideo->GetComponent<Transform>()->SetPosition(Vector2(Application::GetResolution()) / 2.f); // ���� ����
		mVideo->SetSpeed(3.f); // ����ӵ� 3�� ����
		videoAnimator->CreateAnimationFolder(L"OpeningVideo", L"..\\Resources\\Video\\Opening", Vector2::Zero, 0.03196546f / mVideo->GetSpeed());
		videoAnimator->SetAffectedCamera(false);
		videoAnimator->PlayAnimation(L"OpeningVideo", false);

		Scene::Initialize();
	}

	void OpeningScene::Update()
	{
		Scene::Update();

		// ���� ����� ������ ���� ������ �̵�
		if ( mVideo != nullptr && mVideo->GetComponent<Animator>()->IsComplete())
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
	}

	void OpeningScene::Enter()
	{
		// ī�޶� ���� 
		Camera::SetTarget(nullptr);

		// ���� ���
		Animator* videoAnimator = mVideo->GetComponent<Animator>();
		videoAnimator->PlayAnimation(L"OpeningVideo", false);
	}

	void OpeningScene::Exit()
	{
		// ī�޶� ���� ����
		Camera::SetTarget(nullptr);
	}
}