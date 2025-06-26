#ifndef GAME_BANDIT_H
#define GAME_BANDIT_H

extern HGE* hge;

/**
    \todo
        мини игра Bandit
*/
class GameBandit : public GameState
{
public:
    static GameState* Instance() {
        if (_instance == 0) {
            _instance = new GameBandit;
        }

        return _instance;
    }

    bool Frame(GameManager* mgr) {
        if (!Initialize) InitGame();

        static float delay;

        float dt = hge->Timer_GetDelta();
        if (Checking) delay += dt;

        gui->Update(dt);
        for (int i=0; i<3; i++) tape[i]->Update(dt);

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

                if (!Checking)
                if (!tape[0]->GetStatus() && !tape[1]->GetStatus() && !tape[2]->GetStatus()) {
                    for (int i=0; i<3; i++)
                        tape[i]->Play();
                }
                else {
                    for (int i=0; i<3; i++) {
                        if (tape[i]->GetStatus()) {
                            tape[i]->Stop();
                            if (i == 2) {
                                Checking = true;
                                delay = 0.0f;
                            }

                            break;
                        }
                    }
                }
            }
        }

        if (Checking) CheckingBanditMachine(delay);

        if (!LMouseDown && button->GetStatus()) { button->Pop(); }
/*
        if (
            icons[0]->GetStatus() &&
            icons[1]->GetStatus() &&
            icons[2]->GetStatus() &&
            icons[3]->GetStatus()) {
                DestroyGame();
                ChangeState(mgr, GameMenu::Instance());

                return false;
        }
*/
        return false;
    }

    bool Render(GameManager* mgr) {
        hge->Gfx_BeginScene();
        hge->Gfx_Clear(0xFFFFFFFF);

        if (Initialize) {
            button->Show();

            for (int i=0; i<4; i++) icons[i]->Show();
            for (int i=0; i<3; i++) tape[i]->Render();

            slots->Show();
            gui->Render();
        }

        hge->Gfx_EndScene();
        return false;
    }

    void CheckingBanditMachine(float delay)
    {
        if (delay < 1.5f) return;

        int f0 = tape[0]->GetFrame();
        int f1 = tape[1]->GetFrame();
        int f2 = tape[2]->GetFrame();

        if ((f0 == f1) && (f0 == f2) && (f1 == f2)) {
            int frame = tape[0]->GetFrame() + 1;
            if (frame > tape[0]->GetFrames())
                frame -= tape[0]->GetFrames();

            switch (frame - 1) {
                case 0: icons[0]->SetStatus(true); break;
                case 1: icons[1]->SetStatus(true); break;
                case 2: icons[2]->SetStatus(true); break;
                case 3: icons[3]->SetStatus(true); break;
            }
        }

        Checking = false;
    }

    void InitGame() {
        Initialize = true;
        Checking = false;

        CreateGUI();

        button = new GameButton("./cfg/bandit/button.cfg");

        slots = new Slots("./cfg/bandit/slots.cfg");

        icons[0] = new Icons("./cfg/bandit/icons1.cfg");
        icons[1] = new Icons("./cfg/bandit/icons2.cfg");
        icons[2] = new Icons("./cfg/bandit/icons3.cfg");
        icons[3] = new Icons("./cfg/bandit/icons4.cfg");

        tape[0] = new Tape("./cfg/bandit/tape1.cfg");
        tape[1] = new Tape("./cfg/bandit/tape2.cfg");
        tape[2] = new Tape("./cfg/bandit/tape3.cfg");
    }

    void DestroyGame() {
        Initialize = false;

        DestroyGUI();

        delete slots;
        for (int i=0; i<4; i++) delete icons[i];
        for (int i=0; i<3; i++) delete tape[i];

        delete button;
    }

protected:
    GameBandit() {
        LMouseDown = false;
        RMouseDown = false;

        Initialize = false;
    }

private:
    static GameState* _instance;

    bool Initialize;

    bool LMouseDown;
    bool RMouseDown;

    bool Checking;

    GameButton* button;

    Slots* slots;
    Icons* icons[4];
    Tape*  tape[3];
};

#endif
