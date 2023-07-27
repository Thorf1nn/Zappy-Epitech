---
sidebar: auto
---

# IA

## ai.py

### `map_player_same_tile(map)`

```py
def map_player_same_tile(map):
    first_item = map.split(',')[0]
    count = first_item.count("player")
    return count
```

 - Cette fonction prend en paramètre une carte et compte le nombre de joueurs présents sur la même case que vous. Elle renvoie le nombre de joueurs.

### `elevation(client, map, player)`

```py
def elevation(client, map, player):
    nb_player = map_player_same_tile(map)
    if (player.get_linemate() > 0 and player.get_lvl() == 1):
        player.elevation_lvl2()
        client.fork()
        return
    if (player.get_lvl() == 2 and nb_player >= 2 and player.get_linemate() > 0 and player.get_deraumere() > 0 and player.get_sibur() > 0):
        player.elevation_lvl3()
    if (player.get_lvl() == 3 and nb_player >= 2 and player.get_linemate() > 1 and player.get_sibur() > 0 and player.get_phiras() > 1):
        player.elevation_lvl4()
        client.broadcast_send("Play")
        client.fork()
        return
    if (player.get_lvl() == 4 and nb_player >= 4 and player.get_linemate() > 0 and player.get_deraumere() > 0 and player.get_sibur() > 1 \
        and player.get_phiras() > 0):
        player.elevation_lvl5()
    elif (player.get_lvl() == 4 and nb_player >= 2):
        client.broadcast_elevation_4players()
    if (player.get_lvl() == 5 and nb_player >= 4 and player.get_linemate() > 0 and player.get_deraumere() > 1 and player.get
```

- Cette fonction gère l'élévation du joueur en fonction de son niveau actuel et des ressources disponibles sur la carte. Elle utilise la fonction map_player_same_tile(map) pour obtenir le nombre de joueurs sur la même case. Ensuite, en fonction du niveau du joueur et de la disponibilité des ressources nécessaires, elle appelle les méthodes appropriées du joueur pour s'élever vers le niveau suivant. Des actions supplémentaires, telles que la diffusion de messages à d'autres joueurs, peuvent être effectuées à certains niveaux spécifiques.

### `inventory_call(client, player)`

```py
def inventory_call(client, player):
    inv = client.inventory()
    print("=== Inventory: " + inv)
    parts_string = inv.replace('[', '').replace(']','')
    parts_list = parts_string.split(',')
    numbers = [int(part.split()[1]) for part in parts_list]

    player.set_food(numbers[0])
    player.set_linemate(numbers[1])
    player.set_deraumere(numbers[2])
    player.set_sibur(numbers[3])
    player.set_mendiane(numbers[4])
    player.set_phiras(numbers[5])
    player.set_thystame(numbers[6])
```

- Cette fonction récupère l'inventaire du joueur à l'aide de la méthode client.inventory(). Les différentes ressources sont extraites de la chaîne de caractères et stockées dans les attributs correspondants de l'objet player.


### `path_to_location(count, line_lvl, client)`

```py
def path_to_location(count, line_lvl, client):
    mid_line_lvl = line_lvl * (line_lvl + 1)

    if (mid_line_lvl > count):
        for i in range(line_lvl):
            client.move("Forward")
        client.move("Left")
        for i in range(mid_line_lvl - count):
            client.move("Forward")
    elif (mid_line_lvl < count):
        for i in range(line_lvl):
            client.move("Forward")
        client.move("Right")
        for i in range(mid_line_lvl - count):
            client.move("Forward")
    else:
        for i in range(line_lvl):
            client.move("Forward")
```

- Cette fonction permet de déplacer le joueur vers une position spécifique sur la carte en fonction du nombre de cases à parcourir et du niveau de la ligne. Le joueur se déplace vers l'avant, à gauche ou à droite jusqu'à atteindre la position désirée.

### `loop_elements_find(elements, item)(count, line_lvl, client)`

```py
def loop_elements_find(elements, item):
    count = -1
    line_lvl = 0
    find = False

    # Prend le niveau de la case
    for element in elements:
        count += 1
        if (count == 0):
            continue
        element = element.strip()
        if (count > 0):
            line_lvl = 1
        if (count > 3):
            line_lvl = 2
        if (count > 8):
            line_lvl = 3
        if (count > 15):
            line_lvl = 4
        if (count > 24):
            line_lvl = 5
        if (count > 35):
            line_lvl = 6
        if (count > 42):
            line_lvl = 7
        if (count > 63):
            line_lvl = 8
        if item in element:
            find = True
            break
    return line_lvl, find, count
```

- Cette fonction parcourt les éléments d'une liste elements qui représente les cases de la carte. Elle trouve le niveau de la case (line_lvl) en fonction de la position de l'élément dans la liste. Elle retourne également un booléen indiquant si l'élément recherché (item) a été trouvé dans la liste, ainsi que le compte total des éléments parcourus.

### `move_to_precise_location(map, item, player, client)`

```py
def move_to_precise_location(map, item, player, client):
    elements = map.strip('[]').split(',')
    line_lvl = 0
    count = 0
    find = False

    # Prend le niveau de la case
    line_lvl, find, count = loop_elements_find(elements, item)

    if (find == False):
        item = "food"
        line_lvl, find, count = loop_elements_find(elements, item)
    if (item == "player"):
        if (player.get_lvl() == 2):
            client.broadcast_send("Freeze2")
        if (player.get_lvl() == 4):
            client.broadcast_send("Freeze4")
        if (player.get_lvl() == 6):
            client.broadcast_send("Freeze6")
    path_to_location(count, line_lvl, client)
    return item
```

- Cette fonction utilise la fonction loop_elements_find() pour trouver la position précise (line_lvl) d'un élément spécifique (item) dans la carte. Ensuite, en fonction de l'élément trouvé, elle effectue des actions supplémentaires, telles que l'envoi de messages de diffusion, en fonction du niveau du joueur. Enfin, elle utilise la fonction path_to_location() pour déplacer le joueur vers la position précise sur la carte.

### `parsing_first_tile(map)`

```py
def parsing_first_tile(map):
    input_string = map.strip("[]")
    tiles = input_string.split(",")
    parsed_tiles = [tile.strip().split() for tile in tiles]
    parsed_tiles = [[element for element in tile if element != 'player'] for tile in parsed_tiles]

    if (len(parsed_tiles[0]) != 0):
        return (parsed_tiles[0][0])
    return ("Nothing")
```

 - Cette fonction analyse la première case de la carte (map) pour extraire le premier élément non vide. Elle supprime les crochets, divise les éléments en cases individuelles, puis les organise dans une liste. Enfin, elle retourne le premier élément non vide trouvé dans la première case de la liste parsed_tiles. Si aucun élément n'est trouvé, elle renvoie la chaîne "Nothing".

### `take_object_on_tile(client)`

```py
def take_object_on_tile(client):
    item = ""

    while (item != "Nothing"):
        item = parsing_first_tile(client.look())
        print(item)
        take = client.take_object(item)
```

- Cette fonction permet au joueur de prendre tous les objets présents sur la case actuelle. Elle utilise la fonction parsing_first_tile() pour déterminer l'objet présent sur la case et utilise ensuite la méthode take_object() du client pour prendre cet objet. La boucle continue tant qu'il y a des objets à prendre sur la case.


## client_data.py

### `Class ClientData`

```py

def __init__(self, name, client_num, x, y, sock):
    self.name = name
    self.client_num = client_num
    self.x = x
    self.y = y
    self.sock = sock
    self.player = False

    print ("-->TEAM-NAME", self.name)
    print("<--CLIENT-NUM", self.client_num)
    print("<--X Y", self.x, self.y)

```

- Constructeur de la classe `ClientData`. Initialise les attributs de l'objet `ClientData`.

### `set_player(self, player):`

```py
  def set_player(self, player):
        self.player = player
```

- Définit le player
- Args: player (bool): Booléen indiquant si le client est un joueur.

### `wait_message(self)`

```py
def wait_message(self):
    """
    Attend et retourne un message reçu par le socket.

    Returns:
        str: Le message reçu.
    """
    msg = self.sock.receive_message()
    msg2 = msg.replace("\n", "")
    mots = msg2.split()
    if (msg2 == "ko"):
        return msg2
    print("WORDS: " + msg2)
    if (mots[0] != "Current"):
        ret = self.my_broadcast(msg2)
        if (ret == "fine"):
            msg = self.sock.receive_message()
    return msg
```
- Cette méthode permet d'attendre et de retourner un message reçu par le socket du client. Elle renvoie le message sous forme de chaîne de caractères. La méthode effectue également certaines opérations supplémentaires, telles que la suppression des caractères de saut de ligne, l'affichage des mots du message et l'appel à la méthode my_broadcast() dans certaines conditions.

### `move(self, action)`

```py
def move(self, action):
    """
    Effectue un mouvement dans une certaine direction.

    Args:
        action (str): L'action de mouvement à effectuer.

    Returns:
        str: Le résultat du mouvement.
    """
    msg = action + "\n"
    self.sock.send_message(msg)
    move = self.sock.receive_message()
    move2 = move.replace("\n", "")
    if (move2 != "ok"):
        ret = self.my_broadcast(move2)
        if (ret == "fine"):
            move = self.sock.receive_message()
    return move
```

- Cette méthode permet d'effectuer un mouvement dans une certaine direction spécifiée par l'action. Elle renvoie le résultat du mouvement sous forme de chaîne de caractères.

### `look(self)`

```py
def look(self):
    """
    Effectue une action de regarder autour pour obtenir la carte du jeu.

    Returns:
        str: La carte du jeu.
    """
    msg = "Look\n"
    self.sock.send_message(msg)
    map_game = self.sock.receive_message()
    if (map_game[0] != '['):
        ret = self.my_broadcast(map_game)
        if (ret == "fine"):
            map_game = self.sock.receive_message()
    return map_game
```

- Cette méthode permet d'effectuer une action de regarder autour pour obtenir la carte du jeu. Elle renvoie la carte du jeu sous forme de chaîne de caractères.

### `inventory(self)`

```py
def inventory(self):
    """
    Récupère l'inventaire du joueur.

    Returns:
        str: L'inventaire du joueur.
    """
    msg = "Inventory\n"
    self.sock.send_message(msg)
    inv = self.sock.receive_message()
    if (inv[0] != '['):
        ret = self.my_broadcast(inv)
        if (ret == "fine"):
            inv = self.sock.receive_message()
    return inv
```
- Cette méthode permet de récupérer l'inventaire du joueur. Elle renvoie l'inventaire sous forme de chaîne de caractères.

### `broadcast_send(self, msg)`

```py

def broadcast_send(self, msg):
    """
    Envoie un message de diffusion à tous les joueurs.

    Args:
        msg (str): Le message à diffuser.
    """
    msg = "Broadcast " + msg + "\n"
    self.sock.send_message(msg)
    msg = self.sock.receive_message()
```

- Cette méthode permet d'envoyer un message de diffusion à tous les joueurs. Elle n'a pas de valeur de retour.

### `nb_slots_unused(self)`

```py
def nb_slots_unused(self):
    """
    Récupère le nombre d'emplacements inutilisés pour les joueurs.

    Returns:
        str: Le nombre d'emplacements inutilisés.
    """
    msg = "Connect_nbr\n"
    self.sock.send_message(msg)
    self.sock.receive_message()
```

- Cette méthode permet de récupérer le nombre d'emplacements inutilisés pour les joueurs. Elle renvoie le nombre d'emplacements inutilisés sous forme de chaîne de caractères.

### `fork(self)`

```py
def fork(self):
    """
    Déclenche un nouvel appel de joueur.

    Returns:
        str: Le résultat du déclenchement.
    """
    msg = "Fork\n"
    self.sock.send_message(msg)
    msg = self.sock.receive_message()
    msg = msg.replace("\n", "")
    if (msg != "ok"):
        ret = self.my_broadcast(msg)
        if (ret == "fine"):
            msg = self.sock.receive_message()
```

- Cette méthode permet de déclencher un nouvel appel de joueur. Elle renvoie le résultat du déclenchement sous forme de chaîne de caractères.

### `eject(self)`

```py
def eject(self):
    """
    Expulse les joueurs présents sur la même case que le joueur courant.

    Returns:
        str: Le résultat de l'expulsion.
    """
    msg = "Eject\n"
    self.sock.send_message(msg)
    msg = self.sock.receive_message()
    msg = msg.replace("\n", "")
    if (msg != "ok" and msg != "ko"):
        ret = self.my_broadcast(msg)
        if (ret == "fine"):
            msg = self.sock.receive_message()
```
- Cette méthode permet d'expulser les joueurs présents sur la même case que le joueur courant. Elle renvoie le résultat de l'expulsion sous forme de chaîne de caractères.

### `take_object(self, object)`

```py
def take_object(self, object):
    """
    Ramasse un objet de la case actuelle.

    Args:
        object (str): L'objet à ramasser.

    Returns:
        str: Le résultat du ramassage.
    """
    msg = "Take " + object + "\n"
    self.sock.send_message(msg)
    res = self.sock.receive_message()
    res = res.replace("\n", "")
    if (res != "ok" and res != "ko"):
        ret = self.my_broadcast(res)
        if (ret == "fine"):
            res = self.sock.receive_message()
    return res
```

- Cette méthode permet de ramasser un objet de la case actuelle. Elle renvoie le résultat du ramassage sous forme de chaîne de caractères.

### `set_object(self, object)`

```py
def set_object(self, object):
    """
    Pose un objet sur la case actuelle.

    Args:
        object (str): L'objet à poser.

    Returns:
        str: Le résultat de la pose de l'objet.
    """
    msg = "Set " + object + "\n"
    self.sock.send_message(msg)
    res = self.sock.receive_message()
    res2 = res.replace("\n", "")
    if (res2 != "ok" and res2 != "ko"):
        ret = self.my_broadcast(res2)
        if (ret == "fine"):
            res = self.sock.receive_message()
    return res
```

- Cette méthode permet de poser un objet sur la case actuelle. Elle renvoie le résultat de la pose de l'objet sous forme de chaîne de caractères.

### `start_incantation(self)`

```py
def start_incantation(self):
    """
    Démarre l'incantation sur la case actuelle.

    Returns:
        str: Le résultat de l'incantation.
    """
    msg = "Incantation\n"
    self.sock.send_message(msg)
    res = self.sock.receive_message()
    res2 = res.replace("\n", "")
    if (res2 != "Elevation underway"):
        ret = self.my_broadcast(res2)
        if (ret == "fine"):
            res = self.sock.receive_message()
    print("============== ELEVATION LEVEL: " + res)
    return res
```

- Cette méthode permet de démarrer l'incantation sur la case actuelle. Elle renvoie le résultat de l'incantation sous forme de chaîne de caractères.

### `dead(self)`

```py
def dead(self):
    """
    Attends la réponse de l'action `Dead`.
    """
    self.sock.receive_message()
```

- Cette méthode attend la réponse de l'action Dead. Elle ne renvoie aucune valeur.

### `wait_message_broadcast(self)`

```py
def wait_message_broadcast(self):
    """
    Attend un message de diffusion.

    Returns:
        str: Le message de diffusion.
    """
    msg = self.sock.receive_message()
    msg2 = msg.replace("\n", "")
    msg2 = msg2.split(",")[-1].strip()
    if ", " in msg2:
        split_message = msg.split(", ")
        msg = split_message[1]
    if msg2 == "Elevation underway":
        self.player.set_lvl(self.player.get_lvl() + 1)
    return msg2
```

- Cette méthode permet d'attendre un message de diffusion. Elle renvoie le message de diffusion sous forme de chaîne de caractères.

### `broadcast_elevation_2players(self)`

```py
def broadcast_elevation_2players(self):
    """
    Diffuse un message d'élévation pour 2 joueurs.

    Returns:
        str: "OK".
    """
    print("=== I'm Freeze")
    while (1):
        msg = self.wait_message_broadcast()
        if (msg == "dead"):
            print("Player dead")
            sys.exit(0)
        if (msg == "Play"):
            break
    return "OK"
```
- Cette méthode diffuse un message d'élévation pour 2 joueurs. Elle renvoie la chaîne de caractères "OK".

### `broadcast_elevation_4players(self)`

```py
def broadcast_elevation_4players(self):
    """
    Diffuse un message d'élévation pour 4 joueurs.

    Returns:
        str: "OK".
    """
    print("=== I'm Freeze")
    while (1):
        msg = self.wait_message_broadcast()
        if (msg == "dead"):
            print("Player dead")
            sys.exit(0)
        if (msg == "Play4"):
            break
    return "OK"
```
- Cette méthode diffuse un message d'élévation pour 4 joueurs. Elle renvoie la chaîne de caractères "OK".

### `broadcast_elevation_6players(self)`

```py
def broadcast_elevation_6players(self):
    """
    Diffuse un message d'élévation pour 6 joueurs.

    Returns:
        str: "OK".
    """
    print("=== I'm Freeze")
    while (1):
        self.broadcast_send("Food Check")
        msg = self.wait_message_broadcast()  
        if (msg == "dead"):
            print("Player dead")
            sys.exit(0)
        if (self.player.get_food() <= 5):
            break
        if (msg == "Play6"):
            break
        self.broadcast_send("Food Check")
    return "OK"
```

### `my_broadcast(self, msg)`

```py
def my_broadcast(self, msg):
    """
    Diffuse un message de diffusion spécifique.

    Args:
        msg (str): Le message à diffuser.

    Returns:
        str: "fine" ou le résultat spécifique du message.
    """
    msg = msg.replace("\n", "")
    if ", " in msg:
        split_message = msg.split(", ")
        msg = split_message[1]
    self.broadcast_send(msg)
    while (1):
        msg = self.wait_message_broadcast()
        if (msg == "dead"):
            print("Player dead")
            sys.exit(0)
        if (msg == "fine"):
            break
    return "fine"
```

- Cette méthode permet de diffuser un message de diffusion spécifique. Elle renvoie la chaîne de caractères "fine" ou le résultat spécifique du message diffusé.

### `get_client_num(self)`

```py
def get_client_num(self):
    """
    Obtient le numéro du client.

    Returns:
        int: Le numéro du client.
    """
    return self.client_num
```

- Cette méthode permet d'obtenir le numéro du client. Elle renvoie le numéro du client sous forme d'entier.

### `get_world_size(self)`

```py
def get_world_size(self):
    """
    Obtient la taille du monde.

    Returns:
        tuple: Un tuple contenant les dimensions (x, y) du monde.
    """
    return (self.x, self.y)
```

- Cette méthode permet d'obtenir la taille du monde. Elle renvoie un tuple contenant les dimensions (x, y) du monde.

## communication.py

### `Class Communication`

```py
def __init__(self, port, machine):
    """
    Initialise la socket de communication.

    Args:
        port (int): Le numéro de port à utiliser.
        machine (str): L'adresse IP ou le nom de la machine distante.
    """
    self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    self.sock.connect((machine, port))
```

- Cette méthode initialise la socket de communication. Elle prend en paramètres le numéro de port port et le nom de la machine distante machine, puis établit une connexion avec cette machine sur le port spécifié.

### `receive_message(self)`

```py
def receive_message(self):
    """
    Reçoit un message du serveur.

    Returns:
        str: Le message reçu.
    """
    received_data = self.sock.recv(1024)
    data_encode = received_data.decode()
    return data_encode
```

- Cette méthode permet de recevoir un message du serveur. Elle renvoie le message reçu sous forme de chaîne de caractères.

### `send_message(self, msg)`

```py
def send_message(self, msg):
    """
    Envoie un message au serveur.

    Args:
        msg (str): Le message à envoyer.

    Returns:
        bool: True si l'envoi est réussi, False sinon.
    """
    try:
        self.sock.sendall(msg.encode())
        return True
    except Exception as e:
        print("Error occurred while sending message:", str(e))
        return False
```
- Cette méthode permet d'envoyer un message au serveur. Elle prend en paramètre le message `msg` à envoyer et renvoie `True` si l'envoi est réussi, sinon elle renvoie `False`.

### `close(self)`

```py
def close(self):
    """
    Ferme la socket de communication.
    """
    self.sock.close()
```

- Cette méthode permet de fermer la socket de communication.

## connexion.py


### `check_message_send(sock, name)`

```py
# check if the message is a welcome message and send the name to the server
def check_message_send(sock, name):
    data_encode = sock.receive_message()
    if data_encode == "WELCOME\n":
        sock.send_message(name + "\n")
        return True
    return False

```

- Cette méthode permet de vérifier si le message reçu est un message de bienvenue et d'envoyer le nom du joueur au serveur. Elle prend en paramètres la socket de communication `sock` et le nom du joueur `name` et renvoie `True` si le message reçu est un message de bienvenue, sinon elle renvoie `False`.

### `get_infos(sock, name)`

```py
# get the informations from the server
def get_infos(sock, name):
    infos = sock.receive_message()
    infos2 = sock.receive_message()
    lines = infos.strip().split("\n")
    lines2 = infos2.strip().split("\n")
    client_num = int(lines[0])
    x, y = map(int, lines2[0].split())

    # check if possible to connect
    # if (client_num < 1):
    #     print("Unable to connect a new client")
    #     sys.exit(84)

    client = ClientData(name, client_num, x, y, sock)

    ai_model(client)
```

- Cette méthode permet d'obtenir les informations du serveur. Elle prend en paramètres la socket de communication `sock` et le nom du joueur `name`. Elle renvoie les informations du serveur sous forme de chaîne de caractères.

### `init_ai(sock, name)`

```py
def init_ai(sock, name):
    # check message
    if check_message_send(sock, name) == False:
        print("Error: problem with the server")
        sys.exit(84)
    # get infos
    get_infos(sock, name)
```

- Cette méthode permet d'initialiser l'IA. Elle prend en paramètres la socket de communication `sock` et le nom du joueur `name`.

## main.py

### `print_usage()`

```py
def print_usage():
    print("USAGE: ./zappy_ai -p port -n name -h machine")
    print("       port     is the port number")
    print("       name     is the name of the team")
    print("       machine  is the name of the machine; localhost by default")
```

- Cette méthode permet d'afficher l'utilisation du programme.

### `main()`

```py
def main():
    if len(sys.argv) == 2 and sys.argv[1] == "-help":
        print_usage()
        return 0

    # init Parsing
    parser = Parsing()
    parser.error_handing()
    parser.run()

    # Get arguments
    port = parser.get_port()
    name = parser.get_name()
    machine = parser.get_machine()

    # Create Communication
    sock = Communication(port, machine)

    # Init Ai parameters with communication
    # initialize_model()

    init_ai(sock, name)

    # End of the main
    sock.close()

if __name__ == '__main__':
    main()
```

- Cette méthode permet d'exécuter le programme principal.

## parsing.py

### `Class Parsing`

```py
def __init__(self):
        self.parser = argparse.ArgumentParser(prog='./zappy_ai', description='zappy_ai command-line arguments', add_help=False)
        self.port = 0
        self.name = 0
        self.machine = 0
        self.parser.add_argument('-p', dest='port', type=int, help='Port number')
        self.parser.add_argument('-n', dest='name', type=str, help='Name of the team')
        self.parser.add_argument('-h', dest='machine', type=str, default='localhost', help='Name of the machine')
```

- Cette méthode initialise la classe Parsing. Elle prend en paramètres le numéro de port `port`, le nom de la machine `machine` et le nom de l'équipe `name`.

### `parse_arguments(self)`

```py
  def parse_arguments(self):
        return self.parser.parse_args()
```

- Cette méthode permet de parser les arguments.

### `error_handing(self)`

```py
def error_handing(self):
        args = self.parse_arguments()
        if args.port is None or args.name is None:
            print("Error: Invalid number of arguments")
            sys.exit(84)
```

- Cette méthode permet de gérer les erreurs. Elle prend en paramètres les arguments `args` et renvoie `True` si le nombre d'arguments est invalide, sinon elle renvoie `False`.

### `run(self)`

```py
def run(self):
        args = self.parse_arguments()
        self.port = args.port
        self.name = args.name
        self.machine = args.machine
```

- Cette méthode permet d'exécuter le programme principal. Elle prend en paramètres les arguments `args`.

### `get_port(self)`

```py
def get_port(self):
        return self.port
```

- Cette méthode permet d'obtenir le numéro de port.

### `get_name(self)`

```py
def get_name(self):
        return self.name
```

- Cette méthode permet d'obtenir le nom de l'équipe.

### `get_machine(self)`

```py
def get_machine(self):
        return self.machine
```

- Cette méthode permet d'obtenir le nom de la machine.

### `set_things(self, port, name, machine)`

```py
def set_things(self, port, name, machine):
        self.port = port
        self.name = name
        self.machine = machine
```

- Cette méthode permet de définir les paramètres. Elle prend en paramètres le numéro de port `port`, le nom de la machine `machine` et le nom de l'équipe `name`.

## player.py

### `Class Player`

```py
class Player:
    def __init__(self, client):
        self.client = client
        self.lvl = 1
        self.food = 10
        self.linemate = 0
        self.deraumere = 0
        self.sibur = 0
        self.mendiane = 0
        self.phiras = 0
        self.thystame = 0
```

- Cette méthode initialise la classe Player. Elle prend en paramètres le client `client`.

### `set_lvl(self, lvl)`

```py
def set_lvl(self, lvl):
        self.lvl = lvl
```

- Cette méthode permet de définir le niveau du joueur. Elle prend en paramètres le niveau `lvl`.

### `set_food(self, food)`

```py
def set_food(self, food):
        self.food = food
```

- Cette méthode permet de définir la nourriture du joueur. Elle prend en paramètres la nourriture `food`.

### `set_linemate(self, linemate)`

```py
def set_linemate(self, linemate):
        self.linemate = linemate
```

- Cette méthode permet de définir le linemate du joueur. Elle prend en paramètres le linemate `linemate`.

### `set_deraumere(self, deraumere)`

```py
def set_deraumere(self, deraumere):
        self.deraumere = deraumere
```

- Cette méthode permet de définir le deraumere du joueur. Elle prend en paramètres le deraumere `deraumere`.

### `set_sibur(self, sibur)`

```py
def set_sibur(self, sibur):
        self.sibur = sibur
```

- Cette méthode permet de définir le sibur du joueur. Elle prend en paramètres le sibur `sibur`.

### `set_mendiane(self, mendiane)`

```py
def set_mendiane(self, mendiane):
        self.mendiane = mendiane
```

- Cette méthode permet de définir le mendiane du joueur. Elle prend en paramètres le mendiane `mendiane`.

### `set_phiras(self, phiras)`

```py
def set_phiras(self, phiras):
        self.phiras = phiras
```

- Cette méthode permet de définir le phiras du joueur. Elle prend en paramètres le phiras `phiras`.

### `set_thystame(self, thystame)`

```py
def set_thystame(self, thystame):
        self.thystame = thystame
```

- Cette méthode permet de définir le thystame du joueur. Elle prend en paramètres le thystame `thystame`.

### `elevation_lvl2(self)`

```py
self.client.set_object("linemate")
    msg = self.client.start_incantation()
    msg = msg.replace("\n", "")
    if (msg != "ko"):
        self.client.wait_message()
        self.lvl += 1
```

- Cette méthode permet de faire l'incantation pour passer au niveau 2.

### `elevation_lvl3(self)`

```py
def elevation_lvl3(self):
    self.client.set_object("linemate")
    self.client.set_object("deraumere")
    self.client.set_object("sibur")

    msg = self.client.start_incantation()
    msg = msg.replace("\n", "")
    if (msg != "ko"):
        self.client.wait_message()
        self.lvl += 1
```

- Cette méthode permet de faire l'incantation pour passer au niveau 3.

### `elevation_lvl4(self)`

```py
def elevation_lvl4(self):
    self.client.set_object("linemate")
    self.client.set_object("linemate")
    self.client.set_object("sibur")
    self.client.set_object("phiras")

    msg = self.client.start_incantation()
    msg = msg.replace("\n", "")
    if (msg != "ko"):
        self.client.wait_message()
        self.lvl += 1
```

- Cette méthode permet de faire l'incantation pour passer au niveau 4.

### `elevation_lvl5(self)`

```py
def elevation_lvl5(self):
    self.client.set_object("linemate")
    self.client.set_object("deraumere")
    self.client.set_object("sibur")
    self.client.set_object("sibur")
    self.client.set_object("phiras")

    msg = self.client.start_incantation()
    msg = msg.replace("\n", "")
    if (msg != "ko"):
        self.client.wait_message()
        self.lvl += 1
```

- Cette méthode permet de faire l'incantation pour passer au niveau 5.

### `elevation_lvl6(self)`

```py
def elevation_lvl6(self):
    self.client.set_object("linemate")
    self.client.set_object("deraumere")
    self.client.set_object("deraumere")
    self.client.set_object("sibur")
    self.client.set_object("phiras")
    self.client.set_object("phiras")

    msg = self.client.start_incantation()
    msg = msg.replace("\n", "")
    if (msg != "ko"):
        self.client.wait_message()
        self.lvl += 1
```

- Cette méthode permet de faire l'incantation pour passer au niveau 6.

### `elevation_lvl7(self)`

```py
def elevation_lvl7(self):
    self.client.set_object("linemate")
    self.client.set_object("linemate")
    self.client.set_object("deraumere")
    self.client.set_object("deraumere")
    self.client.set_object("sibur")
    self.client.set_object("sibur")
    self.client.set_object("mendiane")
    self.client.set_object("mendiane")
    self.client.set_object("phiras")
    self.client.set_object("phiras")
    self.client.set_object("thystame")

    msg = self.client.start_incantation()
    msg = msg.replace("\n", "")
    if (msg != "ko"):
        self.client.wait_message()
        self.lvl += 1
```

- Cette méthode permet de faire l'incantation pour passer au niveau 7.

### `get_lvl(self)`

```py
def get_lvl(self):
    return self.lvl
```

- Cette méthode permet de récupérer le niveau du joueur.

### `get_food(self)`

```py
def get_food(self):
    return self.food
```

- Cette méthode permet de récupérer la nourriture du joueur.

### `get_linemate(self)`

```py
def get_linemate(self):
    return self.linemate
```

- Cette méthode permet de récupérer le linemate du joueur.

### `get_deraumere(self)`

```py
def get_deraumere(self):
    return self.deraumere
```

- Cette méthode permet de récupérer le deraumere du joueur.

### `get_sibur(self)`

```py
def get_sibur(self):
    return self.sibur
```

- Cette méthode permet de récupérer le sibur du joueur.

### `get_mendiane(self)`

```py
def get_mendiane(self):
    return self.mendiane
```

- Cette méthode permet de récupérer le mendiane du joueur.

### `get_phiras(self)`

```py
def get_phiras(self):
    return self.phiras
```

- Cette méthode permet de récupérer le phiras du joueur.

### `get_thystame(self)`

```py
def get_thystame(self):
    return self.thystame
```

- Cette méthode permet de récupérer le thystame du joueur.
