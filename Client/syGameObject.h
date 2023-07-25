#pragma once
#include "syEntity.h"
#include "syComponent.h"

namespace sy
{
    class GameObject : public Entity
    {
    public:
        GameObject();
        virtual ~GameObject();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        template <typename T>
        T* GetComponent()
        {
            T* comp = nullptr;
            for (Component* c : mComponents)
            {
                // �ڽ�Ÿ�԰� TŸ���� ��ġ�Ѵٸ� �ּҸ� ��ȯ �׷��� ������ nullptr ��ȯ
                comp = dynamic_cast<T*>(c);
                if (comp != nullptr)
                    return comp;
            }
            return comp;
        }

        template <typename T>
        T* AddComponent()
        {
            // �ߺ����� ����ó��
            for (Component* com : mComponents)
            {
                Component* temp = dynamic_cast<T*>(com);

                if (temp != nullptr)       
                    assert(nullptr);
            }            

            // ���ٸ� ���λ���
            T* comp = new T();
            mComponents.push_back(comp);
            comp->SetOwner(this);
            return comp;
        }

        virtual void OnCollisionEnter(class Collider* other) {};
        virtual void OnCollisionStay(class Collider* other) {};
        virtual void OnCollisionExit(class Collider* other) {};

    private:
        std::vector<Component*> mComponents;
    };
}
