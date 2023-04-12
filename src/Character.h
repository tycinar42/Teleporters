/*
 * Character.h
 *
 *  Created on: 29 Haz 2022
 *      Author: 40tyc
 *
 */

#ifndef SRC_CHARACTER_H_
#define SRC_CHARACTER_H_

class Character {
public:
	Character();
	virtual ~Character();

	float x, y;
	float w, h, scaleratio;
	float gapx, gapy;
	int animationno, frameno;
	int framecounter, framecounterlimit;
	float dx, dy;
	float speed;
	int direction;
	bool moving, turning;
	int ex;
	int jumpspeed;
	int jumplimit, groundlimit;
};

#endif /* SRC_CHARACTER_H_ */
