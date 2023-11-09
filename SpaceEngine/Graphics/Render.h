#pragma once

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "Gdi32.lib")

#include <memory.h>

#include "Headers/SpaceEngine.h"
#include "Common/Headers/GeometryGenerator.h"
#include "Common/Headers/Camera.h"

struct ObjectConstants
{
    DirectX::XMFLOAT4X4 World = MathHelper::Identity4x4();
};

struct PassConstants
{
    DirectX::XMFLOAT4X4 View = MathHelper::Identity4x4();
    DirectX::XMFLOAT4X4 InvView = MathHelper::Identity4x4();
    DirectX::XMFLOAT4X4 Proj = MathHelper::Identity4x4();
    DirectX::XMFLOAT4X4 InvProj = MathHelper::Identity4x4();
    DirectX::XMFLOAT4X4 ViewProj = MathHelper::Identity4x4();
    DirectX::XMFLOAT4X4 InvViewProj = MathHelper::Identity4x4();
    DirectX::XMFLOAT3 EyePosW = { 0.0f, 0.0f, 0.0f };
    float cbPerObjectPad1 = 0.0f;
    DirectX::XMFLOAT2 RenderTargetSize = { 0.0f, 0.0f };
    DirectX::XMFLOAT2 InvRenderTargetSize = { 0.0f, 0.0f };
    float NearZ = 0.0f;
    float FarZ = 0.0f;
    float TotalTime = 0.0f;
    float DeltaTime = 0.0f;
};

struct Vertex
{
    DirectX::XMFLOAT3 Pos;
    DirectX::XMFLOAT4 Color;
};

struct GameObject {
    std::string type;
    const float* color;
    float p_x;
    float p_y;
    float p_z;
    float scale_x;
    float scale_y;
    float scale_z;
    bool is_build;
};

// Lightweight structure stores parameters to draw a shape
struct RenderItem
{   
    /* The set of data needed to submit a full draw call the rendering pipeline
    is a render item */
    RenderItem() = default;
    // World matrix of the shape that describes the object�s local space
    // relative to the world space, which defines the position,
    // orientation, and scale of the object in the world.
    DirectX::XMFLOAT4X4 World = MathHelper::Identity4x4();

    MeshGeometry* Geo = nullptr;
    // Primitive topology.
    D3D12_PRIMITIVE_TOPOLOGY PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
   
    // DrawIndexedInstanced parameters.
    UINT IndexCount = 0;
    UINT StartIndexLocation = 0;
    int BaseVertexLocation = 0;

    std::unique_ptr<UploadBuffer<ObjectConstants>> ObjectCB = nullptr;
};

namespace Render
{
    class Window : public D3DApp
    {
    public:
        Window(HINSTANCE hInstance);
        ~Window();

        virtual bool Initialize() override;

        void setWidth(int );
        void setHeight(int );
        void setWindowName(std::wstring );

        static std::shared_ptr<Render::Window> GetInstance();
        void CALLBACK CreateGameWindow(LPCWSTR, int, int);
        void InitializeVariables(/*std::wstring,*/ int, int);

        void setEngine(void *engine);
        void* getEngine();
        float getTotalTime();

    private:
        static std::shared_ptr<Render::Window> _instance;
        static LRESULT CALLBACK WindowProcess(HWND, UINT, WPARAM, LPARAM);
        int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT);
        void CreateWindowClass();
        void MessageLoop();

        virtual void OnResize()override;
        virtual void Update(const GameTimer& gt)override;
        virtual void Draw(const GameTimer& gt)override;

        virtual void OnMouseDown(WPARAM btnState, int x, int y)override;
        virtual void OnMouseUp(WPARAM btnState, int x, int y)override;
        virtual void OnMouseMove(WPARAM btnState, int x, int y)override;

        void OnKeyboardInput(const GameTimer& gt);
        void UpdateCamera(const GameTimer& gt);

        void BuildRootSignature();
        void BuildShadersAndInputLayout();

        void BuildFrameResources();
        void UpdateObjectCBs(const GameTimer& gt);
        void UpdateMainPassCB(const GameTimer& gt);

        void BuildPSOs();
    public:
        void createEntity(int id);
        void setMesh(int id, std::string submesh);
        void setTransform(int, float p_x, float p_y, float p_z,
            float scale_x, float scale_y, float scale_z);
      //  void createGameObject(std::string type, const float* color, float p_x, float p_y, float p_z,
        //    float scale_x, float scale_y, float scale_z);
    private:
       // void createShape(std::string submesh, float p_x, float p_y, float p_z,
         //   float scale_x, float scale_y, float scale_z);
        //void buildShape(float p_x, float p_y, float p_z,
          //  float scale_x, float scale_y, float scale_z, const float* color);
        void buildBox(std::string name, const float* color);
        void buildSphere(std::string name, const float* color);
        //void buildGameObjects();

        void buildGPUBuffers();

        void DrawRenderItems(ID3D12GraphicsCommandList* cmdList,
            const std::vector<RenderItem*>& ritems);

    private:
        WNDCLASSEX _wcex;
        bool _windowShouldClose;
        int _windowWidth;
        int _windowHeight;

        UINT _objCBIndex;
        UINT _shapesIndices;
        UINT _lastGeoVertexOffset;
        UINT _lastGeoVerticesSize;
        UINT _lastGeoIndexOffset;
        UINT _lastGeoIndicesSize;
        GeometryGenerator _geoGen;

        std::vector<Vertex> _vertices;
        std::vector<std::uint16_t> _indices;

        Microsoft::WRL::ComPtr<ID3D12RootSignature> _rootSignature = nullptr;

        std::vector<D3D12_INPUT_ELEMENT_DESC> _inputLayout;

        // List of all the render items.
        std::vector<std::shared_ptr<RenderItem>> _allRenderItems;
        std::unordered_map<int, std::shared_ptr<RenderItem>> _renderItems;

        // Render items divided by PSO.
        std::vector<RenderItem*> _opaqueRenderItems;
        std::vector<RenderItem*> _transparentRenderItems;

        PassConstants _mainPassCB;

        UINT _passCbvOffset = 0;

        bool _isWireframe = false;

       // DirectX::XMFLOAT3 _eyePos = { 0.0f, 0.0f, 0.0f };
        //DirectX::XMFLOAT4X4 _view = MathHelper::Identity4x4();
        //DirectX::XMFLOAT4X4 _proj = MathHelper::Identity4x4();

        std::unordered_map<std::string, std::unique_ptr<MeshGeometry>>
            _geometries;
        std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3DBlob>> _shaders;
        Microsoft::WRL::ComPtr<ID3D12PipelineState> _pso;
        POINT mLastMousePos;

        //float mTheta = 1.5f * DirectX::XM_PI;
        //float mPhi = 0.2f * DirectX::XM_PI;
        //float mRadius = 15.0f;

        Camera _camera;

        std::vector<std::shared_ptr<GameObject>> _gameObjects;
        Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cmdListAlloc;
        std::unique_ptr<UploadBuffer<PassConstants>> passCB = nullptr;

        void* _engine;
        float _elapsedTime;
    };


}