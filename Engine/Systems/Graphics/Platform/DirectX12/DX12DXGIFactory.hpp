#pragma once

#include "Engine/Systems/Graphics/Platform/DirectX12/DX12Common.hpp"
#include "Engine/Common/common.hpp"

namespace nova
{
	class NOVA_API DX12DXGIFactory
	{
	public:
		DX12DXGIFactory();
		
		[[nodiscard]] IDXGIFactory6* getNative() const noexcept;
	private:
		Microsoft::WRL::ComPtr<IDXGIFactory6> dxgi_factory{};
	};
}
