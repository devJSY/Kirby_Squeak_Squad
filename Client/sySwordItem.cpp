#include "sySwordItem.h"
#include "syMetaKnight.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"
#include "syPlayer.h"
#include "syCollider.h"
#include "syTransform.h"

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
		Collider* col = AddComponent<Collider>();
		col->SetSize(Vector2(15.f, 25.f));
		col->SetOffset(Vector2(0.f, 35.f));

		Texture* MetaKnight_SwordItem_Tex = ResourceManager::Load<Texture>(L"MetaKnight_SwordItem_Tex", L"..\\Resources\\Enemy\\Boss\\MetaKnight\\SwordItem.bmp");
		MetaKnight_SwordItem_Tex->SetScale(Vector2(0.35f, 0.35f));

		Animator* animator = AddComponent<Animator>();
		animator->CreateAnimation(MetaKnight_SwordItem_Tex, L"MetaKnight_SwordItem", Vector2::Zero, Vector2(165.f, 282.f), Vector2(165.f, 0.f), 0.1f, 2);
		animator->PlayAnimation(L"MetaKnight_SwordItem", true);

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
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player == nullptr)
			return;

		player->SetKirbyType(eAbilityType::Sword);
		player->AddTransformEffect();
		mOwner->SetAppear();
		Destroy(this);
	}
}