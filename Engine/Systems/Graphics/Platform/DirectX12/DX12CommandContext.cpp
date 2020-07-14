#include "Engine/Systems/Graphics/Platform/DirectX12/DX12CommandContext.hpp"

namespace nova
{
	void DX12CommandContext::setSwapChain(DX12SwapChain* swap_chain) noexcept
	{
		this->swap_chain = swap_chain;
	}

	void DX12CommandContext::setDevice(DX12Device* device) noexcept
	{
		this->device = device;
	}

	void DX12CommandContext::setCurrentFrameIndex(const UInt32 current_frame_index)
	{
		this->current_frame_index = current_frame_index;
	}

	void DX12CommandContext::clearRenderTargetViewColor(const Float red, const Float green, const Float blue, const Float alpha) noexcept
	{
		const auto direct_command_list = device->getDirectCommandList();
		const auto handle = device->getRTVDescriptorHeap()->getCPUHandle(current_frame_index);

		const float color[] = { red, green, blue, alpha };
		direct_command_list->getNative()->ClearRenderTargetView(handle, color, 0, nullptr);
	}
}
