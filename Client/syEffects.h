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

        void SetOwner(GameObject* owner) { mOwner = owner; }
        GameObject* GetOwner() { return mOwner; }

    protected:
        class Animator* mAnimator;
        eDirection mDir;

    private:
        GameObject* mOwner; // ����Ʈ�� ������ ������Ʈ

    };
}
