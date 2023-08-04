#include "syInventory.h"
#include "syAnimator.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syTransform.h"
#include "syApplication.h"
#include "syAnimator.h"
#include "syInventoryItem.h"
#include "syObject.h"
#include "syInput.h"
#include "syCollider.h"
#include "syApplication.h"

namespace sy
{
	Inventory::Inventory()
		: mAnimator(nullptr)
		, mSlot{}
		, mFocusItem(nullptr)
	{
	}

	Inventory::~Inventory()
	{
	}

	void Inventory::Initialize()
	{
		// Inventory 기본위치 하단 화면 중심으로 설정
		Vector2 vec = Vector2(Application::GetResolution()) / 2.f;
		vec.y += vec.y / 2.f;
		GetComponent<Transform>()->SetPosition(vec);

		mAnimator = AddComponent<Animator>();
		Texture* image = ResourceManager::Load<Texture>(L"Inventory_Tex"
			, L"..\\Resources\\Inventory\\Inventory.bmp");
		Texture* Damaged = ResourceManager::Load<Texture>(L"Inventory_Damage_Tex"
			, L"..\\Resources\\Inventory\\Inventory_Damage.bmp");

		mAnimator->CreateAnimation(image, L"Inventory_Animation", Vector2(0.f, 0.f), Vector2(256.f, 192.f), Vector2(256.f, 0.f), 0.2f, 16);
		mAnimator->CreateAnimation(Damaged, L"Inventory_Damage_Animation", Vector2(0.f, 0.f), Vector2(256.f, 192.f), Vector2(256.f, 0.f), 0.07f, 15);
		mAnimator->SetAffectedCamera(false);

		mAnimator->PlayAnimation(L"Inventory_Animation", true);

		GameObject::Initialize();
	}

	void Inventory::Update()
	{
		if (Input::GetKeyDown(eKeyCode::MOUSE_LBTN))
		{
			Vector2 mousePos = Input::GetMousePos();

			for (size_t i = 0; i < 5; i++)
			{
				if (mSlot[i] != nullptr)
				{
					Collider* SlotCollider = mSlot[i]->GetComponent<Collider>();

					// 화면크기 이동한 거리, 화면 비율만큼 계산
					Vector2 SlotPos = SlotCollider->GetPosition();	
					SlotPos *= Application::GetScreenMinRatio();
					SlotPos += Application::GetScreenRenderPos(); 

					// 화면 비율만큼 계산
					float SlotRadius = SlotCollider->GetRadius();	
					SlotRadius *= Application::GetScreenMinRatio();

					Vector2 distance = SlotPos - mousePos;
					float Length = distance.Length();

					// 콜라이더 범위 안에 들어왔다
					if (Length <= SlotRadius)
					{
						mFocusItem = mSlot[i];
						break;
					}					
				}
			}
		}
		else if (Input::GetKeyPressed(eKeyCode::MOUSE_LBTN))
		{
			if (mFocusItem != nullptr)
			{
				// 화면크기 이동한 거리, 화면 비율만큼 계산
				Vector2 mousePos = Input::GetMousePos();
				mousePos -= Application::GetScreenRenderPos();
				mousePos = mousePos  / Application::GetScreenMinRatio();

				// 마우스위치로 설정
				Transform* transform = mFocusItem->GetComponent<Transform>();
				transform->SetPosition(mousePos);
			}
		}
		else if (Input::GetKeyUp(eKeyCode::MOUSE_LBTN))
		{
			if (mFocusItem != nullptr)
			{
				// 놓은 위치가 빈슬롯이었을경우 슬롯번호 변경
				mFocusItem = nullptr;
			}
		}




		GameObject::Update();
	}

	void Inventory::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Inventory::AddItem(eAbilityType type)
	{
		for (size_t i = 0; i < 5; i++)
		{
			if (mSlot[i] == nullptr)
			{
				InventoryItem* item = new InventoryItem(type, (UINT)i);
				mSlot[i] = item;
				object::ActiveSceneAddGameObject(eLayerType::InventoryItem, item);
				break;
			}
		}
	}
}