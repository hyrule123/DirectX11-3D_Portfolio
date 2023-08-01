#include "EnginePCH.h"

#include "Animation.h"
#include "TimeMgr.h"
#include "RenderMgr.h"

#include "ConstBuffer.h"

namespace mh
{



	Animation::Animation()
		: mAnimator(nullptr)
		, mAtlas(nullptr)
		, mSpriteSheet{}
		, mIndex(-1)
		, mTime(0.0f)
		, mbComplete(false)
	{

	}

	Animation::Animation(const Animation& _other)
		: Entity(_other)
		, mAnimator() //이건 이 애니메이션을 복사해서 가져가는 주인이 새로 설정해줘야함
		, mAnimationName(_other.mAnimationName)
		, mAtlas(_other.mAtlas) //Atlas == Texture -> 공유하는 리소스
		, mSpriteSheet(_other.mSpriteSheet) //vector도 value를 담고 있는 경우에는 그냥 복사하면 됨
		, mIndex(_other.mIndex)
		, mTime(_other.mTime)
		, mbComplete(_other.mbComplete)
	{
	}

	Animation::~Animation()
	{
	}

	UINT Animation::Update()
	{
		if (mbComplete)
			return -1;

		// 시간 체크
		mTime += TimeMgr::DeltaTime();

		// 누적 시간이 해당 프레임의 유지시간을 넘어서면 다음프레임으로 이동
		if (mSpriteSheet[mIndex].Duration < mTime)
		{
			mTime = 0.0f;
			++mIndex;
			if (mSpriteSheet.size() <= mIndex)
			{
				mbComplete = true;
				mIndex = static_cast<int>(mSpriteSheet.size()) - 1;
			}

			return mIndex;
		}

		return -1;
	}

	void Animation::FixedUpdate()
	{

	}

	void Animation::Render()
	{
	}

	void Animation::Create(const std::string_view _name
		, std::shared_ptr<Texture> _atlas
		, math::Vector2 _leftTop, math::Vector2 _size, math::Vector2 _offset
		, UINT _spriteLegth, float _duration)
	{
		mAnimationName = _name;

		mAtlas = _atlas;
		float width = static_cast<float>(_atlas->GetWidth());
		float height = static_cast<float>(_atlas->GetHeight());

		for (int index = 0; index < static_cast<int>(_spriteLegth); index++)
		{
			// API 와는 다르게 0~1 사이의 비율좌표로 위치를 표현해야한다.
			tSprite sprite = {};
			sprite.LeftTop = math::Vector2((_leftTop.x + (_size.x * static_cast<float>(index))) / width
				, (_leftTop.y) / height);
			sprite.Size = math::Vector2(_size.x / width, _size.y / height);
			sprite.Offset = _offset;
			sprite.Duration = _duration;
			sprite.AtlasSize = math::Vector2(200.0f / width, 200.0f / height);

			mSpriteSheet.push_back(sprite);
		}

	}

	void Animation::BindShader()
	{
		mAtlas->BindDataSRV(12u, eShaderStageFlag::PS);

		ConstBuffer* cb = RenderMgr::GetConstBuffer(eCBType::Animation);

		AnimationCB info = {};
		info.Type = (UINT)define::eAnimationType::SecondDimension;
		info.LeftTop = mSpriteSheet[mIndex].LeftTop;
		info.Offset = mSpriteSheet[mIndex].Offset;
		info.Size = mSpriteSheet[mIndex].Size;
		info.AtlasSize = mSpriteSheet[mIndex].AtlasSize;

		cb->SetData(&info);
		cb->BindData(eShaderStageFlag::PS);
	}

	void Animation::Reset()
	{
		mTime = 0.0f;
		mIndex = 0;
		mbComplete = false;
	}

	void Animation::Clear()
	{
		//Texture clear
		Texture::Clear(12);

		ConstBuffer* cb = RenderMgr::GetConstBuffer(eCBType::Animation);

		AnimationCB info = {};
		info.Type = (UINT)define::eAnimationType::None;

		cb->SetData(&info);
		cb->BindData(eShaderStageFlag::PS);
	}

}