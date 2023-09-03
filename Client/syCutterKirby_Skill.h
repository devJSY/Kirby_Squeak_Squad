#pragma once
#include "syEffects.h"

namespace sy
{
    class CutterKirby_Skill : public Effects
    {
    public:
        CutterKirby_Skill(class Player* owner);
        virtual ~CutterKirby_Skill();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other) override;
        virtual void OnCollisionStay(class Collider* other) override;

    private:
        eDirection          mDir;
        class Transform*    mTransform;
        class Rigidbody*    mRigidbody;
        float               mDuration;
    };
}

