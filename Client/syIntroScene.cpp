#include "syIntroScene.h"
#include "syCamera.h"
#include "syAnimator.h"
#include "syResourceManager.h"
#include "syTexture.h"
#include "syObject.h"
#include "syTransform.h"
#include "syApplication.h"
#include "syVideo.h"
#include "sySound.h"
#include "syInput.h"

namespace sy
{
	IntroScene::IntroScene()
		: mVideo(nullptr)
	{
	}

	IntroScene::~IntroScene()
	{
	}

	void IntroScene::Initialize()
	{
		// ���� ����
		mVideo = object::Instantiate<Video>(eLayerType::Video);

		// ��ġ ����
		Vector2 pos = Vector2(Application::GetResolution()) / 2.f;
		pos.y /= 2.f;
		mVideo->GetComponent<Transform>()->SetPosition(pos);
		mVideo->SetSpeed(1.f); // ����ӵ� ����

		Animator* videoAnimator = mVideo->AddComponent<Animator>();
		videoAnimator->CreateAnimationFolder(L"IntroVideo", L"..\\Resources\\Video\\Intro", 0.0507757404795487f / mVideo->GetSpeed());
		videoAnimator->PlayAnimation(L"IntroVideo", false);
		videoAnimator->SetAffectedCamera(false);

		// Sound Load
		ResourceManager::Load<Sound>(L"WorldSelectSound", L"..\\Resources\\Sound\\Theme\\WorldSelect.wav");

		Scene::Initialize();
	}

	void IntroScene::Update()
	{
		// ���� ����� ������ ���� ������ �̵�
		if (mVideo != nullptr && mVideo->GetComponent<Animator>()->IsActiveAnimationComplete())
		{
			SceneManager::LoadScene(L"LevelSelectScene");
		}

		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D) || Input::GetKeyDown(eKeyCode::W))
		{
			SceneManager::LoadScene(L"LevelSelectScene");
		}

		Scene::Update();
	}

	void IntroScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void IntroScene::Enter()
	{
		// ī�޶� ���� 
		Camera::SetTarget(nullptr);

		// ���� ���
		Animator* videoAnimator = mVideo->GetComponent<Animator>();
		videoAnimator->PlayAnimation(L"IntroVideo", false);
		videoAnimator->ActiveAnimationReset();
		ResourceManager::Find<Sound>(L"WorldSelectSound")->Play(true);
	}

	void IntroScene::Exit()
	{
		// ī�޶� ���� ����
		Camera::SetTarget(nullptr);

		// ����� ����
		ResourceManager::Find<Sound>(L"WorldSelectSound")->Stop(true);

	}
}