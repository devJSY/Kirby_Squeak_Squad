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
#include "syTime.h"

namespace sy
{
	Inventory::Inventory()
		: mAnimator(nullptr)
		, mSlot{}
		, mFocusItem(nullptr)
		, mFocusTime(0.f)
		, mMixItem(nullptr)
	{
	}

	Inventory::~Inventory()
	{
	}

	void Inventory::Initialize()
	{
		// Inventory �⺻��ġ �ϴ� ȭ�� �߽����� ����
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

					// ȭ��ũ�� �̵��� �Ÿ�, ȭ�� ������ŭ ���
					Vector2 SlotPos = SlotCollider->GetPosition();	
					SlotPos *= Application::GetScreenMinRatio();
					SlotPos += Application::GetScreenRenderPos(); 

					// ȭ�� ������ŭ ���
					float SlotRadius = SlotCollider->GetRadius();	
					SlotRadius *= Application::GetScreenMinRatio();

					Vector2 distance = SlotPos - mousePos;
					float Length = distance.Length();

					// �ݶ��̴� ���� �ȿ� ���Դ�
					if (Length <= SlotRadius)
					{
						mFocusItem = mSlot[i];
						mFocusTime = 0.f;
						break;
					}					
				}
			}
		}
		else if (Input::GetKeyPressed(eKeyCode::MOUSE_LBTN))
		{
			if (mFocusItem != nullptr)
			{
				// ȭ��ũ�� �̵��� �Ÿ�, ȭ�� ������ŭ ���
				Vector2 mousePos = Input::GetMousePos();
				mousePos -= Application::GetScreenRenderPos();
				mousePos = mousePos  / Application::GetScreenMinRatio();

				// �̵�����
				if (mousePos.x < 0)
				{
					mousePos.x = 0;
				}
				if (mousePos.y < 192.f + mFocusItem->GetComponent<Collider>()->GetRadius())
				{
					mousePos.y = 192.f + mFocusItem->GetComponent<Collider>()->GetRadius();
				}
				if (mousePos.x > 256.f)
				{
					mousePos.x = 256.f;
				}
				if (mousePos.y > 384.f)
				{
					mousePos.y = 384.f;
				}

				// ���콺��ġ�� ����
				Transform* FocusItemtransform = mFocusItem->GetComponent<Transform>();
				FocusItemtransform->SetPosition(mousePos);

				if (mMixItem != nullptr)
				{
					// ��ġ ȸ���ϵ��� ����
					Transform* MixItemtransform = mMixItem->GetComponent<Transform>();
					FocusItemtransform->SetPosition(Vector2(mousePos.x - 10.f, mousePos.y));
					MixItemtransform->SetPosition(Vector2(mousePos.x + 10.f, mousePos.y));
				}

				mFocusTime += Time::DeltaTime();
			}
		}
		else if (Input::GetKeyUp(eKeyCode::MOUSE_LBTN))
		{
			// Mix ����
			if (mFocusItem != nullptr && mMixItem != nullptr)
			{
				mSlot[mFocusItem->GetSlotNumber()] = nullptr;
				mSlot[mMixItem->GetSlotNumber()] = nullptr;
				Destroy(mFocusItem);
				Destroy(mMixItem);

				// �ͽ� ȿ�� �߰��ϱ�
			}
			else
			{
				if (mFocusItem != nullptr)
				{
					// ���� ������ġ���� �����ð����� ������ ����� ������ ����
					if (mFocusTime < 0.2f)
					{
						UINT idx = mFocusItem->GetSlotNumber();

						Transform* transform = mFocusItem->GetComponent<Transform>();
						Vector2 CurPos = transform->GetPosition();
						Vector2 SlotPos = mFocusItem->GetSlotPos();

						Vector2 distance = SlotPos - CurPos;
						float Length = distance.Length();
						float SlotRadius = 20;

						// ���� ������ ���� �ȿ� ���Դ�
						if (Length <= SlotRadius)
						{
							mSlot[idx] = nullptr;
							Destroy(mFocusItem);
							SceneManager::PlayerTransform(mFocusItem->GetType());
						}
					}
					else
					{
						// ���� ��ġ�� �󽽷��̾������ ���Թ�ȣ ����
						for (UINT i = 0; i < 5; i++)
						{
							// ������ ����ִ� ��쿡�� ��ġ ����
							if (mSlot[i] != nullptr)
								continue;

							Transform* transform = mFocusItem->GetComponent<Transform>();
							Vector2 CurPos = transform->GetPosition();
							Vector2 SlotPos = Vector2::Zero;

							if (i == 0)
								SlotPos = Vector2(30.f, 270.f);
							else if (i == 1)
								SlotPos = Vector2(63.f, 330.f);
							else if (i == 2)
								SlotPos = Vector2(128.f, 353.f);
							else if (i == 3)
								SlotPos = Vector2(190.f, 330.f);
							else if (i == 4)
								SlotPos = Vector2(225.f, 270.f);


							Vector2 distance = SlotPos - CurPos;
							float Length = distance.Length();
							float SlotRadius = 20;

							// ���� ������ ���� �ȿ� ���Դ�
							if (Length <= SlotRadius)
							{
								mSlot[mFocusItem->GetSlotNumber()] = nullptr;
								mSlot[i] = mFocusItem;
								mFocusItem->SetSlotNumber(i);
								break;
							}
						}
					}
				}
			}

			mFocusItem = nullptr;
			mMixItem = nullptr;
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
			// ����ִ� ���Կ� ����
			if (mSlot[i] == nullptr)
			{
				InventoryItem* item = new InventoryItem(type, (UINT)i);
				mSlot[i] = item;
				object::ActiveSceneAddGameObject(eLayerType::InventoryItem, item);
				break;
			}
		}
	}

	void Inventory::RemoveItemSlot(UINT idx)
	{
		mSlot[idx] = nullptr;
	}
}