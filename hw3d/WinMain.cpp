#include <Windows.h>
#include <string>
#include <sstream>

std::wstring S2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

//single WNDPROC can be used for multiple instances of this pClassName, UINT is msgId, wParam and lParam again their meaning depends on type pf message that we are processing
//meaning of LRESULT also deends in the message we are handling but we dont have to worry about this usually as the last step of our WNDPROC we invoke DefWindowProc
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	/* static WindowsMessageMap mm;
	OutputDebugString(mm(msg, lParam, wParam).c_str());*/

	switch (msg)
	{
		case WM_CLOSE:
			PostQuitMessage(69);//69 is the return value you want the application to exit with this PostQuitMessage posts a WM_QUIT message on MessageQueue
		break;
		case WM_KEYDOWN:
			if (wParam == 'F')
			{
				LPCWSTR NewTitle = L"New Title";
				SetWindowText(hWnd, NewTitle);
			}
		break;
		case WM_KEYUP:
			if (wParam == 'F')
			{
				LPCWSTR NewTitle = L"Happy Hard Window";
				SetWindowText(hWnd, NewTitle);
			}
		break;
		case WM_CHAR:
		{
			static std::string Title;
			Title.push_back( (char)wParam);
			SetWindowText(hWnd, S2ws(Title).c_str());
		}
		break;
		case WM_LBUTTONDOWN:
		{
			if (wParam == MK_LBUTTON)
			{
				const POINTS Pt = MAKEPOINTS(lParam);
				std::ostringstream Oss;
				Oss << "(" << Pt.x << "," << Pt.y << ")";
				SetWindowText(hWnd, S2ws(Oss.str()).c_str());
			}
		}
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{	
	const auto pClassName = "hw3dhw";
	LPCWSTR pClassNameL = L"hw3dhw";
	//Register window class
	WNDCLASSEX wc = {0};
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = pClassNameL;
	wc.hIconSm = nullptr;
	RegisterClassEx(&wc);
	//Create window instance
	HWND HWnd = CreateWindowExA(
		0,
		pClassName,
		"Happy Hard Window",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		200, 200, 640, 480,
		nullptr,nullptr,hInstance,nullptr
	);
	ShowWindow(HWnd, SW_SHOW);

	MSG Msg;
	BOOL GResult;
	while ( (GResult = GetMessage(&Msg, nullptr, 0, 0))>0 )//nullptr is passed for HWND as we want to get msgs from any window in current thread, 0,0 set for wMsgFilterMin and wMsgFilterMax as we want all available msgs to be returned by GetMessage()
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	if (GResult == -1)
		return -1;
	else
		return Msg.wParam;//this is set to 69 when we call PostQuitMessage see doc on WM_QUIT 
}