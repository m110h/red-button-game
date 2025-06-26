#include "state.h"

extern HGE* hge;

GameState* GameMenu::_instance = 0;
GameState* GameBasketBall::_instance = 0;
GameState* GameScaleArrow::_instance = 0;
GameState* GameBandit::_instance = 0;

/**
    \ Реализация GameManager
*/
GameManager::GameManager() {
    _state = GameMenu::Instance();

    DisplayMode = true;
}

bool GameManager::Frame() {
    switch (hge->Input_GetKey()) {
        case HGEK_F:
            DisplayMode = !DisplayMode;
            hge->System_SetState(HGE_WINDOWED, DisplayMode);
            break;
    }

    return _state->Frame(this);
}

bool GameManager::Render() { return _state->Render(this); }

/**
    \ Реализация главного меню
*/
GameMenu::GameMenu() {
    CreateGUI();

    HTEXTURE tbutton = hge->Texture_Load("./images/textures/button.png");

    gui->AddCtrl(new hgeGUIButton(
        1,
        325,
        225,
        150,
        150,
        tbutton,
        0,
        0)
    );

    gui->AddCtrl(new hgeGUIMenuItem(
        2,
        "./images/textures/menu/basketball.png",
        "./sounds/diatake.ogg",
        300,
        100,
        80,
        64)
    );

    gui->AddCtrl(new hgeGUIMenuItem(
        3,
        "./images/textures/menu/scale.png",
        "./sounds/diatake.ogg",
        400,
        100,
        80,
        64)
    );

    gui->AddCtrl(new hgeGUIMenuItem(
        4,
        "./images/textures/menu/bandit.png",
        "./sounds/diatake.ogg",
        500,
        100,
        80,
        64)
    );

    gui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
    gui->SetFocus(2);
    gui->GetCtrl(2)->SetStatus(true);
    gui->Enter();

    lastid = 2;
}

/**
    \ Логика меню
*/
bool GameMenu::Frame(GameManager* mgr) {
    switch(hge->Input_GetKey())
    {
        case HGEK_ESCAPE: {
            DestroyGUI();
            return true;
        }

        default: break;
    }

    int id = gui->Update(hge->Timer_GetDelta());
    switch (id) {
        case 1: {
            switch (lastid) {
                case 2:
                    ChangeState(mgr, GameBasketBall::Instance());
                    break;

                case 3:
                    ChangeState(mgr, GameScaleArrow::Instance());
                    break;

                case 4:
                    ChangeState(mgr, GameBandit::Instance());
                    break;

                default: break;
            }
        }

        case 2:
            gui->GetCtrl(2)->SetStatus(true);

            if (gui->GetCtrl(3)->GetStatus()) gui->GetCtrl(3)->SetStatus(false);
            if (gui->GetCtrl(4)->GetStatus()) gui->GetCtrl(4)->SetStatus(false);

            lastid = 2;
            break;

        case 3:
            gui->GetCtrl(3)->SetStatus(true);

            if (gui->GetCtrl(2)->GetStatus()) gui->GetCtrl(2)->SetStatus(false);
            if (gui->GetCtrl(4)->GetStatus()) gui->GetCtrl(4)->SetStatus(false);

            lastid = 3;
            break;


        case 4:
            gui->GetCtrl(4)->SetStatus(true);

            if (gui->GetCtrl(2)->GetStatus()) gui->GetCtrl(2)->SetStatus(false);
            if (gui->GetCtrl(3)->GetStatus()) gui->GetCtrl(3)->SetStatus(false);

            lastid = 4;
            break;
    }

    return false;
}

bool GameMenu::Render(GameManager* mgr) {
    hge->Gfx_BeginScene();
    hge->Gfx_Clear(0xFFFFFFFF);

    gui->Render();

    hge->Gfx_EndScene();
    return false;
}
