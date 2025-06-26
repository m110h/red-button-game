#ifndef GREEN_H
#define GREEN_H

extern HGE* hge;

class Green : public Base
{
public:
    Green(char* cfgName) {
        Init(cfgName);

        ColorStatus = false;

        cnormal = anim->GetColor() - 0x70000000;
        cdark = anim->GetColor();

        frame = 0;
    }

    ~Green() { Destroy(); }

    void Show() { anim->Render(current.x, current.y); }

    void Next() {
        if (++frame > 2)
            frame = 0;

        anim->SetFrame(frame);
    }

    void SetDark() {
        if (!ColorStatus) {
            anim->SetColor(cdark);
            ColorStatus = true;
        }
    }

    void SetNormal() {
        if (ColorStatus) {
            anim->SetColor(cnormal);
            ColorStatus = false;
        }
    }

private:
    DWORD cnormal;
    DWORD cdark;

    bool ColorStatus;
    int frame;

};

#endif
