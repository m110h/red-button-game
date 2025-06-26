#ifndef ABSTRACT_H
#define ABSTRACT_H

extern HGE* hge;

/**
    \todo
        Абстрактный класс для всех возможных состояний ::
            * главное меню
            * все мини игры
            * что-нибудь ещё
*/
class GameState
{
public:
    virtual bool Frame(GameManager*) = 0;
    virtual bool Render(GameManager*) = 0;

protected:
    void ChangeState(GameManager* mgr, GameState* s) {
        mgr->ChangeState(s);
    }

    void CreateGUI() {
        Cursor = hge->Texture_Load("./images/cursors/cursor.png");
        Cursor_Spr = new hgeSprite(Cursor, 0, 0, 32, 32);

        gui = new hgeGUI();
        gui->SetCursor(Cursor_Spr);
    }

    void DestroyGUI() {
        delete gui;
        delete Cursor_Spr;

        hge->Texture_Free(Cursor);
    }

private:
    HTEXTURE   Cursor;
    hgeSprite* Cursor_Spr;

protected:
    hgeGUI*    gui;
};

#endif
