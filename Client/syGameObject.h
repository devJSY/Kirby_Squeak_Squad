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
                // 자식타입과 T타입이 일치한다면 주소를 반환 그렇지 않으면 nullptr 반환
                comp = dynamic_cast<T*>(c);
                if (comp != nullptr)
                    return comp;
            }
            return comp;
        }

        template <typename T>
        T* AddComponent()
        {
            // 중복생성 에러처리
            for (Component* com : mComponents)
            {
                Component* temp = dynamic_cast<T*>(com);

                if (temp != nullptr)       
                    assert(nullptr);
            }            

            // 없다면 새로생성
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
