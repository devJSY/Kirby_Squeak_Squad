#include "syBlock.h"
#include "syTexture.h"
#include "syAnimator.h"
#include "syTransform.h"
#include "syResourceManager.h"
#include "sySpriteRenderer.h"
#include "syCollider.h"

namespace sy
{
	Block::Block()
		: mAnimator(nullptr)

	{
	}

	Block::~Block()
	{
	}

	void Block::Initialize()
	{
		Texture* Block_tex = ResourceManager::Load<Texture>(L"Block", L"..\\Resources\\Effect\\Block.bmp");
		Texture* Block_Destroy = ResourceManager::Load<Texture>(L"Block_Destroy", L"..\\Resources\\Effect\\Block_Destroy.bmp");

		mAnimator = AddComponent<Animator>();
		SpriteRenderer* sp = AddComponent<SpriteRenderer>();
		sp->SetTexture(Block_tex);
		Collider* col = AddComponent<Collider>();
		col->SetSize(Vector2(16.f, 16.f));

		mAnimator->CreateAnimation(Block_Destroy, L"Block_Destroy", Vector2(0.f, 0.f), Vector2(16.f, 16.f), Vector2(16.f, 0.f), 0.03f, 5);

		GameObject::Initialize();
	}

	void Block::Update()
	{
		GameObject::Update();
	}

	void Block::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Block::OnCollisionEnter(Collider* other)
	{
	}

	void Block::OnCollisionStay(Collider* other)
	{
		//Transform* otherTr = other->GetOwner()->GetComponent<Transform>();

		//float lenX = fabs(other->GetPosition().x - GetComponent<Collider>()->GetPosition().x);
		//float scaleX = fabs(other->GetSize().x / 2.0f + GetComponent<Collider>()->GetSize().x / 2.0f);

		//float lenY = fabs(other->GetPosition().y - GetComponent<Collider>()->GetPosition().y);
		//float scaleY = fabs(other->GetSize().y / 2.0f + GetComponent<Collider>()->GetSize().y / 2.0f);


		//if (lenX < scaleX)
		//{
		//	Vector2 pos = otherTr->GetPosition();
		//	pos.x -= (scaleX - lenX) - 1.0f;
		//	otherTr->SetPosition(pos);
		//}

		//if (lenY < scaleY)
		//{
		//	Vector2 pos = otherTr->GetPosition();
		//	pos.y -= (scaleY - lenY) - 1.0f;
		//	otherTr->SetPosition(pos);
		//}
	}

	void Block::OnCollisionExit(Collider* other)
	{
	}
}