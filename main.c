// LAST RELEASE BUILD: 1.4
// LAST DEV BUILD: 1.4b

// Since we are building an external plugin dll, we need to import from ClassiCube lib instead of exporting these
#ifdef CC_BUILD_WIN
// need to specifically declare as imported for Visual Studio
#define CC_API __declspec(dllimport)
#define CC_VAR __declspec(dllimport)
#else
#define CC_API
#define CC_VAR
#endif


#include <string.h>
#include <time.h>
#include "src/Entity.h"
#include "src/Chat.h"
#include "src/String.h"
#include "src/Stream.h"
#include "src/Platform.h"
#include "src/Event.h"
#include "src/Game.h"
#include "src/Logger.h"
#include "src/Server.h"
#include "src/Constants.h"

#include "src/World.h"
#include "src/Inventory.h"
#include "src/Window.h"
#include "src/Graphics.h"
#include "src/Funcs.h"
#include "src/Block.h"
#include "src/EnvRenderer.h"
#include "src/Utils.h"
#include "src/TexturePack.h"
#include "src/Options.h"
#include "src/Drawer2D.h"

#include "src/Commands.h"
#include "src/Vectors.h"
#include "src/Vorbis.h"
#include "src/Utils.h"
#include "src/Server.h"

/*########################################################################################################################*
*---------------------------------------------------Plugin implementation-------------------------------------------------*
*#########################################################################################################################*/
static struct _ServerConnectionData* Server_;

#define SendChat(msg) const static cc_string str = String_FromConst(msg); Chat_Add(&str);


static void TestCommand_Execute(const cc_string* args, int argsCount) {
    Window_ShowDialog("TEST", "Just a test");
}

static struct ChatCommand TestCmd = {
	"Test", TestCommand_Execute, false,
	{
		"&a/client Test",
		"&eThis is just a test",
		"",
	}
};





static void CpeTestCommand_Execute(const cc_string* args, int argsCount) {
    SendChat("&fuse &a/CpeTest clear &fto reset all CPE Messages");
    cc_string message = String_FromConst("Hello, World!");
    cc_string message2 = String_FromConst("");
    Chat_AddOf(&message, MSG_TYPE_ANNOUNCEMENT);
    Chat_AddOf(&message, MSG_TYPE_BIGANNOUNCEMENT);
    Chat_AddOf(&message, MSG_TYPE_SMALLANNOUNCEMENT);
    Chat_AddOf(&message, MSG_TYPE_STATUS_1);
    Chat_AddOf(&message, MSG_TYPE_STATUS_2);
    Chat_AddOf(&message, MSG_TYPE_STATUS_3);
    Chat_AddOf(&message, MSG_TYPE_BOTTOMRIGHT_1);
    Chat_AddOf(&message, MSG_TYPE_BOTTOMRIGHT_2);
    Chat_AddOf(&message, MSG_TYPE_BOTTOMRIGHT_3);
    Chat_Add(&message);
    if (String_CaselessEqualsConst(&args[0], "clear")) { 
    Chat_AddOf(&message2, MSG_TYPE_ANNOUNCEMENT);
    Chat_AddOf(&message2, MSG_TYPE_BIGANNOUNCEMENT);
    Chat_AddOf(&message2, MSG_TYPE_SMALLANNOUNCEMENT);
    Chat_AddOf(&message2, MSG_TYPE_STATUS_1);
    Chat_AddOf(&message2, MSG_TYPE_STATUS_2);
    Chat_AddOf(&message2, MSG_TYPE_STATUS_3);
    Chat_AddOf(&message2, MSG_TYPE_BOTTOMRIGHT_1);
    Chat_AddOf(&message2, MSG_TYPE_BOTTOMRIGHT_2);
    Chat_AddOf(&message2, MSG_TYPE_BOTTOMRIGHT_3);
    }
}

static struct ChatCommand CpeTestCmd = {
	"CpeTest", CpeTestCommand_Execute, false,
	{
		"&a/client CpeTest",
		"&ePrints 'Hello, World!' with different message types",
		"",
	}
};





static void WeatherCommand_Execute(const cc_string* args, int argsCount) {
    if (argsCount < 1) {
        SendChat("&eUsage: /weather [Sunny/Rainy/Snowy]");
        return;
    }

    if (String_CaselessEqualsConst(&args[0], "Sunny")) {
        Env_SetWeather(0);
        SendChat("&eWeather changed to &aSunny");
    } else if (String_CaselessEqualsConst(&args[0], "Rainy")) {
        Env_SetWeather(1);
	SendChat("&eWeather changed to &aRainy");   
		} else if (String_CaselessEqualsConst(&args[0], "Snowy")) {
        Env_SetWeather(2);
        SendChat("&eWeather changed to &aSnowy");
	   
		}
    else {
        SendChat("Invalid weather type. Please use Sunny, Rainy, or Snowy.");
    }
}

static struct ChatCommand WeatherCmd = {
    "Weather", WeatherCommand_Execute, false,
    {
        "&a/client weather [Sunny/Rainy/Snowy]",
        "&eChange The Weather :D",
    }
};



static void ClearCommand_Execute(const cc_string* args, int argsCount) {
    cc_string msg = String_FromConst("");
    for (int i = 1; i < 20; i++) {Chat_Add(&msg);}
    Chat_Add(&msg);
    SendChat("&cChat Cleared!");


}

static struct ChatCommand ClearCmd = {
    "Clear", ClearCommand_Execute, false,
    {
        		"&a/client clear",
		"&eAlternative Clear Cmd (From MCGalaxy)",
    }
};

static void HacksCommand_Execute(const cc_string* args, int argsCount) {
	
    struct LocalPlayer* p = (struct LocalPlayer*)Entities.List[255];

    // Check if the correct number of arguments is provided.
    if (argsCount != 1) {
        SendChat("&e/Hacks: &cTrue or False!!");
        return;
    }
    

    if (String_CaselessEqualsConst(&args[0], "true")) {
	p->Hacks.CanAnyHacks       = true;
	p->Hacks.CanFly            = true;
	p->Hacks.CanNoclip         = true;
	p->Hacks.CanSpeed          = true;
	p->Hacks.CanRespawn        = true;
	p->Hacks.CanUseThirdPerson = true;
	p->Hacks.CanPushbackBlocks = true;
	p->Hacks.CanBePushed       = false;
        SendChat("&eHacks Enabled!"); 
  }
   else if (String_CaselessEqualsConst(&args[0], "false")) {
	
        p->Hacks.CanAnyHacks       = false;
	p->Hacks.CanFly            = false;
	p->Hacks.CanNoclip         = false;
	p->Hacks.CanSpeed          = false;
	p->Hacks.CanRespawn        = false;
	p->Hacks.CanUseThirdPerson = false;
	p->Hacks.CanPushbackBlocks = false;
	p->Hacks.CanBePushed       = true;
        SendChat("&eHacks Disabled!");

}
  else {
        SendChat("&e/Hacks: &cInvalid argument. Use True or False.");
    }
}

static struct ChatCommand HacksCmd = {
    "Hacks", HacksCommand_Execute, false,
    {
        "/hacks (True/False)",
        "&cNote: &eOnly in Singleplayer",
    }
};

static void TP2Command_Execute(const cc_string* args, int argsCount) {
    
    struct Entity* e = (struct Entity*)Entities.List[255];
	struct LocationUpdate update;
	Vec3 v;

	if (argsCount != 3) {
		SendChat("&e/client TP2: &cYou didn't specify X, Y and Z coordinates.");
		return;
	}
	if (!Convert_ParseFloat(&args[0], &v.x) || !Convert_ParseFloat(&args[1], &v.y) || !Convert_ParseFloat(&args[2], &v.z)) {
		SendChat("&e/client TP2: &cCoordinates must be decimals");
		return;
	}

	update.flags = LU_HAS_POS;
	update.pos   = v;
	e->VTABLE->SetLocation(e, &update);
}

static void ChangeAppnameCommand_Execute(const cc_string* args, int argsCount) {
    
    	cc_uint8 buffer[67];
	buffer[0] = 0x10;
	String_CopyToRaw(buffer + 1, 64, args);
	for (int i = args->length + 1; i < 65; i++) { buffer[i] = ' '; }
	buffer[65] = 0; buffer[66] = 0;
	
	Server.SendData(buffer, 67);
}

static struct ChatCommand ChangeAppnameCommand = {
    "ChangeAppname", ChangeAppnameCommand_Execute,
    COMMAND_FLAG_UNSPLIT_ARGS,
    {
        "&a/ChangeAppname [new app name]",
        "&aChanges your client name to the desired one.",
    }
};

static struct ChatCommand TP2Cmd = {
	"TP2", TP2Command_Execute, false,
	{
		"&a/client TP2 [x y z]",
		"&eMoves you to the given coordinates, also works on Multiplayer.",
                "&aShhh...",
	}
};

static void a(void) {


    char appname[64] = GAME_APP_NAME " + cheats";

    
    cc_uint8 buffer[67];
    buffer[0] = 0x10;
    memcpy(buffer + 1, appname, 64);
    buffer[65] = 0; buffer[66] = 0;
    
    Server.SendData(buffer, 67);
}

static void NovaCraft_Init(void) {

	
    Commands_Register(&CpeTestCmd);
    Commands_Register(&HacksCmd);
    Commands_Register(&ClearCmd);

    Commands_Register(&ChangeAppnameCommand);
    Commands_Register(&WeatherCmd);
    Commands_Register(&TestCmd);
    Commands_Register(&TP2Cmd);
    String_AppendConst(&Server.AppName, " + cheats"); 
    
}


/*########################################################################################################################*
*----------------------------------------------------Plugin boilerplate---------------------------------------------------*
*#########################################################################################################################*/
// Since we are building an external plugin dll, we need to import from ClassiCube lib instead of exporting these
#ifdef CC_BUILD_WIN
// special attribute to get symbols exported with Visual Studio
#define PLUGIN_EXPORT __declspec(dllexport)
#else
// public symbols already exported when compiling shared lib with GCC
#define PLUGIN_EXPORT
#endif





PLUGIN_EXPORT int Plugin_ApiVersion = 1;
PLUGIN_EXPORT struct IGameComponent Plugin_Component = {
	NovaCraft_Init /* Init */
};
