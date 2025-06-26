#ifndef RAIL_H
#define RAIL_H

extern HGE* hge;

class Rail : public Base
{
public:

    Rail(char* cfgFile) {
        Init(cfgFile);

        init  = false;
        count = 0;
    }

    ~Rail() { Destroy(); }

    void Show() {
        if (!init) {
            anim->Render(current.x, current.y);
            for (int i=1; i<count; i++) {
                anim->Render(current.x+i, current.y);
                anim->Render(current.x-i, current.y);
            }

            ++count;
            if (count == 300) init = true;
        }
        else {
            anim->Render(current.x, current.y);
            for (int i=1; i<300; i++) {
                anim->Render(current.x+i, current.y);
                anim->Render(current.x-i, current.y);
            }
        }
    }

    bool GetStatus() { return init; }

private:
    bool init;
    int  count;
};

#endif
