#pragma once
#include "syGameObject.h"
#include "syEnemyHPbarUI.h"

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
		virtual void TakeInhaled(math::Vector2 InhaleDir) {};
		virtual bool IsDamagedState() const = 0;
		virtual bool IsDeadState() const = 0;

		eAbilityType GetAbilityType() const { return mAbilityType; }
		int GetMaxHP() const { return mMaxHp; }
		int GetCurHP() const { return mCurHp; }
		void SetHP(int hp) { mMaxHp = mCurHp = hp; }
		
		EnemyHPbarUI* GetEnemyHPbarUI() const { return mHPbarUI; }
		void SetHPBarUIRenderTrig(bool trig){ mHPbarUI->SetRenderTrig(trig); }

	protected:
		void Damaged(int amount) { mCurHp -= amount; }
		void Recovery(int amount) { mCurHp += amount; }

	private:
		enums::eAbilityType		mAbilityType;
		int						mMaxHp;					
		int						mCurHp;					
		EnemyHPbarUI*			mHPbarUI;
	};
}
