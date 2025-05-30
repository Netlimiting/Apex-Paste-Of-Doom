#include "Overlay/Overlay.hpp"
#include "Thread/Thread.hpp"
#include <iostream>
#include <thread>
#include <windows.h>
#include "utils/returnspoof.hpp"
#include "EADesktop Spoofer/EASpoofer.h"

int main(int argc, char* argv[]) {
    SPOOF_FUNC;
    LI_FN(ShowWindow)(GetConsoleWindow(), SW_SHOW);

    LI_FN(Sleep)(2500);
    LI_FN(system)(_("cls"));

    LOG(_("Waiting for Apex\n"));

    HWND GHandle;
    do {
        GHandle = LI_FN(FindWindowA)(_("Respawn001"), _("Apex Legends"));
    } while (!GHandle);

    LI_FN(Sleep)(2500);

    LOG(_("Found Apex\n"));
    LOG(_("Loading Bypass ETA 2 Minutes\n"));

#ifdef p2c // account for game loading 
    LI_FN(Sleep)(120000); 
#endif

    LOG(_("Waiting For Medal\n"));
    while (!drv::find_process(_("Medal.exe"))) {
    }

    LOG(_("Found Medal\n"));

    if (!drv::initialize()) {
        LOG(_("Bypass failed\n"));
        LI_FN(Sleep)(2500);
        return EXIT_FAILURE;
    }

    if (!drv::set_pid(drv::find_process(_("r5apex_dx12.exe")))) {
        LI_FN(printf)(_("Process not found\n"));
        LI_FN(Sleep)(2500);
        return EXIT_FAILURE;
    }

    drv::process_id = drv::set_pid(drv::find_process(_("r5apex_dx12.exe")));

    if (!drv::set_cr3()) {
        LI_FN(Sleep)(2500);
        LOG(_("Failed to get cr3\n"));
        LI_FN(exit)(0);
    }

    sdk.R5Apex = drv::find_process_base();

    if (sdk.R5Apex != NULL) {
        LI_FN(system)(_("cls"));
        LOG(_("Starting Cheat\n"));
        LOG(_("Close Cheat [EXIT BUTTON]\n"));
        LI_FN(Sleep)(1000);

#ifdef p2c
        LI_FN(ShowWindow)(GetConsoleWindow(), SW_HIDE);
#endif

        LI_FN(SetConsoleOutputCP)(CP_UTF8);

        std::thread(&EntityCacha::EntityThread, entCacha).detach();

        BeginCheat();
    }
    else {
        LOG(_("Failed to setup Bypass\n"));
        LI_FN(Sleep)(2500);
        return EXIT_FAILURE;
    }
}
