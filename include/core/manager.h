#ifndef MANAGER_H
#define MANAGER_H

/**
    \todo
        �������� ��������� ����
*/

class GameState;
class GameManager
{
public:
    GameManager();

    bool Frame();
    bool Render();

private:
    friend class GameState;
    void ChangeState(GameState* s) {
        _state = s;
    }

private:
    GameState* _state;

    bool DisplayMode;
};

#endif
