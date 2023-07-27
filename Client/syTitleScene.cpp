#include "syTitleScene.h"
#include "syObject.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syTransform.h"
#include "syVideo.h"
#include "syApplication.h"
#include "syAnimator.h"
#include "syCamera.h"
#include "syCollisionManager.h"
#include "syApplication.h"
#include "sySoundManager.h"
#include "sySound.h"
#include "syResourceManager.h"
#include "syTime.h"

namespace sy
{
	TitleScene::TitleScene()
		: mVideo(nullptr)
		, mRadius(50.f)
	{
	}

	TitleScene::~TitleScene()
	{
	}

	void TitleScene::Initialize()
	{
		// 생성
		mVideo = object::Instantiate<Video>(eLayerType::Video);
		
		// 위치 설정
		mVideo->GetComponent<Transform>()->SetPosition(Vector2(Application::GetResolution()) / 2.f); 
		mVideo->SetSpeed(1.f); // 재생속도 설정

		Animator* videoAnimator = mVideo->AddComponent<Animator>();
		videoAnimator->CreateAnimationFolder(L"TitleVideo", L"..\\Resources\\Video\\Title", 0.033224f / mVideo->GetSpeed());
		videoAnimator->PlayAnimation(L"TitleVideo", true);
		videoAnimator->SetAffectedCamera(false);

		// Sound Load
		ResourceManager::Load<Sound>(L"TitleSound", L"..\\Resources\\Sound\\Theme\\Title.wav");

		Scene::Initialize();
	}

	void TitleScene::Update()
	{
		Scene::Update();

		Vector2 RenderPos = Application::GetScreenRenderPos();
		Vector2 ScreenSize = Application::GetScreenSize();
		Vector2 center;

		// 화면비율에따라 중점위치 계산
		center.x = RenderPos.x + (ScreenSize.x / 2.f);
		center.y = (ScreenSize.y / 4.f) * 3.f;

		Vector2 mousepos = Input::GetMousePos();

		// 중점에서 늘어난 비율 * 반지름 범위 클릭 인식
		if (fabs(center.x - mousepos.x) < (mRadius * Application::GetScreenMinRatio())
			&& fabs(center.y - mousepos.y) < (mRadius * Application::GetScreenMinRatio())
			&& Input::GetKeyDown(eKeyCode::MOUSE_LBTN))
		{
			SceneManager::LoadScene(L"LevelSelectScene");
		}
	}

	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		// 렌더링위치 설정
		Vector2 Rasolution = Application::GetResolution();
		Vector2 EllipsePos;		
		EllipsePos.x = Rasolution.x / 2.f;
		EllipsePos.y = (Rasolution.y / 4.f) * 3.f;

		// 브러쉬, 펜 설정
		HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transparentBrush);

		HPEN GreenPen = CreatePen(PS_SOLID, 1, RGB(50, 255, 50)); // Green
		HPEN oldPen = (HPEN)SelectObject(hdc, GreenPen);

		// 렌더링
		Ellipse(hdc
			, int(EllipsePos.x - mRadius)
			, int(EllipsePos.y - mRadius)
			, int(EllipsePos.x + mRadius)
			, int(EllipsePos.y + mRadius));

		// 원본 브러쉬, 펜 설정
		SelectObject(hdc, oldBrush);
		DeleteObject(transparentBrush);

		SelectObject(hdc, oldPen);
		DeleteObject(GreenPen);
	}
	void TitleScene::Enter()
	{
		// 카메라 설정 
		Camera::SetTarget(nullptr);

		Animator* videoAnimator = mVideo->GetComponent<Animator>();
		videoAnimator->PlayAnimation(L"TitleVideo", true);
		videoAnimator->ActiveAnimationReset();
	}

	void TitleScene::Exit()
	{
		// 카메라 설정 해제
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();
	}
}