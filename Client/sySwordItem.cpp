#include "sySwordItem.h"
#include "syMetaKnight.h"

namespace sy
{
	SwordItem::SwordItem(MetaKnight* owner)
		: mOwner(owner)
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