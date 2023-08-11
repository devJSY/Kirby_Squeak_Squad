#include "syPortalUI.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"
#include "sySpriteRenderer.h"
#include "syCollider.h"
#include "syPlayer.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syScene.h"
#include "syCamera.h"
#include "syTime.h"

namespace sy
{
	PortalUI::PortalUI()
		: mAnimator(nullptr)
		, mbSceneChange(false)
	{
		// UI »ý¼º 
		Texture* Portal_StarTex = ResourceManager::Load<Texture>(L"Portal_Star", L"..\\Resources\\UI\\Portal_Star.bmp");
		Texture* Portal_Tex = ResourceManager::Load<Texture>(L"Portal", L"..\\Resources\\UI\\Portal.bmp");

		SpriteRenderer* sr = AddComponent<SpriteRenderer>();
		sr->SetTexture(Portal_Tex);

		mAnimator = AddComponent<Animator>();
		Vector2 Animationoffset = Vector2(0.f, -20.f);
		mAnimator->CreateAnimation(Portal_StarTex, L"Portal_Star", Vector2::Zero, Vector2(50.f, 30.f), Vector2(50.f, 0.f), 0.07f, 12, Animationoffset);
		mAnimator->PlayAnimation(L"Portal_Star", true);

		Collider* col = AddComponent<Collider>();

		col->SetSize(Vector2(16.f, 24.f));
	}

	PortalUI::~PortalUI()
	{
	}

	void PortalUI::Initialize()
	{
		UI::Initialize();
	}

	void PortalUI::Update()
	{
		if (mbSceneChange && Camera::IsEmptyCamEffect())
		{
			Scene* activeScene = SceneManager::GetActiveScene();
			std::wstring SceneName = activeScene->GetName();

			if (SceneName == L"Level1_Stage1Scene")
			{
				SceneManager::LoadScene(L"Level1_Stage2Scene");
			}
			else if (SceneName == L"Level1_Stage2Scene")
			{
				SceneManager::LoadScene(L"Level1_Stage3Scene");
			}
			else if (SceneName == L"Level1_Stage3Scene")
			{
				SceneManager::LoadScene(L"Level1_Stage4Scene");
			}
			else if (SceneName == L"Level1_Stage4Scene" || SceneName == L"Level1_BossScene")
			{
				SceneManager::LoadScene(L"PrismPlainsScene");
			}
			else if (SceneName == L"AbilityTestScene")
			{
				SceneManager::LoadScene(L"LevelSelectScene");
			}

			mbSceneChange = false;
			Camera::fadeIn(0.5f, RGB(255, 255, 255));
		}

		UI::Update();
	}

	void PortalUI::Render(HDC hdc)
	{
		UI::Render(hdc);
	}

	void PortalUI::OnCollisionStay(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player == nullptr)
			return;

		if (!mbSceneChange && Input::GetKeyDown(eKeyCode::UP))
		{
			mbSceneChange = true;
			Camera::fadeOut(0.5f, RGB(255, 255, 255));
			Camera::Pause(0.5f, RGB(255, 255, 255));
		}
	}
}