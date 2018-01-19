#include <Windows.h>
#include <chrono>
#if defined(DEBUG) | defined(_DEBUG)
#include <crtdbg.h>
#include <iostream>
#include "Demo.h"
#endif

#ifdef _WINDOWS
#include <glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#endif

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define TITLE_NAME L"SnowPlain-ImageLibrary"

LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(29784);
	if (AllocConsole())
	{
		freopen("CONIN$", "rb", stdin);
		freopen("CONOUT$", "wb", stdout);
		freopen("CONOUT$", "wb", stderr);
	}
#endif

	HDC			dc;
	HGLRC		rc;
	HWND		winHandle;
	HINSTANCE	instance;
	instance = hInstance;

	WNDCLASSEX wcx;
	ZeroMemory(&wcx, sizeof(WNDCLASSEX));

	wcx.cbSize = sizeof(wcx);
	wcx.cbClsExtra = 0;
	wcx.cbWndExtra = 0;
	wcx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcx.hCursor = LoadCursor(instance, IDC_ARROW);
	wcx.hIcon = LoadIcon(instance, IDI_APPLICATION);
	wcx.hInstance = instance;
	wcx.lpfnWndProc = MsgProc;
	wcx.lpszClassName = TITLE_NAME;
	wcx.lpszMenuName = NULL;
	wcx.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wcx))
	{
		printf("Cannot register window class.\n");
		return 0;
	}

	winHandle = CreateWindowEx(
		NULL, TITLE_NAME, TITLE_NAME,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX, 0, 0,
		SCREEN_WIDTH, SCREEN_HEIGHT, NULL, NULL, instance, NULL);
	if (!winHandle)
	{
		printf("Cannot create Window.\n");
		return 0;
	}
	ShowWindow(winHandle, SW_SHOWDEFAULT);
	UpdateWindow(winHandle);

	dc = GetDC(winHandle);

	PIXELFORMATDESCRIPTOR pfd;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
	pfd.cDepthBits = 32;
	pfd.cColorBits = 24;
	pfd.iPixelType = PFD_TYPE_RGBA;

	int pixelFormat = ChoosePixelFormat(dc, &pfd);
	if (!SetPixelFormat(dc, pixelFormat, &pfd))
	{
		printf("Cannot set pixel format.\n");
		return 0;
	}

	rc = wglCreateContext(dc);
	wglMakeCurrent(dc, rc);

	std::chrono::steady_clock::time_point currentTime;
	std::chrono::steady_clock::time_point lastTime;
	float deltaTime = 0.0f;

	Init();

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
		{
			currentTime = std::chrono::high_resolution_clock::now();
			deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count();
			deltaTime /= 1000000000;
			lastTime = currentTime;

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
			SwapBuffers(dc);

			Update(deltaTime);
			Render();
		}
	}
	Destroy();

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(rc);
	if (ReleaseDC(winHandle, dc))
	{
		printf("Cannot release device context.\n");
		return 0;
	}
	DestroyWindow(winHandle);
	UnregisterClass(TITLE_NAME, instance);

	return 0;
}
LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_QUIT:
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}