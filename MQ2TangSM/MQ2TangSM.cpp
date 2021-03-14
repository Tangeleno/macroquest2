// MQ2TangSM.cpp : Defines the entry point for the DLL application.
//

// PLUGIN_API is only to be used for callbacks.  All existing callbacks at this time
// are shown below. Remove the ones your plugin does not use.  Always use Initialize
// and Shutdown for setup and cleanup, do NOT do it in DllMain.



#include "../MQ2Plugin.h"


PreSetup("MQ2TangSM");

// Called once, when the plugin is to initialize
PLUGIN_API VOID InitializePlugin(VOID)
{
    DebugSpewAlways("Initializing MQ2TangSM");

}

// Called once, when the plugin is to shutdown
PLUGIN_API VOID ShutdownPlugin(VOID)
{
    DebugSpewAlways("Shutting down MQ2TangSM");
}

// Called once directly after initialization, and then every time the gamestate changes
PLUGIN_API VOID SetGameState(DWORD GameState)
{
    DebugSpewAlways("MQ2TangSM::SetGameState()");
    //if (GameState==GAMESTATE_INGAME)
    // create custom windows if theyre not set up, etc
}

// This is called every time MQ pulses
PLUGIN_API VOID OnPulse(VOID)
{
    // DONT leave in this debugspew, even if you leave in all the others
    //DebugSpewAlways("MQ2TangSM::OnPulse()");
}
