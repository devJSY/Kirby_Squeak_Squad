#pragma once
#include "syComponent.h"

namespace sy
{
	enum class eColliderType
	{
		Box,
		Sphere,
	};

	using namespace math;

	class Collider : public Component
	{
	public:
		Collider();
		virtual ~Collider();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		void OncollisionEnter(Collider* other);
		void OncollisionStay(Collider* other);
		void OncollisionExit(Collider* other);

		Vector2 GetSize() { return mSize; }
		void SetSize(Vector2 size) { mSize = size; }
		Vector2 GetOffset() { return mOffset; }
		void SetOffset(Vector2 offset) { mOffset = offset; }
		Vector2 GetPosition() { return mPosition; }
		void SetPosition(Vector2 pos) { mPosition = pos; }
		float GetRadius() { return mRadius; }
		void SetRadius(float radius) { mRadius = radius; }
		UINT GetCollisionNumber() { return mCollisionNumber; }

		void SetAffectedCamera(bool enable) { mbAffectedCamera = enable; }
		bool GetAffectedCamera() { return mbAffectedCamera; }

		void SetColliderType(eColliderType type) { mColliderType = type; }
		eColliderType GetColliderType() { return mColliderType; }

	private:
		static UINT mCollisionCount;

		eColliderType mColliderType;

		Vector2 mSize;
		Vector2 mOffset;
		Vector2 mPosition;

		float	mRadius;

		UINT mCollisionNumber;
		bool mbIsCollision;
		bool mbAffectedCamera;			// 카메라 영향 여부		
	};
}

