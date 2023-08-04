#include "syCollider.h"
#include "syTransform.h"
#include "syGameObject.h"
#include "syCamera.h"
#include "syInput.h"

namespace sy
{
	UINT Collider::mCollisionCount = 0;

	Collider::Collider()
		:Component(eComponentType::Collider)
		, mColliderType(eColliderType::Box)
		, mSize(Vector2::Zero)
		, mOffset(Vector2::Zero)
		, mRadius(0.f)
		, mCollisionNumber(mCollisionCount++)
		, mbIsCollision(false)
		, mbAffectedCamera(true)
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
		pos += mOffset;

		if(mbAffectedCamera)
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

		if (Camera::GetColliderRenderTrig())
		{
			// Collider ·»´õ¸µ
			if (mColliderType == eColliderType::Box)
			{
				Rectangle(hdc
					, int(pos.x - mSize.x / 2.f), int(pos.y - mSize.y / 2.f)
					, int(pos.x + mSize.x / 2.f), int(pos.y + mSize.y / 2.f));
			}
			else if (mColliderType == eColliderType::Sphere)
			{
				Ellipse(hdc
					, int(pos.x - mRadius), int(pos.y - mRadius)
					, int(pos.x + mRadius), int(pos.y + mRadius));
			}
		}

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