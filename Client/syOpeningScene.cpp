#include "syOpeningScene.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syObject.h"
#include "syTransform.h"
#include "syVideo.h"
#include "syApplication.h"
#include "syAnimator.h"
#include "syCamera.h"
#include "syCollisionManager.h"
#include "sySoundManager.h"
#include "sySound.h"
#include "syResourceManager.h"
#include "syTime.h"

namespace sy
{
	OpeningScene::OpeningScene()
		: mVideo(nullptr)
		, mPassedTime(0.f)
		, mbSoundPlay(false)
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

		// Sound Load
		ResourceManager::Load<Sound>(L"OpeningSound", L"..\\Resources\\Sound\\Theme\\Opening.wav");

		Scene::Initialize();
	}

	void OpeningScene::Update()
	{
		Scene::Update();

		mPassedTime += Time::DeltaTime();

		if (mPassedTime >= 5.5f && mbSoundPlay == false)
		{
			// ����� ���
			ResourceManager::Find<Sound>(L"OpeningSound")->Play(false);
			mbSoundPlay = true;
		}

		// ���� ����� ������ ���� ������ �̵�
		if ( mVideo != nullptr && mVideo->GetComponent<Animator>()->IsActiveAnimationComplete())
		{
			SceneManager::LoadScene(L"TitleScene");
		}

		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D) || Input::GetKeyDown(eKeyCode::W))
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

		mPassedTime = 0.f;
		mbSoundPlay = false;
	}

	void OpeningScene::Exit()
	{
		// ����� ����
		ResourceManager::AllSoundStop();

		// ī�޶� ���� ����
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();

		mPassedTime = 0.f;
		mbSoundPlay = false;
	}
}