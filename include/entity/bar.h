#ifndef BAR_H
#define BAR_H

extern HGE* hge;

class Bar : public Base
{
public:
    Bar(char* cfgFile) {
        Init(cfgFile);

        empty = hge->Texture_Load("./images/textures/scale&arrow/barEmpty.png");
        filler = hge->Texture_Load("./images/textures/scale&arrow/barFiller.png");

        bar_empty = new hgeSprite(empty, 0, 0, 5, 94);
        bar_empty->SetHotSpot(5.0/2, 0.0);

        bar_filler = new hgeSprite(filler, 0, 0, 3, 1);
        bar_filler->SetHotSpot(3.0/2, 1.0/2);

        fillcounter = 0;
        time = 0;

        Stop();
    }

    ~Bar() {
        Destroy();

        delete bar_filler;
        delete bar_empty;

        hge->Texture_Free(empty);
        hge->Texture_Free(filler);
    }

    void Show() {
        time += hge->Timer_GetDelta();

        if (time > 1.0) {
            if (timer && fillcounter < 90)
                fillcounter += 5;

            if (!timer && fillcounter > 0 && fillcounter < 90)
                fillcounter -= 5;

            time = 0;
        }

        if (fillcounter < 90) {
            anim->SetFrame(0);
        }
        else anim->SetFrame(1);

        anim->Render(current.x, current.y);
        bar_empty->Render(
            current.x,
            current.y + 5
        );

        for (int i=0; i<fillcounter; i++)
            bar_filler->Render(current.x, current.y + 6 + 90 - i);
    }

    void Start() { timer = true; }
    void Stop() { timer = false; }

    bool GetStatus() {
        if (fillcounter < 90)
            return false;
        else return true;
    }

private:
    HTEXTURE empty;
    HTEXTURE filler;

    hgeSprite* bar_empty;
    hgeSprite* bar_filler;

    int fillcounter;

    float time;

    bool timer;
};

#endif
