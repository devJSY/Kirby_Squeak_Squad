#include "syIceKirby.h"
#include "syAnimator.h"
#include "syTransform.h"
#include "syRigidbody.h"
#include "syResourceManager.h"
#include "syTexture.h"
#include "sySound.h"

namespace sy
{
	IceKirby::IceKirby(class Player* owner)
		: Kirby(owner)
		, mState(eIceKirbyState::Idle)
		, mAnimator(nullptr)
		, mTransform(nullptr)
		, mRigidBody(nullptr)
		, mDir(eDirection::RIGHT)
		, mbOnLeftStop(false)
		, mbOnRightStop(false)
		, mbTopStop(false)
		, mbOnSlope(false)
	{
	}

	IceKirby::~IceKirby()
	{
	}

	void IceKirby::Initialize()
	{
		// 텍스쳐 로드
		Texture* DefaultKirby_Right = ResourceManager::Load<Texture>(L"DefaultKirby_Right_Tex", L"..\\Resources\\Kirby\\DefaultKirby\\DefaultKirby_Right.bmp");
		Texture* DefaultKirby_Left = ResourceManager::Load<Texture>(L"DefaultKirby_Left_Tex", L"..\\Resources\\Kirby\\DefaultKirby\\DefaultKirby_Left.bmp");

		// 부모생성자에서 만들었던 컴포넌트 멤버변수로 저장
		mAnimator = GetOwner()->GetComponent<Animator>();
		mTransform = GetOwner()->GetComponent<Transform>();

		mRigidBody = GetOwner()->GetComponent<Rigidbody>();
		mRigidBody->SetGround(true);

		// 애니메이션 생성
		mAnimator->CreateAnimation(DefaultKirby_Right, L"Choice", Vector2(309.f, 324.f), Vector2(22.f, 28.f), Vector2(22.f, 0.f), 0.04f, 9);
		mAnimator->CreateAnimation(DefaultKirby_Right, L"Enter", Vector2(738.f, 7.f), Vector2(19.f, 22.f), Vector2(19.f, 0.f), 1.f, 1);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Idle", Vector2(8.f, 11.f), Vector2(20.f, 18.f), Vector2(20.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Idle", Vector2(972.f, 11.f), Vector2(20.f, 18.f), Vector2(20.f, 0.f), 1.f, 1);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Stop", Vector2(468.f, 8.f), Vector2(22.f, 22.f), Vector2(22.f, 0.f), 0.3f, 1);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Stop", Vector2(510.f, 8.f), Vector2(22.f, 22.f), Vector2(22.f, 0.f), 0.3f, 1);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Walk", Vector2(253.f, 10.f), Vector2(21.f, 19.f), Vector2(21.f, 0.f), 0.07f, 10);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Walk", Vector2(726.f, 10.f), Vector2(21.f, 19.f), Vector2(-21.f, 0.f), 0.07f, 10);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Run", Vector2(569.f, 306.f), Vector2(24.f, 19.f), Vector2(24.f, 0.f), 0.043f, 8);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Run", Vector2(407.f, 306.f), Vector2(24.f, 19.f), Vector2(-24.f, 0.f), 0.043f, 8);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Jump", Vector2(716.f, 9.f), Vector2(20.f, 20.f), Vector2(20.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Jump", Vector2(264.f, 9.f), Vector2(20.f, 20.f), Vector2(-20.f, 0.f), 1.f, 1);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Turn", Vector2(759.f, 9.f), Vector2(22.f, 20.f), Vector2(22.f, 0.f), 0.05f, 6);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Turn", Vector2(219.f, 9.f), Vector2(22.f, 20.f), Vector2(-22.f, 0.f), 0.05f, 6);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Damage", Vector2(0.f, 179.f), Vector2(22.f, 22.f), Vector2(22.f, 0.f), 0.04f, 10);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Damage", Vector2(978.f, 179.f), Vector2(22.f, 22.f), Vector2(-22.f, 0.f), 0.04f, 10);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Drop", Vector2(892.f, 10.f), Vector2(21.f, 19.f), Vector2(21.f, 0.f), 0.05f, 2);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Drop", Vector2(87.f, 10.f), Vector2(21.f, 19.f), Vector2(-21.f, 0.f), 0.05f, 2);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Down", Vector2(31.f, 19.f), Vector2(25.f, 10.f), Vector2(25.f, 0.f), 1.f, 1, Vector2(0.f, 5.f));
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Down", Vector2(944.f, 19.f), Vector2(25.f, 10.f), Vector2(-25.f, 0.f), 1.f, 1, Vector2(0.f, 5.f));

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_FlyStart", Vector2(642.f, 37.f), Vector2(21.f, 24.f), Vector2(21.f, 0.f), 0.05f, 4);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_FlyStart", Vector2(337.f, 37.f), Vector2(21.f, 24.f), Vector2(-21.f, 0.f), 0.05f, 4);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_FlyEnd", Vector2(705.f, 37.f), Vector2(21.f, 24.f), Vector2(-21.f, 0.f), 0.05f, 4);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_FlyEnd", Vector2(274.f, 37.f), Vector2(21.f, 24.f), Vector2(21.f, 0.f), 0.05f, 4);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_FlyDown", Vector2(733.f, 36.f), Vector2(24.f, 25.f), Vector2(24.f, 0.f), 0.15f, 2);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_FlyDown", Vector2(243.f, 36.f), Vector2(24.f, 25.f), Vector2(-24.f, 0.f), 0.15f, 2);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_FlyUp", Vector2(785.f, 36.f), Vector2(26.f, 25.f), Vector2(26.f, 0.f), 0.07f, 4);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_FlyUp", Vector2(189.f, 36.f), Vector2(26.f, 25.f), Vector2(-26.f, 0.f), 0.07f, 4);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Inhale_1", Vector2(796.f, 179.f), Vector2(23.f, 22.f), Vector2(23.f, 0.f), 0.06f, 2);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Inhale_1", Vector2(181.f, 179.f), Vector2(23.f, 22.f), Vector2(-23.f, 0.f), 0.06f, 2);
		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Inhale_2", Vector2(842.f, 179.f), Vector2(23.f, 22.f), Vector2(23.f, 0.f), 0.06f, 2);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Inhale_2", Vector2(135.f, 179.f), Vector2(23.f, 22.f), Vector2(-23.f, 0.f), 0.06f, 2);
		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Inhale_3", Vector2(896.f, 184.f), Vector2(26.f, 17.f), Vector2(26.f, 0.f), 0.1f, 4);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Inhale_3", Vector2(78.f, 184.f), Vector2(26.f, 17.f), Vector2(-26.f, 0.f), 0.1f, 4);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Inhaled", Vector2(738.f, 68.f), Vector2(25.f, 22.f), Vector2(25.f, 0.f), 0.05f, 4);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Inhaled", Vector2(237.f, 68.f), Vector2(25.f, 22.f), Vector2(-25.f, 0.f), 0.05f, 4);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Inhaled_Idle", Vector2(8.f, 218.f), Vector2(25.f, 22.f), Vector2(25.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Inhaled_Idle", Vector2(967.f, 218.f), Vector2(25.f, 22.f), Vector2(-25.f, 0.f), 1.f, 1);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Inhaled_Walk", Vector2(143.f, 216.f), Vector2(24.f, 24.f), Vector2(24.f, 0.f), 0.05f, 15);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Inhaled_Walk", Vector2(833.f, 216.f), Vector2(24.f, 24.f), Vector2(-24.f, 0.f), 0.05f, 15);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Inhaled_Run", Vector2(220.f, 278.f), Vector2(24.f, 24.f), Vector2(24.f, 0.f), 0.03f, 16);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Inhaled_Run", Vector2(756.f, 278.f), Vector2(24.f, 24.f), Vector2(-24.f, 0.f), 0.03f, 16);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Inhaled_Jump", Vector2(550.f, 217.f), Vector2(23.f, 23.f), Vector2(23.f, 0.f), 1.5f, 1);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Inhaled_Jump", Vector2(427.f, 217.f), Vector2(23.f, 23.f), Vector2(-23.f, 0.f), 1.5f, 1);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Inhaled_Turn", Vector2(574.f, 216.f), Vector2(24.f, 23.f), Vector2(24.f, 0.f), 0.05f, 3);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Inhaled_Turn", Vector2(402.f, 216.f), Vector2(24.f, 23.f), Vector2(-24.f, 0.f), 0.05f, 3);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Inhaled_Drop", Vector2(652.f, 217.f), Vector2(26.f, 23.f), Vector2(26.f, 0.f), 0.1f, 2);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Inhaled_Drop", Vector2(322.f, 217.f), Vector2(26.f, 23.f), Vector2(-26.f, 0.f), 0.1f, 2);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Inhaled_Land", Vector2(707.f, 222.f), Vector2(30.f, 18.f), Vector2(30.f, 0.f), 0.1f, 1);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Inhaled_Land", Vector2(263.f, 222.f), Vector2(30.f, 18.f), Vector2(-30.f, 0.f), 0.1f, 1);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Inhaled_Damage", Vector2(235.f, 177.f), Vector2(26.f, 24.f), Vector2(26.f, 0.f), 0.1f, 3);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Inhaled_Damage", Vector2(739.f, 177.f), Vector2(26.f, 24.f), Vector2(-26.f, 0.f), 0.1f, 3);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Inhaled_Down", Vector2(838.f, 68.f), Vector2(32.f, 22.f), Vector2(32.f, 0.f), 0.05f, 5);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Inhaled_Down", Vector2(130.f, 68.f), Vector2(32.f, 22.f), Vector2(-32.f, 0.f), 0.05f, 5);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Inhaled_Skill", Vector2(764.f, 305.f), Vector2(25.f, 22.f), Vector2(25.f, 0.f), 0.07f, 5);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Inhaled_Skill", Vector2(211.f, 305.f), Vector2(25.f, 22.f), Vector2(-25.f, 0.f), 0.07f, 5);

		mAnimator->SetAffectedCamera(true);
		mAnimator->PlayAnimation(L"DefaultKirby_Right_Idle", true);

		// Sound Load
		ResourceManager::Load<Sound>(L"BreathSound", L"..\\Resources\\Sound\\Effect\\Breath.wav");
		ResourceManager::Load<Sound>(L"DamageSound", L"..\\Resources\\Sound\\Effect\\Damage.wav");
		ResourceManager::Load<Sound>(L"FlySound", L"..\\Resources\\Sound\\Effect\\Fly.wav");
		ResourceManager::Load<Sound>(L"InhaleSkillSound", L"..\\Resources\\Sound\\Effect\\InhaleSkill.wav");
		ResourceManager::Load<Sound>(L"JumpSound", L"..\\Resources\\Sound\\Effect\\Jump.wav");
		ResourceManager::Load<Sound>(L"LandSound", L"..\\Resources\\Sound\\Effect\\Land.wav");
		ResourceManager::Load<Sound>(L"RunSound", L"..\\Resources\\Sound\\Effect\\Run.wav");
		ResourceManager::Load<Sound>(L"StarSpitSound", L"..\\Resources\\Sound\\Effect\\StarSpit.wav");
		ResourceManager::Load<Sound>(L"ClickSound", L"..\\Resources\\Sound\\Effect\\Click.wav");

		ResourceManager::Find<Sound>(L"BreathSound")->SetVolume(20.f);
		ResourceManager::Find<Sound>(L"JumpSound")->SetVolume(100.f);
		ResourceManager::Find<Sound>(L"FlySound")->SetVolume(100.f);
		ResourceManager::Find<Sound>(L"InhaleSkillSound")->SetVolume(80.f);
		ResourceManager::Find<Sound>(L"LandSound")->SetVolume(10.f);
		ResourceManager::Find<Sound>(L"RunSound")->SetVolume(100.f);
	}

	void IceKirby::Update()
	{
	}

	void IceKirby::Enter()
	{
	}

	void IceKirby::Exit()
	{
	}

	void IceKirby::OnCollisionEnter(Collider* other)
	{
	}

	void IceKirby::OnCollisionStay(Collider* other)
	{
	}

	void IceKirby::OnCollisionExit(Collider* other)
	{
	}

	void IceKirby::TakeHit(int DamageAmount, math::Vector2 HitDir)
	{
	}

	void IceKirby::CheckPixelCollision()
	{
	}

	void IceKirby::Choice()
	{

	}

	void IceKirby::Level_Enter()
	{
	}

	void IceKirby::Level_Idle()
	{
	}

	void IceKirby::Level_Run()
	{
	}

	void IceKirby::Level_FlyUp()
	{
	}

	void IceKirby::Level_Drop()
	{
	}

	void IceKirby::Idle()
	{
	}

	void IceKirby::Walk()
	{
	}

	void IceKirby::Run()
	{
	}

	void IceKirby::Skill()
	{
	}

	void IceKirby::Down()
	{
	}

	void IceKirby::Jump()
	{
	}

	void IceKirby::Turn()
	{
	}

	void IceKirby::Drop()
	{
	}

	void IceKirby::Fly_Start()
	{
	}

	void IceKirby::Fly_End()
	{
	}

	void IceKirby::Fly_Down()
	{
	}

	void IceKirby::Fly_Up()
	{
	}
}