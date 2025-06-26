#ifndef TAPE_H
#define TAPE_H

extern HGE* hge;

/**
    \todo
        Параметры конструктора :
            TextureName - имя текстуры, соответственно;
            x, y - координаты левого верхнего угла прямоугольника анимации;
            qwidth, qheight - ширина и высота прямоугольника;
            twidth, theight - ширина и высота текстуры
                                (ВАЖНО!!! должны быть степенями 2);
            frames - количество кадров в текстуре;
            speed - скорость анимации;

        qwidth должно быть равно twidth.
*/
class Tape
{
public:
    Tape(char* cfgFile) {
        std::ifstream ifs(cfgFile);

        std::string switcher;
        while (ifs >> switcher) {
            if (switcher == "QuadWidth") ifs >> qwidth;
            if (switcher == "QuadHeight") ifs >> qheight;
            if (switcher == "TextureWidth") ifs >> twidth;
            if (switcher == "TextureHeight") ifs >> theight;
            if (switcher == "Frames") ifs >> frames;
            if (switcher == "Speed") ifs >> speed;

            if (switcher == "TetxureName") {
                ifs >> switcher;
                for (unsigned int i=0; i<switcher.length(); i++) {
                    tname[i] = switcher[i];
                }

                tname[switcher.length()] = 0;
            }

            if (switcher == "QuadX") ifs >> x;
            if (switcher == "QuadY") ifs >> y;
        }

        ifs.close();

        quad = new hgeQuad;
        quad->tex = hge->Texture_Load(tname);

        quad->blend = BLEND_DEFAULT;
		for(int i=0;i<4;i++) {
			quad->v[i].z=0.5f;
			quad->v[i].col=0xFFFFFFFF;
		}

        quad->v[0].x = x; quad->v[0].y = y;
        quad->v[1].x = x + qwidth; quad->v[1].y = y;
        quad->v[2].x = x + qwidth; quad->v[2].y = y + qheight;
        quad->v[3].x = x; quad->v[3].y = y + qheight;

        frameheight = theight/float(frames);
        playing = false;

        tx = 0;
        ty = 0;
    }

    ~Tape() {
        hge->Texture_Free(quad->tex);
        delete quad;
    }

    void Update(float dt) {
        if (!playing) {
            double y;

            float p = (GetFrame()*frameheight - frameheight/2)/theight - fabsf(modf(quad->v[0].ty, &y));

            if (fabsf(p) > 0.001f)
                ty -= 0.001f;
        }
        else {
            ty -= dt * speed;
        }

        quad->v[0].tx = tx; quad->v[0].ty = ty;
        quad->v[1].tx = tx + qwidth/twidth; quad->v[1].ty = ty;
        quad->v[2].tx = tx + qwidth/twidth; quad->v[2].ty = ty + qheight/theight;
        quad->v[3].tx = tx; quad->v[3].ty = ty + qheight/theight;
    }

    void Render() { hge->Gfx_RenderQuad(quad); }

    void Play() { playing = true; }
    void Stop() { playing = false; }
    bool GetStatus() { return playing; }

    /**
        \todo
            возвращает текущий кадр
    */
    int GetFrame() {
        double y;
        float _ty_ = fabsf(modf(quad->v[0].ty, &y));

        for (int i=1; i<=frames; i++) {
            if (
                _ty_ >= float(i-1)*frameheight/theight &&
                _ty_ < float(i)*frameheight/theight
            ) return i;
        }

        return -1;
    }

    int GetFrames() { return frames; }

private:
    hgeQuad* quad;

    float twidth, qwidth;
    float theight, qheight;
    float speed;
    float frameheight;
    float x, y, tx, ty;

    int frames;

    bool playing;
    char tname[256];
};

#endif
