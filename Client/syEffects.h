#pragma once
#include "syGameObject.h"

namespace sy
{
    class Effects : public GameObject
    {
    public:
        Effects(GameObject* owner);
        virtual ~Effects();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other) {};
        virtual void OnCollisionStay(class Collider* other) {};
        virtual void OnCollisionExit(class Collider* other) {};

        GameObject* GetOwner() const { return mOwner; }

    private:
        GameObject* mOwner; // ����Ʈ�� ������ ������Ʈ  
    };
}
