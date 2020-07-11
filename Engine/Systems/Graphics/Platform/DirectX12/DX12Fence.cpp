#include "Engine/Systems/Graphics/Platform/DirectX12/DX12Fence.hpp"
#include "Engine/Logging/ConsoleLogger.hpp"

namespace nova
{
	DX12Fence::DX12Fence(const Microsoft::WRL::ComPtr<ID3D12Device>& device, const UInt64 initial_value, const D3D12_FENCE_FLAGS flags)
		: value{ initial_value }
	{
		if (FAILED(device->CreateFence(value, flags, IID_PPV_ARGS(&fence))))
			ConsoleLogger::logCritical(k_dx12_channel, "Unable to create fence!");
	}

	DX12Fence::~DX12Fence()
	{
		if (handle_complete_event != INVALID_HANDLE_VALUE)
		{
			CloseHandle(handle_complete_event);
			handle_complete_event = INVALID_HANDLE_VALUE;
		}
	}

	void DX12Fence::wait() noexcept
	{
		if (!isSignaled())
		{
			initializeCompleteHandleEvent();
			
			if (FAILED(fence->SetEventOnCompletion(value, handle_complete_event)))
			{
				ConsoleLogger::logCritical(k_dx12_channel, "Unable to set the event for fence");
			}

			WaitForSingleObject(handle_complete_event, INFINITE);
		}

		value++;
	}

	ID3D12Fence1* DX12Fence::getNative() const noexcept
	{
		return fence.Get();
	}

	UINT64 DX12Fence::getValue() const noexcept
	{
		return value;
	}

	Bool DX12Fence::isSignaled() const noexcept
	{
		return fence->GetCompletedValue() > value;
	}

	void DX12Fence::initializeCompleteHandleEvent() noexcept
	{
		handle_complete_event = CreateEvent(nullptr, FALSE, FALSE, nullptr);

		if (!handle_complete_event)
			ConsoleLogger::logCritical(k_dx12_channel, "Unable to create windows event for fence!");
	}
}
