#pragma once

#include "Engine/Systems/Graphics/Platform/DirectX12/DX12Common.hpp"
#include "Engine/Common/common.hpp"

namespace nova
{
	class NOVA_API DX12DXGIFactoryFactory
	{
	public:
		[[nodiscard]] static Microsoft::WRL::ComPtr<IDXGIFactory6> create() noexcept;
	};
}
