/* date = November 26th 2020 6:53 pm */

#ifndef MEMORY_H
#define MEMORY_H

struct MemoryArena{
    void *memory_start;
    u32 size;
    u32 memory_used;
};

#endif //MEMORY_H
