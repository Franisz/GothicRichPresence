// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
  GDiscordRPC GDiscordRPC::oInstance;

  void GDiscordRPC::Initialize()
  {
    language = GetSysPackLanguage().Lower();

    ParseConfig();
    ParseWorlds();
    ParseStrings();

    // Default app keys
#if ENGINE >= Engine_G2
    string AppId = "925674889350889482";
#else
    string AppId = "925673141609574401";
#endif

    if ( config["publickeyoverride"].is_string() ) {
      string publickeyoverride = config["publickeyoverride"].get<std::string>().c_str();
      if ( publickeyoverride.Length() ) {
        AppId = publickeyoverride;
        usingCustomKey = true;
      }
    }

    // Init RPC with given app key (default or from the config)
    DiscordEventHandlers handlers;
    memset( &handlers, 0, sizeof( handlers ) );
    Discord_Initialize( AppId, &handlers, false, NULL );
    tStartTimestamp = std::time( nullptr );
    Update();
  }

  string GDiscordRPC::GetSysPackLanguage()
  {
    string lang;
    Union.GetSysPackOption().Read( lang, "CORE", "Language" );
    return (lang.Length()) ? lang : "eng";
  }

  void GDiscordRPC::ParseConfig()
  {
    zoptions->ChangeDir( DIR_SYSTEM );
    zFILE_VDFS* originFile = new zFILE_VDFS( configFileName );

    if ( !originFile->Exists() ) {
      delete originFile;
      return;
    }

    originFile->Open( false );

    zSTRING line, buffer;
    do {
      originFile->Read( line );
      buffer += line;
    } while ( !originFile->Eof() );

    config = nlohmann::json::parse( buffer.ToChar() );
  }

  void GDiscordRPC::ParseWorlds()
  {
    if ( !config["worlds"].is_array() )
      return;

    if ( config["worlds"].size() < 1 )
      return;

    for ( auto& el : config["worlds"].items() ) {
      if ( !el.value().is_object() )
        continue;

      if ( !el.value()["zen"].is_string() )
        continue;

      if ( !el.value()["image"].is_string() )
        continue;

      if ( !el.value()["name"].is_object() )
        continue;

      if ( !el.value()["name"][language.ToChar()].is_string() )
        continue;

      WorldInfo world;
      world.zen = A el.value()["zen"].get<std::string>().c_str();
      world.image = A el.value()["image"].get<std::string>().c_str();
      world.name = A el.value()["name"][language.ToChar()].get<std::string>().c_str();
      vWorlds.push_back( world );
    }
  }

  void GDiscordRPC::ParseStrings()
  {
#define GETRPCSTRING(x) ( ( config["strings"][x].is_object() && config["strings"][x][language.ToChar()].is_string() ) ? A config["strings"][x][language.ToChar()].get<std::string>().c_str() : "" )

    // Modification title when playing from gothic starter and not using custom application
    if ( zgameoptions && !Union.GetGameIni().Compare( "gothicgame.ini" ) && !usingCustomKey )
      strings.title = A zgameoptions->ReadString( "Info", "Title", "Unknown Title" );

    if ( !config["strings"].is_object() )
      return;

    strings.day = GETRPCSTRING( "day" );
    strings.level = GETRPCSTRING( "level" );
    strings.chapter = GETRPCSTRING( "chapter" );
    strings.unknownworld = GETRPCSTRING( "unknownworld" );

#undef GETRPCSTRING
  }

  void GDiscordRPC::Update()
  {
    RPCData data;

    if ( ogame && ogame->GetGameWorld() && player ) {
      // Ingame time
      if ( strings.day.Length() ) {
        int day, hour, min;
        ogame->GetTime( day, hour, min );
        data.smallImageKey = (hour >= 6 && hour < 20) ? images.day : images.night;
        data.smallImageText = string::Combine( "%s %u - %u:%s", strings.day, day, hour, (min > 9) ? A min : A "0" + A min );
      }

      // Hero guild and level
      if ( strings.level.Length() ) {
        string guild = A ansi_to_utf8( GetGuildName().ToChar() ).c_str();
        data.state = string::Combine( "%s - %s %u", guild, strings.level, player->level );

        // Adding current chapter info if kapitel variable is present
        if ( strings.chapter.Length() )
          if ( auto sym = parser->GetSymbol( "kapitel" ) )
            if ( int kapitel = sym->single_intdata )
              data.state = string::Combine( "%s - %s %u", data.state, strings.chapter, kapitel );
      }

      // Location name and image
      bool foundWorld = false;
      for ( WorldInfo world : vWorlds ) {
        // Must be exact the same names to avoid mistaking for example world.zen with newworld.zen
        if ( ogame->GetGameWorld()->GetWorldName().Compare( Z world.zen.Upper() ) ) {
          data.largeImageKey = world.image;
          data.largeImageText = world.name;
          foundWorld = true;
          break;
        }
      }

      // Unknown location
      if ( !foundWorld && strings.unknownworld.Length() ) {
        data.largeImageKey = images.unknown;
        data.largeImageText = strings.unknownworld;
      }
    }

    // Modification title when playing from gothic starter and not using custom application
    if ( strings.title.Length() )
      data.details = strings.title;

    // General image when not in game
    if ( !data.largeImageKey.Length() )
      data.largeImageKey = images.menu;

    DiscordRichPresence discordPresence;
    memset( &discordPresence, 0, sizeof( discordPresence ) );
    discordPresence.startTimestamp = tStartTimestamp;
    discordPresence.state = data.state;
    discordPresence.details = data.details;
    discordPresence.largeImageKey = data.largeImageKey;
    discordPresence.largeImageText = data.largeImageText;
    discordPresence.smallImageKey = data.smallImageKey;
    discordPresence.smallImageText = data.smallImageText;
    Discord_UpdatePresence( &discordPresence );
  }
}