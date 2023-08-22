#include "syDanceScene.h"
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
#include "syTime.h"

namespace sy
{
	DanceScene::DanceScene()
		: mType(eDanceSceneType::End)
		, mNextSceneName()
		, mVideo(nullptr)
		, mPassedTime(0.f)
		, mbSoundPlay(false)
		, mbSceneChange(false)
	{
	}

	DanceScene::~DanceScene()
	{
	}

	void DanceScene::Initialize()
	{
		// 비디오 생성
		mVideo = object::Instantiate<Video>(eLayerType::Video);

		// 위치 설정
		mVideo->GetComponent<Transform>()->SetPosition(Vector2(Application::GetResolution()) / 2.f);
		mVideo->SetSpeed(1.f); // 재생속도 설정

		Animator* VideoAnimator = mVideo->AddComponent<Animator>();
		VideoAnimator->CreateAnimationFolder(L"BossClearVideo", L"..\\Resources\\Video\\Dance\\BossClear", 0.05f / mVideo->GetSpeed());
		VideoAnimator->CreateAnimationFolder(L"NormalClearVideo", L"..\\Resources\\Video\\Dance\\NormalClear", 0.0467836257309942f / mVideo->GetSpeed());
		VideoAnimator->SetAffectedCamera(false);

		// Sound Load
		ResourceManager::Load<Sound>(L"BossClearSound", L"..\\Resources\\Sound\\Theme\\BossClear.wav");
		ResourceManager::Load<Sound>(L"NormalClearSound", L"..\\Resources\\Sound\\Theme\\NormalClear.wav");

		Scene::Initialize();
	}

	void DanceScene::Update()
	{
		mPassedTime += Time::DeltaTime();
	
		if (mType == eDanceSceneType::BossClear)
		{
			if (mPassedTime >= 2.4f && mbSoundPlay == false)
			{
				ResourceManager::Find<Sound>(L"BossClearSound")->Play(false);
				mbSoundPlay = true;
			}			
		}
		else if (mType == eDanceSceneType::NormalClear)
		{
			if (mPassedTime >= 1.f && mbSoundPlay == false)
			{
				ResourceManager::Find<Sound>(L"NormalClearSound")->Play(false);
				mbSoundPlay = true;
			}		
		}		

		// 비디오 재생이 끝나면 다음 씬으로 이동
		if (mVideo != nullptr 
			&& mVideo->GetComponent<Animator>()->IsActiveAnimationComplete())
		{
			if (mbSceneChange == false)
			{
				Camera::fadeOut(1.f, RGB(255, 255, 255));
				mbSceneChange = true;
			}
			else
			{
				if (!mNextSceneName.empty() && Camera::IsEmptyCamEffect())
				{					
					SceneManager::LoadScene(mNextSceneName);
				}
			}		
		}

		// 키입력으로 씬전환
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D) || Input::GetKeyDown(eKeyCode::W))
		{
			if (mbSceneChange == false)
			{
				Camera::fadeOut(1.f, RGB(255, 255, 255));				
				mbSceneChange = true;
			}
			else
			{
				if (!mNextSceneName.empty() && Camera::IsEmptyCamEffect())
				{
					SceneManager::LoadScene(mNextSceneName);
				}
			}
		}

		Scene::Update();
	}

	void DanceScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void DanceScene::Enter()
	{
		if (mType == eDanceSceneType::BossClear)
		{
			mVideo->GetComponent<Animator>()->PlayAnimation(L"BossClearVideo", false);
		}
		else if (mType == eDanceSceneType::NormalClear)
		{
			mVideo->GetComponent<Animator>()->PlayAnimation(L"NormalClearVideo", false);
		}

		mPassedTime = 0.f;
		mbSoundPlay = false;
		mbSceneChange = false;
	}

	void DanceScene::Exit()
	{
		ResourceManager::Find<Sound>(L"BossClearSound")->Stop(true);
		ResourceManager::Find<Sound>(L"NormalClearSound")->Stop(true);
		Camera::Pause(1.f, RGB(255, 255, 255));
		Camera::fadeIn(1.f, RGB(255, 255, 255));

		mPassedTime = 0.f;
		mbSoundPlay = false;
		mbSceneChange = false;
	}
}