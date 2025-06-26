#ifndef ICONS_H
#define ICONS_H

class Icons : public Base
{
public:
    Icons(char* cfgFile) {
        Init(cfgFile);

        Enabled = false;
        PlayEffect = false;

        time1 = 1.0f;
        time2 = 1.5f;

        dcolor = anim->GetColor() - 0x80000000;
        ecolor = anim->GetColor();

        SndEffect = hge->Effect_Load("./sounds/endlev.ogg");
    }

    ~Icons() {
        hge->Effect_Free(SndEffect);
        Destroy(); }

    void Show() {
        if (!Enabled) {
            anim->SetColor(dcolor);
            anim->Render(current.x, current.y);
        }
        else {
            anim->SetColor(ecolor);

            if (!PlayEffect) {
                hge->Effect_Play(SndEffect);
                PlayEffect = true;
            }

            if (time1 < time2) {
                time1 += hge->Timer_GetDelta();
                anim->RenderEx(current.x, current.y, 0, time1, time1);
            }
            else if (time2 > 1.0) {
                time2 -= hge->Timer_GetDelta();
                anim->RenderEx(current.x, current.y, 0, time2, time2);
            }
            else anim->Render(current.x, current.y);
        }
    }

    void SetStatus(bool status) {
        Enabled = status;
        if (!Enabled) {
            PlayEffect = false;
            time1 = 1.0f;
            time2 = 1.5f;
        }
    }

    bool GetStatus() { return Enabled; }

private:
    bool Enabled;
    bool PlayEffect;

    float time1, time2;

    DWORD dcolor;
    DWORD ecolor;

    HEFFECT SndEffect;
};

#endif
