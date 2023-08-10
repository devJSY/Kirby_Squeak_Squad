#pragma once
#include "syEffects.h"

namespace sy
{
    class SparkKirby_Skill : public Effects
    {
    public:
        SparkKirby_Skill(class Player* owner);
        virtual ~SparkKirby_Skill();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other) override;
        virtual void OnCollisionStay(class Collider* other) override;

    private:
        eDirection mDir;

    };
}
