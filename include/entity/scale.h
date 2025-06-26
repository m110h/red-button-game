#ifndef SCALE_H
#define SCALE_H

extern HGE* hge;

class Scale : public Base
{
public:
    Scale(char* cfgFile) {
        Init(cfgFile);

        alpha = 0x00000000;
        anim->SetColor(anim->GetColor() - 0xF0000000);

        Initialize = false;
        InitTime = 0;
    }

    ~Scale() { Destroy(); }

    void Show() {
        if (!Initialize)
            incalpha();

        anim->Render(current.x, current.y);
    }

    void incalpha() {
        if (alpha < 0xF0000000) {
            InitTime += hge->Timer_GetDelta();
            if (InitTime < 0.07) return;

            InitTime = 0;
            DWORD color = anim->GetColor() - alpha;

            alpha += 0x10000000;
            anim->SetColor(color + alpha);
        }
        else Initialize = true;
    }

    void decalpha() {
        if (alpha > 0x00000000) {
            InitTime += hge->Timer_GetDelta();
            if (InitTime < 0.07) return;

            InitTime = 0;
            DWORD color = anim->GetColor() - alpha;

            alpha -= 0x10000000;
            anim->SetColor(color+alpha);
        }
        else Initialize = false;
    }

    bool GetStatus() { return Initialize; }

private:
    DWORD alpha;
    bool  Initialize;

    float InitTime;

};

#endif
