#pragma once
#include "syGameObject.h"

namespace sy
{
	class Enemy : public GameObject
	{
	public:
		Enemy(eAbilityType type);
		virtual ~Enemy();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);	

		virtual void OnCollisionEnter(class Collider* other) {};
		virtual void OnCollisionStay(class Collider* other) {};
		virtual void OnCollisionExit(class Collider* other) {};

		virtual void TakeHit(int DamageAmount, math::Vector2 HitDir) = 0;
		virtual void InHalded() {};
		virtual void ReleaseInHalded() {};

		eAbilityType GetAbilityType() { return mAbilityType; }

		int GetHP() { return mHP; }

	protected:
		void Damaged(int amount) { mHP -= amount; }
		void Recovery(int amount) { mHP += amount; }

	private:
		enums::eAbilityType mAbilityType;
		int			mHP;					// HP 0 ~ 100 ¹üÀ§
	};
}
