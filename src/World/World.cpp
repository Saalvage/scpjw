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
	graphics = PGE::Graphics::create("SCP: Janitorial Works", 1280, 720, false, PGE::Graphics::Renderer::OpenGL);
	graphics->setViewport(PGE::Rectanglei(0, 0, 1280, 720));
	graphics->setVsync(false);
	io = PGE::IO::create(graphics);

	lol = PGE::Mesh::create(graphics, PGE::Primitive::TYPE::TRIANGLE);

	aaa = PGE::Shader::load(graphics, PGE::FilePath::fromStr("Shaders/UI/"));
	aaa->getFragmentShaderConstant("imageColor")->setValue(PGE::Color::White);
	lol->setMaterial(new PGE::Material(aaa));
	PGE::Vertex v1;
	v1.setVector2f("position", PGE::Vector2f(0.0f, 0.0f));
	PGE::Vertex v2;
	v2.setVector2f("position", PGE::Vector2f(10.0f, 10.0f));
	PGE::Vertex v3;
	v3.setVector2f("position", PGE::Vector2f(0.0f, 10.0f));
	std::vector funny = { v1, v2, v3 };
	std::vector unfunny = { PGE::Primitive(0, 1, 2) };
	lol->setGeometry(3, funny, 1, unfunny);

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

	run();
	//bbb->getVertexShaderConstant("bbbb")->setValue(PGE::Vector4f(1, 1, 0, 0));
}

World::~World() {
	delete lol;
	delete sus;
	delete aaa;
	delete bbb;
	delete graphics;
	delete io;
}

static auto timet = std::chrono::high_resolution_clock::now() += std::chrono::seconds(1);
static int fps = 0;
static bool dir = false;
static float pos = 0.5;
static auto stupidTime = std::chrono::high_resolution_clock::now();
static PGE::Random random = PGE::Random(5);

static bool vsync = false;

bool World::run() {
	if ((std::chrono::high_resolution_clock::now() - timet).count() >= 0) {
		timet = std::chrono::high_resolution_clock::now() += std::chrono::seconds(1);
		std::cout << fps << std::endl;
		fps = 0;
		//graphics->setVsync(vsync = !vsync);
	}
	fps++;
	SysEvents::update();
	graphics->update();
	graphics->clear(PGE::Color::Green);
	//aaa->getFragmentShaderConstant("imageColor")->setValue(PGE::Color::White);
	bbb->getVertexShaderConstant("bbbb")->setValue(PGE::Vector4f(0, pos, 0, 0));
	pos += (dir ? 0.01f : -0.01f) * ((float)(std::chrono::high_resolution_clock::now() - stupidTime).count())/10000000;
	stupidTime = std::chrono::high_resolution_clock::now();
	if (pos < -0.5f || pos > 0.5f) {
		dir = !dir;
		//bbb->getFragmentShaderConstant("imageColor")->setValue(PGE::Color(random.nextFloat(), random.nextFloat(), random.nextFloat()));
	}
	sus->render();
	//lol->render();
	graphics->swap();
	return graphics->isWindowOpen();
}
