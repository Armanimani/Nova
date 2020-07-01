#pragma once

#include "Engine/Common/common.hpp"

namespace nova
{
	class NOVA_API IGraphicContext
	{
	public:
		virtual ~IGraphicContext() = default;
		
		virtual void initialize() noexcept = 0;
		virtual void present() noexcept = 0;
		virtual void finalize() noexcept = 0;
	};
}
