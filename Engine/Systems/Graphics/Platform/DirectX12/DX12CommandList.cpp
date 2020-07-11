#include "Engine/Systems/Graphics/Platform/DirectX12/DX12CommandList.hpp"
#include "Engine/Logging/ConsoleLogger.hpp"

namespace nova
{
	DX12CommandList::DX12CommandList(DX12Device* device, DX12CommandAllocator* command_allocator,
		const D3D12_COMMAND_LIST_TYPE command_list_type)
	{
		if (FAILED(device->get()->CreateCommandList(0, command_list_type, command_allocator->getNative(), nullptr, IID_PPV_ARGS(&command_list))))
			ConsoleLogger::logCritical(k_dx12_channel, "Unable to create the command list!");

		command_list->Close();
	}

	ID3D12GraphicsCommandList* DX12CommandList::getNative() const noexcept
	{
		return command_list.Get();
	}
}
