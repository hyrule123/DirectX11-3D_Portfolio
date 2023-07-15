#pragma once
#include "ComputeShader.h"
#include "Texture.h"

namespace mh::graphics
{
	class PaintShader : public ComputeShader
	{
	public:
		PaintShader();
		~PaintShader();

		virtual void Binds() override;
		virtual void Clear() override;
		
		void SetTarget(std::shared_ptr<Texture> _texture) { mTarget = _texture; }

	private:
		std::shared_ptr<Texture> mTarget;
	};
}
