#ifndef GAME_SCALE_ARROW_H
#define GAME_SCALE_ARROW_H

extern HGE* hge;

/**
    \todo
        мини игра Scale&Arrow
*/
class GameScaleArrow : public GameState
{
public:
    static GameState* Instance() {
        if (_instance == 0) {
            _instance = new GameScaleArrow;
        }

        return _instance;
    }

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

        // Игра на удержание
        if (LMouseDown && button->GetStatus()) arrow->adddelta();

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
                // Игра на быстрые нажатия
                //arrow->adddelta();
            }
        }

        if (bar[currbar]->GetStatus()) {
            if (currbar > 1) {
                DestroyGame();
                ChangeState(mgr, GameMenu::Instance());

                return false;
            }
            else {
                green->Next();
                currbar += 1;
            }
        }

        float angle = arrow->getalpha();
        float limangle[4] = {
            1.55,
            1.20,
            1.08,
            0.90
        };

        if (angle < limangle[currbar] + 0.20 && angle > limangle[currbar + 1]) {
            green->SetDark();
            bar[currbar]->Start();
        }
        else {
            green->SetNormal();
            bar[currbar]->Stop();
        }

        if (!LMouseDown && button->GetStatus()) { button->Pop(); }

        return false;
    }

    bool Render(GameManager* mgr) {
        hge->Gfx_BeginScene();
        hge->Gfx_Clear(0xFFFFFFFF);

        if (Initialize) {
            button->Show();

            scale->Show();

            if (scale->GetStatus()) {
                green->Show();
                arrow->Show();

                for (int i=0; i<3; i++)
                    bar[i]->Show();
            }

            gui->Render();
        }

        hge->Gfx_EndScene();
        return false;
    }

    void InitGame() {
        Initialize = true;
        currbar = 0;

        CreateGUI();

        button = new GameButton("./cfg/scale&arrow/button.cfg");
        arrow = new Arrow("./cfg/scale&arrow/arrow.cfg");
        scale = new Scale("./cfg/scale&arrow/scale.cfg");
        green = new Green("./cfg/scale&arrow/green.cfg");

        bar[0] = new Bar("./cfg/scale&arrow/bar1.cfg");
        bar[1] = new Bar("./cfg/scale&arrow/bar2.cfg");
        bar[2] = new Bar("./cfg/scale&arrow/bar3.cfg");
    }

    void DestroyGame() {
        Initialize = false;

        DestroyGUI();

        delete button;
        delete arrow;
        delete scale;
        delete green;

        for (int i=0; i<3; i++)
            delete bar[i];
    }

protected:
    GameScaleArrow() {
        LMouseDown = false;
        RMouseDown = false;

        Initialize = false;
    }

private:
    static GameState* _instance;

    bool Initialize;

    bool LMouseDown;
    bool RMouseDown;

    GameButton* button;

    Arrow* arrow;
    Scale* scale;
    Green* green;
    Bar*   bar[3];

    int currbar;
};

#endif
