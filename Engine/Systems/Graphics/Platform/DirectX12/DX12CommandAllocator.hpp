#pragma once

#include "Engine/Systems/Graphics/Platform/DirectX12/DX12Device.hpp"

namespace nova
{
	class DX12CommandAllocator
	{
	public:
		DX12CommandAllocator(DX12Device* device, D3D12_COMMAND_LIST_TYPE command_list_type);

		[[nodiscard]] ID3D12CommandAllocator* get() const noexcept;
	private:
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> command_allocator{ nullptr };
	};
}
