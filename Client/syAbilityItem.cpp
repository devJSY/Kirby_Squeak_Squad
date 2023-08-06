#include "syAbilityItem.h"
#include "syAnimator.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syCollider.h"
#include "syPlayer.h"
#include "syInventory.h"
#include "sySceneManager.h"
#include "syTransform.h"
#include "syRigidbody.h"
#include "syTransform.h"
#include "syDefaultKirby.h"

namespace sy
{
	AbilityItem::AbilityItem(eAbilityType type)
		: mType(type)
		, mBubbleAnimator(nullptr)
		, mAbilityAnimator(nullptr)
		, mTransform(nullptr)
		, mRigidbody(nullptr)
		, mInhaled(false)
	{
		mTransform = GetComponent<Transform>();

		Texture* Bubble_Tex = ResourceManager::Load<Texture>(L"Bubble_Tex", L"..\\Resources\\UI\\Item_Bubble.bmp");
		Texture* Ability_UI_Tex = ResourceManager::Load<Texture>(L"Ability_UI_Tex", L"..\\Resources\\UI\\Ability_UI.bmp");

		mBubbleAnimator = AddComponent<Animator>();
		mAbilityAnimator = AddComponent<Animator>();

		mBubbleAnimator->CreateAnimation(Bubble_Tex, L"BubbleAnimation", Vector2::Zero, Vector2(32.f, 34.f), Vector2(32.f, 0.f), 0.08f, 4, Vector2(0.f, 3.f));
		mBubbleAnimator->PlayAnimation(L"BubbleAnimation", true);

		mAbilityAnimator->CreateAnimation(Ability_UI_Tex, L"Fire_AbilityItem", Vector2(0.f, 43.f), Vector2(15.f, 27.f), Vector2(15.f, 0.f), 1.f, 1);
		mAbilityAnimator->CreateAnimation(Ability_UI_Tex, L"Ice_AbilityItem", Vector2(15.f, 43.f), Vector2(17.f, 27.f), Vector2(17.f, 0.f), 1.f, 1);
		mAbilityAnimator->CreateAnimation(Ability_UI_Tex, L"Cutter_AbilityItem", Vector2(32.f, 43.f), Vector2(15.f, 27.f), Vector2(15.f, 0.f), 1.f, 1);
		mAbilityAnimator->CreateAnimation(Ability_UI_Tex, L"Tornado_AbilityItem", Vector2(47.f, 43.f), Vector2(16.f, 27.f), Vector2(16.f, 0.f), 1.f, 1);

		if (mType == eAbilityType::Fire)
			mAbilityAnimator->PlayAnimation(L"Fire_AbilityItem");
		else if (mType == eAbilityType::Ice)
			mAbilityAnimator->PlayAnimation(L"Ice_AbilityItem");
		else if (mType == eAbilityType::Cutter)
			mAbilityAnimator->PlayAnimation(L"Cutter_AbilityItem");
		else if (mType == eAbilityType::Tornado)
			mAbilityAnimator->PlayAnimation(L"Tornado_AbilityItem");

		Collider* col = AddComponent<Collider>();
		col->SetColliderType(eColliderType::Sphere);
		col->SetRadius(16.f);

		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetFloat(true);

	}

	AbilityItem::~AbilityItem()
	{
	}

	void AbilityItem::Initialize()
	{
		GameObject::Initialize();
	}

	void AbilityItem::Update()
	{
		CheckPixelCollision();

		GameObject::Update();
	}

	void AbilityItem::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void AbilityItem::OnCollisionEnter(Collider* other)
	{
		// 흡수상태에선 무시
		if (mInhaled)
			return;

		Player* plyer = dynamic_cast<Player*>(other->GetOwner());

		// 플레이어가 아니면 리턴
		if (plyer == nullptr)
			return;

		DefaultKirby* kirby = dynamic_cast<DefaultKirby*>(plyer->GetActiveKirby());

		if (kirby != nullptr && kirby->GetKirbyState() == eDefaultKirbyState::Inhaled_Skill)
			return;		

		// 인벤토리에 타입전달 // 꽉찬상태라면 삭제X 밀어내야함		
		Inventory* inventory = SceneManager::GetInventory();
		if (!inventory->IsFullSlot())
		{
			Destroy(this);
			inventory->AddItem(mType);
		}
	}

	void AbilityItem::OnCollisionStay(Collider* other)
	{
		// 인벤토리에 타입전달 // 꽉찬상태라면 삭제X 밀어내야함		
		Inventory* inventory = SceneManager::GetInventory();
		if (inventory->IsFullSlot())
		{
			// 스킬 → 몬스터 방향
			Vector2 Dir = GetComponent<Transform>()->GetPosition() - other->GetOwner()->GetComponent<Transform>()->GetPosition();
			Dir.Normalize();
			Dir *= 30.f;
			mRigidbody->SetVelocity(Dir);
		}
	}

	void AbilityItem::CheckPixelCollision()
	{
		// Stage타입에따라 픽셀텍스쳐 변경하기
		Texture* PixelTex = ResourceManager::Find<Texture>(L"Stage1_Pixel");

		if (PixelTex == nullptr)
			return;

		// Offset 픽셀 좌상단위치 설정
		Vector2 offset = Vector2::Zero;

		std::wstring CurSceneName = SceneManager::GetActiveScene()->GetName();

		if (CurSceneName == L"Stage1Scene")
		{
			offset = Vector2::Zero;
		}
		else if (CurSceneName == L"Stage2Scene")
		{
			offset = Vector2(0, 347.f);
		}
		else if (CurSceneName == L"Stage3Scene")
		{
			offset = Vector2(0, 679.f);
		}
		else if (CurSceneName == L"Stage4Scene")
		{
			offset = Vector2(1603.f, 137.f);
		}

		Collider* col = GetComponent<Collider>();
		Vector2 ColPos = col->GetPosition();
		Vector2 ColSize = col->GetSize();

		Vector2 LT = Vector2(ColPos.x - (ColSize.x / 2.f), ColPos.y - (ColSize.y / 2.f));
		Vector2 RT = Vector2(ColPos.x + (ColSize.x / 2.f), ColPos.y - (ColSize.y / 2.f));
		Vector2 LB = Vector2(ColPos.x - (ColSize.x / 2.f), ColPos.y + (ColSize.y / 2.f));
		Vector2 RB = Vector2(ColPos.x + (ColSize.x / 2.f), ColPos.y + (ColSize.y / 2.f));

		LT += offset;
		RT += offset;
		LB += offset;
		RB += offset;


		COLORREF LTColor = PixelTex->GetTexturePixel((int)LT.x, (int)LT.y);
		COLORREF RTColor = PixelTex->GetTexturePixel((int)RT.x, (int)RT.y);
		COLORREF LBColor = PixelTex->GetTexturePixel((int)LB.x, (int)LB.y);
		COLORREF RBColor = PixelTex->GetTexturePixel((int)RB.x, (int)RB.y);

		// 상단 처리
		Vector2 pos = mTransform->GetPosition();

		if (LTColor == RGB(0, 255, 0))
		{
			pos.x += 1.f;
		}
		else if (RTColor == RGB(0, 255, 0))
		{
			pos.x -= 1.f;
		}

		mTransform->SetPosition(pos);



		// 바닥 처리
		if (LBColor == RGB(0, 0, 255) || RBColor == RGB(0, 0, 255))
		{
			// 이동
			Vector2 pos = mTransform->GetPosition();
			pos.y -= 1.f;
			mTransform->SetPosition(pos);
		}

		// Right Stop Check
		if (RBColor == RGB(0, 255, 0))
		{
			// 이동
			Vector2 pos = mTransform->GetPosition();
			pos.x -= 1.f;
			mTransform->SetPosition(pos);
		}

		// Left Stop Check
		if (LBColor == RGB(0, 255, 0))
		{
			// 이동
			Vector2 pos = mTransform->GetPosition();
			pos.x += 1.f;
			mTransform->SetPosition(pos);
		}
	}
}