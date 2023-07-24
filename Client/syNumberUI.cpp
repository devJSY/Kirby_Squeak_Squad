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

		mAnimator->CreateAnimation(Tex, L"Number_Dedede", Vector2(649.f, 1025.f), Vector2(15.f, 15.f), Vector2(15.f, 0), 1.f, 1);
		mAnimator->CreateAnimation(Tex, L"Number_MrsMoley", Vector2(667.f, 1025.f), Vector2(15.f, 15.f), Vector2(15.f, 0), 1.f, 1);
		mAnimator->CreateAnimation(Tex, L"Number_MechaKracko", Vector2(685.f, 1025.f), Vector2(15.f, 15.f), Vector2(15.f, 0), 1.f, 1);
		mAnimator->CreateAnimation(Tex, L"Number_Yadgaine", Vector2(703.f, 1025.f), Vector2(15.f, 15.f), Vector2(15.f, 0), 1.f, 1);
		mAnimator->CreateAnimation(Tex, L"Number_Bohboh", Vector2(721.f, 1025.f), Vector2(15.f, 15.f), Vector2(15.f, 0), 1.f, 1);
		mAnimator->CreateAnimation(Tex, L"Number_Daroach", Vector2(739.f, 1025.f), Vector2(15.f, 15.f), Vector2(15.f, 0), 1.f, 1);
		mAnimator->CreateAnimation(Tex, L"Number_MetaKnight", Vector2(758.f, 1025.f), Vector2(15.f, 15.f), Vector2(15.f, 0), 1.f, 1);
		mAnimator->CreateAnimation(Tex, L"Number_DarkNebula", Vector2(777.f, 1025.f), Vector2(15.f, 15.f), Vector2(15.f, 0), 1.f, 1);
		mAnimator->CreateAnimation(Tex, L"Number_9", Vector2(795.f, 1025.f), Vector2(15.f, 15.f), Vector2(15.f, 0), 1.f, 1);

	
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

		mAnimator->SetBmpRGB(L"Number_Dedede", 0,128,0);
		mAnimator->SetBmpRGB(L"Number_MsMorey", 0,128,0);
		mAnimator->SetBmpRGB(L"Number_Kracko", 0,128,0);
		mAnimator->SetBmpRGB(L"Number_4", 0,128,0);
		mAnimator->SetBmpRGB(L"Number_5", 0,128,0);
		mAnimator->SetBmpRGB(L"Number_6", 0,128,0);
		mAnimator->SetBmpRGB(L"Number_7", 0,128,0);
		mAnimator->SetBmpRGB(L"Number_8", 0,128,0);
		mAnimator->SetBmpRGB(L"Number_9", 0,128,0);


		mAnimator->SetAffectedCamera(false);
		//mAnimator->PlayAnimation(L"One");		

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