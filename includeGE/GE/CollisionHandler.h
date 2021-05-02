#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include <SDL.h>
#include <string>
#include <iostream>
#include <GE/CollisionListener.h>
#include <GE/Tower.h>

namespace play{
	class Spelmotor;

	class CollisionHandler
	{
	public:
		CollisionHandler(); 
		CollisionHandler(Spelmotor * spelmotor);	
		~CollisionHandler();
		void storeCollidable(std::string nameA, std::string nameB,CollisionListener *listener);
		void collisionTick();
	



	


	private:
//		void checkCollisions(Tower * A, Tower *B, CollisionListener * listener);
		struct Collidable{
			std::string nameA;
			std::string nameB;
			CollisionListener *listener;
		};
		std::vector<Collidable*> collidables;
		//Spelmotor *spelmotor;
	};



}
#endif