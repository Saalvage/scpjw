#include <Init/Init.h>

#include "World/World.h"

int PGEMain::Main() {
	World* world = new World();
	while (world->run());
	delete world;
	return 0;
}
