#ifndef COD2_DVARS_H
#define COD2_DVARS_H

#include <windows.h>


enum dvarFlags_e : UINT16
{
    DVAR_NOFLAG = 0x0,
    DVAR_ARCHIVE = 0x1,
    DVAR_USERINFO = 0x2,
    DVAR_SERVERINFO = 0x4,
    DVAR_SYSTEMINFO = 0x8,
    DVAR_NOWRITE = 0x10,
    DVAR_LATCH = 0x20,
    DVAR_ROM = 0x40,
    DVAR_CHEAT = 0x80,
    DVAR_DEVELOPER = 0x100,
    DVAR_SAVED = 0x200,
    DVAR_SCRIPTINFO = 0x400,
    DVAR_CHANGEABLE_RESET = 0x1000,
    DVAR_RENDERER = 0x2000,
    DVAR_EXTERNAL = 0x4000,
    DVAR_AUTOEXEC = 0x8000
};

enum dvarType_e : UINT8
{
    DVAR_TYPE_BOOL = 0x0,
    DVAR_TYPE_FLOAT = 0x1,
    DVAR_TYPE_VEC2 = 0x2,
    DVAR_TYPE_VEC3 = 0x3,
    DVAR_TYPE_VEC4 = 0x4,
    DVAR_TYPE_INT = 0x5,
    DVAR_TYPE_ENUM = 0x6,
    DVAR_TYPE_STRING = 0x7,
    DVAR_TYPE_COLOR = 0x8
};

union DvarLimits
{
	struct
	{
		int stringCount;
		const char **strings;
	} enumeration;
	struct
	{
		int min;
		int max;
	} integer;
	struct
	{
		float min;
		float max;
	} decimal;
};

typedef struct
{
	union
	{
		bool boolean;
		int integer;
		float decimal;
		float* vec2;
		float* vec3;
		float* vec4;
		const char *string;
		unsigned char color[4];
	};
} dvarValue_t;

typedef struct dvar_s
{
    char const* name;
    enum dvarFlags_e flags;
    enum dvarType_e type;
    bool modified;
    dvarValue_t value;
    dvarValue_t latchedValue;
    dvarValue_t defaultValue;
    union DvarLimits limits;
    struct dvar_s* next;
    struct dvar_s* hashNext;
} dvar_t;







inline dvar_t* Dvar_RegisterBool(const char* name, bool value, enum dvarFlags_e flags) {
    return ((dvar_t* (__cdecl*)(const char*, int, unsigned short))0x00438040)(name, value, flags);
}
inline dvar_t* Dvar_RegisterInt(const char* name, int value, int min, int max, enum dvarFlags_e flags) {
    return ((dvar_t* (__cdecl*)(const char*, int, int, int, unsigned short))0x004380a0)(name, value, min, max, flags);
}
inline dvar_t* Dvar_RegisterFloat(const char* name, float value, float min, float max, enum dvarFlags_e flags) {
    return ((dvar_t* (__cdecl*)(const char*, float, float, float, unsigned short))0x00438100)(name, value, min, max, flags);
}
inline dvar_t* Dvar_RegisterString(const char* name, const char* value, enum dvarFlags_e flags) {
    return ((dvar_t* (__cdecl*)(const char*, const char*, unsigned short))0x00438340)(name, value, flags);
}
inline dvar_t* Dvar_RegisterEnum(const char* name, const char** value, int defaultIndex, enum dvarFlags_e flags) {
    return ((dvar_t* (__cdecl*)(const char*, const char**, int, unsigned short))0x004383a0)(name, value, defaultIndex, flags);
}

inline void Dvar_SetBool(struct dvar_s* dvar, int value) {
    ((void (__cdecl*)(struct dvar_s*, int))0x00438b90)(dvar, value);
}
inline void Dvar_SetInt(struct dvar_s* dvar, int value) {
    ((void (__cdecl*)(struct dvar_s*, int))0x00438bf0)(dvar, value);
}
inline void Dvar_SetFloat(struct dvar_s* dvar, float value) {
    ((void (__cdecl*)(struct dvar_s*, float))0x00438c10)(dvar, value);
}
inline void Dvar_SetString(struct dvar_s* dvar, const char* value) {
    ((void (__cdecl*)(struct dvar_s*, const char*))0x00438ca0)(dvar, value);
}

inline char* Dvar_EnumToString(struct dvar_s* dvar) {
    return ((char* (__cdecl*)(struct dvar_s*))0x00435f30)(dvar);
}

//inline void Dvar_SetStringFromSource(struct dvar_s* dvar /*@ ebx*/, const char* value /*@ eax*/, int source) {
/*    const void* original_func = (void*)0x00438900;

    __asm__ volatile (
        "push %3\n"             // Push source (stack argument)
        "movl %2, %%eax\n"      // Load value into EAX
        "movl %1, %%ebx\n"      // Load dvar into EBX
        "call *%0\n"            // Call the function
        "addl $4, %%esp\n"      // Clean up the stack (1 argument × 4 bytes)
        :
        : "m"(original_func), "m"(dvar), "m"(value), "m"(source)
        : "eax", "ebx", "memory"
    );
}*/








#define cl_updateAvailable (*(dvar_t **)(0x0096b644))
#define cl_updateVersion (*(dvar_t **)(0x0096b640))
#define cl_updateOldVersion (*(dvar_t **)(0x0096b64c))
#define cl_updateFiles (*(dvar_t **)(0x0096b5d4))

/*#define vid_xpos (*(dvar_t **)(0x00d77158))
#define vid_ypos (*(dvar_t **)(0x00d77150))
#define r_fullscreen (*(dvar_t **)(0x00d77128))
#define r_fullscreen (*(dvar_t **)(0x00d77128))*/


#endif