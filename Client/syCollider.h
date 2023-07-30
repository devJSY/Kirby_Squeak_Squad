#pragma once
#include "syComponent.h"

namespace sy
{
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
		UINT GetCollisionNumber() { return mCollisionNumber; }

		void SetAffectedCamera(bool enable) { mbAffectedCamera = enable; }
		bool GetAffectedCamera() { return mbAffectedCamera; }

	private:
		static UINT mCollisionCount;

		Vector2 mSize;
		Vector2 mOffset;
		Vector2 mPosition;

		UINT mCollisionNumber;
		bool mbIsCollision;
		bool mbAffectedCamera;			// 카메라 영향 여부
		bool mbRenderTrig;
	};
}

