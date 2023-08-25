#include "sySwordItem.h"


namespace sy
{
	SwordItem::SwordItem()
	{
	}

	SwordItem::~SwordItem()
	{

	}
	void SwordItem::Initialize()
	{
		GameObject::Initialize();
	}

	void SwordItem::Update()
	{
		GameObject::Update();
	}

	void SwordItem::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void SwordItem::OnCollisionEnter(Collider* other)
	{
	}
}