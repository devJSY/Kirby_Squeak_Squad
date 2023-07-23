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

		eAbilityType GetAbilityType() { return mAbilityType; }

		void SetPlayerMode(ePlayerMode mode) { mMode = mode; }
		ePlayerMode GetPlayerMode() { return mMode; }

	private:
		enums::eAbilityType mAbilityType;
		ePlayerMode mMode;		
	};
}
