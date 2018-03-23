**_GTLibc_** library is **[Game Trainer](https://en.wikipedia.org/wiki/Trainer_(games)) library for _c/c++ in windows_** it provides all the necessary methods to make simple game trainer in
windows using **WIN32-API** with ease.
It uses only **WIN32-API** methods instead of **CRT** method because this is intended to work on **Windows** system only
and not shall be portable or to target other OS like **_Linux_,_MAC OS_** etc.

**NOTE** : This ain't memory scanning,hooking,analyzing library, it won't provide methods for scanning/signature or dumping RAW memory.
 
**AIM** : The aim of this library is only to provide the most efficient way of creating game trainer 
and to provide a layer on top of **WIN-32 API** _cumbersome_ methods and to make reading/writing ,finding Game process easier and convenient.


# Main Components :

## Finding game : 

Using **findGameProcess()** method.

**_Finding game by process name_**
![finding_game_process](https://github.com/haseeb-heaven/GTLibc/blob/resources/finding_game_process.jpg?raw=true "")


Using **findGameWindow()** method.

**_Finding game by windows name_**
![finding_game_window](https://github.com/haseeb-heaven/GTLibc/blob/resources/finding_game_window.jpg?raw=true "")


## Reading Values : 

using **readAddress()** or **readAddressoffset()** methods.

**_Reading memory_**
![reading_memory](https://github.com/haseeb-heaven/GTLibc/blob/resources/reading_memory.jpg?raw=true "")

## Writing Values : 

using **writeAddress()** or **writeAddressOffset()** methods.

**_Writing memory_**
![writing_memory](https://github.com/haseeb-heaven/GTLibc/blob/resources/writing_memory.jpg?raw=true "")

## Creating Hot-keys :

using **hotKeysPressed()** **_MACRO_** or **isKeyPressed()/isKeyToggled()** methods.

**_Creating Hotkeys_**
![hotkeys](https://github.com/haseeb-heaven/GTLibc/blob/resources/hotkeys.jpg?raw=true "")

# Additional Components :

## Applying cheat codes : 

using **setCheatCode()** method.

**_Setting cheat code_**
![set_cheat_code](https://github.com/haseeb-heaven/GTLibc/blob/resources/set_cheat_code.jpg?raw=true "")

## Searching offset area : 

using **searchOffsetArea()** method.

**_Searching offset area_**
![search_offset_area](https://github.com/haseeb-heaven/GTLibc/blob/resources/search_offset_area.jpg?raw=true "")

## Automation scripting  : 

using **doMousePress()** and **doKeyPress()** methods.


# GTlibc Logs and errors :

## Multiple Games :
**NOTE** If Multiple games are found then you have to upate the logic of getting input from user again!

**_Multiple Games found warning_**
![multiple_games_warning](https://github.com/haseeb-heaven/GTLibc/blob/resources/multiple_games_warning.jpg?raw=true "")


## Error/Exception Handling :

All the error/exception handling is done by library itself like if you tried read or write from **Invalid Memory section** or if process id,game handle/HWND are invalid  it will autmatically handle error and exits application with error code. So you dont have to check for any error.

**_Game not found error_**
![game_not_found](https://github.com/haseeb-heaven/GTLibc/blob/resources/game_not_found.jpg?raw=true "")


**_Reading invalid memory_**
![reading_invalid_memory](https://github.com/haseeb-heaven/GTLibc/blob/resources/reading_invalid_memory.jpg?raw=true "")


**_Writing invalid memory_**
![writing_invalid_memory](https://github.com/haseeb-heaven/GTLibc/blob/resources/writing_invalid_memory.jpg?raw=true "")


## Methods Accessibility :

All **Public** and **Semi-Public** methods are accessible . But **Private** methods are not and library will throw error if you tried to access them.

**_Private method error_**
![private_method_error](https://github.com/haseeb-heaven/GTLibc/blob/resources/private_method_error.jpg?raw=true "")

## Library Logs :

Logs are **disabled** by default but if you want library to maintain logs use **enableLogs()** method to **enable** logs.
or if you want to **disable** logs again you can use **disableLogs()** method.

**_Enable/Disable Logs_**
![enable_disable_logs](https://github.com/haseeb-heaven/GTLibc/blob/resources/enable_disable_logs.jpg?raw=true "")


# Trainer Demo :
As a demo of this library GTA-SA Trainer is included to show demo of all the methods needed and how to use them in making simple game trainer.

[Video Demo of GTLibc](https://youtu.be/cRCnN987gd8)


**DOCUMENTATION INFO :**
All Public and Semi-Private methods are well documented.
but private methods are not documented as it was not necessary to do so.

**VERSION INFO :**
GTLIBC Version : V 1.0.0.

Written by HaseeB Mir (haseebmir.hm@gmail.com)
Dated : 23/03/2018.
