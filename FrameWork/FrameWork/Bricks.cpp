#include"Bricks.h"

Bricks::Bricks(){}
Bricks::~Bricks(){}
Bricks::Bricks(int x, int y, int w, int h)
:GObject(11, x, y, w, h){
	if (w > h){
		int size = w / BRICK_WIDTH;
		for (int i = 0; i < size; i++){
			Brick* tamp = new Brick(x + i*BRICK_WIDTH, y);
			_listBrick.push_back(tamp);
		}
		if ((w%BRICK_WIDTH) != 0){
			Brick* tamp = new Brick(x + size*BRICK_WIDTH + (w%BRICK_WIDTH) - BRICK_WIDTH, y);
			_listBrick.push_back(tamp);
		}
	}
	else
	{
		int size = h / BRICK_HEIGHT;
		for (int i = 0; i < size; i++){
			Brick* tamp = new Brick(x + i*BRICK_HEIGHT, y);
			_listBrick.push_back(tamp);
		}
		if ((h%BRICK_HEIGHT) != 0){
			Brick* tamp = new Brick(x + size*BRICK_HEIGHT + (h%BRICK_HEIGHT) - BRICK_HEIGHT, y);
			_listBrick.push_back(tamp);
		}
	}
	_box = Box(x, y, w, h, 0, 0);
}
void Bricks::Draw(){

	for each (Brick * b in _listBrick)
		b->Draw();
}