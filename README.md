# SteamEmulator

A tiny x86 stub for `steam_api.dll` that makes a Steam game think Steam is running — no client, no login, no license check.

## What it does

Steam games talk to the Steam client through `steam_api.dll`. This project builds a fake replacement that answers the common questions with "yes":

- `SteamAPI_Init()` / `SteamAPI_ManualDispatch_Init()` → `true`
- `SteamAPI_ISteamUser_BLoggedOn()` → `true`
- `SteamAPI_ISteamUser_GetSteamID()` → hardcoded SteamID
- `SteamAPI_ISteamUtils_GetAppID()` → `105600` (hardcoded fallback)
- every interface getter (`SteamApps()`, `SteamUser()`, `SteamInternal_CreateInterface()`, `SteamAPI_ISteamClient_Get*`, ...) returns one shared fake vtable

That's enough for many games' "is Steam running / is the app owned / is it installed" checks to pass, so you can:

- run a Steam game with the Steam client closed
- hand a game to someone who doesn't actually own it — replace their `steam_api.dll` with this one and it runs

## How it works

- The fake vtable is 128 slots, all pointing at one generic stub. Any call the game makes through it gets logged and answered with `(void*)1` (i.e. "yes" / pointer-ish true).
- Every exported function appends a line to `mini_emulator.log` in the game's working directory — `function name from 0xADDR tid=NNN` — so you can see exactly what a game is calling and add real answers for whatever it turns out to need.

## Building

Needs MSVC (Visual Studio 2022 Community here), 32-bit build:

```bat
build.bat
```

That's just:

```bat
cl /nologo /LD mini_emulator.c steam_api.def /Fe:steam_api.dll
```

Output: `steam_api.dll` (plus the usual `.lib` / `.exp`).

## Using it

1. Build `steam_api.dll` from this repo.
2. Copy it next to the game's `.exe`, **replacing** the game's original `steam_api.dll`.
3. Launch the game — Steam doesn't need to be open.

> This DLL is **x86 (32-bit)**. A 64-bit game won't load it; a 64-bit build of this would need to be made.

## Caveats

- It's a stub, not a full Steam emulation. Only the calls a given game actually makes matter. If a game needs a real answer somewhere (callback data, friends list, achievements...), teach the stub that specific one.
- `mini_emulator.log` is how you find out what's missing: it records everything the game calls.
- App ID and SteamID are hardcoded constants for now.
