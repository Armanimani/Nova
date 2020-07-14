#include "Engine/Systems/Graphics/Platform/DirectX12/DX12CommandListManager.hpp"
#include "Engine/Logging/ConsoleLogger.hpp"

namespace nova
{
	DX12CommandListManager::DX12CommandListManager(ID3D12Device* device, 
		const D3D12_COMMAND_LIST_TYPE type, const UInt32 number_allocators)
		: number_allocators{ number_allocators }
	{
		for (UInt32 i = 0; i != number_allocators; ++i)
			command_allocator_list.push_back(std::make_unique<DX12CommandAllocator>(device, type));

		graphic_command_list = std::make_unique<DX12CommandList>(device, command_allocator_list[0].get(), type);
	}

	void DX12CommandListManager::resetCommandList() noexcept
	{
		updateAllocatorIndex();
		
		auto allocator = getCommandAllocator();
		if (FAILED(allocator->Reset()))
			ConsoleLogger::logCritical(k_dx12_channel, "Unable to reset the command allocator");

		if (FAILED(graphic_command_list->getNative()->Reset(allocator, NULL)))
			ConsoleLogger::logCritical(k_dx12_channel, "Unable to reset the command list");
	}

	void DX12CommandListManager::closeCommandList() const noexcept
	{
		if (FAILED(graphic_command_list->getNative()->Close()))
			ConsoleLogger::logCritical(k_dx12_channel, "Unable to close the command list");
	}

	UInt32 DX12CommandListManager::getNumberAllocators() const noexcept
	{
		return number_allocators;
	}
	
	DX12CommandList* DX12CommandListManager::getCommandList() const noexcept
	{
		return graphic_command_list.get();
	}

	void DX12CommandListManager::updateAllocatorIndex() noexcept
	{
		allocator_index++;
		allocator_index = allocator_index % number_allocators;
	}
	ID3D12CommandAllocator* DX12CommandListManager::getCommandAllocator() noexcept
	{
		return command_allocator_list[allocator_index]->getNative();
	}
}
