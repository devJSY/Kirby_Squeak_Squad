#include "syAnimator.h"
#include "syResourceManager.h"

namespace sy
{
	Animator::Animator()
		: Component(eComponentType::Animator)
		, mActiveAnimation(nullptr)
		, mbLoop(false)					
		, mbAffectedCamera(false)			
		, mAlpha(1.0f)
	{
	}

	Animator::~Animator()
	{
	}

	void Animator::Initialize()
	{
	}

	void Animator::Update()
	{
		if (mActiveAnimation)
		{
			mActiveAnimation->Update();

			// 애니메이션이 한 루프를 돌고난뒤 mbLoop설정이 되어있다면 리셋호출하여 다시 재생하도록 설정
			if (mActiveAnimation->IsComplete() && mbLoop) 
			{
				mActiveAnimation->Reset();
			}
		}
	}

	void Animator::Render(HDC hdc)
	{
		if (mActiveAnimation)
			mActiveAnimation->Render(hdc);
	}

	void Animator::CreateAnimation(const std::wstring& name, Texture* texture, Vector2 leftTop, Vector2 size, Vector2 offset, UINT spriteLength, float duration)
	{
		Animation* animation = nullptr;
		animation = ResourceManager::Find<Animation>(name); // ResourceManager 에서 만든 리소스가 있는지 먼저 확인
		if (animation != nullptr)
			return;

		animation = new Animation();
		animation->Create(name, texture
			, leftTop, size, offset
			, spriteLength, duration);
		animation->SetAnimator(this);

		mAnimations.insert(std::make_pair(name, animation)); // mAnimations에 생성한 애니메이션 추가
		ResourceManager::Insert<Animation>(name, animation); // ResourceManager 에 추가
	}

	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		auto iter = mAnimations.find(name);
		if (iter == mAnimations.end())
			return nullptr;

		return iter->second;
	}

	void Animator::PlayAnimation(const std::wstring& name, bool loop)
	{
		// mAnimations 로부터 찾아와서 현재 애니메이션으로 설정
		Animation* animation = FindAnimation(name);
		if (animation == nullptr)
			return;

		mActiveAnimation = animation;
		mActiveAnimation->Reset();
		mbLoop = loop;
	}
}
