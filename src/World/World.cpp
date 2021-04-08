#include "World.h"

#include <Mesh/Mesh.h>
#include <Shader/Shader.h>
#include <filesystem>
#include <iostream>
#include <Math/Random.h>

static PGE::Mesh* lol;
static PGE::Mesh* sus;
static PGE::Shader* aaa;
static PGE::Shader* bbb;

World::World() {
	graphics = PGE::Graphics::create("SCP-087-B: Remastered", 1280, 720, false, PGE::Graphics::Renderer::Vulkan);
	graphics->setViewport(PGE::Rectanglei(0, 0, 1280, 720));
	graphics->setVsync(false);
	io = PGE::IO::create(graphics);

	//lol = PGE::Mesh::createRef(graphics, PGE::Primitive::TYPE::TRIANGLE);

	//aaa = PGE::Shader::load(graphics, PGE::FilePath::fromStr("Shaders/UI/"));
	//aaa->getFragmentShaderConstant("imageColor")->setValue(PGE::Color::White);
	//aaa->getVertexShaderConstant("projectionMatrix")->setValue(PGE::Matrix4x4f::constructOrthographicMat(1280, 720, 0.01f, 200.f));
	//lol->setMaterial(new PGE::Material(aaa));

	bbb = PGE::Shader::load(graphics, PGE::FilePath::fromStr("Shaders/Test/"));
	bbb->getFragmentShaderConstant("imageColor")->setValue(PGE::Color::Yellow);
	sus = PGE::Mesh::create(graphics, PGE::Primitive::TYPE::TRIANGLE);
	sus->setMaterial(new PGE::Material(bbb));
	std::vector<PGE::Vertex> lola;
	std::vector<PGE::Primitive> lolb;
	PGE::Vertex a;
	a.setVector2f("position", PGE::Vector2f(0.0f, -0.5f));
	a.setVector3f("color", PGE::Vector3f(1, 0, 0));
	lola.push_back(a);
	PGE::Vertex b;
	b.setVector2f("position", PGE::Vector2f(0.5f, 0.5f));
	b.setVector3f("color", PGE::Vector3f(0, 1, 0));
	lola.push_back(b);
	PGE::Vertex c;
	c.setVector2f("position", PGE::Vector2f(-0.5f, 0.5f));
	c.setVector3f("color", PGE::Vector3f(0, 1, 1));
	lola.push_back(c);
	lolb.push_back(PGE::Primitive(0, 1, 2));
	sus->setGeometry(lola, lolb);

	PGE::Rectanglef rec = PGE::Rectanglef(0, 0, 0.5f, 50);
	std::vector<PGE::Vertex> vertices;
	for (int i = 0; i < 4; i++) {
		PGE::Vertex v;
		PGE::Vector2f pos;
		switch (i) {
			case 0:
				pos = rec.topLeftCorner().add(PGE::Vector2f(0.f, 0.1f));
				break;
			case 1:
				pos = rec.topRightCorner();
				break;
			case 2:
				pos = rec.bottomLeftCorner();
				break;
			default:
			case 3:
				pos = rec.bottomRightCorner();
		}
		v.setVector2f("position", pos);
		vertices.push_back(v);
	}
	std::vector<PGE::Primitive> primitives;
	primitives.push_back(PGE::Primitive(2, 1, 0));
	primitives.push_back(PGE::Primitive(1, 2, 3));
	//lol->setGeometry(4, vertices, 2, primitives);

	run();
	bbb->getVertexShaderConstant("bbbb")->setValue(PGE::Vector4f(1, 1, 0, 0));
}

World::~World() {
	delete sus;
	delete lol;
	delete aaa;
	delete bbb;
	delete graphics;
	delete io;
}

#include <Math/Random.h>

static auto timet = std::chrono::high_resolution_clock::now() += std::chrono::seconds(1);
static int fps = 0;
static bool dir = false;
static float pos = 0.5;
static auto stupidTime = std::chrono::high_resolution_clock::now();
static PGE::Random random = PGE::Random(5);

bool World::run() {
	if ((std::chrono::high_resolution_clock::now() - timet).count() >= 0) {
		timet = std::chrono::high_resolution_clock::now() += std::chrono::seconds(1);
		std::cout << fps << std::endl;
		fps = 0;
	}
	fps++;
	SysEvents::update();
	graphics->update();
	graphics->clear(PGE::Color::Green);
	//lol->render();
	bbb->getVertexShaderConstant("bbbb")->setValue(PGE::Vector4f(0, pos, 0, 0));
	pos += (dir ? 0.01f : -0.01f) * ((float)(std::chrono::high_resolution_clock::now() - stupidTime).count())/10000000;
	stupidTime = std::chrono::high_resolution_clock::now();
	if (pos < -0.5f || pos > 0.5f) {
		dir = !dir;
		bbb->getFragmentShaderConstant("imageColor")->setValue(PGE::Color(random.nextFloat(), random.nextFloat(), random.nextFloat()));
	}
	sus->render();
	graphics->swap();
	return graphics->isWindowOpen();
}
