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

    public:
        Component* GetComp(enums::eComponentType ctype)
        {
            for (Component* c : mComponents)
            {
                if (c->GetCompType() == ctype)
                    return c;
            }
            return nullptr;
        }

    private:
        std::vector<Component*> mComponents;
    };
}
