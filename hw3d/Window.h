#pragma once
#include "ChiliWin.h"
//#include <Windows.h>
#include <string>
#include <sstream>

class Window
{
private:
	//singleton manages registeration/cleanup of window class
	class WindowClass 
	{
	public:
		static const char* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;
		static constexpr const char* wndClassName = "Chili Direct 3D Engine Window";
		static WindowClass wndClass;
		HINSTANCE hInst;
	};
public:
	Window(int width, int height, const char* name) noexcept;
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
private:
	//v serves as setup to set the pointer to the window instanceon Win32 side
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam,LPARAM lParam) noexcept;
	//v serves as an adapter to adapt from Win32 calling convention to c++ member function call convention
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam,LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam,LPARAM lParam) noexcept;


	
	int width;
	int height;
	HWND hWnd;
};

