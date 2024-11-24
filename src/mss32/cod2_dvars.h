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
		float vec2[2];
		float vec3[3];
		float vec4[4];
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


void Dvar_SetBool(struct dvar_s* dvar, int value);
void Dvar_SetStringFromSource(struct dvar_s* dvar, const char* value, int source);


#define cl_updateAvailable (*(dvar_t **)(0x0096b644))
#define cl_updateVersion (*(dvar_t **)(0x0096b640))
#define cl_updateOldVersion (*(dvar_t **)(0x0096b64c))
#define cl_updateFiles (*(dvar_t **)(0x0096b5d4))


#endif