#include "Engine/Systems/Graphics/Platform/DirectX12/DX12CommandAllocator.hpp"
#include "Engine/Logging/ConsoleLogger.hpp"

namespace nova
{
	DX12CommandAllocator::DX12CommandAllocator(ID3D12Device* device, const D3D12_COMMAND_LIST_TYPE command_list_type)
	{
		if (FAILED(device->CreateCommandAllocator(command_list_type, IID_PPV_ARGS(&command_allocator))))
			ConsoleLogger::logCritical(k_dx12_channel, "Unable to create command allocator!");
	}

	ID3D12CommandAllocator* DX12CommandAllocator::get() const noexcept
	{
		return command_allocator.Get();
	}
}
