internal MemoryArena MemoryArenaInit(void *memory_start, u32 size){
    MemoryArena arena = {};
    arena.memory_start = memory_start;
    arena.size = size;
    arena.memory_used = 0;
    return arena;
}

internal void * MemoryArenaAllocate(MemoryArena *arena, u32 alloc_size){
    if(arena->memory_used + alloc_size < arena->size){
        void *result = (void *)((u8 *)arena->memory_start + arena->memory_used);
        arena->memory_used += alloc_size;
        return result;
    }else{
        printf("Memory Error: Allocation too big for arena\n");
        return 0;
    }
}