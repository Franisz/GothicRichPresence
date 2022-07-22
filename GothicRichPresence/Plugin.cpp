// This file added in headers queue
// File: "Sources.h"

namespace GOTHIC_ENGINE {
  void GeneralLoop()
  {
    static Timer timer;
    timer.ClearUnused();

    if ( timer[(uint)0].Await( 1000 * 5, true ) )
    {
      GDiscordRPC::Instance().Update();
    }
  }

  void Game_Entry() {
  }

  void Game_Init() {
    GDiscordRPC::Instance().Initialize();
  }

  void Game_Exit() {
  }

  void Game_PreLoop() {
  }

  void Game_Loop() {
    GeneralLoop();
  }

  void Game_PostLoop() {
  }

  void Game_MenuLoop() {
    GeneralLoop();
  }

  // Information about current saving or loading world
  TSaveLoadGameInfo& SaveLoadGameInfo = UnionCore::SaveLoadGameInfo;

  void Game_SaveBegin() {
  }

  void Game_SaveEnd() {
  }

  void LoadBegin() {
  }

  void LoadEnd() {
    GDiscordRPC::Instance().Update();
  }

  void Game_LoadBegin_NewGame() {
    LoadBegin();
  }

  void Game_LoadEnd_NewGame() {
    LoadEnd();
  }

  void Game_LoadBegin_SaveGame() {
    LoadBegin();
  }

  void Game_LoadEnd_SaveGame() {
    LoadEnd();
  }

  void Game_LoadBegin_ChangeLevel() {
    LoadBegin();
  }

  void Game_LoadEnd_ChangeLevel() {
    LoadEnd();
  }

  void Game_LoadBegin_Trigger() {
  }

  void Game_LoadEnd_Trigger() {
  }

  void Game_Pause() {
  }

  void Game_Unpause() {
    GDiscordRPC::Instance().ReadOptions();
    GDiscordRPC::Instance().Update();
  }

  void Game_DefineExternals() {
  }

  /*
  Functions call order on Game initialization:
    - Game_Entry           * Gothic entry point
    - Game_DefineExternals * Define external script functions
    - Game_Init            * After DAT files init

  Functions call order on Change level:
    - Game_LoadBegin_Trigger     * Entry in trigger
    - Game_LoadEnd_Trigger       *
    - Game_Loop                  * Frame call window
    - Game_LoadBegin_ChangeLevel * Load begin
    - Game_SaveBegin             * Save previous level information
    - Game_SaveEnd               *
    - Game_LoadEnd_ChangeLevel   *

  Functions call order on Save game:
    - Game_Pause     * Open menu
    - Game_Unpause   * Click on save
    - Game_Loop      * Frame call window
    - Game_SaveBegin * Save begin
    - Game_SaveEnd   *

  Functions call order on Load game:
    - Game_Pause              * Open menu
    - Game_Unpause            * Click on load
    - Game_LoadBegin_SaveGame * Load begin
    - Game_LoadEnd_SaveGame   *
  */

#define AppDefault True
  CApplication* lpApplication = !CHECK_THIS_ENGINE ? Null : CApplication::CreateRefApplication(
    Enabled( False ) Game_Entry,
    Enabled( AppDefault ) Game_Init,
    Enabled( False ) Game_Exit,
    Enabled( False ) Game_PreLoop,
    Enabled( AppDefault ) Game_Loop,
    Enabled( False ) Game_PostLoop,
    Enabled( AppDefault ) Game_MenuLoop,
    Enabled( False ) Game_SaveBegin,
    Enabled( False ) Game_SaveEnd,
    Enabled( False ) Game_LoadBegin_NewGame,
    Enabled( AppDefault ) Game_LoadEnd_NewGame,
    Enabled( False ) Game_LoadBegin_SaveGame,
    Enabled( AppDefault ) Game_LoadEnd_SaveGame,
    Enabled( False ) Game_LoadBegin_ChangeLevel,
    Enabled( AppDefault ) Game_LoadEnd_ChangeLevel,
    Enabled( False ) Game_LoadBegin_Trigger,
    Enabled( False ) Game_LoadEnd_Trigger,
    Enabled( False ) Game_Pause,
    Enabled( AppDefault ) Game_Unpause,
    Enabled( False ) Game_DefineExternals
  );
}