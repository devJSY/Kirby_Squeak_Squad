#pragma once
#include "syGameObject.h"

namespace sy
{
	class Enemy :public GameObject
	{
	public:
		Enemy(eAbilityType type);
		virtual ~Enemy();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		
		eAbilityType GetAbilityType() { return mAbilityType; }

	protected:
		class Animator* mAnimator;

	private:
		enums::eAbilityType mAbilityType;
	};
}
