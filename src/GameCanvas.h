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

	static const int SCORE_ENEMY = 10, SCORE_HELI = 50;

	enum {
		ANIM_IDLE, ANIM_RUNAIM, ANIM_IDLEAIM, ANIM_JUMPAIM, ANIM_DEATH
	};

	enum {
		BULLETOWNER_CHARACTER, BULLETOWNER_ENEMY
	};

	enum {
		ENEMYSTATE_GOTOTARGET, ENEMYSTATE_INTARGET
	};

    static const int tiletypenum = 16;
    static const int objecttypenum = 14;
    static const int characteranimationnum = 5;
    static const int charactermaxframenum = 10;
    static const int teleportframenum = 10;
    static const int coinframenum = 10;

    void loadMap();
    void moveCharacter();
    void moveEnemies();
    void moveHeli();
    void moveBullets();
    void moveCamera();
    void updateCollectables();
    void updateEffects();
    void drawPlatform();
    void drawCollectables();
    void drawHeli();
    void drawEnemies();
    void drawCharacter();
    void drawBullets();
    void drawEffects();
    void drawGui();
    bool isOverGroundTile();
    void generateBullet(float bulletx, float bullety, float bulletdx, float bulletdy, int bulletOwner, float bulletRot);
    void generateCollectedGoldIcon(float goldIconx, float goldIcony, float goldIcondx, float goldIcondy, float goldIconRot);
	bool checkCollision(int xLeft1, int yUp1, int xRight1, int yBottom1, int xLeft2, int yUp2, int xRight2, int yBottom2);
	void chooseTeleportingEnemies();

	gApp* root;
	gImage background;
	gImage tileimage[tiletypenum];
	gImage objectimage[objecttypenum];
	gImage character[characteranimationnum][charactermaxframenum];
	gFont fpsfont;
	gImage bulletimage;
	gDatabase db;
	gImage enemyimage[characteranimationnum][charactermaxframenum];
	gImage teleport[teleportframenum];
	gImage healthbar, healthbarframe, healthbarbackground;
	gFont gameoverfont;
	gImage deadenemy;
	gImage coinimage[coinframenum];
	gImage arrow;
	gImage taskimage;
	gImage bulletbar;
	gImage heli;
	gImage heliexplosioneffect;
	gImage goldbar;
	gFont goldfont;
	gFont scorefont;
	gFont scoreoverenemyfont;
	gImage scorebar;
//	Character c;
	float cx, cy;
	float cw, ch, cscaleratio;
	float cgapx, cgapy;
	std::vector<std::vector<int>> tile;
	std::vector<std::vector<int>> object;

	int charactertype;
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
	std::vector<int> elookdir;
	std::vector<int> eex;
	float espeed;
	std::vector<int> eanim, eframe, eframecount;
	std::vector<int> edistance;
	bool bulletdestroyed;
	std::vector<int> teleportcounter;
	std::vector<int> teleportframeno;
	std::vector<int> teleportx, teleporty, teleportnewx, teleportnewy;
	int teleportjumpno;
	int emaxy;
	std::vector<std::vector<float>> etarget;
	std::vector<int> etargetdir;
	std::vector<int> estate;
	std::vector<std::vector<float>> ediff;
	std::vector<int> etargetcounter;
	int etargetcounterlimit;
	int healthbarframex, healthbarframey;
	int healthbarx, healthbary;
	int chealth, chealthmax;
	int gameoverx, gameovery;
	int mapscale;
	int coinnum;
	int coinmaxw;
	std::vector<int> coinx, coiny;
	std::vector<bool> coinavailable;
	std::vector<int> coinframeno, coincounter;
	int coincounterlimit;
	int coinimagedx[coinframenum];
	int arrowx, arrowy, arrowrot;
	int taskx, tasky;
	int totaltasknum, completedtasknum;
	int bulletnum, maxbulletnum;
	int bulletbarx, bulletbary, bulletbarframex, bulletbarframey;
	int helix, heliy;
	bool heliavailable;
	int helidx;
	int helicounter;
	int helihealth, helihealthinitial;
	int helibarx, helibary, helibary2, helibary3, helibarw, helibarh;
	int helibarw2;
	int shadowbarh;
	int explosionframeno, explosionframenum;
	int explosionscale, explosionframew, explosionframeh, explosionscalew, explosionscaleh;
	int explosiondx, explosiondy;
	int goldbarx, goldbary;
	int score;
	int scorex, scorey;
	int scoreoe;
	std::vector<float> scoreoex, scoreoey;
	int gfx, gfy, collectedgoldnum;
	int scorebarx, scorebary;
	std::vector<std::vector<float>> collectedgoldicon;
	int goldiconw, goldiconh, goldiconscale;
	float goldiconspeed;
};

#endif /* GAMECANVAS_H_ */
