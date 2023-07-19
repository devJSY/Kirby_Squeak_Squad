#include "syOpeningScene.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syObject.h"
#include "syTransform.h"
#include "syVideo.h"
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
		
		// ��ġ ����
		mVideo->GetComponent<Transform>()->SetPosition(Vector2(Application::GetResolution()) / 2.f);
		mVideo->SetSpeed(1.f); // ����ӵ� ����
		
		Animator* videoAnimator = mVideo->AddComponent<Animator>();
		videoAnimator->CreateAnimationFolder(L"OpeningVideo", L"..\\Resources\\Video\\Opening", 0.03196546f / mVideo->GetSpeed());
		videoAnimator->PlayAnimation(L"OpeningVideo", false);
		videoAnimator->SetAffectedCamera(false);

		Scene::Initialize();
	}

	void OpeningScene::Update()
	{
		Scene::Update();

		// ���� ����� ������ ���� ������ �̵�
		if ( mVideo != nullptr && mVideo->GetComponent<Animator>()->IsActiveAnimationComplete())
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
		videoAnimator->ActiveAnimationReset();
	}

	void OpeningScene::Exit()
	{
		// ī�޶� ���� ����
		Camera::SetTarget(nullptr);
	}
}