#pragma once
#include "syGameObject.h"

namespace sy
{
	using namespace math;

	// 카메라는 기본적으로 화면의 정중앙에 렌더링하도록 하고 맵의 끝부분에 도달했을땐 이동한값만큼 계산해줘야함
	class Camera
	{
	public:
		static void Initalize();
		static void Update();

		static Vector2 CalculatePosition(Vector2 pos) { return pos - mDistance; }

		static GameObject* GetTarget() { return mTarget; }
		static void SetTarget(GameObject* target) { mTarget = target; }

		static void SetCameraLimit(Vector2 limit) { mCameraLimit = limit; }
		static Vector2 GetCameraLimit() { return mCameraLimit; }

	private:
		static Vector2 mResolution;		// 화면 해상도
		static Vector2 mLookPosition;	// 카메라가 바라보고 있는 위치
		static Vector2 mDistance;		// 가운데를 원점으로 이동한 거리
		static GameObject* mTarget;		// 카메라가 바라보는 게임 오브젝트

		static Vector2 mCameraLimit;		// 카메라 이동제한 범위 Stage의 사이즈를 넣어주면됨
	};
}


