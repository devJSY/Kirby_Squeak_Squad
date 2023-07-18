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

		eAbilityType GetAbilityType() { return mAbilityType; }

		eDirection GetDirection() { return mDir; }
		void SetDirection(eDirection dir) { mDir = dir; }

		class Animator* GetAnimator() { return mAnimator; }

	private:
		class Animator* mAnimator;
		eDirection mDir;
		enums::eAbilityType mAbilityType;
	};
}
