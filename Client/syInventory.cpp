#include "syInventory.h"

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