#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <intrin.h>

static FILE* g_log = NULL;
static void log(const char* fmt, ...){ if(!g_log) g_log=fopen("mini_emulator.log","a"); if(g_log){ va_list ap; va_start(ap, fmt); vfprintf(g_log, fmt, ap); va_end(ap); fprintf(g_log, "\n"); fflush(g_log);} }

#define EXPORT __declspec(dllexport)

static void* slot_stub(void){
    char buf[256];
    sprintf(buf, "ISteamVMTCall from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId());
    log(buf);
    return (void*)1;
}

static void** fake_vtable[128];
static struct { void* vtbl; } fake_iface = { fake_vtable };
static void init_vtable() { for (int i=0;i<128;i++) fake_vtable[i]=(void*)slot_stub; }

EXPORT bool SteamAPI_Init() { log("SteamAPI_Init from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); init_vtable(); return true; }
EXPORT void SteamAPI_Shutdown() { log("SteamAPI_Shutdown from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); }
EXPORT bool SteamAPI_RestartAppIfNecessary(unsigned int a) { log("SteamAPI_RestartAppIfNecessary from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return false; }
EXPORT int SteamAPI_GetHSteamUser() { log("SteamAPI_GetHSteamUser from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return 1; }
EXPORT int SteamAPI_GetHSteamPipe() { log("SteamAPI_GetHSteamPipe from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return 1; }
EXPORT void* SteamInternal_CreateInterface(const char* v) { log("SteamInternal_CreateInterface from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamInternal_FindOrCreateUserInterface() { log("SteamInternal_FindOrCreateUserInterface from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamInternal_FindOrCreateGameServerInterface() { log("SteamInternal_FindOrCreateGameServerInterface from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT bool SteamInternal_ContextInit() { log("SteamInternal_ContextInit from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return true; }

EXPORT bool SteamAPI_ManualDispatch_Init() { log("SteamAPI_ManualDispatch_Init from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return true; }
EXPORT int SteamAPI_ManualDispatch_RunFrame(int hPipe) { log("SteamAPI_ManualDispatch_RunFrame from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return 0; }
EXPORT int SteamAPI_ManualDispatch_GetNextCallback(int hPipe, void* pMsg) { log("SteamAPI_ManualDispatch_GetNextCallback from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return 0; }
EXPORT void SteamAPI_ManualDispatch_FreeLastCallback(int hPipe, int cb) { log("SteamAPI_ManualDispatch_FreeLastCallback from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); }
EXPORT int SteamAPI_ManualDispatch_GetAPICallResult(const void* hAPI, const void* hCall, void* pOut) { log("SteamAPI_ManualDispatch_GetAPICallResult from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return 0; }

EXPORT void* SteamApps() { log("SteamApps from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamUser() { log("SteamUser from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamUtils() { log("SteamUtils from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamFriends() { log("SteamFriends from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamUserStats() { log("SteamUserStats from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamMatchmaking() { log("SteamMatchmaking from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamNetworking() { log("SteamNetworking from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamRemoteStorage() { log("SteamRemoteStorage from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamScreenshots() { log("SteamScreenshots from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamHTTP() { log("SteamHTTP from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamController() { log("SteamController from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamUGC() { log("SteamUGC from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamAppList() { log("SteamAppList from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamMusic() { log("SteamMusic from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamMusicRemote() { log("SteamMusicRemote from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamHTMLSurface() { log("SteamHTMLSurface from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamInventory() { log("SteamInventory from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamVideo() { log("SteamVideo from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamParentalSettings() { log("SteamParentalSettings from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamGameServer() { log("SteamGameServer from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamGameServerStats() { log("SteamGameServerStats from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }

EXPORT void* SteamAPI_ISteamClient_GetISteamUser() { log("SteamAPI_ISteamClient_GetISteamUser from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamAPI_ISteamClient_GetISteamFriends() { log("SteamAPI_ISteamClient_GetISteamFriends from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamAPI_ISteamClient_GetISteamUtils() { log("SteamAPI_ISteamClient_GetISteamUtils from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamAPI_ISteamClient_GetISteamMatchmaking() { log("SteamAPI_ISteamClient_GetISteamMatchmaking from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamAPI_ISteamClient_GetISteamMatchmakingServers() { log("SteamAPI_ISteamClient_GetISteamMatchmakingServers from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamAPI_ISteamClient_GetISteamUserStats() { log("SteamAPI_ISteamClient_GetISteamUserStats from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamAPI_ISteamClient_GetISteamApps() { log("SteamAPI_ISteamClient_GetISteamApps from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamAPI_ISteamClient_GetISteamNetworking() { log("SteamAPI_ISteamClient_GetISteamNetworking from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamAPI_ISteamClient_GetISteamRemoteStorage() { log("SteamAPI_ISteamClient_GetISteamRemoteStorage from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamAPI_ISteamClient_GetISteamScreenshots() { log("SteamAPI_ISteamClient_GetISteamScreenshots from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamAPI_ISteamClient_GetISteamGameSearch() { log("SteamAPI_ISteamClient_GetISteamGameSearch from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamAPI_ISteamClient_GetISteamHTTP() { log("SteamAPI_ISteamClient_GetISteamHTTP from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamAPI_ISteamClient_GetISteamUGC() { log("SteamAPI_ISteamClient_GetISteamUGC from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamAPI_ISteamClient_GetISteamAppList() { log("SteamAPI_ISteamClient_GetISteamAppList from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamAPI_ISteamClient_GetISteamMusic() { log("SteamAPI_ISteamClient_GetISteamMusic from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamAPI_ISteamClient_GetISteamMusicRemote() { log("SteamAPI_ISteamClient_GetISteamMusicRemote from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamAPI_ISteamClient_GetISteamHTMLSurface() { log("SteamAPI_ISteamClient_GetISteamHTMLSurface from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamAPI_ISteamClient_GetISteamInventory() { log("SteamAPI_ISteamClient_GetISteamInventory from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamAPI_ISteamClient_GetISteamVideo() { log("SteamAPI_ISteamClient_GetISteamVideo from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamAPI_ISteamClient_GetISteamParentalSettings() { log("SteamAPI_ISteamClient_GetISteamParentalSettings from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamAPI_ISteamClient_GetISteamInput() { log("SteamAPI_ISteamClient_GetISteamInput from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamAPI_ISteamClient_GetISteamParties() { log("SteamAPI_ISteamClient_GetISteamParties from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }
EXPORT void* SteamAPI_ISteamClient_GetISteamRemotePlay() { log("SteamAPI_ISteamClient_GetISteamRemotePlay from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return &fake_iface; }

EXPORT unsigned long long SteamAPI_ISteamUser_GetSteamID() { log("SteamAPI_ISteamUser_GetSteamID from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return 76561198000000000ULL; }
EXPORT bool SteamAPI_ISteamUser_BLoggedOn() { log("SteamAPI_ISteamUser_BLoggedOn from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return true; }
EXPORT unsigned int SteamAPI_ISteamUtils_GetAppID() { log("SteamAPI_ISteamUtils_GetAppID from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return 105600; }
EXPORT bool SteamAPI_ISteamUserStats_RequestCurrentStats(void* pStats) { log("SteamAPI_ISteamUserStats_RequestCurrentStats from 0x%08X tid=%d", (unsigned)_ReturnAddress(), GetCurrentThreadId()); return true; }

BOOL APIENTRY DllMain(HMODULE h, DWORD r, LPVOID x){ if(r==DLL_PROCESS_ATTACH) log("emulator attached"); return TRUE; }
