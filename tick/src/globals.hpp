#ifndef __GLOBALS_HPP
#define __GLOBALS_HPP

#include <assert.h>

#ifdef DEBUG
#define BREAK __asm__("int $3");
#else
#define BREAK ;
#endif

#define global_variable static

typedef uint8_t uint8;


#define KILOBYTES(n) (n*1024)
#define MEGABYTES(n) (KILOBYTES(n))
#define GIGABYTES(n) (MEGABYTES(n))

typedef struct _game_memory {
	void *mainMemory;
	int mainMemorySz;
	void *heapPtr;

	void *transientMemory;
	int transientMemorySz;
} GameMemory;

typedef struct _input_controller {
	float mX, mY;
	int mouseButtons;

	int up, down, left, right;
	int action1;
	int action2;

} InputController;

typedef struct _game_state {
	GameMemory memory;
	bool initialized;
} GameState;

struct memory_arena {
    size_t sz;
    uint8 *base;
    size_t used;
};

#define PushStruct(Arena, type) (type *)PushSize_(Arena, sizeof(type))
#define PushArray(Arena, Count, type) (type *)PushSize_(Arena, (Count)*sizeof(type))

void *PushSize_(memory_arena *arena, size_t sz)
{
    assert((arena->sz + sz) <= arena->sz);
    void *result = arena->base + arena->used;
    arena->used += sz;
    
    return(result);
}

#endif