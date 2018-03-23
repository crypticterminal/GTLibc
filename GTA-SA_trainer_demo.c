#include "GTLibc.c"
#include <stdio.h>

#define NUTTER_TOOLS 0
#define THUG_TOOLS 1
#define PROFESSIONAL_TOOLS 2

/************************************
*GTA-SA Trainer using GTLibc library*
*************************************/

BOOL initGameTrainer();
void runGtaTrainer();
void setUnlimitedMoney();
void setUnlimitedHealth();
void setUnlimitedAmmo();

void testProcess();
void testWindow();
void testSearch();
char* fgets_s(char*, int, FILE*);

LPVOID money_address = NULL,health_address = NULL,weapon_base_address = NULL;

int main()
{
    if(initGameTrainer())
    {
        //initialize complete now run game trainer.
        runGtaTrainer();
    }

    return 0;
}

//initialize game trainer with process ID, handle , base address, weapon address etc.
BOOL initGameTrainer()
{
    DWORD processID = 0;
    LPBYTE base_address = NULL;
    HANDLE g_handle = NULL;
    BOOL g_found = FALSE;
    LPCSTR g_name = "gta_sa";

    //Making GTA:SA trainer example.
    puts("initializing game trainer....");

    //Open game and get process id, handle and base address.
    g_handle = findGameProcess(g_name);
    if (g_handle != NULL)
    {
        processID = getProcessID();
        g_handle = getGameHandle();
        base_address = getGameBaseAddress(processID);
    }
    //don't check for if game not found because that is handled by Library itself.


    //check for valid process ID and print game info.
    if (processID != 0)
    {
        g_found = TRUE;
        printf("Game Found %s\n",getGameName());
        printf("processID = %d\ngame_handle : %p\n\n", processID,g_handle);

        //example of static address.
        money_address = (LPVOID)0xB7CE50;

        //Example of getting base weapon address.
        weapon_base_address =  readPointerOffset(base_address,0x0076F3B8) + 0x5E0;

        //Example of readPointerOffset & readPointerOffsets.
        DWORD health_offsets[] = {0x144,0x160};
        LPVOID base_health = readPointerOffset(base_address,0x0076F3B8);
        health_address = readPointerOffsets(base_health,health_offsets,sizeof(health_offsets)) + 0x540;

        /*base address is address of pistol in this case.
           readAddress example.*/
        DWORD pistol_value = readAddress(weapon_base_address);

        //readAddressOffset example.
        //readAddressOffset(weapon_base_address,0x20);
    }
    return g_found;
}

//run game trainer after initializing.
void runGtaTrainer()
{

    /***********************************************/
    /****************GTA-SA TRAINER*****************/
    /***********************************************/

    //Printing Trainer info...
    puts("GTA-SA +6 TRAINER (V 1.0.0)\n");
    puts("*Unlimited Money... --> CTRL + 1.");
    puts("*Unlimited Health.. --> CTRL + 2.");
    puts("*Unlimited Ammo... --> CTRL + 3.");
    puts("*Select Nutter Tools (Weapon set)... --> ALT + 1.");
    puts("*Select Thug Tools (Weapon set)... --> ALT + 2.");
    puts("*Select Professional Tools (Weapon set)... --> ALT + 3.");
    puts("*Exit.... --> Press ESCAPE.");

    //Cheats list for weapons set.
    char *weapons_cheats[] = {"UZUMYMW","LXGIWYL","KJKSZPJ"};

    //running main game loop.
    while(TRUE)
    {

        //Applying unlimited money,health and ammo .

        if(isKeyPressed(VK_CONTROL) && isKeyToggled('1'))
        {
            setUnlimitedMoney();
        }

        else if(isKeyPressed(VK_CONTROL) && isKeyToggled('2'))
        {
            setUnlimitedHealth();
        }

        else if(isKeyPressed(VK_CONTROL) && isKeyToggled('3'))
        {
            setUnlimitedAmmo();
        }

        //Applying weapons cheat codes.

        else if(hotKeysPressed(VK_MENU,'1'))
        {
            setCheatCode(weapons_cheats[NUTTER_TOOLS]);
            puts("*[NUTTER TOOLS Enabled!....]*");
        }

        else if(hotKeysPressed(VK_MENU,'2'))
        {
            setCheatCode(weapons_cheats[THUG_TOOLS]);
            puts("*[THUG TOOLS Enabled!....]*");
        }

        else if(hotKeysPressed(VK_MENU,'3'))
        {
            setCheatCode(weapons_cheats[PROFESSIONAL_TOOLS]);
            puts("*[PROFESSIONAL TOOLS Enabled!....]*");
        }

        else if(isKeyToggled(VK_ESCAPE))
        {
            break;
        }
    }

    puts("Thanks for using GTA Trainer....Made using GTLIbc. !");
}

void setUnlimitedMoney()
{
    DWORD unlimited_money = 0x7FFFFFFFUL;
    if(writeAddress(money_address,unlimited_money))
        puts("*[Unlimited Money Enabled!....]*");
}

void setUnlimitedHealth()
{
    DWORD unlimited_health = 0x62C80000;
    if(writeAddress(health_address,unlimited_health))
        puts("*[Unlimited Health Enabled!....]*");

}


void setUnlimitedAmmo()
{

    DWORD unlimited_ammo = 0x7FFFFFFFUL;

    //list of weapons and clips offsets from base weapon address.
    static DWORD weapons_offsets[] = {0x0,0x4,0x1C,0x20,0x38,0x3C,0x54,0x58,0x74,0x90,0xAC,0xC4,0xC8};
    size_t offsets_size = sizeof(weapons_offsets);

    //readAddressOffsets example.
    DWORD *ammos_list = readAddressOffsets(weapon_base_address,weapons_offsets,offsets_size);

    if(ammos_list == NULL)
    {
        printf("ammos_list is NULL, error code : 0x%X\n",GetLastError());
        return;
    }

    //printing weapons ammo from offsets list.
    UINT index = NIL;
    //for(index = 0; index < offsets_size / sizeof(DWORD); index++)
    //printf("Weapon No %d Ammo at offset 0x%X : %u\n",(index + 1),weapons_offsets[index]);


    if(writeAddressOffsets(weapon_base_address,weapons_offsets,offsets_size,unlimited_ammo))
        puts("*[Unlimited Ammo Enabled!....]*");

    //free memory using HeapFree() example.
    if(!HeapFree(GetProcessHeap(),NIL,ammos_list))
    {
        printf("Error while freeing memory, error code : 0x%X\n",GetLastError());

        DWORD exit_value;
        GetExitCodeProcess(GetCurrentProcess(),&exit_value);
        ExitProcess(exit_value);
    }
}


//Example of FindGame by Process name.
void testProcess()
{
//enabling/disabling logs example.
    if(enableLogs())
    {
        puts("GTLibc Logs are enabled in this trainer.");
    }

    else if(disableLogs())
    {
        puts("GTLibc Logs are disabled in this trainer.");
    }

    DWORD processID = 0;
    HANDLE g_handle = NULL;
    HWND g_hwnd = NULL;

    //ask for input to open game.
    char g_name[MAX_PATH] = {NUL};
    puts("Enter process/game name to open");
    fgets_s(g_name,sizeof(g_name),stdin);

    //find game by process name.
    g_handle = findGameProcess(g_name);
    if(g_handle != NULL)
    {
        processID = getProcessID();
        g_hwnd = getGameHWND();
    }

    if (processID != 0)
    {
        printf("Name : %s\tprocessID = %d\n",getGameName(),processID);
        printf("Game handle = %p\nGame HWND = %p\n", g_handle,g_hwnd);
    }
}

//Example of FindGame by Window name.
void testWindow()
{
    DWORD processID = 0;
    LPBYTE base_address = NULL;
    HANDLE g_handle = NULL;

    //ask for input to open game.
    char g_window[MAX_PATH] = {NUL};
    puts("Enter game window name to open");
    fgets_s(g_window,sizeof(g_window),stdin);

    HWND g_hwnd = findGameWindow(g_window);

    if (g_hwnd != NULL)
    {
        g_handle = getGameHandle4mHWND(g_hwnd);
        processID = getProcessID4mHWND(g_hwnd);

        printf("Window name : %s\tprocessID = %d\n",g_window,processID);
        printf("Game handle = %p\tWindow handle = %p\n", g_handle,g_hwnd);
    }
}

//Example of searchOffsetArea.
void testSearch()
{

    size_t offset_limit = 100; //limit of searching offset.
    size_t offset_size = 4; // size in bytes 2 bytes,4bytes etc...
    int search = 17; //value to search.

    char *search_list = searchOffsetArea(weapon_base_address,offset_limit,offset_size,search);
    puts(search_list);

    //free memory from search list after printing using HeapFree() method.
    if(search_list == NULL)
    {
        printf("Search list is NULL, error code : 0x%X\n",GetLastError());
    }

    //if error occurred while freeing then exit with error code.
    else
    {
        if(!HeapFree(GetProcessHeap(),NIL,search_list))
        {
            printf("Error while freeing memory, error code : 0x%X\n",GetLastError());
        }
    }

    //exit process with exit code.
    DWORD exit_value;
    GetExitCodeProcess(GetCurrentProcess(),&exit_value);
    ExitProcess(exit_value);
}


char* fgets_s(char* str, int str_size, FILE* out_redirect)
{
    char *str_s = fgets(str,str_size,out_redirect);
    char *pos;

    if ((pos=strchr(str,'\n')) != NULL)
        *pos = '\0';

    else
        fprintf(stderr,"fgets_s -> input too long for buffer");

    return str_s;
}