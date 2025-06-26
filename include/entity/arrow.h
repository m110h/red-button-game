#ifndef ARROW_H
#define ARROW_H

extern HGE* hge;

class Arrow : public Base
{
public:
    Arrow(char* cfgFile) {
        Init(cfgFile);

        using namespace std;

        ifstream ifs(cfgFile);

        string switcher;
        while (ifs >> switcher) {
            if (switcher == "AlphaAngle") ifs >> alpha;
            if (switcher == "AngleMin") ifs >> min;
            if (switcher == "AngleMax") ifs >> max;

            if (switcher == "PushAccel") ifs >> pushaccel;
            if (switcher == "DeltaAccel") ifs >> deltaaccel;
            if (switcher == "DeltaLimit") ifs >> limit;

            if (switcher == "Center") ifs >> center.x >> center.y;
        }

        ifs.close();

        delta = 0;
    }

    ~Arrow() { Destroy(); }

    void Show() {
        Move();
        anim->RenderEx(
            current.x,
            current.y,
            (current-center).Angle() + 3.14/2,
            1.0,
            1.0
        );
    }

    void Move() {
        if (((alpha + delta) < max) && ((alpha + delta) > min)) {
            hgeVector r = current - center;

            float length = r.Length();

            r.x = r.x*cos(delta) + r.y*sin(delta);
            r.y = r.y*cos(delta) - r.x*sin(delta);

            current = r*(length/r.Length()) + center;

            alpha += delta;
        }

        delta += deltaaccel;

        if (fabsf(delta) > limit) {
            int sign;

            if (delta >= 0) sign = 1;
                else sign = -1;

            delta = limit*sign;
        }
    }

    void  adddelta() { delta += pushaccel; }
    float getalpha() { return alpha; }

private:

    float alpha;
    float delta;
    float deltaaccel;
    float limit;
    float pushaccel;

    float min;
    float max;

    hgeVector center;
};

#endif

/**
    180*alpha/PI - радианы в градусы
    alpha*PI/180 - градусы в радианы
*/
