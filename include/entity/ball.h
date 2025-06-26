#ifndef BALL_H
#define BALL_H

extern HGE* hge;

class Ball : public Base
{
public:

    Ball(char* cfgFile) {
        Init(cfgFile);

        /// default settings
        begin = current;
        accel = 0;
        speed = 10;

        Time = 0;

        /// config file settings
        using namespace std;

        ifstream ifs(cfgFile);

        string switcher;
        while (ifs >> switcher) {
            if (switcher == "AccelMove")
                ifs >> accel;

            if (switcher == "SpeedMove")
                ifs >> speed;
        }

        ifs.close();

        processed = false;
    }

    ~Ball() { Destroy(); }

    void Show() {
        if (processed) {
            Time += hge->Timer_GetDelta();

            current.x = begin.x;
            current.y = begin.y + Time*speed + (accel*powf(Time, 2))/2;

            if (sqrt(powf(current.x - begin.x, 2) + powf(current.y - begin.y, 2)) > 600 - begin.y) {
                Stop();
                return;
            }

            anim->Render(current.x, current.y);
        }
    }

    void Start() {
        if (!processed) {
            processed = true;
        }
    }

    void Stop() {
        processed = false;
        current = begin;
        Time = 0;
    }

    hgeVector GetPosition() { return current; }

private:
    bool  processed;
    float Time, speed, accel;

    hgeVector begin;
    hgeVector p;
};

#endif
