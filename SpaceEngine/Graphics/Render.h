#pragma once

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "Gdi32.lib")

#include <memory.h>

#include "FrameResource.h"
#include "Headers/SpaceEngine.h"
#include "Common/Headers/GeometryGenerator.h"

//using namespace DirectX::PackedVector;

struct GameObject {
    std::string type;
    const float* color;
    float p_x;
    float p_y;
    float p_z;
    float scale_x;
    float scale_y;
    float scale_z;
};

struct RenderItem
{   // Lightweight structure stores parameters to draw a shape
    /* The set of data needed to submit a full draw call the rendering pipeline
    is a render item */
    RenderItem() = default;
    // World matrix of the shape that describes the object’s local space
    // relative to the world space, which defines the position,
    // orientation, and scale of the object in the world.
    DirectX::XMFLOAT4X4 World = MathHelper::Identity4x4();
    // Dirty flag indicating the object data has changed and we need
    // to update the constant buffer. Because we have an object
    // cbuffer for each FrameResource, we have to apply the
    // update to each FrameResource. Thus, when we modify obect data we
    // should set
    // NumFramesDirty = gNumFrameResources so that each frame resource
    // gets the update.
    int NumFramesDirty = gNumFrameResources;
    // Index into GPU constant buffer corresponding to the ObjectCB
    // for this render item.
    UINT ObjCBIndex = -1;
    // Geometry associated with this render-item. Note that multiple
    // render-items can share the same geometry.
    MeshGeometry* Geo = nullptr;
    // Primitive topology.
    D3D12_PRIMITIVE_TOPOLOGY PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    // DrawIndexedInstanced parameters.
    UINT IndexCount = 0;
    UINT StartIndexLocation = 0;
    int BaseVertexLocation = 0;
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
        void CALLBACK CreateGameWindow(LPCWSTR, int, int);
        void InitializeVariables(/*std::wstring,*/ int, int);

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
        void createGameObject(std::string type, const float* color, float p_x, float p_y, float p_z,
            float scale_x, float scale_y, float scale_z);
    private:
        void createShape(std::string submesh, float p_x, float p_y, float p_z,
            float scale_x, float scale_y, float scale_z);
        //void buildShape(float p_x, float p_y, float p_z,
          //  float scale_x, float scale_y, float scale_z, const float* color);
        void buildBox(std::string name, const float* color);
        void buildSphere(std::string name, const float* color);
        void buildGameObjects();

        void buildGPUBuffers();

        void BuildDescriptorHeaps();
        void BuildConstantBufferViews();
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

        //std::unordered_map<std::string, GeometryGenerator::MeshData (GeometryGenerator::*) (float width, float height, float depth, GeometryGenerator::uint32 numSubdivisions)> _geometriesMap;

        std::vector<Vertex> _vertices;
        std::vector<std::uint16_t> _indices;

        Microsoft::WRL::ComPtr<ID3D12RootSignature> _rootSignature = nullptr;
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> _cbvHeap = nullptr;

        //std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3DBlob>> _shaders;
        std::vector<D3D12_INPUT_ELEMENT_DESC> _inputLayout;

        // List of all the render items.
        std::vector<std::unique_ptr<RenderItem>> _allRenderItems;

        // Render items divided by PSO.
        std::vector<RenderItem*> _opaqueRenderItems;
        std::vector<RenderItem*> _transparentRenderItems;

        PassConstants _mainPassCB;

        UINT _passCbvOffset = 0;

        bool _isWireframe = false;

        DirectX::XMFLOAT3 _eyePos = { 0.0f, 0.0f, 0.0f };
        DirectX::XMFLOAT4X4 _view = MathHelper::Identity4x4();
        DirectX::XMFLOAT4X4 _proj = MathHelper::Identity4x4();

        std::unordered_map<std::string, std::unique_ptr<MeshGeometry>>
            _geometries;
        std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3DBlob>> _shaders;
        std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D12PipelineState>> _psos;

        POINT mLastMousePos;

        float mTheta = 1.5f * DirectX::XM_PI;
        float mPhi = 0.2f * DirectX::XM_PI;
        float mRadius = 15.0f;

        std::vector<std::shared_ptr<GameObject>> _gameObjects;


        Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cmdListAlloc;

        // We cannot update a cbuffer until the GPU is done processing the
        // commands that reference it. So each frame needs their own cbuffers.
        std::unique_ptr<UploadBuffer<PassConstants>> PassCB = nullptr;
        std::unique_ptr<UploadBuffer<ObjectConstants>> ObjectCB = nullptr;
    };

}