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
		: mBarTex(nullptr)
		, mRedTex(nullptr)
		, mPinkTex(nullptr)
		, mDecreaseHP(0.f)
		, mIncreaseHP(0.f)
		, mHpBarDelay(0.f)
	{		
		mIncreaseHP = (float)SceneManager::GetPlayer()->GetCurHP();
	}

	HPbarUI::~HPbarUI()
	{
	}

	void HPbarUI::Initialize()
	{
		mDecreaseHP = (float)SceneManager::GetPlayer()->GetCurHP();

		mBarTex = ResourceManager::Load<Texture>(L"HP_Bar", L"..\\Resources\\UI\\HpBar\\HP_Bar.bmp");
		mPinkTex = ResourceManager::Load<Texture>(L"HP_Pink", L"..\\Resources\\UI\\HpBar\\HP_Pink.bmp");
		mRedTex = ResourceManager::Load<Texture>(L"HP_Red", L"..\\Resources\\UI\\HpBar\\HP_Red.bmp");

		UI::Initialize();
	}

	void HPbarUI::Update()
	{
		float PlayerCurHP = (float)SceneManager::GetPlayer()->GetCurHP();

		if (SceneManager::GetPlayer()->IsDamaged())
		{
			mHpBarDelay += Time::DeltaTime();			
		}

		// 체력 감소시 서서히 감소 하도록 설정
		if (mHpBarDelay > 1.f)
		{
			if ((int)mDecreaseHP > PlayerCurHP)
				mDecreaseHP -= (float)Time::DeltaTime() * 15.f;
			else
			{
				mHpBarDelay = 0.f;
				mDecreaseHP = PlayerCurHP;
			}
		}

		// 체력 회복시 서서히 증가하도록 설정
		if ((int)mIncreaseHP < PlayerCurHP)
			mIncreaseHP += (float)Time::DeltaTime() * 30.f;
		else
		{
			mIncreaseHP = PlayerCurHP;
			if ((int)mDecreaseHP < PlayerCurHP)
			{
				mDecreaseHP = mIncreaseHP;
			}
		}

		UI::Update();
	}

	void HPbarUI::Render(HDC hdc)
	{
		Player* player = SceneManager::GetPlayer();
		
		TransparentBlt(hdc, 44, 176, mBarTex->GetWidth(), mBarTex->GetHeight(), mBarTex->GetHdc()
			, 0, 0, mBarTex->GetWidth(), mBarTex->GetHeight(), RGB(255, 0, 255));

		TransparentBlt(hdc, 50, 178, (int)(mRedTex->GetWidth() * (mDecreaseHP / player->GetMaxHP())), mRedTex->GetHeight(), mRedTex->GetHdc()
			, 0, 0, (int)(mRedTex->GetWidth() * (mDecreaseHP / player->GetMaxHP())), mRedTex->GetHeight(), RGB(255, 0, 255));

		TransparentBlt(hdc, 50, 178, (int)(mPinkTex->GetWidth() * (mIncreaseHP / player->GetMaxHP())), mPinkTex->GetHeight(), mPinkTex->GetHdc()
			, 0, 0, (int)(mPinkTex->GetWidth() * (mIncreaseHP / player->GetMaxHP())), mPinkTex->GetHeight(), RGB(255, 0, 255));

		UI::Render(hdc);
	}
}