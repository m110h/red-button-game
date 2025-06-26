#ifndef SPLASH_H
#define SPLASH_H

extern HGE* hge;

class Splash : public Base
{
public:

    Splash(char* cfgFile) {
        Init(cfgFile);
    }

    ~Splash() { Destroy(); }

    void Show() {
        if (anim->IsPlaying()) {
            anim->Update(hge->Timer_GetDelta());
            anim->RenderEx(current.x, current.y, 0, 1.5, 1.5);
        }
    }

    void Play(hgeVector p) {
        if (!anim->IsPlaying()) {
            anim->SetMode(HGEANIM_FWD | HGEANIM_NOLOOP | HGEANIM_NOPINGPONG);
            anim->Play();

            current = p;
        }
    }
};

#endif
