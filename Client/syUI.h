#pragma once
#include "syGameObject.h"

namespace sy
{
	class UI : public GameObject
	{
	public:
		UI();
		virtual ~UI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) {};
		virtual void OnCollisionStay(class Collider* other) {};
		virtual void OnCollisionExit(class Collider* other) {};
	};
}
