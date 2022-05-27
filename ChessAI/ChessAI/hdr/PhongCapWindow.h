#ifndef PHONGCAPWINDOW_H
#define PHONGCAPWINDOW_H

#include "Window.h"

class Piece;
class Player;
class PhongCapWindow : public Window{
public:
	Piece * piece[5];
public:
	PhongCapWindow(Player * player);
	~PhongCapWindow();
public:
	char getPiece();
};

#endif
