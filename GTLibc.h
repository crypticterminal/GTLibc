#ifndef _GTLIBC_H_
#define _GTLIBC_H_

/*
BRIEF : GTLibc is library to make game trainer in c/c++ it provide all the necessary methods to make simple game trainer in
windows using win32-API with ease.
It uses only WIN32 API methods instead of CRT method because this is intended to work on Windows system only
and not shall be portable or to target other OS like Linux,MAC OS etc.

From beginning of trainer development till the end, it provides all necessary methods needed.

*****************************
*******Main components.******
*****************************

1)Finding game --> use findGameProcess()  or findGameWindow() method.
2)Reading values Health,XP,Ammos from game --> use readAddress() or readAddressoffset() methods.
3)Writing values Health,XP,Ammos to  game --> use writeAddress() or writeAddressOffset() methods.
4)Creating Hot-keys for trainer --> use hotKeysPressed() MACRO or isKeyPressed()/isKeyToggled() methods.

*****************************
****Additional components.***
*****************************

5)Additional Automation of scripting for trainer --> use doMousePress() and doKeyPress() methods.
6)Cheat code applying tool included in this library --> use setCheatCode() method.
7)Offset area searching tool included in this library --> use searchOffsetArea() method.


NOTE : This ain't memory scanning,hooking,analyzing library, it won't provide methods for scanning/signature or dumping RAW memory.

AIM : The aim of this library is only to provide the most efficient way of creating game trainer 
and to provide a layer on top of WIN-32 API cumbersome methods and to make reading/writing ,finding Game process easier and convenient.

DOCUMENTATION INFO :
All Public and Semi-Private methods are well documented.
but private methods are not documented as it was not necessary to do so.

VERSION INFO :
GTLIBC Version : V 1.0.0.

Written by HaseeB Mir (haseebmir.hm@gmail.com)
Dated : 23/03/2018
*/

/*Including WIN32 libraries*/
#define WINVER 0x0500
#include <windows.h>
#include <tlhelp32.h>

/*Defining constants*/
#define NIL 0x0 	/*Integer NULL*/
#define NUL '\0' 	/*Character NULL*/
#define MOUSE_LEFT_ID 1
#define MOUSE_RIGHT_ID 2
#define hotKeysPressed(...) hotKeysDown(__VA_ARGS__, NULL)
#define ERROR_INVALID (GetLastError() != ERROR_SUCCESS || GetLastError() == ERROR_ALREADY_EXISTS)

/*Re-Defining standard file constants*/
#define FILE_NAME __FILE__
#define LINE_NO __LINE__
#define FUNC_NAME __func__

/*Defining exception handling constants*/
#define try BOOL __HadError=FALSE;
#define catch(x) ExitJmp:if(__HadError)
#define throw(x) __HadError=TRUE;goto ExitJmp;

typedef BYTE* LPBYTE;

/*Structure to store process information*/
typedef struct process_hash
{
	char process_name[MAX_PATH];
    HANDLE process_handle;
    HWND process_hwnd;
    DWORD process_id;
} process_table;


/****************************************************************************/
/*********************-PUBLIC-METHODS-***************************************/
/****************************************************************************/
/*Public methods to find Game process/window.*/
HANDLE findGameProcess(LPCSTR);
HWND findGameWindow(LPCSTR);

/*Public methods to Read/Write values from/at Address.*/
DWORD readAddress(LPVOID);
DWORD readAddressOffset(LPVOID,DWORD);
DWORD* readAddressOffsets(LPVOID,DWORD*,SIZE_T);
BOOL writeAddress(LPVOID,DWORD);
BOOL writeAddressOffset(LPVOID,DWORD,DWORD);
BOOL writeAddressOffsets(LPVOID,DWORD*,SIZE_T,DWORD);

/*Public methods to Read/Write pointer from/at Address.*/
LPVOID readPointerOffset(LPVOID, DWORD);
LPVOID readPointerOffsets(LPVOID,DWORD*,SIZE_T);
BOOL writePointerOffset(LPVOID, DWORD, DWORD);
BOOL writePointerOffsets(LPVOID,DWORD*,SIZE_T,DWORD);

/*Public getter methods to get Game Name,Handle,Process ID,base address.*/
LPCSTR getGameName(void);
DWORD getProcessID(void);
HANDLE getGameHandle4mHWND(HWND);
DWORD getProcessID4mHWND(HWND);
LPBYTE getGameBaseAddress(DWORD);

/*Public methods for creating hot-keys*/
BOOL hotKeysDown(int,...);
BOOL isKeyPressed(const int);
BOOL isKeyToggled(const int);

/****************************************************************************/
/****************-SEMI-PRIVATE-METHODS-**************************************/
/****************************************************************************/
/*Semi-private methods for pressing Keyboard and Mouse keys*/
void doMousePress(int);
void doKeyPress(int);

/*Semi-private Tool for Applying cheat codes*/
void setCheatCode(LPCSTR);

/*Semi-private Tool for searching in offset area*/
LPSTR searchOffsetArea(LPVOID,const size_t,const size_t,DWORD);

/*Semi private method for enabling/disabling Logs*/
BOOL enableLogs(void);
BOOL disableLogs(void);

/*Semi-private getter methods to get Game,Handle,HWND.*/
HANDLE getGameHandle(void);
HWND getGameHWND(void);

/****************************************************************************/
/****************-PRIVATE-METHODS-*******************************************/
/****************************************************************************/
/*Private methods for showing error/info/warning*/
static void showError(DWORD,LPCSTR,DWORD);
static void showInfo(LPCSTR);
static void showWarning(LPCSTR);

/*Private setter methods for setting Game Name, ID,Handle,HWND etc*/
static void setProcessID(DWORD);
static void setGameHandle(HANDLE);
static void setGameName(LPCSTR);
static void setGameHWND(DWORD);

/*Private utility methods for time and Logs*/
static LPSTR getCurrentTime(void);
static void addLog(LPCSTR,...);
static BOOL fileExist(LPCSTR);

/*Private miscellaneous methods*/
static void doVirtualKeyPress(int,int,int);
static BOOL CALLBACK EnumAllWindows(HWND,LPARAM);
static LPSTR strcasestr(LPSTR,LPCSTR);
static BOOL isPrivateField(BOOL,LPCSTR,int);

/*Global variables for storing game information*/
DWORD process_id = NIL;
HANDLE game_handle = (HANDLE)NULL;
CHAR game_name[MAX_PATH] = {NUL};
HWND game_hwnd = (HWND)NULL;

/*Global variable for storing error code*/
DWORD error_code = NIL;

/*Setting private methods inaccessible*/
BOOL private_field = FALSE;

/*Setting add Logs to disable by default.*/
BOOL logs_enabled = FALSE;
	
#endif	/* _GTLIBC_H_ */