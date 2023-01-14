//
// Created by Админ on 29.10.2022.
//

#ifndef PROJECT1_MAIN_CH_H
#define PROJECT1_MAIN_CH_H
#include "Windows.h"
#include "memory_controller.h"
#include <string>
#include <iostream>
#include <array>
#include "offsets.hpp"
namespace v {
    inline std::pair<bool, std::array<float, 4U>> my_team_glow{
            false,
            { 0.f, 1.f, 0.f, 1.f }
    };
    inline std::pair<bool, std::array<float, 4U>> other_team_glow_100{
            false,
            { 1.f, 0.f, 0.f, 1.f }
    };
    inline std::pair<bool, std::array<float, 4U>> other_team_glow_75{
            false,
            { 1.f, 0.f, 1.f, 1.f }
    };
    inline std::pair<bool, std::array<float, 4U>> other_team_glow_50{
            false,
            { 0.5f, 0.f, 1.f, 1.f }
    };
    inline std::pair<bool, std::array<float, 4U>> other_team_glow_25{
            false,
            { 0.f, 0.f, 1.f, 1.f }
    };
}
template <typename T>
struct color4_t {
    constexpr color4_t(const std::array<T, 4U>& arr) noexcept :
            _r(arr[0]), _g(arr[1]), _b(arr[2]), _a(arr[3]) { }

private:
    T _r = { }, _g = { }, _b = { }, _a = { };
};
struct Vec3 {
    float x, y, z;

    Vec3 operator+(Vec3 d) {
        return {x + d.x, y + d.y, z + d.z};
    }

    Vec3 operator-(Vec3 d) {
        return {x - d.x, y - d.y, z - d.z};
    }

    Vec3 operator*(Vec3 d) {
        return {x * d.x, y * d.y, z * d.z};
    }
    void Normalize() {
        while (y < -180) {
            y += 360;
        }
        while (y > 180) {
            y -= 360;
        }
        if (x > 89) {
            x = 89;
        }
        if (x < -89) {
            x = -89;
        }
    }
};

class main_ch {
public:


    bool bunny_hop = false;
    bool trigger_bot = false;
    bool teammates = false;
    bool radar_hack = false;
    bool anti_flash = false;
    bool chams = false;
    bool RCS = false;
    bool wall_hack = false;

    bool legit_trigger_bot = false;
    bool legit_bunny_hop = false;
    bool anti_flash_delay = false;
    //bool anti_aim = false;

    memory_controller m;
    const CHAR *name;


    DWORD client;
    DWORD engine;
    Vec3 RCS_control{0, 2, 2};
    Vec3 oPunch{0, 0, 0};
    main_ch();
    main_ch(const CHAR* name);
    ~main_ch();

    void welcome();
    void print_cheat_menu();

    void set();
    void radarhack();
    void set_chams(DWORD entity, int r, int g, int b);
    void chams_func();
    void antiflash();
    void triggerbot();
    void bunnyhop();
    void recoil_control_system();
    void wallhack();
    void reset_chams();
    void printEntityList();
    void antiaim();
    void printmyweapon();

    static void delay(int d);
    static void click();
    void set_var(bool &var, int key);
};


#endif //PROJECT1_MAIN_CH_H
