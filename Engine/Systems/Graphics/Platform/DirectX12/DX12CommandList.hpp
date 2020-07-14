#pragma once

#include "Engine/Systems/Graphics/Platform/DirectX12/DX12Common.hpp"
#include "Engine/Systems/Graphics/Platform/DirectX12/DX12CommandAllocator.hpp"

namespace nova
{
	class DX12CommandList
	{
	public:
		DX12CommandList(ID3D12Device* device, DX12CommandAllocator* command_allocator, D3D12_COMMAND_LIST_TYPE command_list_type);

		[[nodiscard]] ID3D12GraphicsCommandList* getNative() const noexcept;
	private:
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> command_list{ nullptr };
	};
}
