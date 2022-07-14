#include "ChiliWin.h"
#include <string>
#include <sstream>
#include "Window.h"

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{	
	try
	{
		Window wnd(800, 300, "Donkey fart box");
		/*static int countUp = 0;
		static int countDown = 0;*/

		MSG msg;
		BOOL gResult;
		while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (wnd.kbd.KeyIsPressed(VK_MENU))
			{
				MessageBox(nullptr, "Something soon","Space Keypressed", MB_OK | MB_ICONEXCLAMATION);
			}
			/*while (!wnd.mouse.IsEmpty())
			{
				const auto e = wnd.mouse.Read();
				switch (e.GetType())
				{
					case Mouse::Event::Type::Leave:
						wnd.SetTitle("Gone!");
						break;
					case Mouse::Event::Type::WheelUp:
					{
						countDown = 0;
						countUp++;
						std::ostringstream oss;
						oss << "Up: " << countUp;
						wnd.SetTitle(oss.str());
						break;
					}
					case Mouse::Event::Type::WheelDown:
					{
						countUp = 0;
						countDown++;
						std::ostringstream oss;
						oss << "Down: " << countDown;
						wnd.SetTitle(oss.str());
						break;
					}
					case Mouse::Event::Type::Move:
					{
						std::ostringstream oss;
						oss << "Mouse moved position: (" << e.GetPosX() << "," << e.GetPosY() << ")";
						wnd.SetTitle(oss.str());
						break;
					}
					if (e.GetType() == Mouse::Event::Type::Move)
					{
						std::ostringstream oss;
						oss << "Mouse position: (" << e.GetPosX() << "," << e.GetPosY() << ")";
						wnd.SetTitle(oss.str());
					}
				}
			}*/
		}

		if (gResult == -1)
		{
			return -1;
		}

		return msg.wParam;
	}
	catch (const ChiliException& e)
	{
		MessageBox(nullptr, e.what(), e.GetType(), MB_OK|MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e)
	{
		MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, "No Details Available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	
}