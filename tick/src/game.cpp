#include "game.hpp"

static GLuint GlobalShaderId;
static GameCamera Camera;

void Setup(GameState *applicationData) {
	applicationData->initialized = true;

	char *vertexShaderSource = 0,
		 *fragmentShaderSource = 0;

	ReadFile(&vertexShaderSource, (char *)"resources/shader/test_vertex.glsl");
	ReadFile(&fragmentShaderSource, (char *)"resources/shader/test_fragment.glsl");

	GLuint shader = 0;
	CreateShaderProgram(&shader, vertexShaderSource, fragmentShaderSource);

	GlobalShaderId = shader;

	GameData *data = (GameData*)(applicationData->memory.mainMemory);
	GameCamera *camera = &data->camera;

	std::cout << "SETTING UP CAMERA: " << camera->initialized << std::endl;
	if(!camera->initialized)
	{
		Camera = *camera;
		Camera.eye = glm::vec3(0.f, 4.f, 0.f );
		Camera.center = glm::vec3( 0.f, 4.f, -1.f );
		Camera.up = glm::vec3( 0.f, 0.f, 1.f );
		// Camera.projection = glm::perspectiveFov(45.f, 800.f, 600.f, 0.1f, 1000.f);
		Camera.projection = glm::ortho(-400.f, 400.f, -300.f, 300.f, 0.1f, 1000.0f);
		Camera.view = glm::lookAt(Camera.eye, Camera.center, Camera.up);
		Camera.initialized = true;
		std::cout << "SET UP CAMERA" << std::endl;
		*camera = Camera;
	}

	data->initialized = false;
}


void UpdateAndRender(GameState *applicationData) {

	GameData *data = (GameData*)(applicationData->memory.mainMemory);

	if(data->initialized == false) {

		data->initialized = true;
	}

	glClearColor(0.2f, 0.05f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}