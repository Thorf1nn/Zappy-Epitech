/*
** EPITECH PROJECT, 2023
** zappy [WSL: Ubuntu]
** File description:
** structs
*/

#ifndef STRUCTS_H_
    #define STRUCTS_H_
    #include "libs.h"
    typedef enum dir_e dir_t;
    typedef enum item_e item_t;
    typedef struct pl_s pl_t;
    typedef struct il_s il_t;
    typedef struct cl_s cl_t;
    typedef struct el_s el_t;
    typedef struct ml_s ml_t;
    typedef struct player_s player_t;
    typedef struct cmd_s cmd_t;
    typedef struct egg_s egg_t;
    typedef struct team_s team_t;
    typedef struct square_s square_t;
    typedef struct network_s network_t;
    typedef struct server_s server_t;
    typedef struct check_args_s check_args_t;
    typedef struct strgraph_s strgraph_t;
    typedef struct vec_s vec_t;
    typedef struct ori_s ori_t;
    typedef void (*step_function_ptr)(server_t *, player_t *);
    typedef void (*exec)(server_t *serv, player_t *player, char *cmd);
    typedef bool (*check)(void *, char **av);

    enum item_e {
        FOOD,
        LINEMATE,
        DERAUMERE,
        SIBUR,
        MENDIANE,
        PHIRAS,
        THYSTAME,
        EGG,
        NONE
    };

    enum dir_e { UP, RIGHT, DOWN, LEFT, NO_DIR };

    struct pl_s {
        player_t *data;
        struct pl_s *next;
    };

    struct il_s {
        item_t data;
        struct il_s *next;
    };

    struct ml_s {
        char *data;
        struct ml_s *next;
    };

    struct cl_s {
        struct cmd_s *data;
        struct cl_s *next;
    };

    struct el_s {
        egg_t *data;
        struct el_s *next;
    };

    struct ori_s {
        dir_t dir;
        int up_left;
        int up_center;
        int up_right;
        int down_left;
        int down_center;
        int down_right;
        int center_left;
        int center_right;
    };

    struct vec_s {
        int x;
        int y;
    };

    struct cmd_s {
        char *cmd;
        int cycle;
        exec exec;
        clock_t start;
    };

    struct team_s {
        char *name;
    };

    struct player_s {
        int id;
        int fd;
        int x;
        int y;
        int steps;
        int level;
        int nb_cmd;
        int s_buff;
        char *buff;
        team_t *team;
        clock_t life;
        ml_t *to_send;
        cl_t *to_exec;
        dir_t dir;
        il_t *inventory;
        square_t *square;
        bool disconnected;
        bool is_graphical;
    };

    struct square_s {
        il_t *items;
        pl_t *players;
        vec_t pos;
    };

    struct egg_s {
        int id;
        int pid;
        team_t *team;
        clock_t cycle;
        square_t *square;
    };

    struct network_s {
        int fd_max;
        int fd_server;
        fd_set read_fds;
        fd_set write_fds;
        struct timeval timeout;
    };

    struct server_s {
        int port;
        int freq;
        int id_p;
        int id_e;
        int width;
        int height;
        int clients_nb;
        pl_t *players;
        el_t *eggs;
        network_t *net;
        team_t **teams;
        square_t ***board;
        clock_t item_spawn;
        player_t *graphical;
    };

    struct check_args_s {
        char *flag;
        bool (*check)(void *, char **);
        char *error;
        int offset;
    };

#endif /* !STRUCTS_H_ */
