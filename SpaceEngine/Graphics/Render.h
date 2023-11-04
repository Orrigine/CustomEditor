#pragma once

#include "Headers/SpaceEngine.h"
#include <memory.h>
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "Gdi32.lib")

using Microsoft::WRL::ComPtr;
using namespace DirectX;
using namespace DirectX::PackedVector;

struct Vertex
{
    XMFLOAT3 Pos;
    XMFLOAT4 Color;
};

struct ObjectConstants
{
    XMFLOAT4X4 WorldViewProj = MathHelper::Identity4x4();
};

namespace Render
{
    class Window : public D3DApp
    {

    public:
        Window(HINSTANCE hInstance);
        ~Window();

        virtual bool Initialize() override;

        static std::shared_ptr<Render::Window> GetInstance();
        // void CALLBACK CreateGameWindow(LPCWSTR, int, int);
        void InitializeVariables(/*std::wstring,*/ int, int);

    private:
        WNDCLASSEX _wcex;
        bool _windowShouldClose;
        int _windowWidth;
        int _windowHeight;

        virtual void OnResize() override;
        virtual void Update(const GameTimer &gt) override;
        virtual void Draw(const GameTimer &gt) override;

        void BuildDescriptorHeaps();
        /*reste ici*/ void BuildConstantBuffers();
        void BuildRootSignature();
        void BuildShadersAndInputLayout();
        void BuildGeometry();
        void BuildPSO();

        static std::shared_ptr<Render::Window> _instance;
        static LRESULT CALLBACK WindowProcess(HWND, UINT, WPARAM, LPARAM);
        int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT);

        static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
        static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
        LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

        // void CreateWindowClass();
        void MessageLoop();

    private:
        ComPtr<ID3D12RootSignature> mRootSignature = nullptr;
        ComPtr<ID3D12DescriptorHeap> mCbvHeap = nullptr;

        std::unique_ptr<UploadBuffer<ObjectConstants>> mObjectCB = nullptr;

        std::unique_ptr<MeshGeometry> mBoxGeometry = nullptr;

        ComPtr<ID3DBlob> mvsByteCode = nullptr;
        ComPtr<ID3DBlob> mpsByteCode = nullptr;

        std::vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;

        ComPtr<ID3D12PipelineState> mPSO = nullptr;

        XMFLOAT4X4 mWorld = MathHelper::Identity4x4();
        XMFLOAT4X4 mView = MathHelper::Identity4x4();
        XMFLOAT4X4 mProj = MathHelper::Identity4x4();

        float mTheta = 1.5f * XM_PI;
        float mPhi = XM_PIDIV4;
        float mRadius = 5.0f;

        POINT mLastMousePos;
    };

}