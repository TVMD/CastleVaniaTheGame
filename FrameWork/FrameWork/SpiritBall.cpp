#include "SpiritBall.h"



SpiritBall::SpiritBall(int x, int y, int x2, int y2) :
Item(TYPE, x, y, x2, y2)
{
	GTexture* texture = new GTexture(_SPRITE, 2, 1, 2);
	_sprite = new GSprite(texture, _ANIMATE_RATE);
	this->SetFrame(0);
}
void SpiritBall::SetFrame(float deltaTime)
{
#pragma region __XU_LY_CHUYEN_DOI_FRAME__
	this->_sprite->_start = 0;
	this->_sprite->_end = 1;
#pragma endregion
}


SpiritBall::~SpiritBall(){
	if (_sprite != NULL){
		delete _sprite;
	}
}