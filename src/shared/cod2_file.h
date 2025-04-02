#ifndef COD2_FILE_H
#define COD2_FILE_H

#include "shared.h"
#include "assembly.h"

// Read file in path
inline int FS_ReadFile(const char* path, void** buffer) {
    int ret;
    ASM_CALL(RETURN(ret), ADDR(0x00423240, 0x080a0a9c), 2, PUSH(path), PUSH(buffer));
    return ret;
}

// Write file in location fs_homepath + fs_game + filename
inline bool FS_WriteFile(const char* filename, const char* buffer, size_t size) {
    int ret;
    ASM_CALL(RETURN(ret), ADDR(0x00423340, 0x080a0ba8), 3, PUSH(filename), PUSH(buffer), PUSH(size));
    return ret;
}

// Delete file in location fs_homepath + fs_game + filename
inline bool FS_Delete(const char *filename)
{
    int ret;
	ASM_CALL(RETURN(ret), ADDR(0x00422e00, 0x080a03dc), WL(0, 1), WL(EAX, PUSH)(filename));
    return ret;
}


#endif