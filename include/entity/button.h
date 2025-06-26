#ifndef BUTTON_H
#define BUTTON_H

extern HGE* hge;

class GameButton : public Base
{
public:

    GameButton(char* cfgFile) {
        Init(cfgFile);

        pressed = false;
        moving = false;
    }

    ~GameButton() { Destroy(); }

    void Push() {
        if (!anim->IsPlaying()) {
            pressed = true;
            anim->SetMode(HGEANIM_FWD | HGEANIM_NOLOOP | HGEANIM_NOPINGPONG);
            anim->Play();
        }
    }

    void Pop() {
        if (!anim->IsPlaying()) {
            pressed = false;
            anim->SetMode(HGEANIM_REV | HGEANIM_NOLOOP | HGEANIM_NOPINGPONG);
            anim->Play();
        }
    }

    void Show() {
        if (moving) Move();

        anim->Update(hge->Timer_GetDelta());
        anim->Render(current.x, current.y);
    }

    /**
        \todo
            _alpha - ����, �� ���. ����� ���������
            _delta - ��������� ������� ��������
            _acceleration - ������� ���������
            _limit - ���������� ������� ��������
            _center - ����� ����������, �� ���������� ���. ���������� ��������

            ���� _delta > 0, �� �������� ������ ������� �������,
            ����� �� ������� �������
    */
    void StartMove(float _alpha, float _delta, float _acceleration, float _limit, hgeVector _center) {
        if (moving) return;

        moving = true;

        alpha = _alpha;
        delta = _delta;
        acceleration = _acceleration;
        limit = _limit;

        center = _center;
    }

    bool GetStatus() { return pressed; }

private:
    void PlaySndEffect() {}

    /**
        \todo
            p�������������� �������� ����� �� ����������
    */
    void Move() {
        hgeVector r = current - center;

        float length = r.Length();

        r.x = r.x*cos(delta) + r.y*sin(delta);
        r.y = r.y*cos(delta) - r.x*sin(delta);

        current = r*(length/r.Length()) + center;

        if (fabsf(delta) < limit)
            delta *= acceleration;

        alpha -= fabsf(delta);

        if (alpha < 0) moving = false;
    }

private:
    bool pressed;
    bool moving;

    float alpha;
    float delta;
    float acceleration;
    float limit;

    hgeVector center;
};

#endif
