#include "syEnemyHPbarUI.h"
#include "syResourceManager.h"
#include "syTexture.h"

namespace sy
{
	EnemyHPbarUI::EnemyHPbarUI()
		: mBarTex(nullptr)
		, mHPTex(nullptr)
		, mbRenderTrig(false)
	{
		mBarTex = ResourceManager::Load<Texture>(L"Monster_HP", L"..\\Resources\\UI\\MonsterLifeBar\\Monster_HP.bmp");
		mHPTex = ResourceManager::Load<Texture>(L"Monster_cHP", L"..\\Resources\\UI\\MonsterLifeBar\\Monster_cHP.bmp");		
	}

	EnemyHPbarUI::~EnemyHPbarUI()
	{
	}

	void EnemyHPbarUI::Initialize()
	{
		UI::Initialize();
	}

	void EnemyHPbarUI::Update()
	{
		UI::Update();
	}

	void EnemyHPbarUI::Render(HDC hdc)
	{
		TransparentBlt(hdc, 180, 180, mBarTex->GetWidth(), mBarTex->GetHeight(), mBarTex->GetHdc()
			, 0, 0, mBarTex->GetWidth(), mBarTex->GetHeight(), RGB(255, 0, 255));

		TransparentBlt(hdc, 186, 181, (int)(mHPTex->GetWidth()), mHPTex->GetHeight(), mHPTex->GetHdc()
			, 0, 0, (int)(mHPTex->GetWidth()), mHPTex->GetHeight(), RGB(255, 0, 255));


		UI::Render(hdc);
	}
}