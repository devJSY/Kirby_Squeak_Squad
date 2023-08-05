#pragma once
#include "syEffects.h"

namespace sy
{
    enum class eLandingDir
    {
        LeftTop,
        RightTop,
        LeftBotton,
        RightBotton,
    };

	class Landing_Effect : public Effects
	{
    public:
        Landing_Effect(GameObject* owner);
        virtual ~Landing_Effect();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

    private:
        class Transform*    mTransform;
        eLandingDir         mDir;
        float               mDuration;

	};
}

