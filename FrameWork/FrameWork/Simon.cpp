#include "Simon.h"



Simon* Simon::_simon = 0;
Simon::Simon(int x, int y) :
GObject(TYPE, x, y, SIMON_WIDTH, SIMON_HEIGHT)
{
	_isMoveleft = false;
	_isMoveright = false;
	_isOnStair = false;
	_isJumping = false;
	_isFalling = true;
	_stateCurrent = STATE::IS_FALLING;
	_vy = GRAVITY;
	_box = Box(x, y, SIMON_WIDTH, SIMON_HEIGHT,_vx,_vy);
	
	GTexture* simonTT = new GTexture(SIMON_SPRITE, 8, 3, 24);
	_sptrite = new GSprite(simonTT, ANIMATIONRATE);
}

void Simon::MoveUpdate(float deltaTime)
{
#pragma region __XU_LY_CHUYEN_DONG__
	//Kiem tra doi tuong co nhay duoc hay ko
	if (this->_isOnStair)
	{
		this->_x += int(this->_vx * deltaTime);
	}
	else
	{
		

		/*
		}*/
		
		
		if (this->_stateCurrent == STATE::IS_STANDING)
		{
			this->_vx = 0;
			//this->_vy = 0;
		}
		else
		{
			if (this->_isFalling){
				_vy = GRAVITY;
				this->_y += int(_vy*deltaTime);
			}
		}
		if (this->_isMoveleft)
		{
			if (this->_vx < 0)
			{
				this->_x += int(this->_vx * deltaTime);
			}
		}
		else if (this->_isMoveright)
		{
			if (this->_vx > 0)
			{
				this->_x += int(this->_vx * deltaTime);
			}
		}
		if (this->_stateCurrent == STATE::IS_JUMPING){
			this->_y += int(this->_vy * deltaTime);
			this->_x += int(this->_vx * deltaTime);
			if (_vy < 0)
				_vy += 0.05;
			else {
				this->_stateCurrent = STATE::IS_FALLING;
				_isFalling = true;
				_isJumping = false;
			}
		}
		
	}
#pragma endregion
	_box.x = _x;
	_box.y = _y;
	_box.vx = _vx;
	_box.vy = _vy;
}

void Simon::SetFrame(float deltaTime)
{
#pragma region __XU_LY_CHUYEN_DOI_FRAME__
	if (!this->_isOnStair) //dang o duoi dat
	{
		switch (this->_stateCurrent)
		{
		case STATE::IS_STANDING:
		case STATE::IS_FALLING:
		{
								   this->_sptrite->_start = 0;
								   this->_sptrite->_end = 0;
								   break;
		}
		case STATE::IS_JOGGING://Chay bo
		{
								   this->_sptrite->_start = 0;
								   this->_sptrite->_end = 3;
								   break;
		}
		case STATE::IS_JUMPING: 
		case STATE::IS_SITTING :
		{
								  this->_sptrite->_start = 4;
								  this->_sptrite->_end = 4;
								  break;
		}
		case STATE::IS_FIGHTING:
		{
									this->_sptrite->_start = 5;
									this->_sptrite->_end = 7;
									break;
		}
		case STATE::IS_PASSGATE	:
		{
									this->_sptrite->_start = 9;
									this->_sptrite->_end = 9;
									break;
		}
		case STATE::IS_SITFIGHT:
		{
								   this->_sptrite->_start = 15;
								   this->_sptrite->_end = 17;
								   break;
		}
		default:
		{
				   break;
		}
		}
	}
	else //tren cau thang
	{
		switch (this->_stateCurrent)
		{
		case STATE::IS_UPING:
		{
								this->_sptrite->_start = 12;
								this->_sptrite->_end = 13;
								break;
		}
		case STATE::IS_DOWNING:
		{
								  this->_sptrite->_start = 10;
								  this->_sptrite->_end = 11;
								  break;
		}
		case STATE::IS_UPFIGHT:
		{
								  this->_sptrite->_start = 21;
								  this->_sptrite->_end = 23;
								  break;
		}
		case STATE::IS_DOWNFIGHT:
		{
									this->_sptrite->_start = 18;
									this->_sptrite->_end = 20;
									break;
		}
		default:
			break;
		}
	}
#pragma endregion
}

void Simon::InputUpdate(float deltaTime)
{
#pragma region __KHONG_CO_SU_KIEN_PHIM__
	if (!this->_isJumping)
	{
		this->_vx = 0;
		//this->_vy = 0;
		
		if (!this->_isOnStair)
		{
			//this->_stateCurrent = STATE::IS_FALLING;
		}
		else
		{
			
		}
		if (this->_stateCurrent != STATE::IS_FALLING) _stateCurrent = STATE::IS_STANDING;
	}
#pragma endregion


#pragma region __XU_LY_PHIM_NHAY__
	if (KeyBoard::getCurrentKeyBoard()->IsKeyDown(DIK_SPACE) )
	{
		if (!_isJumping){
			this->_stateCurrent = STATE::IS_JUMPING;
			_vy = -0.3;
			_isJumping = true;
			if (KeyBoard::getCurrentKeyBoard()->IsKeyDown(DIK_RIGHT))
				this->_vx = SIMON_SPEED;
			if (KeyBoard::getCurrentKeyBoard()->IsKeyDown(DIK_LEFT))
				this->_vx = -SIMON_SPEED;
		}
		
	}
#pragma endregion

#pragma region __XU_LY_PHIM_DI_QUA_TRAI_HOAC_PHAI__
	if ((KeyBoard::getCurrentKeyBoard()->IsKeyDown(DIK_LEFT) || KeyBoard::getCurrentKeyBoard()->IsKeyDown(DIK_RIGHT))
		&& this->_stateCurrent != STATE::IS_JUMPING&& this->_stateCurrent != STATE::IS_FALLING)
	{
 		this->_stateCurrent = STATE::IS_JOGGING;
		if (KeyBoard::getCurrentKeyBoard()->IsKeyDown(DIK_RIGHT))
		{
			this->_isMoveright = true;
			this->_isMoveleft = false;
			this->_vx = SIMON_SPEED;
		}
		else
		{
			this->_isMoveright = false;
			this->_isMoveleft = true;
			this->_vx = -SIMON_SPEED;
		}
	}
#pragma endregion

}

void Simon::Update(float deltatime){
	this->InputUpdate(deltatime);
	this->MoveUpdate(deltatime);
	this->SetFrame(deltatime);
	this->_sptrite->Update(deltatime);
}

void Simon::Draw(){
	if (this->_isMoveright){
		this->_sptrite->DrawFlipX(_x, _y);
	}
	else{
		this->_sptrite->Draw(_x, _y);
	}
}
void Simon::ChangeState(int state){
	this->_stateCurrent = state;
	switch (state) {
	case STATE::IS_STANDING:
		this->_isFalling = false; 
		this->_isJumping = false; break;
	case STATE::IS_FALLING: this->_isFalling = true;
		this->_isJumping = false;  break;
	}
}

Simon* Simon::getCurrentSimon(){
	if (!_simon)
		_simon = new Simon(50, 50);
	return _simon;
}




