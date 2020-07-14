#pragma once

#include "Engine/Systems/Graphics/Platform/DirectX12/DX12Common.hpp"

namespace nova
{
	class DX12CommandAllocator
	{
	public:
		DX12CommandAllocator(ID3D12Device* device, D3D12_COMMAND_LIST_TYPE command_list_type);

		[[nodiscard]] ID3D12CommandAllocator* getNative() const noexcept;
	private:
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> command_allocator{ nullptr };
	};
}
