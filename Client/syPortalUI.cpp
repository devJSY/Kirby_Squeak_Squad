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

namespace sy
{
	PortalUI::PortalUI()
		: mAnimator(nullptr)
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

		if (Input::GetKeyDown(eKeyCode::UP))
		{
			Scene* activeScene = SceneManager::GetActiveScene();
			std::wstring SceneName = activeScene->GetName();

			if (SceneName == L"Stage1Scene")
			{
				SceneManager::LoadScene(L"Stage2Scene");
			}
			else if (SceneName == L"Stage2Scene")
			{
				SceneManager::LoadScene(L"Stage3Scene");
			}
			else if (SceneName == L"Stage3Scene")
			{
				SceneManager::LoadScene(L"Stage4Scene");
			}
			else if (SceneName == L"Stage4Scene")
			{
				SceneManager::LoadScene(L"EndingScene");
			}
		}
	}
}