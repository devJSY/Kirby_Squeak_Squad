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
