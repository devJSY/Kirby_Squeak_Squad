#pragma once
#include "syEffects.h"

namespace sy
{
    enum class eMetaKnight_TornadoSkillState
    {
        Active,
        Dead,
    };

    class MetaKnight;
    class MetaKnight_TornadoSkill : public Effects
    {
        friend class MetaKnight;
    private:
        MetaKnight_TornadoSkill(MetaKnight* owner);
        virtual ~MetaKnight_TornadoSkill();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other);
        virtual void OnCollisionStay(class Collider* other);

    private:
        eMetaKnight_TornadoSkillState   mState;
        class Transform*                mTransform;
        class Animator*                 mAnimator;
        eDirection                      mDir;
        float                           mDuration;
        bool                            mbActive;
    };
}

