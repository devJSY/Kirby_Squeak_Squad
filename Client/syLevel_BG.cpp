#include "syLevel_BG.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"

namespace sy
{
	Level_BG::Level_BG()
	{
	}

	Level_BG::~Level_BG()
	{
	}

	void Level_BG::Initialize()
	{
		Texture* tex = ResourceManager::Load<Texture>(L"LevelSelectImage_Tex", L"..\\Resources\\Map\\LevelSelect.png");

		Animator* Ani = AddComponent<Animator>();
		Ani->CreateAnimation(tex, L"AllClear_LevelSelect", Vector2(2, 2.f), Vector2(256.f, 208.f), Vector2(256.f, 0.f), 1.f, 1);
		Ani->CreateAnimation(tex, L"LevelSelect", Vector2(260.f, 2.f), Vector2(256.f, 208.f), Vector2(256.f, 0.f), 1.f, 1);
		Ani->CreateAnimation(tex, L"Level1_Clear", Vector2(2, 212.f), Vector2(256.f, 208.f), Vector2(256.f, 0.f), 1.f, 1);
		Ani->CreateAnimation(tex, L"Level1", Vector2(260, 212.f), Vector2(256.f, 208.f), Vector2(256.f, 0.f), 1.f, 1);
		Ani->CreateAnimation(tex, L"Level2", Vector2(518, 212.f), Vector2(256.f, 208.f), Vector2(256.f, 0.f), 1.f, 1);
		Ani->CreateAnimation(tex, L"Level3", Vector2(776, 212.f), Vector2(256.f, 208.f), Vector2(256.f, 0.f), 1.f, 1);
		Ani->CreateAnimation(tex, L"Level4", Vector2(2, 422.f), Vector2(256.f, 208.f), Vector2(256.f, 0.f), 1.f, 1);
		Ani->CreateAnimation(tex, L"Level5", Vector2(260, 422.f), Vector2(256.f, 208.f), Vector2(256.f, 0.f), 1.f, 1);
		Ani->CreateAnimation(tex, L"Level6_Clear", Vector2(518, 422.f), Vector2(256.f, 208.f), Vector2(256.f, 0.f), 1.f, 1);
		Ani->CreateAnimation(tex, L"Level6", Vector2(776, 422.f), Vector2(256.f, 208.f), Vector2(256.f, 0.f), 1.f, 1);
		Ani->CreateAnimation(tex, L"Level7", Vector2(2, 632.f), Vector2(256.f, 208.f), Vector2(256.f, 0.f), 1.f, 1);
		Ani->CreateAnimation(tex, L"Level8", Vector2(260, 632.f), Vector2(256.f, 208.f), Vector2(256.f, 0.f), 1.f, 1);
		Ani->CreateAnimation(tex, L"Bosses", Vector2(518, 632.f), Vector2(256.f, 208.f), Vector2(256.f, 0.f), 1.f, 1);		
		
		
		Ani->SetAffectedCamera(false);
		Ani->PlayAnimation(L"LevelSelect");

		BackGround::Initialize();
	}

	void Level_BG::Update()
	{
		BackGround::Update();
	}

	void Level_BG::Render(HDC hdc)
	{
		BackGround::Render(hdc);
	}
}