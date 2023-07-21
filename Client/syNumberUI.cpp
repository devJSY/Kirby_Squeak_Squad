#include "syNumberUI.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"
#include "syTransform.h"

namespace sy
{
	NumberUI::NumberUI()
		: mAnimator(nullptr)
	{
	}

	NumberUI::~NumberUI()
	{
	}

	void NumberUI::Initialize()
	{
		// UI »ý¼º 
		Texture* Tex = ResourceManager::Load<Texture>(L"LevelSelectImage_Tex", L"..\\Resources\\Map\\LevelSelect.bmp");
		mAnimator = AddComponent<Animator>();

		mAnimator->CreateAnimation(Tex, L"One", Vector2(649.f, 857.f), Vector2(15.f, 15.f), Vector2(15.f, 0), 1.f, 1);
		mAnimator->CreateAnimation(Tex, L"Two", Vector2(667.f, 857.f), Vector2(15.f, 15.f), Vector2(15.f, 0), 1.f, 1);
		mAnimator->CreateAnimation(Tex, L"Three", Vector2(685.f, 857.f), Vector2(15.f, 15.f), Vector2(15.f, 0), 1.f, 1);
		mAnimator->CreateAnimation(Tex, L"Four", Vector2(703.f, 857.f), Vector2(15.f, 15.f), Vector2(15.f, 0), 1.f, 1);
		mAnimator->CreateAnimation(Tex, L"Five", Vector2(721.f, 857.f), Vector2(15.f, 15.f), Vector2(15.f, 0), 1.f, 1);
		mAnimator->CreateAnimation(Tex, L"Six", Vector2(739.f, 857.f), Vector2(15.f, 15.f), Vector2(15.f, 0), 1.f, 1);
		mAnimator->CreateAnimation(Tex, L"Seven", Vector2(757.f, 857.f), Vector2(15.f, 15.f), Vector2(15.f, 0), 1.f, 1);
		mAnimator->CreateAnimation(Tex, L"Eight", Vector2(775.f, 857.f), Vector2(15.f, 15.f), Vector2(15.f, 0), 1.f, 1);
		mAnimator->CreateAnimation(Tex, L"Ex", Vector2(793.f, 857.f), Vector2(15.f, 15.f), Vector2(15.f, 0), 1.f, 1);
		mAnimator->CreateAnimation(Tex, L"QuestionMark", Vector2(811.f, 857.f), Vector2(15.f, 15.f), Vector2(15.f, 0), 1.f, 1);
		mAnimator->CreateAnimation(Tex, L"D", Vector2(829.f, 857.f), Vector2(15.f, 15.f), Vector2(15.f, 0), 1.f, 1);
	
		mAnimator->SetBmpRGB(L"One", 0,128,0);
		mAnimator->SetBmpRGB(L"Two", 0,128,0);
		mAnimator->SetBmpRGB(L"Three", 0,128,0);
		mAnimator->SetBmpRGB(L"Four", 0,128,0);
		mAnimator->SetBmpRGB(L"Five", 0,128,0);
		mAnimator->SetBmpRGB(L"Six", 0,128,0);
		mAnimator->SetBmpRGB(L"Seven", 0,128,0);
		mAnimator->SetBmpRGB(L"Eight", 0,128,0);
		mAnimator->SetBmpRGB(L"Ex", 0,128,0);
		mAnimator->SetBmpRGB(L"QuestionMark", 0,128,0);
		mAnimator->SetBmpRGB(L"D", 0,128,0);

		mAnimator->SetAffectedCamera(false);
		mAnimator->PlayAnimation(L"One");		

		UI::Initialize();
	}

	void NumberUI::Update()
	{
		UI::Update();
	}

	void NumberUI::Render(HDC hdc)
	{
		UI::Render(hdc);
	}
}