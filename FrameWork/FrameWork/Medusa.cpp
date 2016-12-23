﻿#include "Medusa.h"

Medusa::Medusa(int x, int y) :
GObject(1, x, y, _medusaWIDTH, _medusaHEIGHT)
{
	_isMoveleft = false;
	_isMoveright = true;
	last_x = x;
	_isSleep = true;
	_box = Box(x, y, _medusaWIDTH, _medusaHEIGHT, _vx, _vy);
	GTexture* texture = new GTexture(_medusaSPRITE, 5, 1, 5);
	_sprite = new GSprite(texture, 7);
	_tamp = 0;
	_hp = _medusaHP;
	_flag1 = false;
	_timelive = 0;
	_vx = 0;
	_vy = 0;
	_timedelay = _timeDelay;
	_dx = 0;
	_old_x = x;
	_comeback = false;
	_checkspirit = false;
	_timespirit = 50;

}

void Medusa::MoveUpdate(float deltaTime)
{
#pragma region __XU_LY_CHUYEN_DONG__

	if (Simon::getCurrentSimon()->_x < (this->_x + 32) && abs((Simon::getCurrentSimon()->_y) - _y) <= 70)
	{
		flag = true;
	}

	if (this->_isSleep){
		return;
	}


	int final_y = Simon::getCurrentSimon()->_y;
	int final_x = Simon::getCurrentSimon()->_x;

	if (_x <= final_x)
	{
		_isMoveright = true;
		_isMoveleft = false;

	}
	else
	{
		_isMoveleft = true;
		_isMoveright = false;

	}


	if (_isMoveright)
	{
		if (Simon::getCurrentSimon()->_x + 66 <= _x)
		{
			_comeback = true;
		}
		if (_x <= last_x)
		{
			_comeback = false;

		}

	}

	if (_isMoveleft)
	{
		if (Simon::getCurrentSimon()->_x + 33 >= _x)
		{
			_comeback = false;
		}
		if (_x >= last_x)
		{
			_comeback = true;

		}
	}

	if (!_comeback)
	{
		_vx = _medusaSPEED;
	}
	else
	{
		_vx = -_medusaSPEED;

	}
	//if (_isMoveright)
	//{
	//	//Xác định hướng di chuyển của Medusa
	//	//Chỉ được đổi hướng khi chạm vào Simon
	//	if (_x <= final_x && check == false)
	//	{
	//		_point_right = true;
	//		_point_left = false;
	//		check = true;
	//	}
	//	else
	//	if (_x > final_x && check == false)
	//	{
	//		_point_right = false;
	//		_point_left = true;
	//		check = true;
	//	}

	//	//Di chuyển qua Simon
	//	if (_point_right)
	//	{
	//		if (Simon::getCurrentSimon()->_x <= _x + 32)
	//		{
	//			_point_right = false;
	//			_point_left = true;
	//		}
	//		else
	//			_vx = _medusaSPEED;
	//	}
	//	if (_point_left)
	//	{
	//		if (_x <= last_x)
	//		{
	//			_point_right = true;
	//			_point_left = false;
	//		}
	//		else
	//			_vx = -_medusaSPEED;
	//	}
	//	if (_isMoveleft)
	//	{
	//		//Xác định hướng di chuyển của Medusa
	//		//Chỉ được đổi hướng khi chạm vào Simon
	//		if (_x > final_x && check == false)
	//		{

	//			_point_right = false;
	//			_point_left = true;
	//			check = true;
	//		}
	//		else
	//		if (_x > final_x && check == false)
	//		{
	//			_point_right = true;
	//			_point_left = false;
	//			check = true;
	//		}

	//		//Di chuyển qua Simon
	//		if (_point_right)
	//		{


	//			if (_x <= last_x)
	//			{
	//				_point_right = false;
	//				_point_left = true;
	//			}
	//			else
	//				_vx = -_medusaSPEED;
	//		}
	//		if (_point_left)
	//		{
	//			if (Simon::getCurrentSimon()->_x <= _x)
	//			{

	//				_point_right = true;
	//				_point_left = false;
	//			}
	//			else
	//				_vx = _medusaSPEED;
	//		}
	//	}




#pragma region Xử lý delay

	if (_dx >= 32)
	{
		_timedelay -= deltaTime;
		if (_timedelay < 0)
		{
			_timedelay = _timeDelay;
			_dx = 0;
		}
		else
			_vx = 0;
	}

#pragma endregion
	/*if (Simon::getCurrentSimon()->_x < (this->_x + 32) && abs((Simon::getCurrentSimon()->_y)-_y)<=70)
	{
		flag = true;
	}

	if (Simon::getCurrentSimon()->_x >= _x)
		_isMoveleft = false;
	else
		_isMoveleft = true;



	if (_isMoveleft){

		if (Simon::getCurrentSimon()->_x - _x <= -128)
		{
			if (_vx < 0)
				_vx = -0.5f;
			else
				_vx = 0.5f;
		}
		if (Simon::getCurrentSimon()->_x + 32 >= _x)
		{
			if (_vx < 0)
				_vx = 0.5f;
			else
				_vx = -0.5f;

		}
		if (_x >= last_x && _vx>0)
		{
			if (_vx < 0)
				_vx = 0.5f;
			else
				_vx = -0.5f;

		}
	}
	else{
		if (Simon::getCurrentSimon()->_x - _x <= 128)
		{
			if (_vx < 0)
				_vx = -0.5f;
			else
				_vx = 0.5f;

		}

		if (Simon::getCurrentSimon()->_x <= _x + 32)
		{
			if (_vx < 0)
				_vx = 0.5f;
			else
				_vx = -0.5f;

		}
		if (_x <= last_x && _vx<0)
		{
			if (_vx < 0)
				_vx = 0.5f;
			else
				_vx = -0.5f;

		}
	}*/

	this->_x += int(this->_vx * deltaTime);
	this->_tamp += (this->_vx * deltaTime / 10);
	
	if ((_y-final_y)>40)
		this->_y -= int(3 * sin(float(0.5*deltaTime)));
	else
		this->_y += int(3 * sin(float(_tamp)));
	
	_dx += (abs(_old_x - _x));
	_old_x = _x;
#pragma endregion
	_box.x = _x;
	_box.y = _y;
	_box.vx = _vx;
	_box.vy = _vy;
}

void Medusa::SetFrame(float deltaTime)
{
#pragma region __XU_LY_CHUYEN_DOI_FRAME__
	if (this->_isSleep){
		this->_sprite->_start = 4;
		this->_sprite->_end = 4;
	}
	else{
		this->_sprite->_start = 0;
		this->_sprite->_end = 3;
	}
#pragma endregion
}

void Medusa::Update(float deltatime){
	//if (_hp == 0) {
	//	this->_isDead = true;
	//	this->_timeDeath += deltatime;
	//	this->_spriteDeath->Update(deltatime);
	//}

	if (this->_isDead){
		if (!_checkspirit)
		{
			_nextBall = new NextBall(250, 275);
			_checkspirit = true;
		}
		else
		{
			if (!_eatspirit)
			{
				_nextBall->Update(deltatime);
			}
			else
			{
				//xử lý qua màn
				return;
			}
		}


		return;
	}

	if (_hp == 0) {
		this->_isDead = true;
		this->_timeDeath += deltatime;
		this->_spriteDeath->Update(deltatime);
	}

	if (_isSleep==false)
		_timesnake += deltatime;
	if (_timesnake > 600)
		_snake = true;
	if (_snake == true)
	{
		if (_time1 == 0)
		{			
			_snake1 = new Snake(_x, _y + 48);
		}
		_time1 += deltatime;

		if (snake1 == true)
		{
			_snake1->Update(deltatime);
		}
		if (_time1 >= 800)
		{
			_snake1 = new Snake(_x + 32, _y + 48);
			snake1 = false;
			_time1 = 0;
		}
	}


	if (flag == true && _timesleep >= 0)
		_timesleep -= deltatime;
	if (_timesleep < 0)
		ChangeState(2);

	this->MoveUpdate(deltatime);
	this->SetFrame(deltatime);
	this->_sprite->Update(deltatime);
}

void Medusa::ChangeState(int state){
	if (state == MEDUSASTATE::IS_SLEEPING){
		this->_isSleep = true;
	}
	else
	if (state == MEDUSASTATE::IS_LIVING){
		this->_isSleep = false;
	}
}

void Medusa::Draw(){
	if (this->_isDead){
		if (_timeDeath <= DEATH_TIME)
		{
			this->DrawDeath();

			//Vẽ Spirit Ball
			if (_checkspirit)
			{
				_nextBall->Draw();
			}
		}
		return;
	}
	this->_sprite->Draw(_x, _y);
	if (_time1 > 0)
	{
		_snake1->Draw();
		snake1 = true;
	}
}

void Medusa::Collistion(float deltaTime){
	float x, y;

	if (_isDead){
		if (!_eatspirit)
		{
			if (_checkspirit == true && swepyAABB->AABB(_nextBall->_box, Simon::getCurrentSimon()->_box, x, y)){
				swepyAABB->AABB(_nextBall->_box, Simon::getCurrentSimon()->_box, x, y);
				_eatspirit = true;
			}
		}
		return;
	}
	if (_isSleep == false)
	{
		if (Simon::getCurrentSimon()->isFighting() 
			|| Boomerang::getCurrentBoomerang()->isFlying() 
			|| WeaponKnife::getCurrentKnife()->isFlying()){
			if (swepyAABB->AABB(this->_box, Whip::getCurrentWhip()->_box, x, y)
				|| swepyAABB->AABB(Boomerang::getCurrentBoomerang()->_box, this->_box, x, y)
				|| swepyAABB->AABB(WeaponKnife::getCurrentKnife()->_box, this->_box, x, y)
				){
				if (_hp > 0)
					_hp--;
			}
		}

		if (Simon::getCurrentSimon()->GetState() == STATE::CANT_HURT)
			return;

		if (swepyAABB->AABB(this->_box, Simon::getCurrentSimon()->_box, x, y)){
			swepyAABB->AABB(this->_box, Simon::getCurrentSimon()->_box, x, y);
			Simon::getCurrentSimon()->ChangeState(STATE::CANT_HURT);
			if (_isMoveleft)
				_comeback = false;
			if (_isMoveright)
				_comeback = true;
		}

		if (snake1 == true && swepyAABB->AABB(_snake1->_box, Simon::getCurrentSimon()->_box, x, y)){
			swepyAABB->AABB(_snake1->_box, Simon::getCurrentSimon()->_box, x, y);
			Simon::getCurrentSimon()->ChangeState(STATE::CANT_HURT);
			snake1 = false;
		}
	}
	else
		return;
}


Medusa::~Medusa(){
	if (_sprite != NULL){
		delete _sprite;
	}
}
