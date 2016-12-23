﻿#ifndef __SIMON_H__
#define __SIMON_H__


#include "GObject.h"
#include "GSprite.h"
#include "GCamera.h"
#include "Box.h"
#include "Whip.h"


#define SIMON_SPRITE L"simon.png"

#define SIMON_WIDTH			32
#define SIMON_HEIGHT		64
#define SIMON_SPEED			1.2f
#define SIMON_JUMP_SPEED	5.0f
#define SIMON_Animation_RATE	ANIMATIONRATE
#define TYPE TypeGame::Boss_Simon
#define SIMON_JUMPMAX 64
#define TIME_CANT_HURT 300
#define HURT_FALL_SPEED 1.2f
enum STATE
{
	IS_STANDING = 1, // đứng
	IS_JOGGING = 2, //đi bộ
	IS_SITTING = 3, // NGỒI
	IS_JUMPING = 4, //NHẢY 
	IS_UPING = 5, // LÊN CẦU THANG
	IS_DOWNING = 6, // XUỐNG CẦU THANG
	IS_FIGHTING = 7, // ĐÁNH
	IS_JUMPFIGH = 8, //NHẢY LÊN ĐÁNH
	IS_SITFIGHT = 9, // NGỒI ĐÁNH
	IS_UPFIGHT = 10, //LÊN CẦU THANG VỪA ĐÁH
	IS_DOWNFIGHT =11, // VỪA XUỐNG CẦU THANG VỪA ĐÁNH.
	IS_PASSGATE =12, // QUA MANF.
	IS_FALLING = 13,
	CANT_HURT=14,
	ON_BRICK_MOVING=15
};

class Simon : public GObject {
private:

	static Simon* _simon;

	Box _currentMoving;
	int _drawhurt;
	int _stateCurrent; //trạng thái hiện tại
	bool _isMoveleft; // quay qua trái hay k
	bool _isMoveright;
	bool _isOnStair; // dang o tren cau thang hay k
	bool _isJumping; //dang nhay
	bool _isFalling;// dang roi xuong
	bool _isFighting; // danh danh nhau nek
	bool _isSiting;
	bool _canGoStair;
	bool _canGoRight;
	bool _canGoLeft;
	bool _cantHurt;
	bool _isOnStair2;
	bool _isOnStair1;
	int _keyDown; // lưu phím vừa được nhấn.
	int _keyUp;
	float _tmp = 0;
	int _currentStateGame;// cai nay la state cua game. ko phai cua simon
	int _currentLV;
	int _lastState;
	int _hp;
	int _bossHP = 16;
	int _heart;
	int _timeCantHurt;
	int _life=3;
public:
	GSprite* _sptrite;
	static Simon* getCurrentSimon();
	bool reset = false;
	int xDestinate;
	int yDestinate;
	bool onGoto;

	Simon(int x, int y);
	void MoveUpdate(float deltatime);
	void SetFrame(float deltattime);
	void InputUpdate(float deltatime);
	void Update(float deltatime);
	void MoveState();
	void ChangeState(int state);
	void ChangeState(float deltatime){ 
		_isFighting = false; 
		SetFrame(deltatime); 
		//this->_stateCurrent = this->_lastState;
	}
	void Jump();
	void Fight();
	void Murder(){
		_hp = 0;
	}
	int GetState(){
		return _stateCurrent;
	}
	void Draw();
	void Heal(int more){ 
		this->_heart += more;
	}
	void Hurt(int damage){
		this->_hp -= damage;
	}
	int getHeart(){ return _heart; }
	int getHP(){ return _hp; }
	bool isFighting(){ return _isFighting; }
	bool isFalling(){ return _isFalling; }
	bool isMoveRight(){ return _isMoveright; }
	bool isMoveLeft(){ return _isMoveleft; }
	void isMoveRight(bool tamp){ _isMoveright = tamp; }
	void isMoveLeft(bool tamp){ _isMoveleft=tamp; }
	bool isOnStair2(){ return _isOnStair2; }
	void isOnStair2(bool tamp){ _isOnStair2 = tamp; }
	bool isOnStair1(){ return _isOnStair1; }
	void isOnStair1(bool tamp){ _isOnStair1 = tamp; }
	bool canGoStair(){ return _canGoStair; }
	void canGoStair(bool tamp){ _canGoStair = tamp; }
	bool isOnStair(){ return _isOnStair; }
	void isOnStair(bool tamp){ _isOnStair = tamp; }
	bool canGoLeft(){ return _canGoLeft; }
	void canGoLeft(bool tamp){ _canGoLeft = tamp; }
	bool canGoRight(){ return _canGoRight; }
	void canGoRight(bool tamp){ _canGoRight = tamp; }
	bool cantHurt(){ 
		return _cantHurt; 
	}
	int getCurrentLV(){
		return _currentLV;
	}
	void setBossHP(int hp){
		_bossHP = hp;
	}
	int getBossHP(){
		return _bossHP;
	}
	int getLife(){
		return _life;
	}
	void setBox(Box box){ this->_currentMoving = box; }
	void nextLV(){
		_currentLV = 3;
		_x = 1373;
		_y = 1030;
	}
	void Reset();
	void Cheat();
	Simon();
	~Simon();
};

#endif