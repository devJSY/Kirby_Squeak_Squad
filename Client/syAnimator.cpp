#include "syAnimator.h"
#include "syResourceManager.h"
#include "syTexture.h"

namespace sy
{
	Animator::Animator()
		: Component(eComponentType::Animator)
		, mActiveAnimation(nullptr)
		, mbLoop(false)					
		, mbAffectedCamera(true)			
		, mAlpha(1.0f)
		, mbComplete(false)
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
			if (mActiveAnimation->IsComplete()) 
			{
				if (mbLoop)
				{
					mActiveAnimation->Reset();
				}
				else
				{
					mbComplete = true; // 반복설정이 되어있지않고 한 루프를 끝난경우 완료로 설정
				}
			}
		}
	}

	void Animator::Render(HDC hdc)
	{
		if (mActiveAnimation)
			mActiveAnimation->Render(hdc);
	}

	void Animator::CreateAnimation(const std::wstring& name
		, Texture* texture
		, Vector2 leftTop, Vector2 size
		, UINT spriteLength, Vector2 offset
		, float duration)
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

	void Animator::CreateAnimationFolder(const std::wstring& name
		, const std::wstring& path, Vector2 offset, float duration)
	{
		UINT width = 0;
		UINT height = 0;
		UINT fileCount = 0;

		std::filesystem::path fs(path);
		std::vector<Texture*> images = {};
		// 디렉토리 파일중에 width 와 height 가 제일 큰값 구하기, 파일갯수 저장
		for (auto& p : std::filesystem::recursive_directory_iterator(path))
		{
			std::wstring fileName = p.path().filename();
			std::wstring fullName = p.path();

			// 확장자가 png인 경우 스킵
			const std::wstring ext = p.path().extension();
			if (ext == L".png")
				continue;

			Texture* image = ResourceManager::Load<Texture>(fileName, fullName);
			images.push_back(image);

			if (width < image->GetWidth())
				width = image->GetWidth();

			if (height < image->GetHeight())
				height = image->GetHeight();

			fileCount++;
		}

		// 구한 크기값으로 Texture 생성
		Texture* spriteSheet = Texture::Create(name, width * fileCount, height);

		// Video 기본 타입 Bmp로 설정
		spriteSheet->SetType(eTextureType::Bmp); 

		// 32bit 비트맵 파일인경우 AlphaBmp 타입으로 설정한다
		BITMAP info = {};
		GetObject(spriteSheet->GetBitmap(), sizeof(BITMAP), &info);		
		if (info.bmBitsPixel == 32)
			spriteSheet->SetType(eTextureType::AlphaBmp);


		// Texture 에 Load 해두었던 image 붙여넣기
		int idx = 0;
		for (Texture* image : images)
		{
			BitBlt(spriteSheet->GetHdc(), width * idx, 0
				, image->GetWidth(), image->GetHeight()
				, image->GetHdc(), 0, 0, SRCCOPY);

			idx++;
		}

		// 생성한 spriteSheet로 애니메이션 생성
		CreateAnimation(name
			, spriteSheet, Vector2(0.0f, 0.0f)
			, Vector2(width, height), fileCount
			, offset, duration);
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
		mbComplete = false;
	}
}
