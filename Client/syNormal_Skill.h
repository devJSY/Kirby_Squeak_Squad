#pragma once
#include "syEffects.h"

namespace sy
{
	class Normal_Skill : public Effects
	{
    public:
        Normal_Skill(GameObject* owner);
        virtual ~Normal_Skill();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other) override;
        virtual void OnCollisionStay(class Collider* other) override;
        virtual void OnCollisionExit(class Collider* other) override;

    private:
        void CheckPixelCollision();

    private:
        class Transform* mTransform;
        eDirection       mDir;
      
	};

}

