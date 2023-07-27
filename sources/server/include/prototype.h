/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** prototype
*/

#ifndef PROTOTYPE_H_
    #define PROTOTYPE_H_
    #include "structs.h"
    #include "define.h"

    // main.c:
    int free_exit(char **tab, int ret);
    int main(int ac, char **av);

    // utils/elapse.c:
    bool elapse(server_t *serv, clock_t start_time, double unit);

    // utils/itos.c:
    char *itos(int nb);

    // utils/strarr.c:
    void free_arr(char **tab);
    int count_words(const char *str, const char *del);
    char **strarr(const char *str, const char *del);
    bool compare(char *cmd, int nb);

    // utils/strcats.c:
    void strcats(char *result, ...);

    // cmd/register_graphic.c:
    void register_graphic_fail(player_t *player);
    void register_graphic_cmd(player_t *, char **, char **, int);

    // cmd/steps.c:
    void join_step(server_t *serv, player_t *player);
    void cmd_step(server_t *serv pass, player_t *player);
    void call_step(server_t *serv, player_t *player);

    // cmd/register_cmd.c:
    void register_fail(player_t *player);
    void register_cmd(player_t *player, char **cmds, char **data, int i);

    // cmd/commands/cmd_right.c:
    void cmd_right(server_t *serv, player_t *player, char *cmd);

    // cmd/commands/cmd_incantation.c:
    bool check_player(player_t *player, int level, int need, bool after);
    bool check_resources(player_t *player, int need[7]);
    bool check_can(player_t *pl, bool remove, bool after);
    void cmd_incantation(server_t *serv pass, player_t *player, char *cmd);

    // cmd/commands/cmd_end_incantation.c:
    void create_task_cmd(player_t *player, exec func, int rdn);
    void empty_cmd(server_t *serv pass, player_t *player pass, char *cmd);
    void incress_level(server_t *, player_t *, player_t *, bool);
    void cmd_end_incantation(server_t *serv, player_t *player, char *cmd pass);

    // cmd/commands/cmd_tna.c:
    void cmd_tna(server_t *serv, player_t *player, char *cmd);

    // cmd/commands/cmd_broadcast.c:
    int adapt_orientation(dir_t dir, int ori, int i);
    vec_t get_distance(server_t *serv, player_t *from, player_t *to);
    int get_orientation(server_t *serv, player_t *from, player_t *to);
    void cmd_broadcast(server_t *serv, player_t *player pass, char *cmd);

    // cmd/commands/cmd_inv.c:
    void cmd_inv(server_t *serv pass, player_t *player, char *cmd);

    // cmd/commands/cmd_left.c:
    void cmd_left(server_t *serv, player_t *player, char *cmd);

    // cmd/commands/cmd_fork.c:
    void cmd_fork(server_t *serv, player_t *player, char *cmd);

    // cmd/commands/cmd_mct.c:
    void cmd_mct(server_t *serv, player_t *player, char *cmd);

    // cmd/commands/cmd_ppo.c:
    void cmd_ppo(server_t *serv pass, player_t *player pass, char *cmd pass);

    // cmd/commands/cmd_forward.c:
    void move_player(server_t *serv, player_t *player, int y, int x);
    void cmd_forward(server_t *serv, player_t *player, char *cmd);

    // cmd/commands/cmd_eject.c:
    void eject(server_t *serv, player_t *to, dir_t dir);
    void cmd_eject(server_t *serv, player_t *player, char *cmd);

    // cmd/commands/cmd_sbp.c:
    void cmd_suc(server_t *serv pass, player_t *player, char *cmd pass);

    // cmd/commands/cmd_connect.c:
    void cmd_connect(server_t *, player_t *, char *);

    // cmd/commands/cmd_pin.c:
    void cmd_pin(server_t *serv, player_t *player, char *cmd);

    // cmd/commands/cmd_ko.c:
    void cmd_ko(server_t *serv pass, player_t *player, char *cmd pass);

    // cmd/commands/cmd_msz.c:
    void cmd_msz(server_t *serv, player_t *player, char *cmd);

    // cmd/commands/cmd_plv.c:
    void cmd_plv(server_t *serv pass, player_t *player pass, char *cmd pass);

    // cmd/commands/cmd_take.c:
    void cmd_take(server_t *serv, player_t *player, char *cmd);

    // cmd/commands/cmd_bct.c:
    void cmd_bct(server_t *serv, player_t *player, char *cmd);

    // cmd/commands/cmd_look.c:
    char *item_name(item_t item);
    void square_to_str(square_t *square, char *buff);
    square_t *get_square(server_t *serv, player_t *pl, int i, int j);
    void get_content(server_t *serv, player_t *player, char *buff, int idxs[2]);
    void cmd_look(server_t *serv, player_t *player, char *cmd);

    // cmd/commands/cmd_set.c:
    void cmd_set(server_t *serv, player_t *player, char *cmd);

    // cmd/commands/cmd_sst.c:
    void cmd_sst(server_t *serv pass, player_t *player pass, char *cmd pass);

    // cmd/commands/cmd_sgt.c:
    void cmd_sgt(server_t *serv pass, player_t *player pass, char *cmd pass);

    // args/get.c:
    void init_global_struct(server_t *serv);
    int get_args(server_t *serv, int ac, char **av);

    // args/params.c:
    bool int_check(int *data, char **av);
    bool add_param_team(team_t ***param, char **av);
    bool check_args(server_t *serv, int i, char **av);

    // boards/get_resource.c:
    int *get_resources(il_t *items);
    int getter_resource(il_t *items, item_t item);

    // boards/send_board.c:
    void send_buff(player_t *graphic, char *buff);
    void send_board(server_t *serv, player_t *graphic);

    // boards/init_board.c:
    int board_resources(server_t *serv, item_t item);
    int max_resources(server_t *serv, item_t item);
    void put_resources(server_t *serv);
    void build_board(server_t *serv);

    // chained/chained_players.c:
    pl_t *new_pl(player_t *data);
    void push_pl(pl_t **pls, player_t *data);
    void clear_pl(pl_t **pls, bool free_p);
    void del_pl(pl_t **pls, player_t *data, bool free_p);
    int len_pl(pl_t *pl);

    // chained/chained_cmd.c:
    cl_t *new_cmd(cmd_t *cmd);
    void push_cmd(cl_t **cmds, cmd_t *data);
    void clear_cmd(cl_t **cmds);
    void del_cmd(cl_t **cmds, cmd_t *data, bool free_p);
    int len_cmd(cl_t *cmd);

    // chained/chained_egg.c:
    el_t *new_el(egg_t *data);
    void push_el(el_t **els, egg_t *data);
    void clear_el(el_t **els, bool free_p);
    void del_el(el_t **els, egg_t *data, bool free_p);
    int len_el(el_t *el);

    // chained/chained_items.c:
    il_t *new_il(item_t data);
    void push_il(il_t **ils, item_t data);
    void clear_il(il_t **ils);
    void del_il(il_t **ils, item_t data);
    int len_il(il_t *il);

    // chained/chained_msg.c:
    ml_t *new_msg(char *msg);
    void push_msg(ml_t **msgs, char *data);
    void clear_msg(ml_t **msgs);
    int len_msg(ml_t *msg);

    // players/eggs.c:
    void spawn_eggs(server_t *serv, team_t *team, player_t *player);
    void create_eggs(server_t *serv);
    egg_t *get_egg(server_t *serv, team_t *team);
    void spawn_player(server_t *serv, player_t *player);

    // players/teams.c:
    void default_team(server_t *serv);
    int slot_available(server_t *serv, team_t *team);
    void add_player_to_team(server_t *serv, player_t *player, int team);
    void add_player_to_graphic(server_t *serv, player_t *player);

    // players/players.c:
    void delete_player(server_t *serv, pl_t **players);
    void player_join_team(server_t *serv, player_t *player, int team);
    void new_player(server_t *serv, int fd);

    // server/init_server.c:
    int create_socket(void);
    int create_server(int port);
    int init_server(server_t *serv);

    // server/loop_server.c:
    bool main_server(server_t *serv);
    bool loop_server(server_t *serv);

    // server/networks/send.c:
    void to_send(player_t *player, char *cmd, ...);
    bool send_to(player_t *player);

    // server/networks/select.c:
    void fill_select(server_t *serv);
    bool fd_select(server_t *serv);

    // server/networks/fd.c:
    int max_fd(server_t *serv);
    bool new_fd(server_t *serv);
    bool handle_fd(player_t *player);

    // server/handle/handle_eggs.c:
    void handle_eggs(server_t *serv);

    // server/handle/handle_select.c:
    bool handle_select(server_t *serv);

    // server/handle/handle_life.c:
    void eat(server_t *serv pass, player_t *player);
    void handle_life(server_t *serv);

    // server/handle/handle_cmd.c:
    bool execute_failed(server_t *serv, player_t *player);
    void execute_action(server_t *serv, player_t *player);
    void handle_cmd(server_t *serv);

    // server/handle/handle_resources.c:
    void handle_resources(server_t *serv);

    // output/usage.c:
    int print_usage(void);
    void usage_error(void);
    int print_usage_error(char *str pass, int ret);
    int print_err(int ret, char *str pass, ...);

#endif /* !PROTOTYPE_H_ */
