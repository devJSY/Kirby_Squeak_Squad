#include "syGround.h"
#include "syCollider.h"
#include "syTransform.h"
#include "syPlayer.h"
#include "syRigidbody.h"

namespace sy
{
	Ground::Ground()
	{
		AddComponent<Collider>()->SetSize(Vector2(1600.f, 50.f));
		GetComponent<Transform>()->SetPosition(Vector2(800.f, 170.f));
	}

	Ground::~Ground()
	{
	}

	void Ground::Initialize()
	{
	}

	void Ground::Update()
	{
		GameObject::Update();
	}

	void Ground::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Ground::OnCollisionEnter(Collider* other)
	{
		other->GetOwner()->GetComponent<Rigidbody>()->SetGround(true);

		Player* player = dynamic_cast<Player*>(other->GetOwner());
		Transform* tr = player->GetComponent<Transform>();
		Rigidbody* rb = player->GetComponent<Rigidbody>();

		float len = fabs(other->GetPosition().y - this->GetComponent<Collider>()->GetPosition().y);
		float scale = fabs(other->GetSize().y / 2.0f + this->GetComponent<Collider>()->GetSize().y / 2.0f);

		if (len < scale)
		{
			Vector2 playerPos = tr->GetPosition();
			playerPos.y -= (scale - len) - 1.0f;
			tr->SetPosition(playerPos);
		}

		rb->SetGround(true);
	}

	void Ground::OnCollisionStay(Collider* other)
	{
	}

	void Ground::OnCollisionExit(Collider* other)
	{
		other->GetOwner()->GetComponent<Rigidbody>()->SetGround(false);
	}
}
