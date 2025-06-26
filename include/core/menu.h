#ifndef MENU_H
#define MENU_H

/**
    \todo
        Класс главного меню
*/
class GameMenu : public GameState
{
public:
    static GameState* Instance() {
        if (_instance == 0) {
            _instance = new GameMenu;
        }

        return _instance;
    }

    bool Frame(GameManager*);
    bool Render(GameManager*);

protected:
    GameMenu();

private:
    static GameState* _instance;
    int lastid;
};

#endif
