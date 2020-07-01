#include "Engine/Systems/Graphics/Platform/DirectX12/DX12Fence.hpp"
#include "Engine/Logging/ConsoleLogger.hpp"

namespace nova
{
	DX12Fence::DX12Fence(const Microsoft::WRL::ComPtr<ID3D12Device>& device, const D3D12_FENCE_FLAGS flags)
	{
		value = 0;
		if (FAILED(device->CreateFence(value, flags, IID_PPV_ARGS(&fence))))
			ConsoleLogger::logCritical(k_dx12_channel, "Unable to create fence!");

		handle = CreateEvent(nullptr, FALSE, FALSE, nullptr);

		if (!handle)
			ConsoleLogger::logCritical(k_dx12_channel, "Unable to create windows event for fence!");
	}

	void DX12Fence::wait() noexcept
	{
		if (!isSignaled())
		{
			if (FAILED(fence->SetEventOnCompletion(value, handle)))
			{
				ConsoleLogger::logCritical(k_dx12_channel, "Unable to set the event for fence");
			}

			WaitForSingleObject(handle, INFINITE);
		}

		value++;
	}

	ID3D12Fence1* DX12Fence::getNativeFence() const noexcept
	{
		return fence.Get();
	}

	Bool DX12Fence::isSignaled() const noexcept
	{
		return fence->GetCompletedValue() > value;
	}

	UInt64 DX12Fence::getNextValue() const noexcept
	{
		return value + 1;
	}

	UInt64 DX12Fence::getValue() const noexcept
	{
		return value;
	}
}
