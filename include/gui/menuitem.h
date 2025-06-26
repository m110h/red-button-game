#ifndef MENU_ITEM_H
#define MENU_ITEM_H

extern HGE* hge;

class hgeGUIMenuItem : public hgeGUIObject
{
public:
	hgeGUIMenuItem( int _id, char* TextureName, char* SoundName, float _x, float _y, float _width, float _height ) {
        id = _id;

        x = _x;
        y = _y;

        Texture = hge->Texture_Load(TextureName);
        Sound = hge->Effect_Load(SoundName);

        anim = new hgeAnimation(
            Texture,
            2,
            1,
            0,
            64,
            _width,
            _height
        );

        anim->SetHotSpot(_width/2, _height/2);

        scale = 1.0;

        bStatic = false;
        bVisible = true;
        bEnabled = true;

        Selected = false;

        rect.Set(_x-_width/2, _y-_height/2, _x+_width/2, _y+_height/2);
	}

	~hgeGUIMenuItem() {
	    delete anim;

	    hge->Texture_Free(Texture);
	    hge->Effect_Free(Sound);
	}

	void Render() { anim->RenderEx(x, y, 0, scale, scale); }

	void Update(float dt) {}
	void Enter() {}
	void Leave() {}

	bool IsDone() {
	    return true;
    }

	void Focus(bool bFocused) {
        if(bFocused)
        {
            hge->Effect_Play(Sound);
            scale = 1.2;
        }
        else
        {
            scale = 1.0;
        }
    }

	void MouseOver(bool bOver) {
	    if(bOver) { gui->SetFocus(id); }
    }

	bool MouseLButton(bool bDown) {
        if(!bDown)
        {
            return true;
        }
        else
        {
            Selected = !Selected;
            SetStatus(Selected);
            return false;
        }
    }

	bool KeyClick(int key, int chr) {
        if(key==HGEK_ENTER || key==HGEK_SPACE) {
            MouseLButton(true);
            return MouseLButton(false);
        }

        return false;
    }

    bool GetStatus() { return Selected; }

    void SetStatus(bool flag) {
        Selected = flag;

        if (flag == true) anim->SetFrame(1);
        if (flag == false) anim->SetFrame(0);
    }

private:
    HTEXTURE    Texture;
	HEFFECT		Sound;

    hgeAnimation* anim;

    float x, y;
    float scale;

	bool Selected;
};

#endif
