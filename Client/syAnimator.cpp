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
		, mScale(Vector2::One)
	{
	}

	Animator::~Animator()
	{
		//for (auto iter : mAnimations)
		//{
		//	if (nullptr != iter.second)
		//	{
		//		delete iter.second;
		//		iter.second = nullptr;
		//	}
		//}
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

	Animation* Animator::CreateAnimation(Texture* texture
		, const std::wstring& name
		, Vector2 leftTop
		, Vector2 size, Vector2 Interbal
		, float duration, UINT spriteLength
		, Vector2 offset)
	{
		// Animation은 ResourceManager가 관리하지않고 각 Animator 가 관리
		Animation* animation = nullptr;
		animation = ResourceManager::Find<Animation>(name);
		if (animation != nullptr)
		{
			mAnimations.insert(std::make_pair(name, animation));
			return animation;
		}

		animation = new Animation();
		animation->Create(texture, name
			, leftTop, size, Interbal
			, duration, spriteLength, offset);
		animation->SetAnimator(this);

		mAnimations.insert(std::make_pair(name, animation));
		ResourceManager::Insert<Animation>(name, animation);

		return animation;
	}

	void Animator::CreateAnimationFolder(
		const std::wstring& name
		, const std::wstring& path
		, float duration
		, Vector2 offset)
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

		std::wstring spriteSheetName = name + L"SpriteSheet";
		// 구한 크기값으로 Texture 생성
		Texture* spriteSheet = Texture::Create(spriteSheetName, width * fileCount, height);

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
			// 이미지 중상단에 붙여넣기
			BitBlt(spriteSheet->GetHdc(), int((width * idx) + ((width - image->GetWidth()) / 2.0f)), 0
				, image->GetWidth(), image->GetHeight()
				, image->GetHdc(), 0, 0, SRCCOPY);

			idx++;
		}

		// 생성한 spriteSheet로 애니메이션 생성
		CreateAnimation(spriteSheet, name
			, Vector2(0.0f, 0.0f)
			, Vector2(width, height), Vector2(width, 0), duration
			,fileCount, offset);
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

		// 애니메이션이 변경되는 경우에만 Reset() 적용
		if (mActiveAnimation != animation)		
			animation->Reset();		

		mActiveAnimation = animation;
		mbLoop = loop;			
	}

	void Animator::SetAniScale(const std::wstring& name, Vector2 scale)
	{
		Animation* animation = FindAnimation(name);
		if (animation == nullptr)
			return;

		animation->SetScale(scale);
	}
}
