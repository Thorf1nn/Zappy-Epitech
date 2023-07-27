/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** define
*/

#ifndef DEFINE_H_
    #define DEFINE_H_
    #define EXIT_FAILED       84
    #define MAX_CLIENTS       1024
    #define READ_SIZE         4095
    #define FOOD_DENSITY      0.5
    #define LINEMATE_DENSITY  0.3
    #define DERAUMERE_DENSITY 0.15
    #define SIBUR_DENSITY     0.10
    #define MENDIANE_DENSITY  0.10
    #define PHIRAS_DENSITY    0.08
    #define THYSTAME_DENSITY  0.05
    #define RESOURCES_CYCLE   20
    #define EGG_CYCLE         42
    #define LIFE_CYCLE        126

    #define STR_WELCOME strdup("WELCOME\n")
    #define STR_KO      strdup("ko\n")
    #define STR_OK      strdup("ok\n")
    #define STR_DEAD    strdup("dead\n")

    #define MSZ strdup("msz %d %d\n")
    #define BCT strdup("bct %d %d %d %d %d %d %d %d %d\n")
    #define TNA strdup("tna %s\n")
    #define PNW strdup("pnw %d %d %d %d %d %s\n")
    #define PPO strdup("ppo %d %d %d %d\n")
    #define PLV strdup("plv %d %d\n")
    #define PIN strdup("pin %d %d %d %d %d %d %d %d %d %d\n")
    #define PEX strdup("pex %d\n")
    #define PBC strdup("pbc %d %s\n")
    #define PIC strdup("pic %d %d %d %d %d %d %d %d\n") // @todo check this
    #define PIE strdup("pie %d %d %d\n")
    #define PFK strdup("pfk %d\n")
    #define PDR strdup("pdr %d %d\n")
    #define PGT strdup("pgt %d %d\n")
    #define PDI strdup("pdi %d\n")
    #define ENW strdup("enw %d %d %d %d\n")
    #define EBO strdup("ebo %d\n")
    #define EDI strdup("edi %d\n")
    #define SGT strdup("sgt %d\n")
    #define SST strdup("sst %d\n")
    #define SEG strdup("seg %s\n")
    #define SMG strdup("smg %s\n")
    #define SUC strdup("suc\n")
    #define SBP strdup("sbp\n")

    #define RDN(d) ((float) (rand() % ((int) (100 * d))) / 100)

    #define pass __attribute__((unused))

#endif /* !DEFINE_H_ */
