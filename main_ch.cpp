#include "main_ch.h"

void main_ch::set_chams(DWORD entity, int r, int g, int b) {
    m.WPM<int>(entity + 112, r);
    m.WPM<int>(entity + 113, g);
    m.WPM<int>(entity + 114, b);
}

void main_ch::reset_chams() {
    for (int i = 0; i < 64; i++) {
        auto entity = m.RPM<DWORD>(client + hazedumper::signatures::dwEntityList + i * 0x10);
        set_chams(entity, 255, 255, 255);
    }
}

void main_ch::delay(int d) {
    if (d) {
        Sleep(d);
    }
}

void main_ch::click() {
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}
void main_ch::set_var(bool &var, int key){
    if (GetKeyState(key)) {
        if (!var) {
            var = true;
            print_cheat_menu();
        }
    } else {
        if (var) {
            var = false;
            print_cheat_menu();
        }
    }
}
void main_ch::set() {
    set_var(radar_hack, VK_F1);
    set_var(bunny_hop, VK_F2);
    set_var(legit_bunny_hop, VK_HOME);
    set_var(trigger_bot, VK_F3);
    set_var(legit_trigger_bot, VK_END);
    set_var(teammates, VK_DELETE);
    set_var(anti_flash, VK_F4);
    //set_var(anti_aim, VK_F6);
    set_var(RCS, VK_F7);
    set_var(anti_flash_delay, VK_PRIOR);
    set_var(wall_hack, VK_NEXT);

    if (GetKeyState(VK_F8)) {
        if (!chams) {
            chams = true;
            print_cheat_menu();
        }
    } else {
        if (chams) {
            chams = false;
            reset_chams();
            print_cheat_menu();
        }

    }
    if (GetAsyncKeyState(VK_HOME)) {
        RCS_control.x = 2;
        RCS_control.y = 0;
        Sleep(100);
    }
    if (GetAsyncKeyState(VK_F9)) {
        RCS_control.x = 0;
        RCS_control.y = 2;
        Sleep(100);
    }
    if (GetAsyncKeyState(VK_F11)) {
        RCS_control.x = 2;
        RCS_control.y = 2;
        Sleep(100);
    }
}

void main_ch::print_cheat_menu() {
    system("cls");
    /*
    std::cout << std::string(52, '=') << "LEGIT CSGO CHEAT" << std::string(52, '=')
              << "\n \n Functions of cheat:\n -Radarhack " << radar_hack << "\n -Bunnyhop " << bunny_hop
              << "\n -Trigger Bot (ALT) " << trigger_bot << "\n" << " -Antiflash " << anti_flash << "\n -Chams "
              << chams
              << "\n -RCS (F7) " << RCS << "\n -Glow Wallhack "<< wall_hack << std::endl << std::endl << "Settings: " << std::endl
              << " -MEGA Legit RCS (Only X)" << std::endl
              << " -Legit RCS(Only Y) - F9" << std::endl << " -RCS(X and Y) - F11" << std::endl
              << " -Trigger bot and chams teammates " << teammates << std::endl << " -Legit trigger bot "
              << legit_trigger_bot << std::endl << " -Legit bunny hop " << legit_bunny_hop << std::endl << " -Antiflash delay " << anti_flash_delay
              << "\n \n Exit cheat - INSERT"
              << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl
              << std::string(120, '=');
    */


}

main_ch::main_ch() {
    this->name = "Counter-Strike: Global Offensive - Direct3D 9";
    client = m.GetModuleBaseAddress("client.dll");
    engine = m.GetModuleBaseAddress("engine.dll");
}

main_ch::main_ch(const CHAR *name) {

    this->name = name;
    m.setNewWindow(name);
    client = m.GetModuleBaseAddress("client.dll");
    engine = m.GetModuleBaseAddress("engine.dll");


}

main_ch::~main_ch() {
    CloseHandle(m.handle);
}

void main_ch::radarhack() {
    for (int i = 0; i < 64; i++) {
        auto entity = m.RPM<DWORD>(client + hazedumper::signatures::dwEntityList + i * 0x10);
        m.WPM<bool>(entity + hazedumper::netvars::m_bSpotted, true);
    }
}



void main_ch::chams_func() {
    for (int i = 0; i < 64; i++) {
        auto local_player = m.RPM<DWORD>(client + hazedumper::signatures::dwLocalPlayer);
        auto entity = m.RPM<DWORD>(client + hazedumper::signatures::dwEntityList + i * 0x10);
        if (teammates) {
            set_chams(entity, 255, 0, 0);
        } else {
            auto eTeam = m.RPM<int>(entity + hazedumper::netvars::m_iTeamNum);
            auto pTeam = m.RPM<int>(local_player + hazedumper::netvars::m_iTeamNum);
            if (eTeam && eTeam != pTeam) {
                set_chams(entity, 255, 0, 0);
            } else {
                set_chams(entity, 0, 255, 0);
            }
        }
    }
}

void main_ch::antiflash() {
    auto local_player = m.RPM<DWORD>(client + hazedumper::signatures::dwLocalPlayer);
    auto flash = m.RPM<float>(local_player + hazedumper::netvars::m_flFlashDuration);
    if (flash > 0) {
        if(anti_flash_delay) Sleep(200);
        m.WPM(local_player + hazedumper::netvars::m_flFlashDuration, 0);
    }
}

void main_ch::triggerbot() {
    if (GetAsyncKeyState(VK_MENU)) {
        auto local_player = m.RPM<DWORD>(client + hazedumper::signatures::dwLocalPlayer);
        if (local_player) {
            int pTeam = m.RPM<int>(local_player + hazedumper::netvars::m_iTeamNum);
            int crosshair = m.RPM<int>(local_player + hazedumper::netvars::m_iCrosshairId);
            if (crosshair != 0 && crosshair < 64) {
                auto entity = m.RPM<DWORD>(client + hazedumper::signatures::dwEntityList + (crosshair - 1) * 0x10);
                if (entity) {
                    if (teammates) {
                        if (legit_trigger_bot) delay(50);
                        click();
                        Sleep(100);
                    } else {
                        int eTeam = m.RPM<int>(entity + hazedumper::netvars::m_iTeamNum);
                        if (eTeam != pTeam && eTeam) {
                            if (legit_trigger_bot) delay(50);
                            click();
                            Sleep(100);
                        }
                    }
                }
            }
        }
    }
}

void main_ch::bunnyhop() {
    if (GetAsyncKeyState(VK_SPACE)) {
        auto local_player = m.RPM<DWORD>(client + hazedumper::signatures::dwLocalPlayer);
        auto player_state = m.RPM<int>(local_player + hazedumper::netvars::m_fFlags);
        if (player_state == 257) {
            if (legit_bunny_hop) {
                int random = rand() % 5;
                if (!random) Sleep(50);
            }
            mouse_event(MOUSEEVENTF_MIDDLEDOWN, 0, 0, 0, 0);
            mouse_event(MOUSEEVENTF_MIDDLEUP, 0, 0, 0, 0);
            Sleep(100);
        }
    }
}

void main_ch::recoil_control_system() {
    auto local_player = m.RPM<DWORD>(client + hazedumper::signatures::dwLocalPlayer);
    auto clientState = m.RPM<DWORD>(engine + hazedumper::signatures::dwClientState);
    Vec3 viewAngles = m.RPM<Vec3>(clientState + hazedumper::signatures::dwClientState_ViewAngles);
    int shotsFired = m.RPM<int>(local_player + hazedumper::netvars::m_iShotsFired);
    Vec3 aimPunchAngle = m.RPM<Vec3>(local_player + hazedumper::netvars::m_aimPunchAngle);


    Vec3 punchAngle = aimPunchAngle * RCS_control;
    if (shotsFired > 1) {
        Vec3 newAngle = viewAngles + oPunch - punchAngle;
        newAngle.Normalize();
        m.WPM<Vec3>(clientState + hazedumper::signatures::dwClientState_ViewAngles, newAngle);

    }
    oPunch = punchAngle;
}



void main_ch::printEntityList() {
    std::cout << "Entity health list: " << std::endl;
    for (int i = 0; i < 64; i++) {
        auto entity = m.RPM<DWORD>(client + hazedumper::signatures::dwEntityList + i * 0x10);
        if (entity) {
            auto eHealth = m.RPM<int>(entity + hazedumper::netvars::m_iHealth);
            auto eTeam = m.RPM<int>(entity + hazedumper::netvars::m_iTeamNum);
            std::cout << eHealth << std::endl;
            std::cout << eTeam << std::endl << std::endl;
        }
    }

}

void main_ch::antiaim() {
    /*
    auto clientState = m.RPM<DWORD>(engine + hazedumper::signatures::dwClientState);
    Vec3 viewAngles = m.RPM<Vec3>(clientState + hazedumper::signatures::dwClientState_ViewAngles);
    Vec3 newAngle = viewAngles - Vec3{0, 180, 0};
    newAngle.Normalize();
    m.WPM(clientState + hazedumper::signatures::dwClientState_ViewAngles, newAngle);
    Sleep(10);
    viewAngles = m.RPM<Vec3>(clientState + hazedumper::signatures::dwClientState_ViewAngles);
    newAngle = viewAngles - Vec3{0, 180, 0};
    newAngle.Normalize();
    m.WPM(clientState + hazedumper::signatures::dwClientState_ViewAngles, newAngle);
    Sleep(150);
    */
}
void main_ch::wallhack(){
    auto glow_object_manager = m.RPM<DWORD>(client + hazedumper::signatures::dwGlowObjectManager);
    auto local_player = m.RPM<DWORD>(client + hazedumper::signatures::dwLocalPlayer);
    auto p_team = m.RPM<int>(local_player + hazedumper::netvars::m_iTeamNum);
    for(int i = 1; i < 64; i++){
        auto entity = m.RPM<DWORD>(client + hazedumper::signatures::dwEntityList + i * 0x10);

        if(entity){
            auto glow_index = m.RPM<int>(entity + hazedumper::netvars::m_iGlowIndex);
            auto e_team = m.RPM<int>(entity + hazedumper::netvars::m_iTeamNum);
            if(e_team != p_team){
                auto e_health = m.RPM<int>(entity + hazedumper::netvars::m_iHealth);
                if(e_health > 75){
                    m.WPM(
                            glow_object_manager + (0x38 * glow_index) + 0x8,
                            color4_t{ v::other_team_glow_100.second }
                    );
                }else if(e_health > 50){
                    m.WPM(
                            glow_object_manager + (0x38 * glow_index) + 0x8,
                            color4_t{ v::other_team_glow_75.second }
                    );
                }else if(e_health > 25){
                    m.WPM(
                            glow_object_manager + (0x38 * glow_index) + 0x8,
                            color4_t{ v::other_team_glow_50.second }
                    );
                }else{
                    m.WPM(
                            glow_object_manager + (0x38 * glow_index) + 0x8,
                            color4_t{ v::other_team_glow_25.second }
                    );
                }

            }else{
                m.WPM(
                        glow_object_manager + (0x38 * glow_index) + 0x8,
                        color4_t{ v::my_team_glow.second }
                );
            }
            constexpr struct visible_t { bool a{ true }, b{ false }; }vis;
            m.WPM(glow_object_manager + (0x38 * glow_index) + 0x28, vis);
        }
    }
}
void main_ch::printmyweapon() {
    auto local_player = m.RPM<DWORD>(client + hazedumper::signatures::dwLocalPlayer);
    auto weapon = m.RPM<int>(local_player + hazedumper::netvars::m_hActiveWeapon);
    std::cout << weapon << std::endl;
}

void main_ch::welcome() {
    system("cls");
    int d = 100;
    std::cout<<'W';
    Sleep(d);
    std::cout<<'e';
    Sleep(d);
    std::cout<<'l';
    Sleep(d);
    std::cout<<'c';
    Sleep(d);
    std::cout<<'o';
    Sleep(d);
    std::cout<<'m';
    Sleep(d);
    std::cout<<'e';
    Sleep(d);
    std::cout<<' ';
    Sleep(d);
    std::cout<<'t';
    Sleep(d);
    std::cout<<'o';
    Sleep(d);
    std::cout<<' ';
    Sleep(d);
    std::cout<<'m';
    Sleep(d);
    std::cout<<'y';
    Sleep(d);
    std::cout<<' ';
    Sleep(d);
    std::cout<<'C';
    Sleep(d);
    std::cout<<'S';
    Sleep(d);
    std::cout<<':';
    Sleep(d);
    std::cout<<'G';
    Sleep(d);
    std::cout<<'O';
    Sleep(d);
    std::cout<<' ';
    Sleep(d);
    std::cout<<'C';
    Sleep(d);
    std::cout<<'h';
    Sleep(d);
    std::cout<<'e';
    Sleep(d);
    std::cout<<'a';
    Sleep(d);
    std::cout<<'t';
    Sleep(d + 200);
    system("cls");
}
