---
sidebar: auto
---

# Server

## Initiation

### `int create_socket(void)`

```c
int create_socket(void)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int reuse = 1;

    if (sockfd < 0) {
        perror("socket");
        exit(1);
    }
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char *) &reuse,
            sizeof(reuse))
        < 0) {
        perror("setsockopt");
        exit(EXIT_FAILED);
    }
    return sockfd;
}
```

- Cette fonction permet de créer un socket.

### `int create_server(int port)`

```c
int create_server(int port)
{
    int fd = create_socket();
    struct sockaddr_in sock_in = {0};

    if (fd == -1) return -1;
    sock_in.sin_family = AF_INET;
    sock_in.sin_port = htons(port);
    sock_in.sin_addr.s_addr = INADDR_ANY;
    if (bind(fd, (struct sockaddr *) &sock_in, sizeof(sock_in)) < 0) {
        perror("bind");
        close(fd);
        exit(EXIT_FAILED);
    }
    if (listen(fd, MAX_CLIENTS) < 0) {
        perror("listen");
        close(fd);
        exit(EXIT_FAILED);
    }
    return fd;
}
```

- Cette fonction permet de créer un serveur.

### `int init_server(server_t *serv)`

```c
int init_server(server_t *serv)
{
    int fd = create_server(serv->port);
    build_board(serv);
    create_eggs(serv);
    serv->net = calloc(1, sizeof(network_t));
    serv->net->fd_server = fd;
    serv->net->timeout.tv_sec = 0;
    serv->net->timeout.tv_usec = 1 / serv->freq;
    return 0;
}
```

- Cette fonction permet d'initialiser le serveur.

## Procesus serveur

### `bool main_server(server_t *serv)`

```c
bool main_server(server_t *serv)
{
    fill_select(serv);
    if (!fd_select(serv)) return false;
    handle_select(serv);
    handle_cmd(serv);
    handle_life(serv);
    handle_eggs(serv);
    handle_resources(serv);
    return true;
}
```

- Cette fonction permet de gérer le serveur.

### `bool loop_server(server_t *serv)`

```c
bool loop_server(server_t *serv)
{
    bool succ_loop;

    printf("Port : %d\n", serv->port);
    while (1) {
        succ_loop = main_server(serv);
        if (!succ_loop) return false;
    }
    return true;
}
```

- Cette fonction permet de boucler le serveur.

## Network

### `int max_fd(server_t *serv)`

```c
int max_fd(server_t *serv)
{
    int fd_max = serv->net->fd_server;

    for (pl_t *tmp = serv->players; tmp; tmp = tmp->next)
        if (tmp->data && tmp->data->fd > fd_max) fd_max = tmp->data->fd;
    serv->net->fd_max = fd_max;
    return fd_max;
}
```

- Cette fonction permet de récupérer le plus grand fd.

### `bool new_fd(server_t *serv)`

```c
bool new_fd(server_t *serv)
{
    struct sockaddr_in addr_in;
    struct sockaddr *addr = (struct sockaddr *) &addr_in;
    socklen_t addr_len = sizeof(addr_in);
    int fd = accept(serv->net->fd_server, addr, &addr_len);

    if (fd == -1) return print_usage_error(strerror(errno), false);
    new_player(serv, fd);
    return true;
}
```

- Cette fonction permet de récupérer un nouveau fd.

### `bool handle_fd(player_t *player)`

```c
bool handle_fd(player_t *player)
{
    char buff[READ_SIZE + 1];
    ssize_t size;

    if (player->disconnected) return false;
    memset(buff, 0, READ_SIZE + 1);
    if ((size = read(player->fd, buff, READ_SIZE)) <= 0)
        player->disconnected = true;
    else if (size > 0 && strlen(buff) > 0)
        strcat(player->buff, buff);
    for (int i = 0; player->buff[i]; i++)
        if (player->buff[i] == '\n') player->nb_cmd++;
    return true;
}
```

- Cette fonction permet de gérer un fd.

### `void fill_select(server_t *serv)`

```c
void fill_select(server_t *serv)
{
    fd_set *read_fds = &(serv->net->read_fds);
    fd_set *write_fds = &(serv->net->write_fds);

    FD_ZERO(read_fds);
    FD_ZERO(write_fds);
    FD_SET(serv->net->fd_server, read_fds);
    for (pl_t *tmp = serv->players; tmp && tmp->data; tmp = tmp->next) {
        FD_SET(tmp->data->fd, read_fds);
        if (len_msg(tmp->data->to_send) > 0) FD_SET(tmp->data->fd, write_fds);
    }
}
```

- Cette fonction permet de remplir le select.

### `bool fd_select(server_t *serv)`

```c
bool fd_select(server_t *serv)
{
    network_t *net = serv->net;
    int fd = max_fd(serv) + 1;
    fd_set *read_fds = &(net->read_fds);
    fd_set *write_fds = &(net->write_fds);

    if (select(fd, read_fds, write_fds, NULL, &(net->timeout)) == -1)
        return print_usage_error(strerror(errno), false);
    return true;
}
```

- Cette fonction permet de gérer le select.

### `void to_send(player_t *player, char *cmd, ...)`

```c
void to_send(player_t *player, char *cmd, ...)
{
    va_list ap;
    char *buff;

    if (!player) return;
    buff = calloc(READ_SIZE + 1, sizeof(char));
    va_start(ap, cmd);
    vsprintf(buff, cmd, ap);
    va_end(ap);
    push_msg(&(player->to_send), buff);
}
```

- Cette fonction permet d'envoyer un message à un joueur.

### `bool send_to(player_t *player)`

```c
bool send_to(player_t *player)
{
    if (!player->to_send) return true;
    for (ml_t *msg = player->to_send; msg; msg = msg->next)
        if (write(player->fd, msg->data, strlen(msg->data)) == -1)
            return !(player->disconnected = true);
    clear_msg(&(player->to_send));
    return true;
}
```

- Cette fonction permet d'envoyer un message à un joueur.

## Commande bct

### `void cmd_bct(server_t *serv, player_t *player, char *cmd)`

```c
void cmd_bct(server_t *serv, player_t *player, char *cmd)
{
    char **data;
    int *res;

    if (!compare(cmd, 3)) return to_send(player, SBP);
    data = strarr(cmd, " ");
    res = get_resources(serv->board[atoi(data[1])][atoi(data[2])]->items);
    to_send(player, BCT, atoi(data[1]), atoi(data[2]), res[0], res[1], res[2],
        res[3], res[4], res[5], res[6]);
    free(res);
    free_arr(data);
}
```

- Cette fonction permet de récupérer les informations d'une case.

## Commande Broadcast

### `int adapt_orientation(dir_t dir, int ori, int i)`

```c
static const ori_t ORI[] = {{UP, 2, 1, 8, 4, 5, 6, 3, 7},
    {RIGHT, 4, 3, 2, 6, 7, 8, 5, 1}, {DOWN, 6, 5, 4, 8, 1, 2, 7, 3},
    {LEFT, 8, 7, 6, 2, 3, 4, 1, 5}, {NO_DIR, 0, 0, 0, 0, 0, 0, 0, 0}};

int adapt_orientation(dir_t dir, int ori, int i)
{
    while (ORI[++i].dir != dir);
    switch (ori) {
        case (11): return (ORI[i].up_left);
        case (21): return (ORI[i].down_left);
        case (31): return (ORI[i].center_left);
        case (12): return (ORI[i].up_right);
        case (22): return (ORI[i].down_right);
        case (32): return (ORI[i].center_right);
        case (13): return (ORI[i].up_center);
        case (23): return (ORI[i].down_center);
        default: return (0);
    }
}
```

- Cette fonction permet d'adapter l'orientation d'un joueur.

### `vec_t get_distance(server_t *serv, player_t *from, player_t *to)`

```c
vec_t get_distance(server_t *serv, player_t *from, player_t *to)
{
    bool bx = abs(serv->width - abs(to->x - from->x)) < abs(to->x - from->x);
    bool by = abs(serv->height - abs(to->y - from->y)) < abs(to->y - from->y);
    int x = from->x < to->x ? 1 : from->x > to->x ? -1 : 0;
    int y = from->y < to->y ? 1 : from->y > to->y ? -1 : 0;

    return (vec_t){x * (bx ? -1 : 1), y * (by ? -1 : 1)};
}
```

- Cette fonction permet de récupérer la distance entre deux joueurs.

### `int get_orientation(server_t *serv, player_t *from, player_t *to)`

```c
int get_orientation(server_t *serv, player_t *from, player_t *to)
{
    vec_t dist = get_distance(serv, from, to);
    int ori = 0;

    if (to->square == from->square) return 0;
    ori += dist.x == 1 ? 1 : dist.x == -1 ? 2 : 3;
    ori += dist.y == 1 ? 10 : dist.y == -1 ? 20 : 30;
    return adapt_orientation(to->dir, ori, -1);
}
```

- Cette fonction permet de récupérer l'orientation d'un joueur par rapport à un autre.

### `void cmd_broadcast(server_t *serv, player_t *player pass, char *cmd)`

```c
void cmd_broadcast(server_t *serv, player_t *player pass, char *cmd)
{
    pl_t *to = serv->players;
    int ori;
    char **av;

    if (!compare(cmd, 2)) return to_send(player, STR_KO);
    av = strarr(cmd, " ");
    for (; to; to = to->next) {
        if (to->data == player || !to->data->team) continue;
        ori = get_orientation(serv, player, to->data);
        to_send(to->data, "message %d, %s\n", ori, av[1]);
    }
    to_send(player, STR_OK);
    to_send(serv->graphical, PBC, player->id, av[1]);
    free_arr(av);
}
```

- Cette fonction permet d'envoyer un message à tous les joueurs.

## Commande connect

### `void cmd_connect(server_t *serv pass, player_t *player pass, char *cmd pass)
`

```c
void cmd_connect(server_t *serv pass, player_t *player pass, char *cmd pass)
{
    if (!compare(cmd, 1)) return to_send(player, STR_KO);
    to_send(player, "%d\n", slot_available(serv, player->team));
}
```

- Cette fonction permet de récupérer le nombre de slots disponibles.

## Commande eject

### `void eject(server_t *serv, player_t *to, dir_t dir)`

```c
void eject(server_t *serv, player_t *to, dir_t dir)
{
    int d[7][5] = {{5, 3, 1, 7, 0}, {1, 7, 5, 3, 0}, {3, 5, 7, 1, 0},
        {7, 1, 3, 5, 0}, {0, 0, 0, 0, 0}, {-1, 0, 1, 0, 0}, {0, 1, 0, -1, 0}};

    move_player(serv, to, d[5][dir], d[6][dir]);
    to_send(to, "eject: %d\n", d[to->dir][dir]);
    to_send(serv->graphical, PPO, to->id, to->x, to->y, to->dir + 1);
}
```

- Cette fonction permet au client de pouvoir d'éjecter un joueur.

### `void cmd_eject(server_t *serv, player_t *player, char *cmd)`

```c
void cmd_eject(server_t *serv, player_t *player, char *cmd)
{
    bool ko = true;

    if (!compare(cmd, 1)) return to_send(player, STR_KO);
    for (pl_t *tmp = player->square->players; tmp; tmp = tmp->next) {
        if (tmp->data == player) continue;
        eject(serv, tmp->data, player->dir);
        ko = false;
    }
    for (el_t *tmp = serv->eggs; tmp; tmp = tmp->next) {
        if (tmp->data->square != player->square) continue;
        to_send(serv->graphical, EDI, tmp->data->id);
        del_el(&serv->eggs, tmp->data, true);
        ko = false;
    }
    to_send(player, ko ? STR_KO : STR_OK);
    if (!ko) to_send(serv->graphical, PEX, player->id);
}
```

- Cette fonction permet d'éjecter un joueur.

## Commande end incantation

### `void create_task_cmd(player_t *player, clock_t time, exec func, int cycle)
`

```c
void create_task_cmd(player_t *player, clock_t time, exec func, int cycle)
{
    cl_t *cl;
    cmd_t *tmp = calloc(1, sizeof(cmd_t));

    tmp->cmd = strdup("empty");
    tmp->exec = func;
    tmp->cycle = cycle;
    tmp->start = time;
    cl = new_cmd(tmp);
    cl->next = func == cmd_end_incantation ? player->to_exec->next : NULL;
    if (func == cmd_end_incantation)
        player->to_exec->next = cl;
    else
        player->to_exec = cl;
    to_send(player, "Elevation underway\n");
}
```

- Cette fonction permet de créer une tâche pour un joueur.

### `void empty_cmd(server_t *serv pass, player_t *player pass, char *cmd)`

```c
void empty_cmd(server_t *serv pass, player_t *player pass, char *cmd)
{
    if (!compare(cmd, 1)) return;
    return;
}
```

- Cette checker si il y a une commande entrée.

### `void cmd_end_incantation(server_t *serv pass, player_t *player, char *cmd pass)`

```c
void cmd_end_incantation(server_t *serv pass, player_t *player, char *cmd pass)
{
    bool valid = check_can(player, true);

    for (pl_t *tmp = player->square->players; tmp; tmp = tmp->next)
        if (tmp->data->level == player->level) {
            if (valid) {
                tmp->data->level++;
                to_send(tmp->data, "Current level: %d\n", tmp->data->level);
            }
            tmp->data->to_exec->data->cycle = 0;
        }
    if (!valid) to_send(player, STR_KO);
}
```

- Cette fonction permet de finir l'incantation.

## Commande fork

### `void cmd_fork(server_t *serv, player_t *player, char *cmd)`

```c
void cmd_fork(server_t *serv, player_t *player, char *cmd)
{
    if (!compare(cmd, 1)) return to_send(player, STR_KO);
    spawn_eggs(serv, NULL, player);
    to_send(player, STR_OK);
    to_send(serv->graphical, PFK, player->id);
}
```

- Cette fonction permet de créer un oeuf.

## Commande forward

### `void move_player(server_t *serv, player_t *player, int y, int x)`

```c
void move_player(server_t *serv, player_t *player, int y, int x)
{
    player->y = (player->y + y) % serv->height;
    player->x = (player->x + x) % serv->width;
    if (player->y < 0) player->y = serv->height + player->y;
    if (player->x < 0) player->x = serv->width + player->x;
    del_pl(&player->square->players, player, false);
    player->square = serv->board[player->y][player->x];
    push_pl(&player->square->players, player);
}
```

- Cette fonction permet de déplacer un joueur.

### `void cmd_forward(server_t *serv, player_t *player, char *cmd)`

```c
void cmd_forward(server_t *serv, player_t *player, char *cmd)
{
    if (!compare(cmd, 1)) return to_send(player, STR_KO);
    switch (player->dir) {
        case (UP): move_player(serv, player, -1, 0); break;
        case (RIGHT): move_player(serv, player, 0, 1); break;
        case (DOWN): move_player(serv, player, 1, 0); break;
        case (LEFT): move_player(serv, player, 0, -1); break;
        default: to_send(player, STR_KO); return;
    }
    to_send(player, STR_OK);
    to_send(serv->graphical, PPO, player->id, player->x, player->y,
        player->dir + 1);
}
```

- Cette fonction permet de déplacer un joueur.

## Commande incantation

### `bool check_player(player_t *player, int level, int need)
`

```c
bool check_player(player_t *player, int level, int need)
{
    int nb = 0;

    for (pl_t *tmp = player->square->players; tmp; tmp = tmp->next)
        if (tmp->data->level == level) nb++;
    return (nb >= need);
}
```

- Cette fonction permet de checker si il y a assez de joueurs pour l'incantation.

### `bool check_resources(player_t *player, int need[7])`

```c
bool check_resources(player_t *player, int need[7])
{
    int *res = get_resources(player->square->items);

    for (int i = 1; i < 6; i++)
        if (res[i] < need[i]) return false;
    return true;
}
```

- Cette fonction permet de checker si il y a assez de ressources pour l'incantation.

### `bool check_can(player_t *player, bool send)`

```c
bool check_can(player_t *pl, bool remove)
{
    int need[7][7] = {{1, 1, 0, 0, 0, 0, 0}, {2, 1, 1, 1, 0, 0, 0},
        {2, 2, 0, 1, 0, 2, 0}, {4, 1, 1, 2, 0, 1, 0}, {4, 1, 2, 1, 3, 0, 0},
        {6, 1, 2, 3, 0, 1, 0}, {6, 2, 2, 2, 2, 2, 1}};

    if (!check_player(pl, pl->level, need[pl->level - 1][0])) return false;
    if (!check_resources(pl, need[pl->level - 1])) return false;
    if (!remove) return true;
    for (int i = 1; i < 6; i++)
        for (int j = 0; j < need[pl->level - 1][i]; j++)
            del_il(&pl->square->items, i);
    return true;
}
```

- Cette fonction permet de checker si l'incantation est possible.

### `void cmd_incantation(server_t *serv pass, player_t *player, char *cmd)`

```c
void cmd_incantation(server_t *serv pass, player_t *player, char *cmd)
{
    clock_t cycle = clock();

    if (!compare(cmd, 1)) return to_send(player, STR_KO);
    if (!check_can(player, false)) return to_send(player, STR_KO);
    for (pl_t *tmp = player->square->players; tmp; tmp = tmp->next)
        if (tmp->data->level == player->level && tmp->data != player)
            create_task_cmd(tmp->data, cycle, empty_cmd, INT_MAX);
    create_task_cmd(player, cycle, cmd_end_incantation, 300);
}
```

- Cette fonction permet de lancer l'incantation.

## Commande inventaire

### `void cmd_inv(server_t *serv pass, player_t *player, char *cmd)`

```c
void cmd_inv(server_t *serv pass, player_t *player, char *cmd)
{
    int *res;
    char buff[READ_SIZE + 1] = {0};

    if (!compare(cmd, 1)) return to_send(player, STR_KO);
    res = get_resources(player->inventory);
    buff[0] = '[';
    for (int i = 0; i < 7; i++)
        strcats(buff, " ", item_name((item_t) i), " ", itos(res[i]),
            i == 6 ? "" : ",", NULL);
    strcats(buff, " ]\n", NULL);
    to_send(player, buff);
    free(res);
}
```

- Cette fonction permet d'afficher l'inventaire du joueur.

## Commande ko

### `void cmd_ko(server_t *serv pass, player_t *player, char *cmd pass)`

```c
void cmd_ko(server_t *serv pass, player_t *player, char *cmd pass)
{
    to_send(player, STR_KO);
}
```

- Cette fonction permet d'envoyer ko au client.

## Commande left

### `void cmd_left(server_t *serv, player_t *player, char *cmd)`

```c
void cmd_left(server_t *serv, player_t *player, char *cmd)
{
    if (!compare(cmd, 1)) return to_send(player, STR_KO);
    player->dir = (dir_t) ((player->dir - 1) % 4);
    to_send(player, STR_OK);
    to_send(serv->graphical, PPO, player->id, player->x, player->y,
        player->dir + 1);
}
```

- Cette fonction permet de tourner le joueur à gauche.

## Commande right

### `void cmd_right(server_t *serv, player_t *player, char *cmd)`

```c
void cmd_right(server_t *serv, player_t *player, char *cmd)
{
    if (!compare(cmd, 1)) return to_send(player, STR_KO);
    player->dir = (dir_t) ((player->dir + 1) % 4);
    to_send(player, STR_OK);
    to_send(serv->graphical, PPO, player->id, player->x, player->y,
        player->dir + 1);
}
```

- Cette fonction permet de tourner le joueur à droite.

## Commande look

### `char *item_name(item_t item)`

```c
char *item_name(item_t item)
{
    char *name[8] = {"food", "linemate", "deraumere", "sibur", "mendiane",
        "phiras", "thystame", "player"};

    return name[(int) item];
}
```

- Cette fonction permet de récupérer le nom d'un item.

### `void square_to_str(square_t *square, char *buff)`

```c
void square_to_str(square_t *square, char *buff)
{
    for (il_t *tmp = square->items; tmp; tmp = tmp->next)
        strcats(buff, " ", item_name(tmp->data), NULL);
}
```

- Cette fonction permet de convertir une case en string.

### `square_t *get_square(server_t *serv, player_t *pl, int i, int j)`

```c
square_t *get_square(server_t *serv, player_t *pl, int i, int j)
{
    int pos[4][2] = {{-i, j}, {j, i}, {i, -j}, {-j, -i}};
    int p[2] = {pl->y + pos[pl->dir][0], pl->x + pos[pl->dir][1]};
    int x = p[1] < 0 ? p[1] + serv->width : (p[1] % serv->width);
    int y = p[0] < 0 ? p[0] + serv->height : (p[0] % serv->height);

    return serv->board[y][x];
}
```

- Cette fonction permet de récupérer une case en fonction de la direction du joueur.

### `void get_content(server_t *serv, player_t *player, char *buff, int idxs[2])`

```c
void get_content(server_t *serv, player_t *player, char *buff, int idxs[2])
{
    square_t *square = get_square(serv, player, idxs[0], idxs[1]);
    int nb_players = len_pl(square->players);

    for (int i = 0; i < nb_players; i++) strcats(buff, " player", NULL);
    if (len_il(square->items) > 0) square_to_str(square, buff);
    if (idxs[0] != player->level || idxs[1] != idxs[0] * 2)
        strcats(buff, ",", NULL);
}
```

- Cette fonction permet de récupérer le contenu d'une case.

### `void cmd_look(server_t *serv, player_t *player, char *cmd)`

```c
void cmd_look(server_t *serv, player_t *player, char *cmd)
{
    char *buff;
    int idxs[2] = {0, 0};

    if (!compare(cmd, 1)) return to_send(player, STR_KO);
    buff = calloc(READ_SIZE, sizeof(char));
    strcats(buff, "[", NULL);
    for (idxs[0] = 0; idxs[0] <= player->level; idxs[0]++)
        for (idxs[1] = -idxs[0]; idxs[1] <= idxs[0]; idxs[1]++)
            get_content(serv, player, buff, idxs);
    strcats(buff, " ]\n", NULL);
    to_send(player, buff);
    free(buff);
}
```

- Cette fonction permet de récupérer le contenu des cases autour du joueur.

## Commande mct

### `void cmd_mct(server_t *serv, player_t *player, char *cmd)`

```c
void cmd_mct(server_t *serv, player_t *player, char *cmd)
{
    int *res;

    if (!compare(cmd, 1)) return to_send(player, SBP);
    for (int i = 0; i < serv->height; i++)
        for (int j = 0; j < serv->width; j++) {
            res = get_resources(serv->board[i][j]->items);
            to_send(player, BCT, j, i, res[0], res[1], res[2], res[3], res[4],
                res[5], res[6]);
            free(res);
        }
}
```

- Cette fonction permet d'envoyer le contenu de toutes les cases du serveur.

## Commande msz

### `void cmd_msz(server_t *serv, player_t *player, char *cmd)`

```c
void cmd_msz(server_t *serv, player_t *player, char *cmd)
{
    if (!compare(cmd, 1)) return to_send(player, SBP);
    to_send(player, MSZ, serv->width, serv->height);
}
```

- Cette fonction permet d'envoyer la taille du serveur.

## Commande pin

### `void cmd_pin(server_t *serv, player_t *player, char *cmd)`

```c
void cmd_pin(server_t *serv, player_t *player, char *cmd)
{
    char **data;
    player_t *tmp = NULL;
    int *inv;

    if (!compare(cmd, 2)) return to_send(player, SBP);
    data = strarr(cmd, " ");
    for (pl_t *pls = serv->players; pls; pls = pls->next)
        if (pls->data->id == atoi(data[1])) tmp = pls->data;
    if (!tmp) return to_send(player, SBP);
    inv = get_resources(tmp->inventory);
    to_send(player, PIN, tmp->id, tmp->x, tmp->y, inv[0], inv[1], inv[2],
        inv[3], inv[4], inv[5], inv[6]);
    free(inv);
    free_arr(data);
}
```

- Cette fonction permet d'envoyer les informations d'un joueur.

## Commande plv

### `void cmd_plv(server_t *serv pass, player_t *player pass, char *cmd pass)`

```c
void cmd_plv(server_t *serv pass, player_t *player pass, char *cmd pass)
{
    char **data;
    player_t *tmp = NULL;

    if (!compare(cmd, 2)) return to_send(player, SBP);
    data = strarr(cmd, " ");
    for (pl_t *pls = serv->players; pls; pls = pls->next)
        if (pls->data->id == atoi(data[1])) tmp = pls->data;
    if (!tmp) return to_send(player, SBP);
    to_send(player, PLV, tmp->id, tmp->level);
    free_arr(data);
}
```

- Cette fonction permet d'envoyer le niveau d'un joueur.

## Commande ppo

### `void cmd_ppo(server_t *serv pass, player_t *player pass, char *cmd pass)`

```c
void cmd_ppo(server_t *serv pass, player_t *player pass, char *cmd pass)
{
    char **data;
    player_t *tmp = NULL;

    if (!compare(cmd, 2)) return to_send(player, SBP);
    data = strarr(cmd, " ");
    for (pl_t *pls = serv->players; pls; pls = pls->next)
        if (pls->data->id == atoi(data[1])) tmp = pls->data;
    if (!tmp) return to_send(player, SBP);
    to_send(player, PPO, tmp->id, tmp->x, tmp->y, tmp->dir);
    free_arr(data);
}
```

- Cette fonction permet d'envoyer la position d'un joueur.

## Commande sgt

### `void cmd_suc(server_t *serv pass, player_t *player, char *cmd pass)`

```c
void cmd_suc(server_t *serv pass, player_t *player, char *cmd pass)
{
    to_send(player, SUC);
}
```

- Cette fonction permet d'envoyer un message de succès.

## Commande set

### `void cmd_set(server_t *serv, player_t *player, char *cmd)`

```c
void cmd_set(server_t *serv, player_t *player, char *cmd)
{
    char **tab;
    item_t data;

    if (!compare(cmd, 2)) return to_send(player, STR_KO);
    tab = strarr(cmd, " ");
    for (il_t *items = player->inventory; items; items = items->next) {
        data = items->data;
        if (data >= 7 || strcmp(item_name(data), tab[1]) != 0) continue;
        del_il(&player->inventory, data);
        push_il(&player->square->items, data);
        free_arr(tab);
        to_send(serv->graphical, PDR, player->id, data);
        return to_send(player, STR_OK);
    }
    free_arr(tab);
    to_send(player, STR_KO);
}
```

- Cette fonction permet de poser un objet sur le sol.

## Commande sgt

### `void cmd_sgt(server_t *serv, player_t *player, char *cmd)`

```c
void cmd_sgt(server_t *serv pass, player_t *player pass, char *cmd pass)
{
    if (!compare(cmd, 1)) return to_send(player, SBP);
    to_send(player, SGT, serv->freq);
}
```

- Cette fonction permet d'envoyer la fréquence du serveur.

## Commande sst

### `void cmd_sst(server_t *serv, player_t *player, char *cmd)`

```c
void cmd_sst(server_t *serv pass, player_t *player pass, char *cmd pass)
{
    char **data;
    int freq;

    if (!compare(cmd, 2)) return to_send(player, SBP);
    data = strarr(cmd, " ");
    freq = atoi(data[1]);
    if (freq < 2) return to_send(player, SBP);
    serv->freq = freq;
    to_send(player, SST, serv->freq);
    free_arr(data);
}
```

- Cette fonction permet de changer la fréquence du serveur.

## Commande take

### `void cmd_take(server_t *serv, player_t *player, char *cmd)`

```c
void cmd_take(server_t *serv, player_t *player, char *cmd)
```

- Cette fonction permet de prendre un objet sur le sol.

## Commande tna

### `void cmd_tna(server_t *serv, player_t *player, char *cmd)`

```c
void cmd_tna(server_t *serv, player_t *player, char *cmd)
{
    if (!compare(cmd, 1)) return to_send(player, SBP);
    for (int i = 0; serv->teams[i]; i++)
        to_send(player, TNA, serv->teams[i]->name);
}
```

- Cette fonction permet d'envoyer le nom de toutes les équipes.