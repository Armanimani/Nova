#pragma once

#include "Engine/Systems/Graphics/Platform/DirectX12/DX12Common.hpp"
#include "Engine/Systems/Graphics/Platform/DirectX12/DX12CommandAllocator.hpp"
#include "Engine/Systems/Graphics/Platform/DirectX12/DX12CommandList.hpp"
#include "Engine/Common/common.hpp"

namespace nova
{
	class NOVA_API DX12CommandListManager
	{
	public:
		DX12CommandListManager(ID3D12Device* device, D3D12_COMMAND_LIST_TYPE type, UInt32 number_allocators);

		void resetCommandList() noexcept;
		void closeCommandList() const noexcept;
		
		[[nodiscard]] UInt32 getNumberAllocators() const noexcept;
		[[nodiscard]] DX12CommandList* getCommandList() const noexcept;
	private:
		std::unique_ptr<DX12CommandList> graphic_command_list{};
		std::vector<std::unique_ptr<DX12CommandAllocator>> command_allocator_list{};

		UInt32 allocator_index{};
		UInt32 number_allocators{};

		void updateAllocatorIndex() noexcept;
		ID3D12CommandAllocator* getCommandAllocator() noexcept;
	};
}