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
#include "syMixItem.h"
#include "syPlayer.h"

namespace sy
{
	Inventory::Inventory()
		: mAnimator(nullptr)
		, mSlot{}
		, mFocusItem(nullptr)
		, mFocusTime(0.f)
		, mMixItem(nullptr)
		, mAngle(0.f)
		, mMixItems()
	{
		// ���� �ʱ�ȭ
		for (size_t i = 0; i < 5; i++)
		{
			mSlot[i] = nullptr;		
		}
	}

	Inventory::~Inventory()
	{
		for (size_t i = 0; i < 5; i++)
		{
			if (mSlot[i] != nullptr)
			{
				delete mSlot[i];
				mSlot[i] = nullptr;
			}
		}

		for (size_t i = 0; i < mMixItems.size(); i++)
		{
			if (nullptr != mMixItems[i])
			{
				delete mMixItems[i];
				mMixItems[i] = nullptr;
			}
		}

		mMixItems.clear();
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

		mAnimator->CreateAnimation(image, L"Inventory_Animation", Vector2(0.f, 0.f), Vector2(256.f, 192.f), Vector2(256.f, 0.f), 0.2f, 16);
		mAnimator->CreateAnimationFolder(L"Inventory_Damage_Animation", L"..\\Resources\\Video\\InvenDamage", 0.03f);
		mAnimator->CreateAnimationFolder(L"Inventory_Transform_Fire", L"..\\Resources\\Video\\Fire", 0.03f);
		mAnimator->CreateAnimationFolder(L"Inventory_Transform_Ice", L"..\\Resources\\Video\\Ice", 0.03f);
		mAnimator->CreateAnimationFolder(L"Inventory_Transform_Cutter", L"..\\Resources\\Video\\Cutter", 0.03f);
		mAnimator->CreateAnimationFolder(L"Inventory_Transform_Tornado", L"..\\Resources\\Video\\Tornado", 0.03f);
		mAnimator->CreateAnimationFolder(L"Inventory_Transform_Ninja", L"..\\Resources\\Video\\Ninja", 0.03f);
		mAnimator->CreateAnimationFolder(L"Inventory_Transform_Spark", L"..\\Resources\\Video\\Spark", 0.03f);
		mAnimator->CreateAnimationFolder(L"Inventory_Transform_Sword", L"..\\Resources\\Video\\Sword", 0.03f);
		mAnimator->CreateAnimationFolder(L"Inventory_Transform_Heal", L"..\\Resources\\Video\\Heal", 0.03f);
		mAnimator->CreateAnimationFolder(L"Inventory_Transform_Non", L"..\\Resources\\Video\\Non", 0.03f);
		mAnimator->SetAffectedCamera(false);

		mAnimator->PlayAnimation(L"Inventory_Animation", true);

		GameObject::Initialize();
	}

	void Inventory::Update()
	{
		// �ӽ� �ͽ� ȿ�� �߰��ϱ�
		if (Input::GetKeyDown(eKeyCode::R))
		{
			SceneManager::GetInventory()->AddMixItem();
		}

		// Damage �ִϸ��̼� ��� ���� ���
		if (mAnimator->IsActiveAnimationComplete())
		{
			mAnimator->PlayAnimation(L"Inventory_Animation", true);
		}


		// ���콺Ŭ�� ��ȣ�ۿ�
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
						// mFocusItem ����
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

				if (mMixItem != nullptr)
				{
					// ��ġ ȸ���ϵ��� ����
					Transform* FocusItemtransform = mFocusItem->GetComponent<Transform>();
					Transform* MixItemtransform = mMixItem->GetComponent<Transform>();
					Vector2 ItemPos = FocusItemtransform->GetPosition();
					Vector2 MixItemPos = MixItemtransform->GetPosition();

					// �ʴ� 15��
					mAngle += 15.f * (float)Time::DeltaTime();

					// 2�� (2.0f * 3.1415f)�� �� ����(360��)�� �ش��ϴ� ����
					if (mAngle > 2.0f * 3.1415f)
					{
						mAngle -= 2.0f * 3.1415f;
					}

					ItemPos.x = mousePos.x + 15.f * std::cos(mAngle);
					ItemPos.y = mousePos.y + 15.f * std::sin(mAngle);
					MixItemPos.x = mousePos.x - 15.f * std::cos(mAngle);
					MixItemPos.y = mousePos.y - 15.f * std::sin(mAngle);

					FocusItemtransform->SetPosition(ItemPos);
					MixItemtransform->SetPosition(MixItemPos);
				}
				else
				{
					// ���콺��ġ�� ����
					Transform* FocusItemtransform = mFocusItem->GetComponent<Transform>();
					FocusItemtransform->SetPosition(mousePos);
				}

				mFocusTime += Time::DeltaTime();
			}
		}
		else if (Input::GetKeyUp(eKeyCode::MOUSE_LBTN))
		{
			// Mix ����
			if (mFocusItem != nullptr && mMixItem != nullptr)
			{
				Destroy(mFocusItem);
				Destroy(mMixItem);

				// �ͽ� ȿ�� �߰��ϱ�
				AddMixItem();
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
							// ������ Ÿ���� �ڱ��ڽ��� �ƴϸ鼭 ���Ű����� �����̸� ����
							if (mFocusItem->GetType() != SceneManager::GetPlayer()->GetAbilityType()
								&& SceneManager::GetPlayer()->GetActiveKirby()->IsTransformableCheck())
							{				
								Destroy(mFocusItem);
								SceneManager::GetPlayer()->PlayerTransformations(mFocusItem->GetType());
							}
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

		// Slot Update
		for (size_t i = 0; i < 5; i++)
		{
			if (mSlot[i] != nullptr)
			{
				if (mSlot[i]->GetGameObjectState() == eGameObjectState::Pause)
					continue;

				mSlot[i]->Update();
			}
		}

		// MixItems Update
		for (size_t i = 0; i < mMixItems.size(); i++)
		{
			if (mMixItems[i]->GetGameObjectState() == eGameObjectState::Pause)
				continue;

			mMixItems[i]->Update();
		}
	}

	void Inventory::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		// Slot Render
		for (size_t i = 0; i < 5; i++)
		{
			if (mSlot[i] != nullptr)
			{
				if (mSlot[i]->GetGameObjectState() == eGameObjectState::Pause)
					continue;

				mSlot[i]->Render(hdc);
			}
		}

		// Dead������ Item �� Inventory ���� �����Ѵ�
		for (size_t i = 0; i < 5; i++)
		{
			if (mSlot[i] != nullptr)
			{
				if (mSlot[i]->GetGameObjectState() == eGameObjectState::Dead)
				{
					delete mSlot[i];
					mSlot[i] = nullptr;
				}
			}
		}

		// MixItems Render
		for (size_t i = 0; i < mMixItems.size(); i++)
		{
			if (mMixItems[i]->GetGameObjectState() == GameObject::eGameObjectState::Pause)
				continue;

			mMixItems[i]->Render(hdc);
		}

		// Dead������ MixItem�� MixItems ���� �����Ѵ�
		for (std::vector<MixItem*>::iterator iter = mMixItems.begin()
			; iter != mMixItems.end()
			; )
		{
			if ((*iter)->GetGameObjectState() == GameObject::eGameObjectState::Dead)
			{
				MixItem* obj = *iter;
				iter = mMixItems.erase(iter);
				delete obj;
				obj = nullptr;
			}
			else
			{
				iter++;
			}
		}
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
				break;
			}
		}
	}
	
	void Inventory::AddMixItem()
	{
		mMixItems.push_back(new MixItem);
	}
}