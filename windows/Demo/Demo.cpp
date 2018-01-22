#include "Demo.h"

void Demo::init()
{
	int imageWidth, imageHeight;

	material = new Material();
	material->materialID = 0;
	material->shader = loadShader("res/shader.vert", "res/shader.frag");
	material->texture = loadBmpDemo("res/bmpTest_16.bmp", &imageWidth, &imageHeight);

	renderer = new BatchRenderer();

	sprite = new Sprite();
	sprite->material = material;
	sprite->position = vec3(100.0f, 100.0f, 0.0f);
	sprite->size = vec2(imageWidth, imageHeight);

	mat4 projection = glm::ortho(0.0f, 1280.0f, 720.0f, 0.0f, 0.0f, 100.0f);
	vec3 cameraPos = vec3(0.0f, 0.0f, 0.0f);
	mat4 view = glm::lookAt(cameraPos, cameraPos + vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 1.0f, 0.0f));
	pv = projection * view;
}

void Demo::update(Time& time)
{
}

void Demo::render()
{
	renderer->addSprite(sprite);
	renderer->render(pv);
}

void Demo::destroy()
{
	safeDelete(sprite);
	safeDelete(renderer);
	safeDelete(material);
}