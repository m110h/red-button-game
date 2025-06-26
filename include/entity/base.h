#ifndef BASE_CLASS_ENTITY_H
#define BASE_CLASS_ENTITY_H

using std::string;
using std::ifstream;

extern HGE* hge;

/**
    \ Базовый класс для игровых сущностей
*/
class Base
{
    public:

        Base() {}
       ~Base() {}

        bool Init(char* cfgFile) {
            ifstream ifs(cfgFile);

            string switcher;
            while (ifs >> switcher) {
                if (switcher == "TextureName") {
                    ifs >> switcher;
                    for (unsigned int j=0; j<switcher.length(); j++) {
                        TName[j] = switcher[j];
                    }

                    TName[switcher.length()] = 0;
                }

                if (switcher == "AnimFrames") ifs >> Frames;
                if (switcher == "AnimFps") ifs >> Fps;
                if (switcher == "TextureWidth") ifs >> Width;
                if (switcher == "TextureHeight") ifs >> Height;
                if (switcher == "CurrentPos") ifs >> current.x >> current.y;
                if (switcher == "BoundingRadius") ifs >> BoundingRadius;
            }

            ifs.close();

            texture = hge->Texture_Load(TName);
            if (!texture)
                return false;

            anim = new hgeAnimation(
                texture,
                Frames,
                Fps,
                0,
                0,
                Width,
                Height
            );

            anim->SetHotSpot(Width/2, Height/2);

            return true;
        }

        void Destroy() {
            delete anim;
            hge->Texture_Free(texture);
        }

        hgeVector GetPosition() { return current; }
        float GetBoundingRadius() { return BoundingRadius; }

    protected:
        hgeAnimation* anim;
        hgeVector current;

    private:
        HTEXTURE texture;
        char  TName[256];
        float Fps, Width, Height;
        int   Frames;

        float BoundingRadius;
};

#endif
