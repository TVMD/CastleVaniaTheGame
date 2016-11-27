﻿#include "Roast.h"



Roast::Roast(int x, int y, int x2, int y2) :
Item(TYPE, x, y, x2, y2)
{
	GTexture* texture = new GTexture(_SPRITE, 1, 1, 1);
	_sprite = new GSprite(texture, _ANIMATE_RATE);
	this->SetFrame(0); // nếu chỉ có 1 ô hình thì quất thế này luôn cho nhanh.
}
Roast::~Roast(){
	if (_sprite != NULL){
		delete _sprite;
	}
}