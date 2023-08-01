#pragma once
#include "syGameObject.h"

namespace sy
{
	enum class ePlayerMode
	{
		LevelMode,
		PlayMode,
	};

	class Player : public GameObject
	{
	public:
		Player(eAbilityType type, ePlayerMode mode);
		virtual ~Player();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) {};
		virtual void OnCollisionStay(class Collider* other) {};
		virtual void OnCollisionExit(class Collider* other) {};

		virtual void TakeHit(int DamageAmount, math::Vector2 HitDir) = 0;

		eAbilityType GetAbilityType() { return mAbilityType; }

		void SetPlayerMode(ePlayerMode mode) { mMode = mode; }
		ePlayerMode GetPlayerMode() { return mMode; }		

		int GetHP() { return mHP; }

	protected:
		void Damaged(int amount) { mHP -= amount; }
		void Recovery(int amount) { mHP += amount; }

	private:
		enums::eAbilityType mAbilityType;
		ePlayerMode mMode;		

		int			mHP;	// HP 0 ~ 100 ¹üÀ§
		int			mLife;	
	};
}
