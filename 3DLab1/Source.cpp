#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#include <d3d9types.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 )


//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
LPDIRECT3D9             g_pD3D = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; // Our rendering device
LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL; // Buffer to hold vertices
LPDIRECT3DINDEXBUFFER9	g_pIB = NULL; // Buffer to hold indices

// A structure for our custom vertex type
struct CUSTOMVERTEX
{
	FLOAT x, y, z;      // The untransformed, 3D position for the vertex
	DWORD color;        // The vertex color
};

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)


//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT InitD3D(HWND hWnd)
{
	// Create the D3D object.
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	// Set up the structure used to create the D3DDevice
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	// Create the D3DDevice
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice)))
	{
		return E_FAIL;
	}

	// Turn off culling, so we see the front and back of the triangle
	//BUT I NEED CULLING!
	//g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE ); 

	// Turn off D3D lighting, since we are providing our own vertex colors
	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	return S_OK;
}



//-----------------------------------------------------------------------------
// Name: InitGeometry()
// Desc: Creates the scene geometry
//-----------------------------------------------------------------------------
HRESULT InitGeometry()
{
	// Initialize three vertices for rendering a triangle
	CUSTOMVERTEX g_Vertices[] =
	{
		{ -1.0f,-1.0f,-1.0f, 0xff00f0ff, },
		{  1.0f,-1.0f,-1.0f, 0xff0000ff, },
		{  1.0f, 1.0f,-1.0f, 0xff0000ff, },
		{ -1.0f, 1.0f,-1.0f, 0xfff00fff, },
		{ -1.0f,-1.0f, 1.0f, 0xffff0f00, },
		{  1.0f,-1.0f, 1.0f, 0xff00ffff, },
		{  1.0f, 1.0f, 1.0f, 0xffffff00, },
		{ -1.0f, 1.0f, 1.0f, 0xff00ffff, },
	};


	int g_Indices[] =
	{
		0, 2, 1,
		0, 3, 2,
		3, 7, 6,
		2, 3, 6,
		1, 2, 6,
		1, 6, 5,
		5, 7, 4,
		5, 6, 7,
		0, 7, 3,
		4, 7, 0,
		0, 1, 5,
		0, 5, 4,
	};

	// Create the vertex buffer.
	if (FAILED(g_pd3dDevice->CreateVertexBuffer(8 * sizeof(CUSTOMVERTEX),
		0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &g_pVB, NULL)))
	{
		return E_FAIL;
	}

	// Fill the vertex buffer.
	VOID* pVertices;
	if (FAILED(g_pVB->Lock(0, sizeof(g_Vertices), (void**)&pVertices, 0)))
		return E_FAIL;
	memcpy(pVertices, g_Vertices, sizeof(g_Vertices));
	g_pVB->Unlock();


	// Create the index buffer.
	if (FAILED(g_pd3dDevice->CreateIndexBuffer(36 * sizeof(int),
		0, D3DFMT_INDEX32,
		D3DPOOL_DEFAULT, &g_pIB, NULL)))
	{
		return E_FAIL;
	}

	// Fill the index buffer.
	VOID* pIndices;
	if (FAILED(g_pIB->Lock(0, sizeof(g_Indices), (void**)&pIndices, 0)))
		return E_FAIL;
	memcpy(pIndices, g_Indices, sizeof(g_Indices));
	g_pIB->Unlock();

	return S_OK;
}


//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
{
	if (g_pIB != NULL)
		g_pIB->Release();

	if (g_pVB != NULL)
		g_pVB->Release();

	if (g_pd3dDevice != NULL)
		g_pd3dDevice->Release();

	if (g_pD3D != NULL)
		g_pD3D->Release();
}





//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID Render()
{
	// Clear the backbuffer to a black color
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	// Begin the scene
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		UINT iTime = timeGetTime() % 2000;
		FLOAT fAngle = iTime * (2.0f * D3DX_PI) / 2000.0f;
		// Setup the world, view, and projection matrices
		//SetupMatrices();

		// Render the vertex buffer contents
		g_pd3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(CUSTOMVERTEX));
		g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX); //the format of vertices
		g_pd3dDevice->SetIndices(g_pIB);

		D3DXVECTOR3 vEyePt(0.0f, 3.0f, -9.0f);
		D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
		D3DXMATRIXA16 matView;
		D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
		g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);

		D3DXMATRIXA16 matProj;
		D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI/2, 1.0f, 1.0f, 100.0f);
		g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);

		D3DXMATRIXA16 matRotZ, matRotY, matRotX, matWorld, matTrans1, matTrans2, matTrans3;

		D3DXMatrixRotationX(&matRotX, fAngle);
		D3DXMatrixRotationY(&matRotY, fAngle);
		D3DXMatrixRotationZ(&matRotZ, fAngle);


		//sun
		D3DXMatrixTranslation(&matTrans1, 0.0f, 0.0f, 0.0f);
		matWorld = matRotY * matTrans1;
		g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);


		//earth
		D3DXMATRIXA16 matScale2, matScale3;
		D3DXMatrixTranslation(&matTrans2, 6.0f, 0.0f, 0.0f);
		D3DXMatrixScaling(&matScale2, 0.8, 0.8, 0.8);
		//matWorld = matRotX * matTrans2 * matRotZ;
		matWorld = matScale2
			* matRotY //вращение вокруг своей оси 
			* matTrans2 * matRotZ; //перемещаемся и вращаемся вокруг первого; //уменьшаемся
			//* matTrans2 * matRotY; 
		g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);


		//moon
		D3DXMatrixScaling(&matScale3, 0.4, 0.4, 0.4);
		//D3DXMatrixTranslation(&matTrans3, 0.0f, 3.0f, 0.0f);
		D3DXMatrixTranslation(&matTrans3, 0.0f, 3.0f, 0.0f);
		matWorld = matScale3 * //масштаб
			matRotY * //вращение вокруг своей оси
			matTrans3 *
			matRotZ *
			(matTrans2 * matRotZ)
			;// matTrans2 * matRotZ - вот вокруг этой точки надо вращаться
		g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);
		
		
		

		// End the scene
		g_pd3dDevice->EndScene();
	}


	// Present the backbuffer contents to the display
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}




//-----------------------------------------------------------------------------
// Name: MsgProc() aka WInProc
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		Cleanup();
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}



//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
{
	UNREFERENCED_PARAMETER(hInst);

	// Register the window class
	WNDCLASSEX wc =
	{
		sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		L"Cube", NULL
	};
	RegisterClassEx(&wc);

	// Create the application's window
	HWND hWnd = CreateWindow(L"Cube", L"Rotating Cube",
		WS_OVERLAPPEDWINDOW, 100, 100, 512, 512,
		NULL, NULL, wc.hInstance, NULL);

	// Initialize Direct3D
	if (SUCCEEDED(InitD3D(hWnd)))
	{
		// Create the scene geometry
		if (SUCCEEDED(InitGeometry()))
		{
			// Show the window
			ShowWindow(hWnd, SW_SHOWDEFAULT);
			UpdateWindow(hWnd);

			// Enter the message loop
			MSG msg;
			ZeroMemory(&msg, sizeof(msg));
			while (msg.message != WM_QUIT)
			{
				if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
					Render();
			}
		}
	}

	UnregisterClass(L"Cube", wc.hInstance);
	return 0;
}