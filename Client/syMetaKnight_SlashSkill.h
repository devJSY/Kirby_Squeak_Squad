#pragma once
#include "syEffects.h"

namespace sy
{
    using namespace math;
    class MetaKnight;
    class MetaKnight_SlashSkill : public Effects
    {
        friend class MetaKnight;
    private:
        MetaKnight_SlashSkill(MetaKnight* owner, Vector2 MoveDir);
        virtual ~MetaKnight_SlashSkill();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other);
        virtual void OnCollisionStay(class Collider* other);

    private:
        class Transform*        mTransform;
        Vector2                 mMoveDir;
        float                   mDuration;
    };
}

