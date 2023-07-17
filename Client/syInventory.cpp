#include "syInventory.h"
#include "syAnimator.h"
#include "syTexture.h"
#include "syResourceManager.h"

namespace sy
{
	Inventory::Inventory()
	{
	}

	Inventory::~Inventory()
	{
	}

	void Inventory::Initialize()
	{
		Animator* InvenAt = AddComponent<Animator>();
		Texture* image = ResourceManager::Load<Texture>(L"Inventory"
			, L"..\\Resources\\Inventory\\Inventory.bmp");
		Texture* Damaged = ResourceManager::Load<Texture>(L"Inventory_Damage"
			, L"..\\Resources\\Inventory\\Inventory_Damage.bmp");

		InvenAt->CreateAnimation(image, L"Inventory", Vector2(0.f, 0.f), Vector2(256.f, 192.f), Vector2(256.f, 0.f), 0.2f, 16);
		InvenAt->CreateAnimation(Damaged, L"Inventory_Damage", Vector2(0.f, 0.f), Vector2(256.f, 192.f), Vector2(256.f, 0.f), 0.07f, 15);
		
		InvenAt->PlayAnimation(L"Inventory", true);
		InvenAt->SetAffectedCamera(false);

		GameObject::Initialize();
	}

	void Inventory::Update()
	{
		GameObject::Update();
	}

	void Inventory::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}