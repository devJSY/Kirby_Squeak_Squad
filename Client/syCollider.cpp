#include "syCollider.h"
#include "syTransform.h"
#include "syGameObject.h"
#include "syCamera.h"

namespace sy
{
	UINT Collider::mCollisionCount = 0;

	Collider::Collider()
		:Component(eComponentType::Collider)
		, mSize(Vector2::Zero)
		, mOffset(Vector2::Zero)
		, mCollisionNumber(mCollisionCount++)
		, mbIsCollision(false)
	{
	}

	Collider::~Collider()
	{
	}

	void Collider::Initialize()
	{
	}

	void Collider::Update()
	{
	}

	void Collider::Render(HDC hdc)
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		// pos ÁÂ»ó´Ü ¼³Á¤
		Vector2 pos = tr->GetPosition();
		mPosition = pos + mOffset;

		pos.x -= mSize.x / 2.0f;
		pos.y -= mSize.y / 2.0f;
		pos.x += mOffset.x;
		pos.y += mOffset.y;

		pos = Camera::CalculatePosition(pos);

		HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transparentBrush);

		HPEN ColorPen = NULL;
		if (mbIsCollision)
		{
			ColorPen = CreatePen(PS_SOLID, 1, RGB(255, 50, 50)); // Red
		}
		else
		{
			ColorPen = CreatePen(PS_SOLID, 1, RGB(50, 255, 50)); // Green
		}

		HPEN oldPen = (HPEN)SelectObject(hdc, ColorPen);

		Rectangle(hdc
			, int(pos.x), int(pos.y)
			, int(pos.x + mSize.x), int(pos.y + mSize.y));

		SelectObject(hdc, oldBrush);
		DeleteObject(transparentBrush);

		SelectObject(hdc, oldPen);
		DeleteObject(ColorPen);
	}

	void Collider::OncollisionEnter(Collider* other)
	{
		mbIsCollision = true;
		GetOwner()->OnCollisionEnter(other);
	}

	void Collider::OncollisionStay(Collider* other)
	{
		GetOwner()->OnCollisionStay(other);
	}

	void Collider::OncollisionExit(Collider* other)
	{
		mbIsCollision = false;
		GetOwner()->OnCollisionExit(other);
	}
}