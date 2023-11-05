#pragma once

#include "Headers/SpaceEngine.h"
#include <memory.h>
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "Gdi32.lib")

using Microsoft::WRL::ComPtr;
using namespace DirectX;
using namespace DirectX::PackedVector;

class ShaderBase : public D3DApp
{
public:
    ShaderBase(/* args */);
    ~ShaderBase();

    void BuildDescriptorHeaps();
    void BuildRootSignature();
    void BuildShadersAndInputLayout();
    void BuildPSO();

    ComPtr<ID3D12DescriptorHeap> mCbvHeap = nullptr;
    ComPtr<ID3D12RootSignature> mRootSignature = nullptr;
    ComPtr<ID3D12PipelineState> mPSO = nullptr;

private:
    std::vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;

    ComPtr<ID3DBlob> mvsByteCode = nullptr;
    ComPtr<ID3DBlob> mpsByteCode = nullptr;
};
