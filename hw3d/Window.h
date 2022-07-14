#pragma once
#include "ChiliWin.h"
#include "ChiliException.h"
//#include <Windows.h>
#include <string>
#include <sstream>
#include "Keyboard.h"
#include "Mouse.h"

class Window
{
public:
	class Exception : public ChiliException
	{
	public:
		Exception(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
	private:
		HRESULT hr;
	};
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
	//Window(int width, int height, const char* name) noexcept;
	Window(int width, int height, const char* name);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	void SetTitle(const std::string& title);
private:
	//v serves as setup to set the pointer to the window instanceon Win32 side
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam,LPARAM lParam) noexcept;
	//v serves as an adapter to adapt from Win32 calling convention to c++ member function call convention
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam,LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam,LPARAM lParam) noexcept;


	
	int width;
	int height;
	HWND hWnd;
public:
	Keyboard kbd;
	Mouse mouse;
};

#define CHWND_EXCEPT(hr) Window::Exception(__LINE__,__FILE__, hr)
#define CHWND_LAST_EXCEPT() Window::Exception(__LINE__,__FILE__, GetLastError())