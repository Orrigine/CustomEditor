#include <Graphics.h>
#include "Engine.h"
//#include "Engine/System/ISystem.h"

int const gNumFrameResources = 1;


WCHAR WindowClass[MAX_NAME_STRING] = L"SpaceEngineWindowClass";
std::shared_ptr<Render::Window> Render::Window::_instance = nullptr;

Render::Window::Window(HINSTANCE hInstance) : D3DApp(hInstance),
_shapesIndices(1), _lastGeoIndexOffset(0), _lastGeoIndicesSize(0),
_lastGeoVertexOffset(0), _lastGeoVerticesSize(0), _objCBIndex(0), _engine(nullptr)
{
    auto geo = std::make_unique<MeshGeometry>();

    geo->Name = "shapeGeo";
    _geometries[geo->Name] = std::move(geo);
    _wcex = {};
    _instance = nullptr;
}

Render::Window::~Window()
{
}

LRESULT CALLBACK Render::Window::WindowProcess(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void Render::Window::InitializeVariables(/*std::wstring name,*/ int width, int height)
{

    D3DApp::mClientWidth = width;
    D3DApp::mClientHeight = height;
    // D3DApp::mMainWindowName = name;
}

void Render::Window::CreateWindowClass()
{
    _wcex.cbSize = sizeof(WNDCLASSEX);
    _wcex.style = CS_HREDRAW | CS_VREDRAW; // Redraw on horizontal or vertical movement/adjustment
    _wcex.cbClsExtra = 0;
    _wcex.cbWndExtra = 0;

    _wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);           // Load the arrow cursor
    _wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH); // Set the background color to white

    _wcex.lpszClassName = WindowClass;
    _wcex.lpszMenuName = nullptr;

    _wcex.hInstance = HInstance();
    _wcex.lpfnWndProc = WindowProcess;

    RegisterClassEx(&_wcex);
}

bool Render::Window::Initialize()
{
    if (!D3DApp::Initialize())
        return false;
    ThrowIfFailed(mCommandList->Reset(mDirectCmdListAlloc.Get(), nullptr));
    _camera.SetPosition(0.0f, 0.0f, -30.0f);
    BuildRootSignature();
    BuildShadersAndInputLayout();
    buildBox("box", DirectX::Colors::AliceBlue);
    buildSphere("sphere", DirectX::Colors::BurlyWood);
    buildGPUBuffers();
    BuildFrameResources();
    BuildPSOs();
    ThrowIfFailed(mCommandList->Close());
    ID3D12CommandList* cmdsLists[] = { mCommandList.Get() };
    mCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);
    FlushCommandQueue();
    return true;
}

void Render::Window::setWidth(int width)
{
    mClientWidth = width;
}

void Render::Window::setHeight(int height)
{
    mClientHeight = height;
}

void Render::Window::setWindowName(std::wstring name)
{
    mMainWindowName = name;
}

void Render::Window::BuildRootSignature()
{
    CD3DX12_ROOT_PARAMETER slotRootParameter[2];
    slotRootParameter[0].InitAsConstantBufferView(0);
    slotRootParameter[1].InitAsConstantBufferView(1);
    CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc(2, slotRootParameter, 0, nullptr,
        D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

    Microsoft::WRL::ComPtr<ID3DBlob> serializedRootSig = nullptr;
    Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;
    HRESULT hr = D3D12SerializeRootSignature(&rootSigDesc,
        D3D_ROOT_SIGNATURE_VERSION_1, serializedRootSig.GetAddressOf(),
        errorBlob.GetAddressOf());
    if (errorBlob != nullptr)
        ::OutputDebugStringA((char*)errorBlob->GetBufferPointer());
    ThrowIfFailed(hr);
    ThrowIfFailed(md3dDevice->CreateRootSignature(0,
        serializedRootSig->GetBufferPointer(), serializedRootSig->GetBufferSize(),
        IID_PPV_ARGS(_rootSignature.GetAddressOf())));
}

void Render::Window::BuildShadersAndInputLayout()
{
    /*    ####      BUILD VERTEX AND PIXEL SHADERS   ####    */
    _shaders["standardVS"] = d3dUtil::CompileShader(L"Shaders\\color.hlsl", nullptr, "VS", "vs_5_1");
    _shaders["opaquePS"] = d3dUtil::CompileShader(L"Shaders\\color.hlsl", nullptr, "PS", "ps_5_1");

    /*    ####  DEFINE THE VERTEX INPUT LAYOUT   ####    */
    /* An imput layout contain the description of each element
        in a vertex structure */
    _inputLayout = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
        D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
        D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }, };
}

void Render::Window::buildBox(std::string name, const float* color)
{
    GeometryGenerator::MeshData newGeo = _geoGen.CreateBox(1.0f, 1.0f,
        1.0f, 3);
    UINT newGeoVertexOffset = _lastGeoVertexOffset + _lastGeoVerticesSize;
    _lastGeoVertexOffset = newGeoVertexOffset;
    _lastGeoVerticesSize = newGeo.Vertices.size();
    UINT newGeoIndexOffset = _lastGeoIndexOffset + _lastGeoIndicesSize;
    _lastGeoIndexOffset = newGeoIndexOffset;
    _lastGeoIndicesSize = (UINT)newGeo.Indices32.size();
    SubmeshGeometry newGeoSubmesh;
    newGeoSubmesh.IndexCount = (UINT)newGeo.Indices32.size();
    newGeoSubmesh.StartIndexLocation = newGeoIndexOffset;
    newGeoSubmesh.BaseVertexLocation = newGeoVertexOffset;
    UINT k = _vertices.size();
    /* Copies each geometry vertex into a big one */
    _vertices.resize(_vertices.size() + newGeo.Vertices.size());
    for (size_t i = 0; i < newGeo.Vertices.size(); i++, k++) {
        _vertices[k].Pos = newGeo.Vertices[i].Position;
        _vertices[k].Color = DirectX::XMFLOAT4(color);
    }
    /* Copies each geometry indices into a big one*/
    _indices.insert(_indices.end(),
        std::begin(newGeo.GetIndices16()),
        std::end(newGeo.GetIndices16()));
    // create vertices and indices upload buffer
    _geometries["shapeGeo"]->DrawArgs[name] = newGeoSubmesh;
    // createShape(std::to_string(_shapesIndices), p_x, p_y, p_z, scale_x, scale_y, scale_z);
    _shapesIndices++;
}


void Render::Window::buildSphere(std::string name, const float* color)
{
    GeometryGenerator::MeshData newGeo = _geoGen.CreateSphere(1.0f, 20, 20);
    UINT newGeoVertexOffset = _lastGeoVertexOffset + _lastGeoVerticesSize;
    _lastGeoVertexOffset = newGeoVertexOffset;
    _lastGeoVerticesSize = newGeo.Vertices.size();
    UINT newGeoIndexOffset = _lastGeoIndexOffset + _lastGeoIndicesSize;
    _lastGeoIndexOffset = newGeoIndexOffset;
    _lastGeoIndicesSize = (UINT)newGeo.Indices32.size();
    SubmeshGeometry newGeoSubmesh;
    newGeoSubmesh.IndexCount = (UINT)newGeo.Indices32.size();
    newGeoSubmesh.StartIndexLocation = newGeoIndexOffset;
    newGeoSubmesh.BaseVertexLocation = newGeoVertexOffset;
    UINT k = _vertices.size();
    _vertices.resize(_vertices.size() + newGeo.Vertices.size());
    for (size_t i = 0; i < newGeo.Vertices.size(); i++, k++) {
        _vertices[k].Pos = newGeo.Vertices[i].Position;
        _vertices[k].Color = DirectX::XMFLOAT4(color);
    }
    _indices.insert(_indices.end(),
        std::begin(newGeo.GetIndices16()),
        std::end(newGeo.GetIndices16()));
    _geometries["shapeGeo"]->DrawArgs[name] = newGeoSubmesh;
}

void Render::Window::createEntity(int id)
{
    std::unique_ptr<RenderItem> newRenderItem(new RenderItem());
    DirectX::XMMATRIX world =
        DirectX::XMMatrixTranslation(0, 0, 0)
        * DirectX::XMMatrixScaling(1, 1, 1);
    DirectX::XMStoreFloat4x4(&newRenderItem->World, world);
    _renderItems[id] = std::move( newRenderItem );
}

void Render::Window::setTransform(int id, float p_x, float p_y, float p_z,
    float scale_x, float scale_y, float scale_z, float r_x, float r_y, float r_z)
{
    auto newRenderItem = _renderItems[id];
    DirectX::XMMATRIX world =
        DirectX::XMMatrixTranslation(p_x, p_y, p_z) * DirectX::XMMatrixRotationY(r_y)
        * DirectX::XMMatrixScaling(scale_x, scale_y, scale_z);
    DirectX::XMStoreFloat4x4(&newRenderItem->World, world);
}

void Render::Window::setMesh(int id, std::string submesh)
{
    auto newRenderItem = _renderItems[id];
    newRenderItem->ObjectCB = std::make_unique<UploadBuffer<ObjectConstants>>((md3dDevice.Get()), 1, true);
    newRenderItem->Geo = _geometries["shapeGeo"].get();
    newRenderItem->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    newRenderItem->IndexCount = newRenderItem->Geo->DrawArgs[submesh].
        IndexCount;
    newRenderItem->StartIndexLocation =
        newRenderItem->Geo->DrawArgs[submesh].StartIndexLocation;
    newRenderItem->BaseVertexLocation =
        newRenderItem->Geo->DrawArgs[submesh].BaseVertexLocation;
    _opaqueRenderItems.push_back(newRenderItem.get());
    _allRenderItems.push_back(newRenderItem);
}

void Render::Window::buildGPUBuffers()
{
    const UINT vbByteSize = (UINT)_vertices.size() * sizeof(Vertex);
    const UINT ibByteSize = (UINT)_indices.size() * sizeof(std::uint16_t);
    ThrowIfFailed(D3DCreateBlob(vbByteSize, &_geometries["shapeGeo"]->VertexBufferCPU));
    CopyMemory(_geometries["shapeGeo"]->VertexBufferCPU->GetBufferPointer(),
        _vertices.data(), vbByteSize);
    ThrowIfFailed(D3DCreateBlob(ibByteSize, &_geometries["shapeGeo"]->IndexBufferCPU));
    CopyMemory(_geometries["shapeGeo"]->IndexBufferCPU->GetBufferPointer(), _indices.data(),
        ibByteSize);
    _geometries["shapeGeo"]->VertexBufferGPU = d3dUtil::CreateDefaultBuffer(md3dDevice.Get(),
        mCommandList.Get(), _vertices.data(), vbByteSize, _geometries["shapeGeo"]->VertexBufferUploader);
    _geometries["shapeGeo"]->IndexBufferGPU = d3dUtil::CreateDefaultBuffer(md3dDevice.Get(),
        mCommandList.Get(), _indices.data(), ibByteSize, _geometries["shapeGeo"]->IndexBufferUploader);

    _geometries["shapeGeo"]->VertexByteStride = sizeof(Vertex);
    _geometries["shapeGeo"]->VertexBufferByteSize = vbByteSize;
    _geometries["shapeGeo"]->IndexFormat = DXGI_FORMAT_R16_UINT;
    _geometries["shapeGeo"]->IndexBufferByteSize = ibByteSize;
}

void Render::Window::BuildFrameResources()
{
    ThrowIfFailed((md3dDevice.Get())->CreateCommandAllocator(
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        IID_PPV_ARGS(cmdListAlloc.GetAddressOf())));
    passCB = std::make_unique<UploadBuffer<PassConstants>>((md3dDevice.Get()),
        1, true);
}

void Render::Window::BuildPSOs()
{
    D3D12_GRAPHICS_PIPELINE_STATE_DESC opaquePsoDesc;
    ZeroMemory(&opaquePsoDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
    opaquePsoDesc.InputLayout = { _inputLayout.data(), (UINT)_inputLayout.size() };
    opaquePsoDesc.pRootSignature = _rootSignature.Get();
    opaquePsoDesc.VS = {
        reinterpret_cast<BYTE*>(_shaders["standardVS"]->GetBufferPointer()),
        _shaders["standardVS"]->GetBufferSize() };
    opaquePsoDesc.PS = {
        reinterpret_cast<BYTE*>(_shaders["opaquePS"]->GetBufferPointer()),
        _shaders["opaquePS"]->GetBufferSize() };
    opaquePsoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
    opaquePsoDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
    opaquePsoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
    opaquePsoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
    opaquePsoDesc.SampleMask = UINT_MAX;
    opaquePsoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    opaquePsoDesc.NumRenderTargets = 1;
    opaquePsoDesc.RTVFormats[0] = mBackBufferFormat;
    opaquePsoDesc.SampleDesc.Count = m4xMsaaState ? 4 : 1;
    opaquePsoDesc.SampleDesc.Quality = m4xMsaaState ? (m4xMsaaQuality - 1) : 0;
    opaquePsoDesc.DSVFormat = mDepthStencilFormat;
    ThrowIfFailed(md3dDevice->CreateGraphicsPipelineState(
        &opaquePsoDesc, IID_PPV_ARGS(&_pso)));
}

void Render::Window::setEngine(void* engine)
{
    _engine = engine;
}

void *Render::Window::getEngine()
{
    return _engine;
}

float Render::Window::getTotalTime()
{
    return _elapsedTime;
}

float Render::Window::getDeltaTime()
{
    return _deltaTime;
}

void Render::Window::Update(const GameTimer& gt)
{
    _elapsedTime = gt.TotalTime();
    _deltaTime  = gt.DeltaTime();

    //DirectX::XMMATRIX skullScale = DirectX::XMMatrixScaling(0.2f, 0.2f, 0.2f);
   /* DirectX::XMMATRIX skullOffset = DirectX::XMMatrixTranslation(3.0f, 2.0f, 0.0f);
    DirectX::XMMATRIX skullLocalRotate = DirectX::XMMatrixRotationY(2.0f * gt.TotalTime());

    DirectX::XMMATRIX skullGlobalRotate = DirectX::XMMatrixRotationY(0.5f * gt.TotalTime());
    if (_opaqueRenderItems.size() >= 3)
        DirectX::XMStoreFloat4x4(&_opaqueRenderItems[2]->World, /*skullScale / skullLocalRotate * skullOffset * skullGlobalRotate);*/

    SpaceEngine::Engine* engine = (SpaceEngine::Engine*) _engine;
    std::vector<std::shared_ptr<SpaceEngine::ISystem>> systems = engine->getSystems();
    OnKeyboardInput(gt);

    for (int i = 0; i < systems.size(); i++) {
        systems[i]->init(&engine->getEntities(), engine->getRenderApplication());
        systems[i]->update(&engine->getEntities(), engine->getRenderApplication());
    }

    UpdateObjectCBs(gt);
    UpdateMainPassCB(gt);
}

void Render::Window::UpdateObjectCBs(const GameTimer& gt)
{
    for (auto& e : _allRenderItems) {
        // Only update the cbuffer data if the constants have changed.
        // This needs to be tracked per frame resource.
        auto currObjectCB = e->ObjectCB.get();
        // get the word matrix of each drawable obj
        DirectX::XMMATRIX world = XMLoadFloat4x4(&e->World);
        ObjectConstants objConstants;
        XMStoreFloat4x4(&objConstants.World, XMMatrixTranspose(world));
        currObjectCB->CopyData(0 , objConstants);
    }
}

void Render::Window::UpdateMainPassCB(const GameTimer& gt)
{
    DirectX::XMMATRIX view = _camera.GetView();
    DirectX::XMMATRIX proj = _camera.GetProj();
    DirectX::XMMATRIX viewProj = XMMatrixMultiply(view, proj);
    DirectX::XMMATRIX invView = XMMatrixInverse(
        &XMMatrixDeterminant(view), view);
    DirectX::XMMATRIX invProj = XMMatrixInverse(
        &XMMatrixDeterminant(proj), proj);
    DirectX::XMMATRIX invViewProj = XMMatrixInverse(
        &XMMatrixDeterminant(viewProj), viewProj);
    XMStoreFloat4x4(&_mainPassCB.View, XMMatrixTranspose(view));
    XMStoreFloat4x4(&_mainPassCB.InvView, XMMatrixTranspose(invView));
    XMStoreFloat4x4(&_mainPassCB.Proj, XMMatrixTranspose(proj));
    XMStoreFloat4x4(&_mainPassCB.InvProj, XMMatrixTranspose(invProj));
    XMStoreFloat4x4(&_mainPassCB.ViewProj, XMMatrixTranspose(viewProj));
    XMStoreFloat4x4(&_mainPassCB.InvViewProj,
        XMMatrixTranspose(invViewProj));
    _mainPassCB.EyePosW = _camera.GetPosition3f();
    _mainPassCB.RenderTargetSize = DirectX::XMFLOAT2((float)mClientWidth,
        (float)mClientHeight);
    _mainPassCB.InvRenderTargetSize = DirectX::XMFLOAT2(1.0f / mClientWidth, 1.0f
        / mClientHeight);
    _mainPassCB.NearZ = 1.0f;
    _mainPassCB.FarZ = 1000.0f;
    _mainPassCB.TotalTime = gt.TotalTime();
    _mainPassCB.DeltaTime = gt.DeltaTime();
    auto currPassCB = passCB.get();
    currPassCB->CopyData(0, _mainPassCB);
}

void Render::Window::DrawRenderItems(ID3D12GraphicsCommandList* cmdList,
    const std::vector<RenderItem*>& ritems)
{
    UINT objCBByteSize = d3dUtil::CalcConstantBufferByteSize(
        sizeof(ObjectConstants));

    // For each render item...
    for (size_t i = 0; i < ritems.size(); ++i) {
        auto ri = ritems[i];
        auto objectCB = ri->ObjectCB->Resource();
        cmdList->IASetVertexBuffers(0, 1, &ri->Geo->VertexBufferView());
        cmdList->IASetIndexBuffer(&ri->Geo->IndexBufferView());
        cmdList->IASetPrimitiveTopology(ri->PrimitiveType);

        D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = objectCB->GetGPUVirtualAddress();
        cmdList->SetPipelineState(_pso.Get());
        cmdList->SetGraphicsRootConstantBufferView(0, objCBAddress);
        cmdList->DrawIndexedInstanced(ri->IndexCount, 1, ri->StartIndexLocation, ri->BaseVertexLocation, 0);
    }
}

void Render::Window::Draw(const GameTimer& gt)
{
    ThrowIfFailed(cmdListAlloc->Reset());
    mCommandList->Reset(cmdListAlloc.Get(), nullptr);

    // A command list can be reset after it has been added to the command queue via ExecuteCommandList.
    // Reusing the command list reuses memory.

    mCommandList->RSSetViewports(1, &mScreenViewport);
    mCommandList->RSSetScissorRects(1, &mScissorRect);

    // Indicate a state transition on the resource usage.
    mCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(),
        D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

    // Clear the back buffer and depth buffer.
    mCommandList->ClearRenderTargetView(CurrentBackBufferView(), DirectX::Colors::LightSteelBlue, 0, nullptr);
    mCommandList->ClearDepthStencilView(DepthStencilView(), D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);

    // Specify the buffers we are going to render to.
    mCommandList->OMSetRenderTargets(1, &CurrentBackBufferView(), true, &DepthStencilView());

    mCommandList->SetGraphicsRootSignature(_rootSignature.Get());

    // Bind per-pass constant buffer.  We only need to do this once per-pass.
    //auto passCB = mCurrFrameResource->PassCB->Resource();
    mCommandList->SetGraphicsRootConstantBufferView(1, passCB->Resource()->GetGPUVirtualAddress());
   // mCommandList->SetPipelineState(_psos["opaque"].Get());
    DrawRenderItems(mCommandList.Get(), _opaqueRenderItems);

    // Indicate a state transition on the resource usage.
    mCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(),
        D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

    // Done recording commands.
    ThrowIfFailed(mCommandList->Close());

    // Add the command list to the queue for execution.
    ID3D12CommandList* cmdsLists[] = { mCommandList.Get() };
    mCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

    // Swap the back and front buffers
    ThrowIfFailed(mSwapChain->Present(0, 0));
    mCurrBackBuffer = (mCurrBackBuffer + 1) % SwapChainBufferCount;
    FlushCommandQueue();
}

void Render::Window::OnResize()
{
    D3DApp::OnResize();

    _camera.SetLens(0.25f * MathHelper::Pi, AspectRatio(), 1.0f, 1000.0f);
}

void Render::Window::OnMouseDown(WPARAM btnState, int x, int y)
{
    mLastMousePos.x = x;
    mLastMousePos.y = y;

    SetCapture(mhMainWnd);
}

void Render::Window::OnMouseUp(WPARAM btnState, int x, int y)
{
    ReleaseCapture();
}

void Render::Window::OnMouseMove(WPARAM btnState, int x, int y)
{
    if ((btnState & MK_LBUTTON) != 0)
    {
        // Make each pixel correspond to a quarter of a degree.
        float dx = DirectX::XMConvertToRadians(0.25f * static_cast<float>(x - mLastMousePos.x));
        float dy = DirectX::XMConvertToRadians(0.25f * static_cast<float>(y - mLastMousePos.y));

        _camera.Pitch(dy);
        _camera.RotateY(dx);
    }

    mLastMousePos.x = x;
    mLastMousePos.y = y;
}


void Render::Window::OnKeyboardInput(const GameTimer& gt)
{
    const float dt = gt.DeltaTime();

    if (GetAsyncKeyState('Z') & 0x8000)
        _camera.Walk(10.0f * dt);

    if (GetAsyncKeyState('S') & 0x8000)
        _camera.Walk(-10.0f * dt);

    if (GetAsyncKeyState('Q') & 0x8000)
        _camera.Strafe(-10.0f * dt);

    if (GetAsyncKeyState('D') & 0x8000)
        _camera.Strafe(10.0f * dt);
    _camera.UpdateViewMatrix();
}

void Render::Window::MessageLoop()
{
    MSG msg = { 0 };

    if (msg.message == WM_QUIT)
    {
        _windowShouldClose = true;
    }
    while (msg.message != WM_QUIT)
    {

        if (_windowShouldClose == true)
        {
            return;
        };
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg); // Translate virtual-key messages into character messages
            DispatchMessage(&msg);  // Send message to WindowProc
        }
    }
}



void CALLBACK Render::Window::CreateGameWindow(LPCWSTR name, int width, int height)
{
    InitializeVariables(width, height);
    CreateWindowClass();
    Initialize();
    MessageLoop();
}

std::shared_ptr<Render::Window> Render::Window::GetInstance()
{
    if (_instance == nullptr)
    {
        std::shared_ptr<Render::Window> ptr(new Render::Window(HInstance()));
        _instance = ptr;
    }
    return _instance;
}