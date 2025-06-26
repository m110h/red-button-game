#ifndef HOLE_H
#define HOLE_H

extern HGE* hge;

class Hole : public Base
{
public:

    Hole(char* cfgFile) { Init(cfgFile); }
    ~Hole() { Destroy(); }

    void Show() {
        anim->Update(hge->Timer_GetDelta());
        anim->Render(current.x, current.y);
    }

    void Open() {
        if (!anim->IsPlaying()) {
            anim->SetMode(HGEANIM_FWD | HGEANIM_NOLOOP | HGEANIM_PINGPONG);
            anim->Play();
        }
    }

private:
};

#endif
