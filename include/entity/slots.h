#ifndef SLOTS_H
#define SLOTS_H

class Slots : public Base
{
public:
    Slots(char* cfgFile) {
        Init(cfgFile);
    }

    ~Slots() { Destroy(); }

    void Show() {
        anim->RenderEx(current.x, current.y, 0, 0.9, 0.9);
    }
};

#endif
