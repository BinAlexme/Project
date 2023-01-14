#include <thread>
#include "memory_controller.h"
#include "main_ch.h"

const CHAR *name = "Counter-Strike: Global Offensive - Direct3D 9";

int main() {
    srand(time(NULL));
    main_ch cheat(name);
    //cheat.welcome();
    cheat.print_cheat_menu();
    while (!GetAsyncKeyState(VK_INSERT)) {
        cheat.set();
        if(cheat.wall_hack){
            cheat.wallhack();
        }
        if (cheat.RCS) {
            cheat.recoil_control_system();
        }
        if (cheat.radar_hack) {
            cheat.radarhack();
        }
        if (cheat.chams) {
            cheat.chams_func();
        }
        if (cheat.anti_flash) {
            cheat.antiflash();
        }
        if (cheat.trigger_bot) {
            cheat.triggerbot();
        }
        if (cheat.bunny_hop) {
            cheat.bunnyhop();
        }
    }

    cheat.reset_chams();

    return 0;
}
