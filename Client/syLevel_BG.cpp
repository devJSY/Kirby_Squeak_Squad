#include "syLevel_BG.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"
#include "syTransform.h"
#include "syApplication.h"

namespace sy
{
	Level_BG::Level_BG()
		: mAnimator(nullptr)
		, mtype(eLevelType::None)
	{
		// Level_BG 객체 기본위치 상단화면 중심으로 설정
		Vector2 vec = Vector2(Application::GetResolution()) / 2.f;
		vec.y /= 2.f;
		GetComponent<Transform>()->SetPosition(vec); // 중점 설정
	}

	Level_BG::~Level_BG()
	{
	}

	void Level_BG::Initialize()
	{
		Texture* tex = ResourceManager::Load<Texture>(L"LevelSelectImage_Tex", L"..\\Resources\\Map\\LevelSelect.png");

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(tex, L"AllClear_LevelSelect", Vector2(2, 2.f), Vector2(256.f, 208.f), Vector2(256.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(tex, L"LevelSelect", Vector2(260.f, 2.f), Vector2(256.f, 208.f), Vector2(256.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(tex, L"Level1_Clear", Vector2(2, 212.f), Vector2(256.f, 208.f), Vector2(256.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(tex, L"Level1", Vector2(260, 212.f), Vector2(256.f, 208.f), Vector2(256.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(tex, L"Level2", Vector2(518, 212.f), Vector2(256.f, 208.f), Vector2(256.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(tex, L"Level3", Vector2(776, 212.f), Vector2(256.f, 208.f), Vector2(256.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(tex, L"Level4", Vector2(2, 422.f), Vector2(256.f, 208.f), Vector2(256.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(tex, L"Level5", Vector2(260, 422.f), Vector2(256.f, 208.f), Vector2(256.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(tex, L"Level6_Clear", Vector2(518, 422.f), Vector2(256.f, 208.f), Vector2(256.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(tex, L"Level6", Vector2(776, 422.f), Vector2(256.f, 208.f), Vector2(256.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(tex, L"Level7", Vector2(2, 632.f), Vector2(256.f, 208.f), Vector2(256.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(tex, L"Level8", Vector2(260, 632.f), Vector2(256.f, 208.f), Vector2(256.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(tex, L"Bosses", Vector2(518, 632.f), Vector2(256.f, 208.f), Vector2(256.f, 0.f), 1.f, 1);	

		// BackGround 는 카메라영향 X
		mAnimator->SetAffectedCamera(false);

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

	void Level_BG::SetLevelType(eLevelType type)
	{
		mtype = type;

		if (mtype == eLevelType::AllClear_LevelSelect)
			mAnimator->PlayAnimation(L"AllClear_LevelSelect");
		else if (mtype == eLevelType::LevelSelect)
			mAnimator->PlayAnimation(L"LevelSelect");
		else if (mtype == eLevelType::Level1_Clear)
			mAnimator->PlayAnimation(L"Level1_Clear");
		else if (mtype == eLevelType::Level1)
			mAnimator->PlayAnimation(L"Level1");
		else if (mtype == eLevelType::Level2)
			mAnimator->PlayAnimation(L"Level2");
		else if (mtype == eLevelType::Level3)
			mAnimator->PlayAnimation(L"Level3");
		else if (mtype == eLevelType::Level4)
			mAnimator->PlayAnimation(L"Level4");
		else if (mtype == eLevelType::Level5)
			mAnimator->PlayAnimation(L"Level5");
		else if (mtype == eLevelType::Level6_Clear)
			mAnimator->PlayAnimation(L"Level6_Clear");
		else if (mtype == eLevelType::Level6)
			mAnimator->PlayAnimation(L"Level6");
		else if (mtype == eLevelType::Level7)
			mAnimator->PlayAnimation(L"Level7");
		else if (mtype == eLevelType::Level8)
			mAnimator->PlayAnimation(L"Level8");
		else if (mtype == eLevelType::Bosses)
			mAnimator->PlayAnimation(L"Bosses");
	}
}