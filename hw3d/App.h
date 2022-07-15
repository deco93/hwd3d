#pragma once
#include "Window.h"
#include "ChiliTimer.h"
class App
{
public:
	App();
	//master frame/	message loop, called when game starts to start the game loop
	int Go();
private:
	//logic for every frame will be put in DoFrame function
	void DoFrame();
private:
	Window wnd;
	ChiliTimer timer;
};

