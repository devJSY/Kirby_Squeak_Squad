#pragma once
#include "syGameObject.h"

namespace sy
{
	class Player : public GameObject
	{
	public:
		Player(eAbilityType type);
		virtual ~Player();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) {};
		virtual void OnCollisionStay(class Collider* other) {};
		virtual void OnCollisionExit(class Collider* other) {};

		eAbilityType GetAbilityType() { return mAbilityType; }

	private:
		enums::eAbilityType mAbilityType;
	};
}
