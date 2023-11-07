#include "FrameResource.h"

FrameResources::FrameResources(ID3D12Device* device, UINT passCount, UINT
	objectCount, UINT materialCount)
{
	ThrowIfFailed(device->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(CmdListAlloc.GetAddressOf())));
	/* per pass constants only need to be updated once per rendering pass */
	PassCB = std::make_unique<UploadBuffer<PassConstants>>(device,
		passCount, true);
	/*  the object constants only need to change when an object’s world matrix
	 changes */
	ObjectCB = std::make_unique<UploadBuffer<ObjectConstants>>(device,
		objectCount, true);
	MaterialCB = std::make_unique<UploadBuffer<MaterialConstants>>(device, materialCount, true);
}

FrameResources::~FrameResources()
{
}