 /*
 * GameCanvas.h
 *
 *  Created on: May 6, 2020
 *      Author: noyan
 */

#ifndef GAMECANVAS_H_
#define GAMECANVAS_H_

#include "gBaseCanvas.h"
#include "gApp.h"
#include "gImage.h"
#include "gFont.h"
#include "gDatabase.h"
//#include "Character.h"


class GameCanvas : public gBaseCanvas {
public:
	GameCanvas(gApp* root);
	virtual ~GameCanvas();

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void charPressed(unsigned int codepoint);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseScrolled(int x, int y);
	void mouseEntered();
	void mouseExited();

	void showNotify();
	void hideNotify();

private:
	static const int KEY_NONE = 0, KEY_D = 1, KEY_A = 2, KEY_W = 4, KEY_S = 8;

	enum {
		ANIM_IDLE, ANIM_RUNAIM, ANIM_IDLEAIM, ANIM_JUMPAIM, ANIM_DEATH
	};

    static const int tiletypenum = 16;
    static const int objecttypenum = 14;
    static const int characteranimationnum = 5;
    static const int charactermaxframenum = 10;

    void loadMap();
    void moveCharacter();
    void moveEnemies();
    void moveBullets();
    void moveCamera();
    bool isOverGroundTile();
    void generateBullet(float bulletx, float bullety, float bulletdx, float bulletdy);
	bool checkCollision(int xLeft1, int yUp1, int xRight1, int yBottom1, int xLeft2, int yUp2, int xRight2, int yBottom2);

	gApp* root;
	gImage background;
	gImage tileimage[tiletypenum];
	gImage objectimage[objecttypenum];
	gImage character[characteranimationnum][charactermaxframenum];
	gFont fpsfont;
	gImage bulletimage;
	gDatabase db;
	gImage enemyimage[characteranimationnum][charactermaxframenum];
//	Character c;
	float cx, cy;
	float cw, ch, cscaleratio;
	float cgapx, cgapy;
	std::vector<std::vector<int>> tile;
	std::vector<std::vector<int>> object;

	int animationframenum[characteranimationnum];
	int characterfirstframeno[characteranimationnum];
	int canimationno, cframeno;
	int characterframecounter, framecounterlimit;
	float cdx, cdy;
	float cspeed;
	int cdirection;
	int keystate, pressedkey;
	bool cmoving, cturning;
	int cex;
	int cjumpspeed;
	int cjumplimit, cgroundlimit;
	float tilescaleratio;
	int tilew, tileh;
	int mapw;
	float camx;
	int camleftmargin, camrightmargin;
	float biw, bih;
	std::vector<std::vector<float>> bullets;
	float bulletspeed;
	bool objectcollidable[objecttypenum];
	int horcollidingobjectno, vercollidingobjectno;
	int enemynum;
	std::vector<std::vector<float>> epos;
	std::vector<int> edir;
	std::vector<int> eex;
	float espeed;
	std::vector<int> eanim, eframe, eframecount;
	std::vector<int> edistance;
};

#endif /* GAMECANVAS_H_ */
