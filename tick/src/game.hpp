#ifndef __GAME_HPP
#define __GAME_HPP

#include <SDL2/sdl.h>
#include <OpenGL/opengl.h>
#include <OpenGL/gl3.h>

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "globals.hpp"
#include "hogl.hpp"

typedef void (*setup_method)(GameState *gameState);
typedef void (*update_method)(GameState *gameState);

// NOTE(Brett): This might wanna be put in the globals or the system stuff
typedef struct _resource {
	int id;
	void *data;
	int dataSz;
} Resource;

typedef struct _resource_map {

} ResourceMap;

typedef struct _gpu_vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
	glm::vec4 tint;
} Vertex;

typedef struct _goemetry_quad {
	GLuint vao;
	GLuint vbo;
	GLuint shaderId;
	GLuint textureId;

	Vertex data[6];
} GeometryQuad;

typedef struct _geometry_array {
	GLuint vao;
	GLuint vbo;
	GLuint shaderId;
	GLuint textureId;

	GeometryQuad *data;
	int dataSz;

} GeometryArray;

typedef struct _map_chunk {

} MapChunk;

typedef struct _camera {
	int initialized;

	glm::vec3 eye;
	glm::vec3 center;
	glm::vec3 up;

	glm::mat4 projection;
	glm::mat4 view;
} GameCamera;

typedef struct _tile_arena {


} TileArena;

typedef struct _game_data {
	GameCamera camera;
	bool initialized;

} GameData;

void PushResource(GameState *memory, Resource *rez);

#define CameraSz sizeof(struct _camera);

extern "C" 
{
	void Setup(GameState *gameData);
	void UpdateAndRender(GameState *gameData);
}

#endif

