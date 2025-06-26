#ifndef BASKET_H
#define BASKET_H

extern HGE* hge;

class Basket : public Base
{
public:

    Basket(char* cfgFile) {
        Init(cfgFile);

        count = 0;
        time  = 0;
        scale = 0;

        /// config file settings
        using namespace std;

        ifstream ifs(cfgFile);

        string switcher;
        while (ifs >> switcher) {
            if (switcher == "SpeedMove") ifs >> speed;
            if (switcher == "DeltaSpeed") ifs >> deltas;
            if (switcher == "LeftPoint") ifs >> begin.x >> begin.y;
            if (switcher == "RightPoint") ifs >> end.x >> end.y;
        }

        ifs.close();
    }

    ~Basket() { Destroy(); }

    void Show(bool flag) {
        if (flag && scale > 1.0f) {
            if ((begin - current).Length() < (begin - end).Length()) {
                float dt = hge->Timer_GetDelta();
                time += dt;

                hgeVector p = end - begin;
                p.Normalize();

                current.x = begin.x + p.x*time*(speed);
                current.y = begin.y;
            }
            else {
                end = begin;
                begin = current;
                time = 0;

                if (accelflag) {
                    speed += deltas;
                    accelflag = false;
                }
            }

            anim->Render(current.x, current.y);
        }
        else {
            if (scale < 1.0)
                scale += 0.003;

            anim->RenderEx(current.x, current.y, 0, scale, scale);
        }
    }

    void NextFrame() {
        count += 1;
        accelflag = true;
        if (count > 4) count = 0;

        anim->SetFrame(count);
    }

    int GetCurrentFrame() { return count; }

private:
    int count;
    float speed, time, scale, deltas;
    bool accelflag;

    hgeVector begin, end;
};

#endif
