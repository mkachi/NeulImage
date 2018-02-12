#pragma once

#include "Scene.h"
#include "Renderer.h"
#include "Config.h"

#define TEXTURE_SIZE 6

class Demo
	: public Scene
{
private:
	Sprite* sprites[TEXTURE_SIZE];
	Material* materials[TEXTURE_SIZE];
	BatchRenderer* renderer;
	mat4 pv;

public:
	Demo() {}
	virtual ~Demo() {}

	void init() override;
	void update(Time& time) override;
	void render() override;
	void destroy() override;

};