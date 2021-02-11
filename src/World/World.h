#include <Graphics/Graphics.h>
#include <IO/IO.h>

class World {
	public:
		World();
		~World();
		void run();

	private:
		PGE::Graphics* graphics;
		PGE::IO* io;
};
