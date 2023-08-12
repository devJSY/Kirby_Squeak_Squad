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

		Kirby* GetActiveKirby() { return mKirbyType[(UINT)mAbilityType]; }

		void SetLevelEnter(bool enter) { mbLevelEnter = enter; }
		bool GetLevelEnter() { return mbLevelEnter; }

		eAbilityType GetAbilityType() { return mAbilityType; }

		void SetPlayerMode(ePlayerMode mode) { mMode = mode; }
		ePlayerMode GetPlayerMode() { return mMode; }		

		int GetMaxHP() { return mMaxHp; }
		int GetCurHP() { return mCurHp; }
		void SetHP(int hp) { mMaxHp = mCurHp = hp; }
		int GetLife() { return mLife; }

		void SetHitEnemy(class Enemy* enemy) { mHitEnemy = enemy; }
		Enemy* GetHitEnemy() { return mHitEnemy; }

		void Damaged(int amount) { mCurHp -= amount; }
		void Recovery(int amount) { mCurHp += amount; }

	private:
		std::vector<Kirby*>		mKirbyType;
		eAbilityType			mAbilityType;
		ePlayerMode				mMode;		

		bool					mbLevelEnter;	// Level Mode State ù���Խ� ����
		int						mMaxHp;
		int						mCurHp;			
		int						mLife;	

		Enemy*					mHitEnemy;

	};
}
