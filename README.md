# SteamEmulator

A tiny MSVC stub for `steam_api.dll` that makes a Steam game think Steam is running — no client, no login, no license check.

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

- The fake vtable is 128 slots, all pointing at one generic stub. Any call the game makes through it gets logged and answered with a "yes"-ish value.
- Every exported function appends a line to `mini_emulator.log` in the game's working directory, so you can see exactly what a game is calling and teach the stub a specific answer for whatever it turns out to need.

## Folder layout

```
x86/    32-bit build (for 32-bit games)
x64/    64-bit build (for 64-bit games)
```

Each folder is self-contained: `mini_emulator.c`, a `.def` file, and a `build.bat`. The two are independent implementations of the same idea — the x86 one has richer logging (caller address + thread id), the x64 one is a simpler earlier iteration.

## Building

Needs MSVC (Visual Studio 2022 Community here), via the 32/64-bit build environments:

```bat
:: 32-bit
cd x86
build.bat
```
→ produces `steam_api.dll`

```bat
:: 64-bit
cd x64
build.bat
```
→ produces `steam_api64.dll`

## Using it

1. Build the DLL that matches the game's architecture.
2. Copy it next to the game's `.exe`, **replacing** the game's original `steam_api.dll` (rename the 64-bit one to `steam_api.dll` if needed).
3. Launch the game — Steam doesn't need to be open.

> A 32-bit game won't load a 64-bit DLL and vice versa, so pick the matching folder.

## Caveats

- It's a stub, not a full Steam emulation. Only the calls a given game actually makes matter. If a game needs a real answer somewhere (callback data, friends list, achievements...), teach the stub that specific one.
- `mini_emulator.log` is how you find out what's missing: it records everything the game calls.
- App ID and SteamID are hardcoded constants for now.
