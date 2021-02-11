#include "World.h"

World::World() {
	graphics = PGE::Graphics::create("SCP-087-B: Remastered", 1280, 720, false);
	graphics->setViewport(PGE::Rectanglei(0, 0, 1280, 720));
	io = PGE::IO::create(graphics->getWindow());
}

World::~World() {

}

void World::run() {
	while (true) {

	}
}
