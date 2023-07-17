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

	protected:
		class Animator* mAnimator;
		eDirection mDir;

	private:
		enums::eAbilityType mAbilityType;
	};
}
