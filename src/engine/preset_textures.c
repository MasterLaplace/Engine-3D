/*
** ME PROJECT, 2022
** DEN-GINER-Master-Laplace
** File description:
** textures
*/

#include "engine.h"

const sizint NB_TEXTURES = 30;
const char *TEXTURE_PATHS[] = {
    "./assets/textures/PlayStation-Spyro_the_Dragon-Artisans_Hub/High.png",
    "./assets/textures/PlayStation-Spyro_the_Dragon-Artisans_Hub/Low.png",
    "./assets/textures/water_surface.png",
    "./assets/textures/bubble.png",
    "./assets/textures/mon_986/mon_986_001.png",
    // "assets/textures/Peachs_Castle_Exterior/1D0CA178_c.png",
    // "assets/textures/Peachs_Castle_Exterior/1FEE462_c.png",
    // "assets/textures/Peachs_Castle_Exterior/1FFBC780_c.png",
    // "assets/textures/Peachs_Castle_Exterior/2BC808F1_c.png",
    // "assets/textures/Peachs_Castle_Exterior/3AB7B2BC_c.png",
    // "assets/textures/Peachs_Castle_Exterior/3C6851DA_c.png",
    // "assets/textures/Peachs_Castle_Exterior/3FBAB8A0_c.png",
    // "assets/textures/Peachs_Castle_Exterior/5EDC83BD_c.png",
    // "assets/textures/Peachs_Castle_Exterior/6AE21407_c.png",
    // "assets/textures/Peachs_Castle_Exterior/6DAF90F6_c.png",
    // "assets/textures/Peachs_Castle_Exterior/7EB1C6A1_c.png",
    // "assets/textures/Peachs_Castle_Exterior/19D5421D_c.png",
    // "assets/textures/Peachs_Castle_Exterior/20EF7F7C_c.png",
    // "assets/textures/Peachs_Castle_Exterior/31BEEA74_c.png",
    // "assets/textures/Peachs_Castle_Exterior/36B9F48_c.png",
    // "assets/textures/Peachs_Castle_Exterior/41EDCCB_c.png",
    // "assets/textures/Peachs_Castle_Exterior/60A64656_c.png",
    // "assets/textures/Peachs_Castle_Exterior/61BE951F_c.png",
    // "assets/textures/Peachs_Castle_Exterior/148EB7B9_c.png",
    // "assets/textures/Peachs_Castle_Exterior/154B175A_c.png",
    // "assets/textures/Peachs_Castle_Exterior/1916F8C5_c.png",
    // "assets/textures/Peachs_Castle_Exterior/49254A53_c.png",
    // "assets/textures/Peachs_Castle_Exterior/114626C6_c.png",
    "assets/textures/Peachs_Castle/carpet_red.png",
    "assets/textures/Peachs_Castle/concwall_32.png",
    "assets/textures/Peachs_Castle/mc_bridge.png",
    "assets/textures/Peachs_Castle/mc_fence.png",
    "assets/textures/Peachs_Castle/mc_flow_a.png",
    "assets/textures/Peachs_Castle/mc_gake.png",
    "assets/textures/Peachs_Castle/mc_grass.png",
    "assets/textures/Peachs_Castle/mc_kakine00.png",
    "assets/textures/Peachs_Castle/mc_kakine01.png",
    "assets/textures/Peachs_Castle/mc_road.png",
    "assets/textures/Peachs_Castle/mc_roof.png",
    "assets/textures/Peachs_Castle/mc_sand_d.png",
    "assets/textures/Peachs_Castle/mc_sand.png",
    "assets/textures/Peachs_Castle/mc_til_str.png",
    "assets/textures/Peachs_Castle/mc_til00.png",
    "assets/textures/Peachs_Castle/mc_tritile.png",
    "assets/textures/Peachs_Castle/mc_window.png",
    "assets/textures/Peachs_Castle/mc_yama.png",
    "assets/textures/Peachs_Castle/peach.png",
    "assets/textures/Peachs_Castle/renga_grass.png",
    "assets/textures/Peachs_Castle/renga_shik00.png",
    "assets/textures/Peachs_Castle/tree_shadow.png",
    "assets/textures/Peachs_Castle/water_surface.png",
    "assets/textures/Peachs_Castle/water.png",
    "assets/textures/mon_986/mon_986_001.png",
};
// const sizint NB_TEXTURES = 27;
// const char *TEXTURE_PATHS[] = {
//     "./assets/textures/PlayStation-Spyro_the_Dragon-Artisans_Hub/High.png",
//     "./assets/textures/PlayStation-Spyro_the_Dragon-Artisans_Hub/Low.png",
//     "./assets/textures/Peachs_Castle/carpet_red.png",
//     "./assets/textures/Peachs_Castle/mc_flow_a.png",
//     "./assets/textures/Peachs_Castle/mc_kakine00.png",
//     "./assets/textures/Peachs_Castle/mc_sand_d.png",
//     "./assets/textures/Peachs_Castle/mc_tritile.png",
//     "./assets/textures/Peachs_Castle/tree_shadow.png",
//     "./assets/textures/Peachs_Castle/concwall_32.png",
//     "./assets/textures/Peachs_Castle/mc_flow_b.png",
//     "./assets/textures/Peachs_Castle/mc_kakine01.png",
//     "./assets/textures/Peachs_Castle/mc_sand.png",
//     "./assets/textures/Peachs_Castle/mc_window.png",
//     "./assets/textures/Peachs_Castle/renga_grass.png",
//     "./assets/textures/Peachs_Castle/water.png",
//     "./assets/textures/Peachs_Castle/mc_bridge.png",
//     "./assets/textures/Peachs_Castle/mc_gake.png",
//     "./assets/textures/Peachs_Castle/mc_road.png",
//     "./assets/textures/Peachs_Castle/mc_til00.png",
//     "./assets/textures/Peachs_Castle/mc_yama.png",
//     "./assets/textures/Peachs_Castle/renga_shik00.png",
//     "./assets/textures/Peachs_Castle/water_surface.png",
//     "./assets/textures/Peachs_Castle/mc_fence.png",
//     "./assets/textures/Peachs_Castle/mc_grass.png",
//     "./assets/textures/Peachs_Castle/mc_roof.png",
//     "./assets/textures/Peachs_Castle/mc_til_str.png",
//     "./assets/textures/Peachs_Castle/peach.png",
// };

const sizint NB_MTL = 3;
const char *MTL_PATHS[] = {
    "./assets/textures/PlayStation-Spyro_the_Dragon-Artisans_Hub/Artisans_Hub.mtl"
    "./assets/textures/mon_986/mon_986_001.mtl",
    "./assets/textures/Peachs_Castle_Exterior/Peaches_Castle.mtl",
    "./assets/textures/Peachs_Castle/Peachs_Castle.mtl"
};
