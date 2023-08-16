#pragma once
#include "syBossEnemy.h"

namespace sy
{
	class DarkNebula;

    class DarkNebula_Border : public GameObject
    {
		friend class DarkNebula;

	private:
		DarkNebula_Border(DarkNebula* owner);
		virtual ~DarkNebula_Border();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

	private:
		DarkNebula*			mOwner;
		class Transform*	mTransform;

    };
}

