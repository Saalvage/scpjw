#include "World.h"

#include <Mesh/Mesh.h>
#include <Shader/Shader.h>
#include <filesystem>
#include <iostream>

static PGE::Mesh* lol;

World::World() {
	graphics = PGE::Graphics::create("SCP-087-B: Remastered", 1280, 720, false);
	graphics->setViewport(PGE::Rectanglei(0, 0, 1280, 720));
	io = PGE::IO::create(graphics->getWindow());

	lol = PGE::Mesh::create(graphics, PGE::Primitive::TYPE::TRIANGLE);

	PGE::Shader* aaa = PGE::Shader::load(graphics, PGE::FilePath::fromStr("Shaders/UI/"));
	aaa->getFragmentShaderConstant("imageColor")->setValue(PGE::Color::White);
	aaa->getVertexShaderConstant("projectionMatrix")->setValue(PGE::Matrix4x4f::constructOrthographicMat(1280, 720, 0.01f, 200.f));
	lol->setMaterial(new PGE::Material(aaa));

	PGE::Rectanglef rec = PGE::Rectanglef(0, 0, 600, 50);
	std::vector<PGE::Vertex> vertices;
	for (int i = 0; i < 4; i++) {
		PGE::Vertex v;
		PGE::Vector2f pos;
		switch (i) {
			case 0:
				pos = rec.topLeftCorner();
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
	lol->setGeometry(4, vertices, 2, primitives);
}

World::~World() {
	delete graphics;
	delete io;
}

bool World::run() {
	SysEvents::update();
	graphics->update();
	graphics->clear(PGE::Color::Green);
	lol->render();
	graphics->swap(false);
	return graphics->getWindow()->isOpen();
}
