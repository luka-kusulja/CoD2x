#ifndef COD2_H
#define COD2_H

#include "cod2_dvars.h"
#include <windows.h>


enum errorParm_e
{
    // Show message box, close window, show console window
	ERR_FATAL = 0x0,
    // Show ingame error
	ERR_DROP = 0x1,
	ERR_SERVERDISCONNECT = 0x2,
	ERR_DISCONNECT = 0x3,
	ERR_SCRIPT = 0x4,
	ERR_SCRIPT_DROP = 0x5,
	ERR_LOCALIZATION = 0x6,
	ERR_MAPLOADERRORSUMMARY = 0x7,
};

enum netadrtype_e
{
    NA_BOT = 0x0,
    NA_BAD = 0x1,
    NA_LOOPBACK = 0x2,
    NA_BROADCAST = 0x3,
    NA_IP = 0x4,
    NA_IPX = 0x5,
    NA_BROADCAST_IPX = 0x6
};

struct netaddr_s
{
    enum netadrtype_e type;
    byte ip[0x4];
    UINT16 port;
    int ipx_data;
    int ipx_data2;
    int ipx_data3;
};


void Cbuf_AddText(const char* text);

int Cmd_Argc( void );
const char *Cmd_Argv( int arg );

int NET_OutOfBandPrint(const char* msg, int mode, struct netaddr_s addr);
int NET_StringToAdr(const char* updateServerUri, struct netaddr_s* a);


#define Com_Error ((int (*)(enum errorParm_e, const char *, ...))0x004324c0)

#define Com_DPrintf ((int (*)(const char *, ...))0x00431f30)

#define va ((char* (*)(const char *, ...))0x0044a990)


#endif