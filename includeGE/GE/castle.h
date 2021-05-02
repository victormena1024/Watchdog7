#ifndef CASTLE_H
#define CASTLE_H
/*

	One castle can have many towers.
	One tower can have many sprites.
	Each Tower do have one prototype.
	One sprite can have many images.
	one Image can have many SDL_Surfaces
	One Image have one name.

*/
#include <vector>
#include "GE/Tower.h"

namespace play{

	class Castle
	{
	public:
		Castle(void);
		~Castle(void);

		std::vector<Tower*> getTowers();
		Tower* createTowerAndInsertPrototypeSprite(Sprite * inputSprite, char *name, int howmanycopiestomake);

		void killTowerByName(char *spriteName);
		void reviveTowerByName(char *towerName);
		void killTowerByIndex(int index);
		void reviveTowerByIndex(int index);

		bool isTowerAlive(char *towerName);

		char *getCurrentTowerName();
		Tower *getCurrentTower();
		void resetCurrentTowerIndex();
		//
		Tower *goNextTower();
		Tower *goPrevTower();
		//
		Tower *goTower(int index);	// getTower(...)
		Tower *goTower(char *name);
		Tower *goTower(std::string &name);
		Tower *goTowerByIndex(int index);
	
		void debugPrint();

		int	getMaximumTowerSize();
		int	getMaximumTowerIndex();

		// -------------------
		void *getUserData(void);
		void setUserData(void *usr);
		// -------------------

		void renderAllTowers();
		void tickAllTowers();


		// --------------------------------------------------------------------------------------------------------------------------------
		// returns true if collision happened, else false.
		// if callbackfunc is not nullptr, then it is called.
		// if callbackfunc returns false, then further collision check is canceled.
		bool	checkCollisionFromOneToOne(Sprite *spr, Sprite *zspr, void(*callbackfunc)(Castle*, Sprite*, Sprite*));
		bool	checkCollisionFromOneToMany(Sprite *spr, Tower *twr,   bool(*callbackfunc)(Castle*, Tower*, Sprite*, Sprite*));
		bool	checkCollisionFromManyToMany(Tower *towerA, Tower *towerB, bool(*callbackfunc)(Castle*, Tower *, Tower*, Sprite*, Sprite*));
		// --------------------------------------------------------------------------------------------------------------------------------



private:
	void privateAdjustCurrentTowers(int& towerIndex);	//make sure index stays within bounds
	
	std::vector<Tower*> towers;		// towers
		int  currentTower = 0;
		//
		bool debuggy;
		void *userData;
		//
	};
}
#endif