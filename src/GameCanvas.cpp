/*
 * GameCanvas.cpp
 *
 *  Created on: May 6, 2020
 *      Author: noyan
 */


#include "GameCanvas.h"


GameCanvas::GameCanvas(gApp* root) : gBaseCanvas(root) {
	this->root = root;
}

GameCanvas::~GameCanvas() {
}

void GameCanvas::setup() {
	gLogi("GameCanvas") << "setup";
	background.loadImage("tileset1/sky1.png");
	for(int i = 0; i < tiletypenum; i++) tileimage[i].loadImage("tileset1/Tile/" + gToStr(i + 1) + ".png");
	for(int i = 0; i < objecttypenum; i++) {
		std::string ono = gToStr(i + 1);
		if(i < 9) ono = "0" + ono;
		objectimage[i].loadImage("tileset1/Objects/0" + ono + ".png");
	}
	for(int i = 0; i < characteranimationnum; i++) characterfirstframeno[i] = 0;
	characterfirstframeno[ANIM_JUMPAIM] = 3;
	animationframenum[ANIM_IDLE] = 10;
	animationframenum[ANIM_RUNAIM] = 8;
	animationframenum[ANIM_IDLEAIM] = 10;
	animationframenum[ANIM_JUMPAIM] = 3;
	animationframenum[ANIM_DEATH] = 10;
	for(int i = 0; i < characteranimationnum; i++) {
		std::string ipath = "2_Char_Idle_0";
		if(i == ANIM_RUNAIM) ipath = "2_Char_Run_Aim_0";
		else if(i == ANIM_IDLEAIM) ipath = "2_Char_Idle_Aim_0";
		else if(i == ANIM_JUMPAIM) ipath = "2_Char_Jump_Aim_0";
		else if(i == ANIM_DEATH) ipath = "2_Char_Dead_0";
		for(int j = characterfirstframeno[i]; j < characterfirstframeno[i] + animationframenum[i]; j++) {
			std::string ino = gToStr(j);
			if(j < 10) ino = "0" + ino;
//			gLogi("GameCanvas") << "Loaded i:" << i << ", j:" << j;
			character[i][j - characterfirstframeno[i]].loadImage("characters1/2/" + ipath + ino + ".png");
		}
	}
	for(int i = 0; i < characteranimationnum; i++) {
		std::string ipath = "11_Char_Idle_0";
		if(i == ANIM_RUNAIM) ipath = "11_Char_Run_Aim_0";
		else if(i == ANIM_IDLEAIM) ipath = "11_Char_Idle_Aim_0";
		else if(i == ANIM_JUMPAIM) ipath = "11_Char_Jump_Aim_0";
		else if(i == ANIM_DEATH) ipath = "11_Char_Dead_0";
		for(int j = characterfirstframeno[i]; j < characterfirstframeno[i] + animationframenum[i]; j++) {
			std::string ino = gToStr(j);
			if(j < 10) ino = "0" + ino;
//			gLogi("GameCanvas") << "Loaded i:" << i << ", j:" << j;
			enemyimage[i][j - characterfirstframeno[i]].loadImage("characters1/11/" + ipath + ino + ".png");
		}
	}
	bulletimage.loadImage("characters1/Bullet/1_Bullet_Bullet 1_000.png");
	loadMap();
	fpsfont.loadFont("FreeSans.ttf", 16);
	for(int i = 0; i < teleportframenum; i++) teleport[i].loadImage("teleport_images/Teleport_00" + gToStr(i) + ".png");
	healthbar.loadImage("healthbar/bar.png");
	healthbarframe.loadImage("healthbar/barframe.png");
	healthbarbackground.loadImage("healthbar/barbackground.png");
	gameoverfont.loadFont("soupofjustice.ttf", 200);
	cscaleratio = 1;
	cw = character[0][0].getWidth() / cscaleratio;
	ch = character[0][0].getHeight() / cscaleratio;
	cgapx = cw / 2.35f;
	cgapy = ch / 11.2f;
	cx = 400;
	cy = getHeight() - tileimage[1].getHeight() / 2 - ch + cgapy;
	canimationno = ANIM_IDLE;
	cframeno = 0;
	characterframecounter = 0;
	framecounterlimit = 4;
	cspeed = 6.0f;
	cdx = 0.0f;
	cdy = 0.0f;
	cdirection = 1;
	cmoving = false;
	cturning = false;
	cjumpspeed = -12;
	cgroundlimit = 1016;
	cjumplimit = cgroundlimit + cjumpspeed * 200;
	tilescaleratio = 2;
	tilew = tileimage[1].getWidth() / tilescaleratio;
	tileh = tilew;
	mapw = 4000;
	camx = 0;
	camleftmargin = getWidth() / 4;
	camrightmargin = getWidth() * 3 / 4;
	biw = bulletimage.getWidth();
	bih = bulletimage.getHeight();
	bulletspeed = cspeed * 4.0f;
	enemynum = 10;
	teleportjumpno = 5;
	emaxy = getHeight() - tileimage[1].getHeight() / 2 - ch + cgapy;
	for(int i = 0; i < enemynum; i++) {
		std::vector<float> ep;
		ep.push_back(gRandom(mapw - cw));
		//ep.push_back(getHeight() - tileimage[1].getHeight() / 2 - ch + cgapy);
		ep.push_back(gRandom(emaxy));
		epos.push_back(ep);
		edir.push_back(1);
		eex.push_back(0);
		eanim.push_back(ANIM_IDLEAIM);
		eframe.push_back(gRandom(animationframenum[ANIM_IDLEAIM]));
		eframecount.push_back(gRandom(framecounterlimit));
		edistance.push_back((cw + gRandom(cw * 2)));
		teleportcounter.push_back(-1);
		teleportx.push_back(0);
		teleporty.push_back(0);
		teleportnewx.push_back(0);
		teleportnewy.push_back(0);
		teleportframeno.push_back(0);
	}
	espeed = cspeed * 60 / 100;
	healthbarframex = healthbarframe.getWidth() / 8;
	healthbarframey = healthbarframex;
	healthbarx = healthbarframex + 69;
	healthbary = healthbarframey + 15;
	chealthmax = 100;
	chealth = chealthmax;
	gameoverx = (getWidth() - gameoverfont.getStringWidth("GAME OVER!")) / 2;
	gameovery = (getHeight() + gameoverfont.getStringHeight("GAME OVER!")) / 2;
}

void GameCanvas::update() {
	//gLogi("GameCanvas") << "update";
	moveCharacter();
	moveCamera();
	chooseTeleportingEnemies();
	moveEnemies();
	moveBullets();
}

void GameCanvas::draw() {
	//gLogi("GameCanvas") << "draw";
	drawPlatform();
	drawEnemies();
	drawCharacter();
	drawBullets();
	drawGui();
//	fpsfont.drawText("FPS: " + gToStr(root->getFramerate()), 20, 20);
}

void GameCanvas::moveCharacter() {
	cdx = 0.0f;
	cdy = -cjumpspeed;
	if(isOverGroundTile()) cdy = 0;
//	cdirection = 0;
	cmoving = false;
	cturning = false;
	if(keystate & KEY_D) {
		if(cdirection == -1) cturning = true;
		cdirection = 1;
		cmoving = true;
	} else if(keystate & KEY_A) {
		if(cdirection == 1) cturning = true;
		cdirection = -1;
		cmoving = true;
	}
	if(keystate & KEY_W) {
		cdy = cjumpspeed;
		if(canimationno != ANIM_JUMPAIM) cframeno = 0;
		canimationno = ANIM_JUMPAIM;
	} else if(keystate & KEY_S) {

	}

	if(cmoving && !cturning) cdx += cdirection * cspeed;

	// Character - Object collision test
	horcollidingobjectno = -1;
	vercollidingobjectno = -1;
	for(int i = 0; i < object.size(); i++) {
		if(objectcollidable[object[i][2]] && checkCollision(cx + camx + cdx, cy, cx + camx + cdx + cw / 1.26f, cy + ch / 1.093f, object[i][0], object[i][1] - objectimage[object[i][2]].getHeight(), object[i][0] + objectimage[object[i][2]].getWidth(), object[i][1])) {
			horcollidingobjectno = i;
		}
		if(objectcollidable[object[i][2]] && checkCollision(cx + camx, cy + cdy, cx + camx + cw / 1.26f, cy + cdy + ch / 1.093f, object[i][0], object[i][1] - objectimage[object[i][2]].getHeight(), object[i][0] + objectimage[object[i][2]].getWidth(), object[i][1])) {
			vercollidingobjectno = i;
		}
	}
	if(horcollidingobjectno != -1) {
		cdx = 0.0f;
	}
	if(vercollidingobjectno != -1) {
		cdy = 0.0f;
	}

	cx += cdx;
	cy += cdy;
	if(cy < 0) cy = 0;
	cex = 0;
	if(cdirection == -1) cex = 80;

	if(cdx != 0.0f || cdy != 0.0f) {
		if(cdy == 0.0f) {
			if(canimationno != ANIM_RUNAIM) cframeno = 0;
			canimationno = ANIM_RUNAIM;
		}
	} else {
		if(canimationno != ANIM_IDLE && canimationno != ANIM_IDLEAIM) cframeno = 0;
		if(canimationno != ANIM_IDLEAIM) canimationno = ANIM_IDLE;
	}

	characterframecounter++;
	if(characterframecounter >= framecounterlimit) {
		cframeno++;
		if(cframeno >= animationframenum[canimationno]) {
			cframeno = 0;
			if(canimationno == ANIM_IDLEAIM) canimationno = ANIM_IDLE;
		}
		characterframecounter = 0;
	}
//	if(canimationno == ANIM_JUMPAIM) gLogi("GC") << "f:" << cframeno;
}

void GameCanvas::moveCamera() {
	camleftmargin = getWidth() / 4;
	if(camx <= 0) camleftmargin = 0;
	camrightmargin = getWidth() * 3 / 4;
	if(camx + getWidth() >= mapw) camrightmargin = getWidth();

	if(cx <= camleftmargin || cx + cw >= camrightmargin) {
		cx -= cdx;
		camx += cdx;
		if(camx < 0) camx = 0;
		if(camx + getWidth() > mapw) camx = mapw - getWidth();
	}
}

void GameCanvas::moveEnemies() {
	for(int i = 0; i < enemynum; i++) {
		if(teleportcounter[i] > -1) {
			if(teleportcounter[i] == teleportjumpno) {
				epos[i][0] = teleportnewx[i];
				epos[i][1] = teleportnewy[i];
			}
			teleportcounter[i]++;
			teleportframeno[i]++;
			if(teleportcounter[i] >= teleportframenum) {
				teleportcounter[i] = -1;
				teleportframeno[i] = 0;
			}
		}

		if(eanim[i] != ANIM_DEATH) edir[i] = -gSign(epos[i][0] - (cx + camx));
		eex[i] = 0;
		if(edir[i] == -1) eex[i] = 80;

		float edx, edy;
		edx = 0.0f;
		edy = 0.0f;
		if(eanim[i] != ANIM_DEATH && epos[i][0] + cw >= camx && epos[i][0]< camx + getWidth()) {
			edx = edir[i] * espeed;
			edy = 2.0f;
		}

		//bool iscolliding = checkCollision(epos[i][0], epos[i][1], epos[i][0] + cw, epos[i][1] + ch,
		//		cx + camx - edistance[i], cy, cx + camx + cw + edistance[i], cy + ch);
		if(std::fabs(cx + camx + cw / 2 - (epos[i][0] + cw / 2)) < edistance[i]) {
			edx = 0.0f;
			edy = 0.0f;
		}

		epos[i][0] += edx;
		epos[i][1] += edy;
		if(epos[i][1] > emaxy) epos[i][1] = emaxy;

		eframecount[i]++;
		if(eframecount[i] >= framecounterlimit) {
			eframe[i]++;
			if(eframe[i] >= animationframenum[eanim[i]]) {
				if(eanim[i] == ANIM_DEATH) eframe[i] = animationframenum[ANIM_DEATH] - 1;
				else eframe[i] = 0;
			}
			eframecount[i] = 0;
		}

		if(edx != 0.0f || edy != 0.0f) {
			if(eanim[i] != ANIM_DEATH) {
				if(eanim[i] != ANIM_RUNAIM) eframe[i] = 0;
				eanim[i] = ANIM_RUNAIM;
			}
		} else {
			if(eanim[i] != ANIM_DEATH) {
				if(eanim[i] != ANIM_IDLEAIM) eframe[i] = 0;
				eanim[i] = ANIM_IDLEAIM;
				if((eframe[i] == 2 || eframe[i] == 5) && eframecount[i] == 0 && epos[i][0] + cw >= camx && epos[i][0] < camx + getWidth()) {
					float bulletx = epos[i][0] + (((edir[i] - 1) / -2) * cw / 3.925f) + (cw * edir[i] / 1.6f);
					float bullety = epos[i][1] + ch * 5 / 12;
					float bulletrot = std::atan2((cy + ch / 2) - (epos[i][1] + ch / 2), (cx + camx + cw / 2) - (epos[i][0] + cw / 2));
					float bulletdx = bulletspeed * std::cos(bulletrot);
					//float bulletdx = bulletspeed * edir[i];
					float bulletdy = bulletspeed * std::sin(bulletrot);
					generateBullet(bulletx, bullety, bulletdx, bulletdy, BULLETOWNER_ENEMY, gRadToDeg(bulletrot));
				}
			}
		}
	}
}

void GameCanvas::moveBullets() {
	for(int i = bullets.size() - 1; i >= 0; i--) {
		bullets[i][0] += bullets[i][2];
		bullets[i][1] += bullets[i][3];
		bullets[i][4]++;
		if(bullets[i][4] > 55) {
			bullets.erase(bullets.begin() + i);
			continue;
		}
		if(bullets[i][0] > camx + getWidth() || bullets[i][0] + bulletimage.getWidth() < camx) {
			bullets.erase(bullets.begin() + i);
			continue;
		}

		bulletdestroyed = false;
		if(bullets[i][5] == BULLETOWNER_CHARACTER) {
			for(int j = enemynum - 1; j >= 0; j--) {
				bool iscolliding = checkCollision(bullets[i][0], bullets[i][1], bullets[i][0] + bulletimage.getWidth(), bullets[i][1] + bulletimage.getHeight(),
						epos[j][0], epos[j][1], epos[j][0] + cw, epos[j][1] + ch);
				if(eanim[j] != ANIM_DEATH && iscolliding) {
					eanim[j] = ANIM_DEATH;
					eframe[j] = 0;

					bulletdestroyed = true;
					bullets.erase(bullets.begin() + i);
					break;
				}
			}
		} else if(bullets[i][5] == BULLETOWNER_ENEMY) {
			bool iscolliding = checkCollision(bullets[i][0], bullets[i][1], bullets[i][0] + bulletimage.getWidth(), bullets[i][1] + bulletimage.getHeight(),
					cx + camx, cy, cx + camx + cw, cy + ch);
			if(iscolliding) {
				chealth -= 5;
				if(chealth <= 0) {
					chealth = 0;
					gLogi("GameCanvas") << "OYUN BITTI";
				}
				bullets.erase(bullets.begin() + i);
				continue;
			}
		}

		if(bulletdestroyed == true) continue;
		for(int j = 0; j < object.size(); j++) {
			if(objectcollidable[object[j][2]] && checkCollision(bullets[i][0], bullets[i][1], bullets[i][0] + bulletimage.getWidth(), bullets[i][1] + bulletimage.getHeight(),
					object[j][0], object[j][1] - objectimage[object[j][2]].getHeight(), object[j][0] + objectimage[object[j][2]].getWidth(), object[j][1])) {
				bullets.erase(bullets.begin() + j);
				break;
			}
		}
	}
}

void GameCanvas::drawPlatform() {
	background.draw(0, 0, getWidth(), getHeight());
	for(int i = 0; i < tile.size(); i++) {
		tileimage[tile[i][2]].draw(tile[i][0] - camx, tile[i][1], tilew, tileh);
	}
	for(int i = 0; i < object.size(); i++) {
		objectimage[object[i][2]].draw(object[i][0] - camx, object[i][1] - objectimage[object[i][2]].getHeight());
	}
}

void GameCanvas::drawEnemies() {
	for(int i = 0; i < enemynum; i++) {
		enemyimage[eanim[i]][eframe[i]].draw(glm::vec2(epos[i][0] + eex[i] - camx, epos[i][1]), glm::vec2(edir[i] * cw, ch), 0.0f);
		if(teleportcounter[i] > -1) teleport[teleportcounter[i]].draw(teleportx[i] - camx, teleporty[i]);
	}
}

void GameCanvas::drawCharacter() {
	character[canimationno][cframeno].draw(glm::vec2(cx + cex, cy), glm::vec2(cdirection * cw, ch), 0.0f);
}

void GameCanvas::drawBullets() {
	for(int i = bullets.size() - 1; i >= 0; i--) {
		bulletimage.draw(bullets[i][0] - camx, bullets[i][1], biw, bih, bullets[i][6]);
	}
}

void GameCanvas::drawGui() {
	healthbarbackground.draw(healthbarx, healthbary);
	healthbar.drawSub(healthbarx, healthbary, healthbar.getWidth() * chealth / chealthmax, healthbar.getHeight(),
			healthbar.getWidth() - healthbar.getWidth() * chealth / chealthmax, 0, healthbar.getWidth() * chealth / chealthmax, healthbar.getHeight());
	healthbarframe.draw(healthbarframex, healthbarframey);
	if(chealth <= 0) {
		setColor(255, 220, 0);
		gameoverfont.drawText("GAME OVER!", gameoverx, gameovery);
		setColor(255, 255, 255);
	}
}

void GameCanvas::keyPressed(int key) {
//	gLogi("GameCanvas") << "keyPressed:" << key;
	if(key == G_KEY_ESC) exit(0);

	pressedkey = KEY_NONE;
	switch(key) {
	case G_KEY_D:
		pressedkey = KEY_D;
		break;
	case G_KEY_A:
		pressedkey = KEY_A;
		break;
	case G_KEY_W:
		pressedkey = KEY_W;
		break;
	case G_KEY_S:
		pressedkey = KEY_S;
		break;
	default:
		break;
	}
	keystate |= pressedkey;
}

void GameCanvas::keyReleased(int key) {
//	gLogi("GameCanvas") << "keyReleased:" << key;
	pressedkey = KEY_NONE;
	switch(key) {
	case G_KEY_D:
		pressedkey = KEY_D;
		break;
	case G_KEY_A:
		pressedkey = KEY_A;
		break;
	case G_KEY_W:
		pressedkey = KEY_W;
		break;
	case G_KEY_S:
		pressedkey = KEY_S;
		break;
	default:
		break;
	}
	keystate &= ~pressedkey;
}

void GameCanvas::charPressed(unsigned int codepoint) {
//	gLogi("GameCanvas") << "charPressed:" << gCodepointToStr(codepoint);
}

void GameCanvas::mouseMoved(int x, int y) {
//	gLogi("GameCanvas") << "mouseMoved" << ", x:" << x << ", y:" << y;
}

void GameCanvas::mouseDragged(int x, int y, int button) {
//	gLogi("GameCanvas") << "mouseDragged" << ", x:" << x << ", y:" << y << ", b:" << button;
}

void GameCanvas::mousePressed(int x, int y, int button) {
}

void GameCanvas::mouseReleased(int x, int y, int button) {
//	gLogi("GameCanvas") << "mouseReleased" << ", button:" << button;
	canimationno = ANIM_IDLEAIM;
	cframeno = 0;
	float bulletx = cx + camx + (((cdirection - 1) / -2) * cw / 3.925f) + (cw * cdirection / 1.6f);
	float bullety = cy + ch * 5 / 12;
	float bulletdx = bulletspeed * cdirection;
	float bulletdy = 0;
	generateBullet(bulletx, bullety, bulletdx, bulletdy, BULLETOWNER_CHARACTER, (1 - cdirection) * 90.0f);

}

void GameCanvas::mouseScrolled(int x, int y) {
//	gLogi("GameCanvas") << "mouseScrolled" << ", x:" << x << ", y:" << y;
}

void GameCanvas::mouseEntered() {
}

void GameCanvas::mouseExited() {
}

void GameCanvas::showNotify() {

}

void GameCanvas::hideNotify() {

}

bool GameCanvas::isOverGroundTile() {
	for(int i = 0; i < tile.size(); i++) {
		if(cy < tile[i][1] && cy + ch - cgapy >= tile[i][1] && ((cx + camx + cex >= tile[i][0] && cx + camx + cex < tile[i][0] + tilew) || (cx + camx + cex + cw - cgapx >= tile[i][0] && cx + camx + cex + cw - cgapx < tile[i][0] + tilew))) return 1;
	}
	return 0;
}

void GameCanvas::generateBullet(float bulletx, float bullety, float bulletdx, float bulletdy, int bulletOwner, float bulletRot) {
	std::vector<float> newbullet;
	newbullet.push_back(bulletx);
	newbullet.push_back(bullety);
	newbullet.push_back(bulletdx);
	newbullet.push_back(bulletdy);
	newbullet.push_back(0);
	newbullet.push_back(bulletOwner);
	newbullet.push_back(bulletRot);
	bullets.push_back(newbullet);
}

bool GameCanvas::checkCollision(int xLeft1, int yUp1, int xRight1, int yBottom1, int xLeft2, int yUp2, int xRight2, int yBottom2) {
	if(xLeft1 < xRight2 && xRight1 > xLeft2 && yBottom1 > yUp2 && yUp1 < yBottom2) {
		return true;
	}
	return false;
}

void GameCanvas::chooseTeleportingEnemies() {
	for(int i = 0; i < enemynum; i++) {
		if(eanim[i] != ANIM_IDLEAIM) continue;
		if(teleportcounter[i] > -1) continue;
		if(epos[i][0] + eex[i] < camx || epos[i][0] + eex[i] > camx + getWidth()) continue;
		if(gRandom(1000) > 1) continue;
		teleportcounter[i] = 0;
		teleportx[i] = epos[i][0] + ((enemyimage[0][0].getWidth() - teleport[0].getWidth()) / 2); //+ eex[i]
		teleporty[i] = epos[i][1] - (teleport[0].getHeight() - enemyimage[0][0].getHeight()) / 2;
//		teleportnewx[i] = teleportx[i];
		//int newdir = gSign((cx + camx) - epos[i][0]);
		teleportnewx[i] = camx + gRandom(getWidth() - cw);
		teleportnewy[i] = epos[i][1];
	}
}

void GameCanvas::loadMap() {
	/*std::vector<std::vector<int>> map = {
			{0, 1016, 1},
			{64, 1016, 1},
			{128, 1016, 1},
			{192, 1016, 1},
			{256, 1016, 1},
			{320, 1016, 1},
			{384, 1016, 1},
			{448, 1016, 1},
			{512, 1016, 1},
			{576, 1016, 1},
			{640, 1016, 1},
			{704, 1016, 1},
			{768, 1016, 1},
			{832, 1016, 1},
			{896, 1016, 1},
			{960, 1016, 1},
			{1024, 1016, 1},
			{1088, 1016, 1},
			{1152, 1016, 1},
			{1216, 1016, 1},
			{1280, 1016, 1},
			{1344, 1016, 1},
			{1408, 1016, 1},
			{1472, 1016, 1},
			{1536, 1016, 1},
			{1600, 1016, 1},
			{1664, 1016, 1},
			{1728, 1016, 1},
			{1792, 1016, 1},
			{1856, 1016, 1},
			{1920, 1016, 1},
			{1984, 1016, 1},
			{2048, 1016, 1},
			{2112, 1016, 1},
			{2176, 1016, 1},
			{2240, 1016, 1},
			{2304, 1016, 1},
			{2368, 1016, 1},
			{2432, 1016, 1},
			{2496, 1016, 1},
			{2560, 1016, 1},
			{2624, 1016, 1},
			{2688, 1016, 1},
			{2752, 1016, 1},
			{2816, 1016, 1},
			{2880, 1016, 1},
			{2944, 1016, 1},
			{3008, 1016, 1},
			{3072, 1016, 1},
			{3136, 1016, 1},
			{3200, 1016, 1},
			{3264, 1016, 1},
			{3328, 1016, 1},
			{3392, 1016, 1},
			{3456, 1016, 1},
			{3520, 1016, 1},
			{3584, 1016, 1},
			{3648, 1016, 1},
			{3712, 1016, 1},
			{3776, 1016, 1},
			{3840, 1016, 1},
			{3904, 1016, 1},
			{3968, 1016, 1},
			{4032, 1016, 1},
			{400, 500, 13},
			{464, 500, 14},
			{528, 500, 14},
			{592, 500, 14},
			{656, 500, 15},
			{1100, 400, 13},
			{1164, 400, 14},
			{1228, 400, 14},
			{1292, 400, 14},
			{1356, 400, 15},
			{2400, 600, 13},
			{2464, 600, 14},
			{2528, 600, 14},
			{2592, 600, 14},
			{2656, 600, 15}
	};
	tile = map;

	std::vector<std::vector<int>> omap = {
			{1200, 1016, 5},
			{1464, 1016, 1},
			{2528, 1016, 2},
			{3200, 1016, 13},
			{3500, 1016, 0}
	};
	object = omap;
	*/
	for(int i = 0; i < objecttypenum; i++) objectcollidable[i] = false;
	objectcollidable[5] = true;
	objectcollidable[12] = true;

	db.loadDatabase("map.db");
	db.execute("SELECT * FROM SCENE WHERE levelno=0 AND tob=0");
	while(db.hasSelectData()) {
		std::string data = db.getSelectData();
//		gLogi("GC") << "data:" << data;
		std::vector<std::string> line = gSplitString(data, "|");
		std::vector<int> t;
		t.push_back(gToInt(line[3]));
		t.push_back(gToInt(line[4]));
		t.push_back(gToInt(line[5]));
		tile.push_back(t);
	}

	db.execute("SELECT * FROM SCENE WHERE levelno=0 AND tob=1");
	while(db.hasSelectData()) {
		std::string data = db.getSelectData();
//		gLogi("GC") << "data:" << data;
		std::vector<std::string> line = gSplitString(data, "|");
		std::vector<int> t;
		t.push_back(gToInt(line[3]));
		t.push_back(gToInt(line[4]));
		t.push_back(gToInt(line[5]));
		object.push_back(t);
	}

	db.close();
}
