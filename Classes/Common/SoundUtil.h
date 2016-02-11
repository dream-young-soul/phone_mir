#ifndef SOUNDUTIL_H_
#define SOUNDUTIL_H_
#include <string>
void PlaySound_(int idx,int x = 0,int y = 0,bool Loop = false);
void PlayMp3(const char* wavname,bool boFlag);
void PlayMapMusic(std::string sOldMusic,std::string sNewMusic);
void ClearSound();
const char S_SoundFile[] = "data/a/%d.wav";
const int s_walk_ground_l   = 1;    //走动
const int s_walk_ground_r   = 2;
const int s_run_ground_l    = 3;
const int s_run_ground_r    = 4;
const int s_walk_stone_l    = 5;
const int s_walk_stone_r    = 6;
const int s_run_stone_l     = 7;
const int s_run_stone_r     = 8;
const int s_walk_lawn_l     = 9;
const int s_walk_lawn_r     = 10;
const int s_run_lawn_l      = 11;
const int s_run_lawn_r      = 12;
const int s_walk_rough_l    = 13;
const int s_walk_rough_r    = 14;
const int s_run_rough_l     = 15;
const int s_run_rough_r     = 16;
const int s_walk_wood_l     = 17;
const int s_walk_wood_r     = 18;
const int s_run_wood_l      = 19;
const int s_run_wood_r      = 20;
const int s_walk_cave_l     = 21;
const int s_walk_cave_r     = 22;
const int s_run_cave_l      = 23;
const int s_run_cave_r      = 24;
const int s_walk_room_l     = 25;
const int s_walk_room_r     = 26;
const int s_run_room_l      = 27;
const int s_run_room_r      = 28;
const int s_walk_water_l    = 29;
const int s_walk_water_r    = 30;
const int s_run_water_l     = 31;
const int s_run_water_r     = 32;

const int s_hit_short       = 50;
const int s_hit_wooden      = 51;
const int s_hit_sword       = 52;
const int s_hit_do          = 53;
const int s_hit_axe         = 54;
const int s_hit_club        = 55;
const int s_hit_long        = 56;
const int s_hit_fist        = 1200;     //空手攻击
const int s_hit_Weapon      = 1201; //带武器攻击

const int s_struck_short    = 60;
const int s_struck_wooden   = 61;
const int s_struck_sword    = 62;
const int s_struck_do       = 63;
const int s_struck_axe      = 64;
const int s_struck_club     = 65;

const int s_struck_body_sword = 70;
const int s_struck_body_axe = 71;
const int s_struck_body_longstick = 72;
const int s_struck_body_fist = 73;

const int s_struck_armor_sword = 80;
const int s_struck_armor_axe = 81;
const int s_struck_armor_longstick = 82;
const int s_struck_armor_fist = 83;

const int s_strike_stone    = 91;
const int s_drop_stonepiece = 92;

const int s_rock_door_open  = 100;
const int s_intro_theme     = 102;
const int s_meltstone       = 101;
const int s_main_theme      = 102;
const int s_money           = 110; //金币声音
const int s_eat_drug        = 107;

const int s_click_drug      = 100; //吃药
const int s_norm_button_click = 101;   //点击按钮   关闭用这个
const int s_rock_button_click = 102;    //普通ui点击
const int s_glass_button_click = 103;
const int s_Level_Up = 104; //等级提升

const int s_sitdown = 105 ;//蹲下 106采集

const int s_spacemove_out   = 2001;     //飞走
const int s_spacemove_in    = 2002;     //飞来

const int s_click_weapon    = 111;
const int s_click_armor     = 112;
const int s_click_ring      = 113;
const int s_click_armring   = 114;
const int s_click_necklace  = 115;
const int s_click_helmet    = 116;
const int s_click_grobes    = 117;
const int s_itmclick        = 118;

const int s_yedo_man        = 1111;   //攻杀的那个声音
const int s_yedo_woman      = 1112;
const int s_longhit         = 1132;  //刺杀
const int s_widehit         = 133;
const int s_rush_l          = 134;
const int s_rush_r          = 135;
const int s_firehit_ready   = 136;
const int s_firehit         = 11137;  //烈火声音



const int s_man_struck      = 150;
const int s_wom_struck      = 151;
const int s_34hit           = 140;
const int s_35hit           = 141;
const int s_103hit          = 11030;
const int s_man_die         = 152;
const int s_wom_die         = 153;
#endif