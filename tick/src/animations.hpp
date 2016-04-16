#ifndef __ANIMATIONS_HPP
#define __ANIMATIONS_HPP

#include <glm/glm.hpp>

#define array_size(ar) (sizeof(ar) / sizeof(ar[0]))

#define uint8 unsigned char
#define uint32 unsigned int
#define real32 float
#define real64 double

enum ACTION {
	PROTECTED = 0,
	ABSOLUTE_MOVE_TO,
	RELATIVE_MOVE_TO,
	ACTION_COUNT
};

typedef struct q_entity {
	glm::vec3 position;
	glm::vec3 size;
	glm::vec3 scale;

	uint8 *imageBytes;

	q_entity *parent;
} QEntity;


typedef void (*QActionCallback)();

typedef struct q_action {
	 
} QAction;


#endif