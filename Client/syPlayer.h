#pragma once
#include "syGameObject.h"
#include "syDefaultKirby.h"

namespace sy
{
	enum class ePlayerMode
	{
		LevelMode,
		PlayMode,
	};

	class Kirby;
	class Enemy;

	class Player : public GameObject
	{
	public:
		Player(eAbilityType type, ePlayerMode mode);
		virtual ~Player();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		virtual void TakeHit(int DamageAmount, math::Vector2 HitDir);

		void PlayerTransformations(eAbilityType type);
		void ReleaseTransformations(eDefaultKirbyState state);
		void SetKirbyType(eAbilityType type);
		void AddTransformEffect();

		Kirby* GetActiveKirby() const { return mKirbyType[(UINT)mAbilityType]; }

		void SetLevelEnter(bool enter) { mbLevelEnter = enter; }
		bool GetLevelEnter() const { return mbLevelEnter; }

		eAbilityType GetAbilityType() const { return mAbilityType; }

		void SetPlayerMode(ePlayerMode mode) { mMode = mode; }
		ePlayerMode GetPlayerMode() const { return mMode; }

		int GetMaxHP() const { return mMaxHp; }
		int GetCurHP() const { return mCurHp; }
		void SetHP(int hp) { mMaxHp = mCurHp = hp; }
		int GetLife() const { return mLife; }

		void SetHitEnemy(class Enemy* enemy) { mHitEnemy = enemy; }
		Enemy* GetHitEnemy() const { return mHitEnemy; }

		void Damaged(int amount) { mCurHp -= amount; }
		void Recovery(int amount) { mCurHp += amount; }

		bool IsDamaged() const { return mbDamaged; }

	private:
		std::vector<Kirby*>		mKirbyType;
		eAbilityType			mAbilityType;
		ePlayerMode				mMode;		

		bool					mbLevelEnter;	// Level Mode State ù���Խ� ����
		int						mMaxHp;
		int						mCurHp;			
		int						mLife;	

		Enemy*					mHitEnemy;

		bool					mbDamaged;
		float					mDamageDelay;
	};
}
