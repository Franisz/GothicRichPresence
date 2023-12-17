// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
  zSTRING GDiscordRPC::GetGuildName() {
    if ( int index = parser->GetIndex( "RX_IsDemonHunter" ) )
      if ( int ret = *(int*)parser->CallFunc( index ) )
        if ( auto sym = parser->GetSymbol( "RX_GuildDemonHunter" ) )
          return sym->stringdata;

    if ( int index = parser->GetIndex( "RX_IsDarkWarrior" ) )
      if ( int ret = *(int*)parser->CallFunc( index ) )
        if ( auto sym = parser->GetSymbol( "RX_GuildDarkWarrior" ) )
          return sym->stringdata;

    if ( int index = parser->GetIndex( "RX_IsDarkMage" ) )
      if ( int ret = *(int*)parser->CallFunc( index ) )
        if ( auto sym = parser->GetSymbol( "RX_GuildDarkMage" ) )
          return sym->stringdata;

    if ( int index = parser->GetIndex( "RX_IsNecroSummoner" ) )
      if ( int ret = *(int*)parser->CallFunc( index ) )
        if ( auto sym = parser->GetSymbol( "RX_GuildSummoner" ) )
          return sym->stringdata;

    if ( int index = parser->GetIndex( "RX_IsScout" ) )
      if ( int ret = *(int*)parser->CallFunc( index ) )
        if ( auto sym = parser->GetSymbol( "RX_GuildScout" ) )
          return sym->stringdata;

    return player->GetGuildName();
  }
}
