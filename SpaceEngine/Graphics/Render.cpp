#include <Graphics.h>

const int gNumFrameResources = 3;
/*
using namespace Render;
using namespace DirectX;
using namespace DirectX::PackedVector;
using Microsoft::WRL::ComPtr;*/

WCHAR WindowClass[MAX_NAME_STRING] = L"SpaceEngineWindowClass";
std::shared_ptr<Render::Window> Render::Window::_instance = nullptr;

Render::Window::Window(HINSTANCE hInstance) : D3DApp(hInstance),
_shapesIndices(1), _lastGeoIndexOffset(0), _lastGeoIndicesSize(0), 
_lastGeoVertexOffset(0), _lastGeoVerticesSize(0), _objCBIndex(0)
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
    /*
        - Create the window
        - Init DirectX
            - Creer la factory
            - Creer le device
            - Creer les fences
            - Check les tailles des types descriptors (view)
            - Creer la commande queue et la command list
            - Creer la swap chain
            - Creer les heap des descriptors
    */
    if (!D3DApp::Initialize())
        return false;
    // Reset the command list to prep for initialization commands.
    ThrowIfFailed(mCommandList->Reset(mDirectCmdListAlloc.Get(), nullptr));
    /* Create an empty root signature */
    BuildRootSignature();
    /* Compile the VS AND PS shaders -- set the vertex input layout */
    BuildShadersAndInputLayout();
    /* Build all app shapes */
    buildShape(0, 1, 0, 3, 3, 3, DirectX::Colors::BlueViolet);
    buildShape(2, 0, 0, 2, 2, 2, DirectX::Colors::BurlyWood);
    /* Buils the constant buffers */
    buildGPUBuffers();
    /* Create the three frames ressources with a copy of thr render item */
    BuildFrameResources();
    /* Create the constant buffer heap  */
    BuildDescriptorHeaps();
    /* Create a CBV descriptor for each object of each frame resource */
    BuildConstantBufferViews();
    /* Create a PSO for Opaque render items ans transparent render items */
    BuildPSOs();
    // Execute the initialization commands.
    ThrowIfFailed(mCommandList->Close());
    ID3D12CommandList* cmdsLists[] = { mCommandList.Get() };
    mCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);
    // Wait until initialization is complete.
    FlushCommandQueue();

    return true;
    /*
        build the new shape
        create a new render item
        add it to the frame ressources
        create a new cbv
        update the pso ??
    */
}

void Render::Window::BuildRootSignature()
{
    /* We need to update the root signature to take two descriptor tables:
    (we need two tables because the CBVs will be set at different frequencies
        — the per pass CBV only needs to be set once per rendering pass
        - the per object CBV needs to be set per render item */
    CD3DX12_DESCRIPTOR_RANGE cbvTable0;
    cbvTable0.Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);
    CD3DX12_DESCRIPTOR_RANGE cbvTable1;
    cbvTable1.Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 1);

    // Root parameter can be a table, root descriptor or root constants.
    CD3DX12_ROOT_PARAMETER slotRootParameter[2];
    // Create root CBVs.
    slotRootParameter[0].InitAsDescriptorTable(1, &cbvTable0);
    slotRootParameter[1].InitAsDescriptorTable(1, &cbvTable1);

    // A root signature is an array of root parameters.
    CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc(2, slotRootParameter, 0, nullptr,
        D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

    // create a root signature with a single slot which points to a 
    // descriptor range consisting of a single constant buffer
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

void Render::Window::buildShape(float p_x, float p_y, float p_z,
    float scale_x, float scale_y, float scale_z, const float* color)
{
    GeometryGenerator::MeshData newGeo = _geoGen.CreateBox(1.0f, 1.0f,
        1.0f, 3);
    // We are concatenating all the geometry into one big vertex/index
    // buffer. So define the regions in the buffer each submesh covers.
    // Cache the vertex offsets to each object in the concatenated vertex
    // buffer.
    UINT newGeoVertexOffset = _lastGeoVertexOffset + _lastGeoVerticesSize;
    _lastGeoVertexOffset = newGeoVertexOffset;
    _lastGeoVerticesSize = newGeo.Vertices.size();
    // Cache the starting index for each object in the concatenated index
    // buffer.
    UINT newGeoIndexOffset = _lastGeoIndexOffset + _lastGeoIndicesSize;
    _lastGeoIndexOffset = newGeoIndexOffset;
    _lastGeoIndicesSize = (UINT)newGeo.Indices32.size();
    // Define the SubmeshGeometry that cover different
    // regions of the vertex/index buffers.
    SubmeshGeometry newGeoSubmesh;
    newGeoSubmesh.IndexCount = (UINT)newGeo.Indices32.size();
    newGeoSubmesh.StartIndexLocation = newGeoIndexOffset;
    newGeoSubmesh.BaseVertexLocation = newGeoVertexOffset;
    // Extract the vertex elements we are interested in and pack the
    // vertices of all the meshes into one vertex buffer.
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
    _geometries["shapeGeo"]->DrawArgs[std::to_string(_shapesIndices)] = newGeoSubmesh;
    createShape(std::to_string(_shapesIndices), p_x, p_y, p_z, scale_x, scale_y, scale_z);
    _shapesIndices++;
}

void Render::Window::createShape(std::string submesh, float p_x, float p_y, 
    float p_z, float scale_x, float scale_y, float scale_z)
{
    /* Create the render item */
    auto newRenderItem = std::make_unique<RenderItem>();
    /* set up its position */
    DirectX::XMMATRIX world =
        DirectX::XMMatrixTranslation(p_x, p_y, p_z)
        * DirectX::XMMatrixScaling(scale_x, scale_y, scale_z);
    DirectX::XMStoreFloat4x4(&newRenderItem->World, world);
    newRenderItem->ObjCBIndex = _objCBIndex++;
    newRenderItem->Geo = _geometries["shapeGeo"].get();
    newRenderItem->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    newRenderItem->IndexCount = newRenderItem->Geo->DrawArgs[submesh].
        IndexCount;
    newRenderItem->StartIndexLocation =
        newRenderItem->Geo->DrawArgs[submesh].StartIndexLocation;
    newRenderItem->BaseVertexLocation =
        newRenderItem->Geo->DrawArgs[submesh].BaseVertexLocation;
    _opaqueRenderItems.push_back(newRenderItem.get());
    /* add the render item to the render items vect */
    _allRenderItems.push_back(std::move(newRenderItem));
}

void Render::Window::buildGPUBuffers()
{
    // create vertices and indices upload buffer
    const UINT vbByteSize = (UINT)_vertices.size() * sizeof(Vertex);
    const UINT ibByteSize = (UINT)_indices.size() * sizeof(std::uint16_t);
    //auto geo = std::make_unique<MeshGeometry>();

    //geo->Name = "shapeGeo";
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
    for (int i = 0; i < gNumFrameResources; i++) {
        _frameResources.push_back(std::make_unique<FrameResources>(
            md3dDevice.Get(), 1, (UINT)_allRenderItems.size()));
    }
}

void Render::Window::BuildDescriptorHeaps()
{
    UINT objCount = (UINT)_opaqueRenderItems.size();
    // Need a CBV descriptor for each object for each frame resource,
    // +1 for the perPass CBV for each frame resource.
    UINT numDescriptors = (objCount + 1) * gNumFrameResources;
    // Save an offset to the start of the pass CBVs. These are the last descriptors.
    _passCbvOffset = objCount * gNumFrameResources;
    D3D12_DESCRIPTOR_HEAP_DESC cbvHeapDesc = {};
    cbvHeapDesc.NumDescriptors = numDescriptors;
    cbvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    cbvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    cbvHeapDesc.NodeMask = 0;
    ThrowIfFailed(md3dDevice->CreateDescriptorHeap(&cbvHeapDesc,
        IID_PPV_ARGS(&_cbvHeap)));
}

void Render::Window::BuildConstantBufferViews()
{
    UINT objCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof
    (ObjectConstants));
    UINT objCount = (UINT)_opaqueRenderItems.size();
    // Need a CBV descriptor for each object for each frame resource.
    for (int frameIndex = 0; frameIndex < gNumFrameResources; frameIndex++) {
        auto objectCB = _frameResources[frameIndex]->ObjectCB->Resource();
        for (UINT i = 0; i < objCount; ++i) {
            D3D12_GPU_VIRTUAL_ADDRESS cbAddress =
                objectCB->GetGPUVirtualAddress();
            // Offset to the ith object constant buffer heap 
            // in the current buffer.
            cbAddress += i * objCBByteSize;
            // Offset to the object CBV in the descriptor heap.
            int heapIndex = frameIndex * objCount + i;
            /* Once we know the descriptor increment size,
            we can use one of the two CD3DX12_CPU_DESCRIPTOR_HANDLE::Offset
            methods to offset the handle by n descriptors: */
            auto handle = CD3DX12_CPU_DESCRIPTOR_HANDLE(
                _cbvHeap->GetCPUDescriptorHandleForHeapStart());
            handle.Offset(heapIndex, mCbvSrvUavDescriptorSize);
            D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
            cbvDesc.BufferLocation = cbAddress;
            cbvDesc.SizeInBytes = objCBByteSize;
            md3dDevice->CreateConstantBufferView(&cbvDesc, handle);
        }
    }
    UINT passCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof
    (PassConstants));
    // Last three descriptors are the pass CBVs for each frame resource.
    for (int frameIndex = 0; frameIndex < gNumFrameResources; frameIndex++) {
        auto passCB = _frameResources[frameIndex]->PassCB->Resource();
        // Pass buffer only stores one cbuffer per frame resource.
        D3D12_GPU_VIRTUAL_ADDRESS cbAddress = passCB->GetGPUVirtualAddress();
        // Offset to the pass cbv in the descriptor heap.
        int heapIndex = _passCbvOffset + frameIndex;
        auto handle = CD3DX12_CPU_DESCRIPTOR_HANDLE(
            _cbvHeap->GetCPUDescriptorHandleForHeapStart());
        handle.Offset(heapIndex, mCbvSrvUavDescriptorSize);
        D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
        cbvDesc.BufferLocation = cbAddress;
        cbvDesc.SizeInBytes = passCBByteSize;
        md3dDevice->CreateConstantBufferView(&cbvDesc, handle);
    }
}

void Render::Window::BuildPSOs()
{
    /*		####	PSO FOR OPAQUE OBJECTS		####	 */
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
        &opaquePsoDesc, IID_PPV_ARGS(&_psos["opaque"])));

    /*		####	PSO FOR OPAQUE WIREFRAME OBJECTS		####	 */
    D3D12_GRAPHICS_PIPELINE_STATE_DESC opaqueWireframePsoDesc = opaquePsoDesc;
    opaqueWireframePsoDesc.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;
    ThrowIfFailed(md3dDevice->CreateGraphicsPipelineState(
        &opaqueWireframePsoDesc, IID_PPV_ARGS(&_psos["opaque_wireframe"])));
}

void Render::Window::Update(const GameTimer& gt)
{
    OnKeyboardInput(gt);
    UpdateCamera(gt);

    // Cycle through the circular frame resource array.
    _currFrameResourceIndex = (_currFrameResourceIndex + 1) % gNumFrameResources;
    _currFrameResource = _frameResources[_currFrameResourceIndex].get();
    // Has the GPU finished processing the commands of the current frame
    // resource. If not, wait until the GPU has completed commands up to
    // this fence point.
    if (_currFrameResource->Fence != 0 && mFence->GetCompletedValue() <
        _currFrameResource->Fence) {
        HANDLE eventHandle = CreateEventEx(nullptr, false, false, EVENT_ALL_ACCESS);
        ThrowIfFailed(mFence->SetEventOnCompletion(_currFrameResource->Fence,
            eventHandle));
        WaitForSingleObject(eventHandle, INFINITE);
        CloseHandle(eventHandle);
    }
    // [...] Update resources in mCurrFrameResource (like cbuffers).
    UpdateObjectCBs(gt);
    UpdateMainPassCB(gt);
}

void Render::Window::UpdateObjectCBs(const GameTimer& gt)
{
    auto currObjectCB = _currFrameResource->ObjectCB.get();
    for (auto& e : _allRenderItems)
    {
        // Only update the cbuffer data if the constants have changed.
        // This needs to be tracked per frame resource.
        if (e->NumFramesDirty > 0)
        {
            // get the word matrix of each drawable obj
            DirectX::XMMATRIX world = XMLoadFloat4x4(&e->World);
            ObjectConstants objConstants;
            XMStoreFloat4x4(&objConstants.World, XMMatrixTranspose(world));
            currObjectCB->CopyData(e->ObjCBIndex, objConstants);
            // Next FrameResource need to be updated too.
            e->NumFramesDirty--;
        }
    }
}

void Render::Window::UpdateMainPassCB(const GameTimer& gt)
{
    DirectX::XMMATRIX view = XMLoadFloat4x4(&_view);
    DirectX::XMMATRIX proj = XMLoadFloat4x4(&_proj);
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
    _mainPassCB.EyePosW = _eyePos;
    _mainPassCB.RenderTargetSize = DirectX::XMFLOAT2((float)mClientWidth,
        (float)mClientHeight);
    _mainPassCB.InvRenderTargetSize = DirectX::XMFLOAT2(1.0f / mClientWidth, 1.0f
        / mClientHeight);
    _mainPassCB.NearZ = 1.0f;
    _mainPassCB.FarZ = 1000.0f;
    _mainPassCB.TotalTime = gt.TotalTime();
    _mainPassCB.DeltaTime = gt.DeltaTime();
    auto currPassCB = _currFrameResource->PassCB.get();
    currPassCB->CopyData(0, _mainPassCB);
}

void Render::Window::DrawRenderItems(ID3D12GraphicsCommandList* cmdList,
    const std::vector<RenderItem*>& ritems)
{
    UINT objCBByteSize = d3dUtil::CalcConstantBufferByteSize(
        sizeof(ObjectConstants));
    auto objectCB = _currFrameResource->ObjectCB->Resource();

    // For each render item...
    for (size_t i = 0; i < ritems.size(); ++i) {
        auto ri = ritems[i];
        cmdList->IASetVertexBuffers(0, 1, &ri->Geo->VertexBufferView());
        cmdList->IASetIndexBuffer(&ri->Geo->IndexBufferView());
        cmdList->IASetPrimitiveTopology(ri->PrimitiveType);
        // Offset to the CBV in the descriptor heap for this object and
        // for this frame resource.
        UINT cbvIndex = _currFrameResourceIndex *
            (UINT)_opaqueRenderItems.size() + ri->ObjCBIndex;
        auto cbvHandle = CD3DX12_GPU_DESCRIPTOR_HANDLE(
            _cbvHeap->GetGPUDescriptorHandleForHeapStart());
        cbvHandle.Offset(cbvIndex, mCbvSrvUavDescriptorSize);
        cmdList->SetGraphicsRootDescriptorTable(0, cbvHandle);
        cmdList->DrawIndexedInstanced(ri->IndexCount, 1,
            ri->StartIndexLocation, ri->BaseVertexLocation, 0);
    }
}

void Render::Window::Draw(const GameTimer& gt)
{
    auto cmdListAlloc = _currFrameResource->CmdListAlloc;
    // Reuse the memory associated with command recording.
    // We can only reset when the associated command lists have
    // finished execution on the GPU.
    ThrowIfFailed(cmdListAlloc->Reset());
    // A command list can be reset after it has been added to the
    // command queue via ExecuteCommandList.
    // Reusing the command list reuses memory.
    if (_isWireframe) {
        ThrowIfFailed(mCommandList->Reset(
            cmdListAlloc.Get(), _psos["opaque_wireframe"].Get()));
    }
    else {
        ThrowIfFailed(mCommandList->Reset(cmdListAlloc.Get(),
            _psos["opaque"].Get()));
    }
    mCommandList->RSSetViewports(1, &mScreenViewport);
    mCommandList->RSSetScissorRects(1, &mScissorRect);
    // Indicate a state transition on the resource usage.
    mCommandList->ResourceBarrier(1,
        &CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(),
            D3D12_RESOURCE_STATE_PRESENT,
            D3D12_RESOURCE_STATE_RENDER_TARGET));
    // Clear the back buffer and depth buffer.
    mCommandList->ClearRenderTargetView(CurrentBackBufferView(),
        DirectX::Colors::LightSteelBlue, 0, nullptr);
    mCommandList->ClearDepthStencilView(DepthStencilView(),
        D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL,
        1.0f, 0, 0, nullptr);
    // Specify the buffers we are going to render to.
    mCommandList->OMSetRenderTargets(1, &CurrentBackBufferView(),
        true, &DepthStencilView());
    ID3D12DescriptorHeap* descriptorHeaps[] = { _cbvHeap.Get() };
    mCommandList->SetDescriptorHeaps(_countof(descriptorHeaps),
        descriptorHeaps);
    mCommandList->SetGraphicsRootSignature(_rootSignature.Get());
    int passCbvIndex = _passCbvOffset + _currFrameResourceIndex;
    auto passCbvHandle = CD3DX12_GPU_DESCRIPTOR_HANDLE(
        _cbvHeap->GetGPUDescriptorHandleForHeapStart());
    passCbvHandle.Offset(passCbvIndex, mCbvSrvUavDescriptorSize);
    mCommandList->SetGraphicsRootDescriptorTable(1, passCbvHandle);
    DrawRenderItems(mCommandList.Get(), _opaqueRenderItems);
    // Indicate a state transition on the resource usage.
    mCommandList->ResourceBarrier(1,
        &CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(),
            D3D12_RESOURCE_STATE_RENDER_TARGET,
            D3D12_RESOURCE_STATE_PRESENT));
    // Done recording commands.
    ThrowIfFailed(mCommandList->Close());
    // Add the command list to the queue for execution.
    ID3D12CommandList* cmdsLists[] = { mCommandList.Get() };
    mCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);
    // Swap the back and front buffers
    ThrowIfFailed(mSwapChain->Present(0, 0));
    mCurrBackBuffer = (mCurrBackBuffer + 1) % SwapChainBufferCount;
    // Advance the fence value to mark commands up to this fence point.
    _currFrameResource->Fence = ++mCurrentFence;
    // Add an instruction to the command queue to set a new fence point.
    // Because we are on the GPU timeline, the new fence point won’t be
    // set until the GPU finishes processing all the commands prior to 
    // this Signal().
    mCommandQueue->Signal(mFence.Get(), mCurrentFence);
}

void Render::Window::OnResize()
{
    D3DApp::OnResize();

    // The window resized, so update the aspect ratio and recompute the projection matrix.
    DirectX::XMMATRIX P = DirectX::XMMatrixPerspectiveFovLH(
        0.25f * MathHelper::Pi, AspectRatio(), 1.0f, 1000.0f);
    XMStoreFloat4x4(&_proj, P);
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
    if ((btnState & MK_LBUTTON) != 0) {
        // Make each pixel correspond to a quarter of a degree.
        float dx = DirectX::XMConvertToRadians(0.25f * static_cast<float>(x - mLastMousePos.x));
        float dy = DirectX::XMConvertToRadians(0.25f * static_cast<float>(y - mLastMousePos.y));

        // Update angles based on input to orbit camera around box.
        mTheta += dx;
        mPhi += dy;

        // Restrict the angle mPhi.
        mPhi = MathHelper::Clamp(mPhi, 0.1f, MathHelper::Pi - 0.1f);
    } else if ((btnState & MK_RBUTTON) != 0) {
        // Make each pixel correspond to 0.2 unit in the scene.
        float dx = 0.05f * static_cast<float>(x - mLastMousePos.x);
        float dy = 0.05f * static_cast<float>(y - mLastMousePos.y);

        // Update the camera radius based on input.
        mRadius += dx - dy;

        // Restrict the radius.
        mRadius = MathHelper::Clamp(mRadius, 5.0f, 150.0f);
    }

    mLastMousePos.x = x;
    mLastMousePos.y = y;
}

void Render::Window::OnKeyboardInput(const GameTimer& gt)
{
}

void Render::Window::UpdateCamera(const GameTimer& gt)
{
    // Convert Spherical to Cartesian coordinates.
    _eyePos.x = mRadius * sinf(mPhi) * cosf(mTheta);
    _eyePos.z = mRadius * sinf(mPhi) * sinf(mTheta);
    _eyePos.y = mRadius * cosf(mPhi);

    // Build the view matrix.
    DirectX::XMVECTOR pos = DirectX::XMVectorSet(_eyePos.x, _eyePos.y, _eyePos.z, 1.0f);
    DirectX::XMVECTOR target = DirectX::XMVectorZero();
    DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

    DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(pos, target, up);
    DirectX::XMStoreFloat4x4(&_view, view);
}


void Render::Window::MessageLoop()
{
    MSG msg = {0};

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