#include "Demo.h"

void Demo::init()
{
	std::string imagePaths[] = {
		"res/bmpTest_24.bmp",
		"res/pngTest.png",
		"res/tgaTest_24.tga",
		"res/jpegTest.jpg",

		"res/bmpTest_32.bmp",
		"res/tgaTest_32.tga",
	};

	vec2 positions[] = {
		vec2(0.0f, SCREEN_HEIGHT / 2),
		vec2(SCREEN_WIDTH, SCREEN_HEIGHT / 2),
		vec2(SCREEN_WIDTH / 2, 0.0f),
		vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT),

		vec2(0.0f, SCREEN_HEIGHT / 2),
		vec2(SCREEN_WIDTH / 2, 0.0f),
	};

	vec2 pivots[] = {
		vec2(0.0f, 0.5f),
		vec2(1.0f, 0.5f),
		vec2(0.5f, 0.0f),
		vec2(0.5f, 1.0f),

		vec2(-1.2f, 0.5f),
		vec2(0.5f, -1.2f),
	};

	//GLuint shader = loadShader("res/shader.vert", "res/shader.frag");
	for (int i = 0; i < TEXTURE_SIZE; ++i)
	{
		int width, height;
		materials[i] = new Material();
		materials[i]->materialID = i;
		//materials[i]->shader = shader;
		materials[i]->texture = loadImage(imagePaths[i].c_str(), width, height);

		float x = positions[i].x - (width * pivots[i].x);
		float y = positions[i].y - (height * pivots[i].y);

		sprites[i] = new Sprite();
		sprites[i]->material = materials[i];
		sprites[i]->position = vec3(x, y, 0.0f);
		sprites[i]->size = vec2(width, height);
	}
	renderer = new BatchRenderer();

	mat4 projection = glm::ortho(0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f, 0.0f, 100.0f);
	vec3 cameraPos = vec3(0.0f, 0.0f, 0.0f);
	mat4 view = glm::lookAt(cameraPos, cameraPos + vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 1.0f, 0.0f));
	pv = projection * view;
}

void Demo::update(Time& time)
{
}

void Demo::render()
{
	for (int i = 0; i < TEXTURE_SIZE; ++i)
	{
		renderer->addSprite(sprites[i]);
	}
	renderer->render(pv);
}

void Demo::destroy()
{
	for (int i = 0; i < TEXTURE_SIZE; ++i)
	{
		safeDelete(sprites[i]);
	}
	safeDelete(renderer);
	for (int i = 0; i < TEXTURE_SIZE; ++i)
	{
		safeDelete(materials[i]);
	}
}