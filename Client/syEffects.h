#pragma once
#include "syGameObject.h"

namespace sy
{
    class Effects : public GameObject
    {
    public:
        Effects();
        virtual ~Effects();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other) {};
        virtual void OnCollisionStay(class Collider* other) {};
        virtual void OnCollisionExit(class Collider* other) {};

        void SetOwner(GameObject* owner) { mOwner = owner; }
        GameObject* GetOwner() { return mOwner; }

        class Animator* GetAnimator() { return mAnimator; }

    private:
        GameObject* mOwner; // 이펙트를 생성한 오브젝트
        class Animator* mAnimator;
  
    };
}
