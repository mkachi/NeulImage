#pragma once

#include "Scene.h"
#include "Renderer.h"

class Demo
	: public Scene
{
private:
	Sprite* sprite;
	BatchRenderer* renderer;
	Material* material;
	mat4 pv;

public:
	Demo() {}
	virtual ~Demo() {}

	void init() override;
	void update(Time& time) override;
	void render() override;
	void destroy() override;

};