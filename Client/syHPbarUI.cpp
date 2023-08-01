#include "syHPbarUI.h"
#include "syTexture.h"
#include "syAnimator.h"
#include "syResourceManager.h"
#include "syPlayer.h"
#include "syTransform.h"
#include "syApplication.h"
#include "sySceneManager.h"
#include "syTime.h"

namespace sy
{
	HPbarUI::HPbarUI()
		: mBar(nullptr)
		, mRed(nullptr)
		, mPink(nullptr)
		, mDecreaseHP(0.f)
	{
		mDecreaseHP = SceneManager::GetPlayer()->GetHP();
	}

	HPbarUI::~HPbarUI()
	{
	}

	void HPbarUI::Initialize()
	{
		mBar = ResourceManager::Load<Texture>(L"HP_Bar", L"..\\Resources\\UI\\HpBar\\HP_Bar.bmp");
		mPink = ResourceManager::Load<Texture>(L"HP_Pink", L"..\\Resources\\UI\\HpBar\\HP_Pink.bmp");
		mRed = ResourceManager::Load<Texture>(L"HP_Red", L"..\\Resources\\UI\\HpBar\\HP_Red.bmp");

		UI::Initialize();
	}

	void HPbarUI::Update()
	{
		static float time = 0.f;

		time += Time::DeltaTime();

		// 1초뒤에 감소
		if (time > 1.f)
		{
			if ((int)mDecreaseHP >= SceneManager::GetPlayer()->GetHP())
				mDecreaseHP -= (float)Time::DeltaTime() * 15.f;
			else
			{
				time = 0.f;
			}
		}


		UI::Update();
	}

	void HPbarUI::Render(HDC hdc)
	{
		Player* player = SceneManager::GetPlayer();
		int hp = player->GetHP();
		float fhp = (float)hp / 100.f;


		//TransparentBlt(hdc, 44, 178, mBar->GetWidth(), mBar->GetHeight(), mBar->GetHdc()
		//	, 0, 0, mBar->GetWidth(), mBar->GetHeight(), RGB(255, 0, 255));

		//TransparentBlt(hdc, 50, 180, (int)(mRed->GetWidth() * mDraw / mMHP), mRed->GetHeight(), mRed->GetHdc()
		//	, 0, 0, (int)(mRed->GetWidth() * mDraw / mMHP), mRed->GetHeight(), RGB(255, 0, 255));

		//TransparentBlt(hdc, 50, 180, (int)(mPink->GetWidth() * mHP / mMHP), mPink->GetHeight(), mPink->GetHdc()
		//	, 0, 0, (int)(mPink->GetWidth() * mHP / mMHP), mPink->GetHeight(), RGB(255, 0, 255));
		
		TransparentBlt(hdc, 44, 178, mBar->GetWidth(), mBar->GetHeight(), mBar->GetHdc()
			, 0, 0, mBar->GetWidth(), mBar->GetHeight(), RGB(255, 0, 255));

		TransparentBlt(hdc, 50, 180, (int)(mRed->GetWidth() * (mDecreaseHP / 100.f)), mRed->GetHeight(), mRed->GetHdc()
			, 0, 0, (int)(mRed->GetWidth() * (mDecreaseHP / 100.f)), mRed->GetHeight(), RGB(255, 0, 255));

		TransparentBlt(hdc, 50, 180, (int)(mPink->GetWidth() * fhp), mPink->GetHeight(), mPink->GetHdc()
			, 0, 0, (int)(mPink->GetWidth() * fhp), mPink->GetHeight(), RGB(255, 0, 255));

		UI::Render(hdc);
	}
}