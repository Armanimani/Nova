#pragma once

#include "Engine/Systems/Graphics/Platform/DirectX12/DX12Common.hpp"
#include "Engine/Common/common.hpp"

namespace nova
{
	class NOVA_API DX12Fence
	{
	public:
		DX12Fence(const Microsoft::WRL::ComPtr<ID3D12Device>& device, UInt64 initial_value,  D3D12_FENCE_FLAGS flags);
		~DX12Fence();

		DX12Fence(const DX12Fence& other) = delete;
		DX12Fence(DX12Fence&& other) noexcept = delete;
		DX12Fence& operator=(const DX12Fence& other) = delete;
		DX12Fence& operator=(DX12Fence&& other) noexcept = delete;
		
		void wait() noexcept;
		
		[[nodiscard]] Bool isSignaled() const noexcept;
		[[nodiscard]] ID3D12Fence1* getNative() const noexcept;
		[[nodiscard]] UINT64 getValue() const noexcept;
	private:
		Microsoft::WRL::ComPtr<ID3D12Fence1> fence{};
		
		HANDLE handle_complete_event{ INVALID_HANDLE_VALUE };
		UInt64 value{};

		void initializeCompleteHandleEvent() noexcept;
	};
}