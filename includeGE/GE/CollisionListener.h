#ifndef COLLISIONLISTENER_H
#define COLLISIONLISTENER_H

#include "GE/Sprite.h"

namespace play{

	class CollisionListener
	{
	public:
		virtual void onCollision(Sprite* aspr, Sprite *bspr) = 0;
	};
}

#endif