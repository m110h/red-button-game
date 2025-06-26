#ifndef GAME_BASKETBALL_H
#define GAME_BASKETBALL_H

extern HGE* hge;

/**
    \todo
        мини игра Basketball
*/
class GameBasketBall : public GameState
{
public:
    static GameState* Instance() {
        if (_instance == 0) {
            _instance = new GameBasketBall;
        }

        return _instance;
    }

    /**
        \ Логика игры && формирование следующего кадра
    */
    bool Frame(GameManager* mgr) {
        if (!Initialize) InitGame();

        gui->Update(hge->Timer_GetDelta());

        switch(hge->Input_GetKey())
        {
            case HGEK_ESCAPE:
                DestroyGame();
                ChangeState(mgr, GameMenu::Instance());
                return false;
        }

        if (hge->Input_KeyDown(HGEK_LBUTTON)) LMouseDown = true;
        if (hge->Input_KeyUp(HGEK_LBUTTON)) LMouseDown = false;
        if (hge->Input_KeyDown(HGEK_RBUTTON)) RMouseDown = true;
        if (hge->Input_KeyUp(HGEK_RBUTTON)) RMouseDown = false;

        if (LMouseDown && !button->GetStatus()) {
            float mx, my;

            hge->Input_GetMousePos(&mx, &my);
            if (
                CircleCollision(
                    button->GetPosition(),
                    hgeVector(mx, my),
                    button->GetBoundingRadius(),
                    1
                )
            ) {
                button->Push();
                hole->Open();
                ball->Start();
            }
        }

        if (!LMouseDown && button->GetStatus()) {
            button->Pop();
        }

        if (
            CircleCollision(
                ball->GetPosition(),
                basket->GetPosition(),
                ball->GetBoundingRadius(),
                basket->GetBoundingRadius()
            )
        ){
            splash->Play(hgeVector(ball->GetPosition().x, basket->GetPosition().y - 12));
            ball->Stop();
            basket->NextFrame();

            if (basket->GetCurrentFrame() == 4) {
                FinishGame = true;
            }
        }

        if (FinishGame) {
            DestroyGame();
            ChangeState(mgr, GameMenu::Instance());

            return false;
        }

        return false;
    }


    /**
        \ Визуализация
    */
    bool Render(GameManager* mgr) {
        hge->Gfx_BeginScene();
        hge->Gfx_Clear(0xFFFFFFFF);

        if (Initialize) {
            button->Show();

            rail->Show();
            hole->Show();
            ball->Show();
            basket->Show(rail->GetStatus());
            splash->Show();

            gui->Render();
        }

        hge->Gfx_EndScene();
        return false;
    }

    void InitGame() {
        Initialize = true;
        FinishGame = false;

        CreateGUI();

        button = new GameButton("./cfg/basketball/button.cfg");
        rail = new Rail("./cfg/basketball/rail.cfg");
        hole = new Hole("./cfg/basketball/hole.cfg");
        basket = new Basket("./cfg/basketball/basket.cfg");
        ball = new Ball("./cfg/basketball/ball.cfg");
        splash = new Splash("./cfg/basketball/splash.cfg");
    }

    void DestroyGame() {
        Initialize = false;

        DestroyGUI();

        delete button;
        delete rail;
        delete hole;
        delete basket;
        delete ball;
        delete splash;
    }

protected:
    GameBasketBall() {
        Initialize = false;
        LMouseDown = false;
        RMouseDown = false;
    }

private:
    static GameState* _instance;

    GameButton *button;
    Rail *rail;
    Hole *hole;
    Basket* basket;
    Ball* ball;
    Splash* splash;

    bool Initialize;
    bool FinishGame;

    bool LMouseDown;
    bool RMouseDown;
};

#endif
