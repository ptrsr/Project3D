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
	switchButton1 = 3
};

enum Effect {
	splash,
	speed,
	slow
};

#endif // !ENUMS_H
