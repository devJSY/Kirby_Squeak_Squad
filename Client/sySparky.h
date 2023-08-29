#pragma once
#include "syEnemy.h"

namespace sy
{
    enum class eSparkyState
    {
        Move,
        Jump,
        SkillReady,
        Skill,
        Damage,
        Dead,
        Inhaled,
        End,
    };

    class Sparky : public Enemy
    {
    public:
        Sparky();
        virtual ~Sparky();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other);
        virtual void OnCollisionStay(class Collider* other);
        virtual void OnCollisionExit(class Collider* other);

        virtual void TakeHit(int DamageAmount, math::Vector2 HitDir) override;
        virtual void TakeInhaled(math::Vector2 InhaleDir) override;
        virtual bool IsDamagedState() const { return mState == eSparkyState::Damage; }
        virtual bool IsDeadState() const { return mState == eSparkyState::Dead; }

        eSparkyState GetSparkyState() const { return mState; }

    private:
        void Move();
        void Jump();
        void SkillReady();
        void Skill();
        void Damage();
        void Dead();
        void Inhaled();

    private:
        eSparkyState	     mState;
        class Animator*      mAnimator;
        class Transform*     mTransform;

        float               mAttackDelay;
    };
}

