#pragma once
#include "syEnemy.h"

namespace sy
{
    enum class eCrimpState
    {
        Move,
        Attack,
        Damage,
        Dead,

        End,
    };

    class Crimp : public Enemy
    {
    public:
        Crimp();
        virtual ~Crimp();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other);
        virtual void OnCollisionStay(class Collider* other);
        virtual void OnCollisionExit(class Collider* other);

        virtual void TakeHit(int DamageAmount, math::Vector2 HitDir) override;

    private:
        void Move();
        void Attack();
        void Damage();
        void Dead();

    private:
        eCrimpState	        mState;
        class Animator*     mAnimator;
        class Transform*    mTransform;

    };
}

