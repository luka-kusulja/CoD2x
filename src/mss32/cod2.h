#ifndef COD2_H
#define COD2_H

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

void Cbuf_AddText(char* text);
void Com_Error(enum errorParm_e code, const char *format, ...);



#endif