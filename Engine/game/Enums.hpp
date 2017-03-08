#ifndef ENUMS_H
#define ENUMS_H

enum Id {
	empty,
	p1,
	p2,
	p3,
	p4
};

enum PType {
	score
};

enum Dir {
	none,
	up,
	down,
	left,
	right
};

enum SFX {
	playerJump1 = 0, 
	backButton1 = 1,
	enterButton1 = 2,
	switchButton1 = 3,
	grabPickup1 = 4,
	usespeedPickup1 = 5,
	usesplashPickup1 = 6,
	connectionFailed1 = 7,
	connectionSucces1 = 8

};

enum Effect {
	splash,
	speed
};

#endif // !ENUMS_H
