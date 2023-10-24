// Supported with union (c) 2020 Union team
// Union HEADER file

#define PLUGIN_NAME "GothicRichPresence"

namespace GOTHIC_ENGINE {
  struct WorldInfo
  {
    string zen;
    string image;
    string name;
  };

  struct RPCStrings
  {
    string title;
    string day;
    string level;
    string chapter;
    string unknownworld;
  };

  struct RPCImages
  {
    const string menu = "menu";
    const string info = "info";
    const string day = "day";
    const string night = "night";
    const string unknown = "unknown";
  };

  struct RPCData
  {
    string state;
    string details;
    string largeImageKey;
    string largeImageText;
    string smallImageKey;
    string smallImageText;
  };

  class GDiscordRPC
  {
  private:
    GDiscordRPC() = default;
    static GDiscordRPC oInstance;
    time_t tStartTimestamp{ 0 };

    nlohmann::json config;
    const string configFileName = "GothicRichPresence.json";

    TSystemLangID language;
    text langSymbol;
    uint ansi_codepage;

    std::vector< WorldInfo > vWorlds;
    RPCStrings strings;
    RPCImages images;
    bool usingCustomKey;
    bool initializedOptions;
    bool enabled;

  public:
    GDiscordRPC( const GDiscordRPC& ) = delete;
    GDiscordRPC& operator=( GDiscordRPC& ) = delete;
    static GDiscordRPC& Instance() { return oInstance; }

    void Initialize();
    void ReadOptions();
    void ParseConfig();
    void ParseWorlds();
    void ParseStrings();
    zSTRING GetGuildName();
    text GetLanguageSymbol( TSystemLangID id );
    uint GetGameEncoding();
    void Update();
  };
}