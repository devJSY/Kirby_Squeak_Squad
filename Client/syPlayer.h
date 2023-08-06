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

		Kirby* GetActiveKirby() { return mKirbyType[(UINT)mAbilityType]; }

		void SetLevelEnter(bool enter) { mbLevelEnter = enter; }
		bool GetLevelEnter() { return mbLevelEnter; }

		eAbilityType GetAbilityType() { return mAbilityType; }

		void SetPlayerMode(ePlayerMode mode) { mMode = mode; }
		ePlayerMode GetPlayerMode() { return mMode; }		

		int GetHP() { return mHP; }

		void SetHitEnemy(class Enemy* enemy) { mHitEnemy = enemy; }
		Enemy* GetHitEnemy() { return mHitEnemy; }

		void Damaged(int amount) { mHP -= amount; }
		void Recovery(int amount) { mHP += amount; }

	private:
		std::vector<Kirby*>		mKirbyType;
		eAbilityType			mAbilityType;
		ePlayerMode				mMode;		

		bool					mbLevelEnter;	// Level Mode State 첫진입시 설정
		int						mHP;			// HP 0 ~ 100 범위
		int						mLife;	

		Enemy*					mHitEnemy;

	};
}
