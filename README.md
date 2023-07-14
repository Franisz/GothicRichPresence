# GothicRichPresence

This is [Discord Rich Presence](https://discord.com/rich-presence) plugin made in [Union](https://worldofplayers.ru/threads/40376/) **1.0l** for Gothic I and II.

## Preview

![Preview](https://i.imgur.com/1fBTsKt.gif)

# Usage for regular users

1. Download and install [Union](https://worldofplayers.ru/threads/40376/).
2. Download `GothicRichPresence.vdf` file from the [latest release](../../releases) and place it in `<GothicPath>\Data\Plugins\` folder.
3. If for some reason, language of the rich presence is not right, change is via ingame menu.

# Usage for mod developers

You can easily implement this plugin into your mod to change images or handle more worlds.

#### 1. First you have to set up your own Discord application:

- Log-In to [Discord Developer Portal](https://discord.com/developers/applications) and go to `Applications` section.
- Create `New Application` and set a name. This name will be displayed as a title on rich presence and should be named `Gothic: Mod Name` or somewhat similar.
- Copy `Application ID`, it will be needed later.

#### 2. Upload and set your own images for worlds specified later in the config. Additionally some images have constant names, and you need to upload them for proper usage:

- Image with name `menu` will be displayed when player currently is in menu, or in unknown location.
- Image with name `info`, `day` and `night` will be displayed in the bottom-right corner of your location pic, and it contains information about game time.
- Image with name `unknown` will be displayed when player is in `zen` not present in the config.
- One image for every `zen` in your mod. Those images will be used as a cover when player is in this location.
- Remember to also set `App Icon` and `Cover Image`.

#### 3. Now you need to create a `GothicRichPresence.json` config file, which you can put right into your `.vdf`/`.mod` file in the `System\` folder. I advise editing default config that can be downloaded in [releases](../../releases). And don't use zipped `.vdf`/`.mod`.

#### 4. Create `publickeyoverride` and copy `APPLICATION ID` from [Discord Developer Portal](https://discord.com/developers/applications) as it's value as shown below.

```json
{
  "publickeyoverride": "APPLICATION ID",
  "strings": {},
  "worlds": []
}
```

#### 5. `strings` object contains translations for general strings used by the plugin. I recommend not to change them.

```json
{
  "publickeyoverride": "APPLICATION ID",
  "strings": {
    "day": {
      "eng": "Day",
      "pol": "Dzień",
      "rus": "День",
      "ger": "Tag"
    },
    "level": {
      "eng": "Level",
      "pol": "Poziom",
      "rus": "ур.",
      "ger": "Stufe"
    },
    "chapter": {
      "eng": "Chapter",
      "pol": "Rozdział",
      "rus": "Глава",
      "ger": "Kapitel"
    },
    "unknownworld": {
      "eng": "Unknown Lands",
      "pol": "Nieznana Kraina",
      "rus": "Неизвестные Земли",
      "ger": "Unbekanntes Land"
    }
  },
  "worlds": []
}
```

#### 6. `worlds` array contains names and images for all `zen`'s.

```json
{
  "publickeyoverride": "APPLICATION ID",
  "strings": {},
  "worlds": [
    {
      "zen": "orcgraveyard",
      "image": "orcgraveyard",
      "name": {
        "eng": "Orc Graveyard",
        "pol": "Cmentarzysko Orków",
        "rus": "Кладбище Орков",
        "ger": "Orkfriedhof"
      }
    },
    {
      "zen": "orctempel",
      "image": "orctempel",
      "name": {
        "eng": "Sleeper Temple",
        "pol": "Świątynia Śniącego",
        "rus": "Храм Спящего",
        "ger": "Tempel des Schläfers"
      }
    }
  ]
}
```

- Each location object must have 2 strings: `zen` and `image`.
- `zen` must be the same as the `.zen` in game files.
- `image` is cover image of that location. You **must** upload image with same name to _Rich Presence Assets_ at [Discord Developer Portal](https://discord.com/developers/applications).
- `name` is an object containing names for different languages.

  - Plugin supports all languages that are supported by [Union](https://worldofplayers.ru/threads/40376/).
  - Language is based on `Language` symbol in `[CORE]` section from `SystemPack.ini`.

<details>
  <summary>Default config</summary>

```json
{
  "publickeyoverride": "",
  "strings": {
    "day": {
      "eng": "Day",
      "pol": "Dzień",
      "rus": "День",
      "ger": "Tag"
    },
    "level": {
      "eng": "Level",
      "pol": "Poziom",
      "rus": "ур.",
      "ger": "Stufe"
    },
    "chapter": {
      "eng": "Chapter",
      "pol": "Rozdział",
      "rus": "Глава",
      "ger": "Kapitel"
    },
    "unknownworld": {
      "eng": "Unknown Lands",
      "pol": "Nieznana Kraina",
      "rus": "Неизвестные Земли",
      "ger": "Unbekanntes Land"
    }
  },
  "worlds": [
    {
      "zen": "newworld",
      "image": "newworld",
      "name": {
        "eng": "Khorinis",
        "pol": "Khorinis",
        "rus": "Хоринис",
        "ger": "Neue Welt"
      }
    },
    {
      "zen": "oldworld",
      "image": "oldworld",
      "name": {
        "eng": "Valley of Mines",
        "pol": "Górnicza Dolina",
        "rus": "Долина Рудников",
        "ger": "Alte Welt"
      }
    },
    {
      "zen": "addonworld",
      "image": "addonworld",
      "name": {
        "eng": "Jharkendar",
        "pol": "Jarkendar",
        "rus": "Яркендар",
        "ger": "Jharkendar"
      }
    },
    {
      "zen": "dragonisland",
      "image": "dragonisland",
      "name": {
        "eng": "Irdorath",
        "pol": "Irdorath",
        "rus": "Ирдорат",
        "ger": "Irdorath"
      }
    },
    {
      "zen": "world",
      "image": "world",
      "name": {
        "eng": "Penal Colony",
        "pol": "Kolonia Karna",
        "rus": "Колония",
        "ger": "Strafkolonie"
      }
    },
    {
      "zen": "oldmine",
      "image": "oldmine",
      "name": {
        "eng": "Old Mine",
        "pol": "Stara Kopalnia",
        "rus": "Старая Шахта",
        "ger": "Alte Mine"
      }
    },
    {
      "zen": "freemine",
      "image": "freemine",
      "name": {
        "eng": "Free Mine",
        "pol": "Wolna Kopalnia",
        "rus": "Свободная Шахта",
        "ger": "Freie Mine"
      }
    },
    {
      "zen": "orcgraveyard",
      "image": "orcgraveyard",
      "name": {
        "eng": "Orc Graveyard",
        "pol": "Cmentarzysko Orków",
        "rus": "Кладбище Орков",
        "ger": "Orkfriedhof"
      }
    },
    {
      "zen": "orctempel",
      "image": "orctempel",
      "name": {
        "eng": "Sleeper Temple",
        "pol": "Świątynia Śniącego",
        "rus": "Храм Спящего",
        "ger": "Tempel des Schläfers"
      }
    }
  ]
}
```

</details>
