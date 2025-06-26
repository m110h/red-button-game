#include "state.h"

HGE* hge;
GameManager* mgr;

bool FrameFunc() { return mgr->Frame(); }
bool RenderFunc() { return mgr->Render(); }

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	hge = hgeCreate(HGE_VERSION);

    hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);

	hge->System_SetState(HGE_TITLE, "Button Mini Games");
	hge->System_SetState(HGE_LOGFILE, "Game.log");

	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SHOWSPLASH, false);

	hge->System_SetState(HGE_FPS, 120);

	hge->System_SetState(HGE_SCREENWIDTH, 800);
	hge->System_SetState(HGE_SCREENHEIGHT, 600);
	hge->System_SetState(HGE_SCREENBPP, 32);

	if(hge->System_Initiate()) {
	    mgr = new GameManager();
        hge->System_Start();
        delete mgr;
    }

    hge->System_Shutdown();
	hge->Release();
	return 0;
}
