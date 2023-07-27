#pragma once
#include "syGameObject.h"

namespace sy
{
	using namespace math;

	// ī�޶�� �⺻������ ȭ���� ���߾ӿ� �������ϵ��� �ϰ� ���� ���κп� ���������� �̵��Ѱ���ŭ ����������
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
		static Vector2 mResolution;		// ȭ�� �ػ�
		static Vector2 mLookPosition;	// ī�޶� �ٶ󺸰� �ִ� ��ġ
		static Vector2 mDistance;		// ����� �������� �̵��� �Ÿ�
		static GameObject* mTarget;		// ī�޶� �ٶ󺸴� ���� ������Ʈ

		static Vector2 mCameraLimit;		// ī�޶� �̵����� ���� Stage�� ����� �־��ָ��
	};
}


