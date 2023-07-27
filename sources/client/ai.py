#!/bin/python3

from sources.client.player import Player

# Take number of player on the same tile than you
def map_player_same_tile(map):
    first_item = map.split(',')[0]
    count = first_item.count("player")

    return count

# Function use for the elevation of player
# Non c'pas une forêt de if c'est github qui bug
def elevation(client, map, player, food_required):
    nb_player = map_player_same_tile(map)
    if (player.get_linemate() > 0 and player.get_lvl() == 1):
        player.elevation_lvl2()
        client.fork()
        return
    if (food_required == 0):
        return
    if (player.get_lvl() == 2 and nb_player == 2 and player.get_linemate() > 0 and player.get_deraumere() > 0 and player.get_sibur() > 0):
        player.elevation_lvl3()
    if (player.get_lvl() == 3 and nb_player == 2 and player.get_linemate() > 1 and player.get_sibur() > 0 and player.get_phiras() > 1):
        player.elevation_lvl4()
        client.broadcast_send("Play")
        client.fork()
        return
    if (player.get_lvl() == 4 and nb_player >= 4 and player.get_linemate() > 0 and player.get_deraumere() > 0 and player.get_sibur() > 1 \
        and player.get_phiras() > 0):
        player.elevation_lvl5()
    elif (player.get_lvl() == 4 and nb_player >= 2):    
        client.broadcast_elevation_4players()
    if (player.get_lvl() == 5 and nb_player >= 4 and player.get_linemate() > 0 and player.get_deraumere() > 1 and player.get_sibur() > 0 \
        and player.get_mendiane() > 2):
        player.elevation_lvl6()
        client.broadcast_send("Play2")
        client.fork()
        return
    if (player.get_lvl() == 6 and nb_player >= 6 and player.get_linemate() > 0 and player.get_deraumere() > 1 and player.get_sibur() > 2 \
        and player.get_phiras() > 0):
        player.elevation_lvl7()
    elif (player.get_lvl() == 6 and nb_player >= 2):    
        client.broadcast_elevation_6players()
    if (player.get_lvl() == 7 and nb_player >= 6 and player.get_linemate() > 1 and player.get_deraumere() > 1 and player.get_sibur() > 1 \
        and player.get_mendiane() > 1 and player.get_phiras() > 1 and player.get_thystame() > 0):
        player.elevation_lvl8()
        client.broadcast_send("Play3")
        return

# Stock in player class the inventory
def inventory_call(client, player):
    inv = client.inventory()
    print("=== Inventory: " + inv)
    parts_string = inv.replace('[', '').replace(']', '')    
    parts_list = parts_string.split(',')
    numbers = [int(part.split()[1]) for part in parts_list]

    player.set_food(numbers[0])
    player.set_linemate(numbers[1])
    player.set_deraumere(numbers[2])
    player.set_sibur(numbers[3])
    player.set_mendiane(numbers[4])
    player.set_phiras(numbers[5])
    player.set_thystame(numbers[6])

# Compare and move to desired location
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

def loop_elements_find(elements, item):
    count = -1
    line_lvl = 0
    find = False

    # Take the lvl of the tile
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

def move_to_precise_location(map, item, player, client):
    elements = map.strip('[]').split(',')
    line_lvl = 0
    count = 0
    find = False

    # Take the lvl of the tile
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

# Map example: [ player food deraumere, food, food food food linemate, food food food food linemate ]
def parsing_first_tile(map):
    input_string = map.strip("[]")
    tiles = input_string.split(",")
    parsed_tiles = [tile.strip().split() for tile in tiles]
    parsed_tiles = [[element for element in tile if element != 'player'] for tile in parsed_tiles]

    if (len(parsed_tiles[0]) != 0):
        return (parsed_tiles[0][0])
    return ("Nothing")

# Take all objects on the floor
def take_object_on_tile(client):
    item = ""

    while (item != "Nothing"):
        item = parsing_first_tile(client.look())
        print(item)
        take = client.take_object(item)

##### Ressources Needed for all lvl
def we_need_lvl2(player):
    if (player.get_linemate() < 3):
        return "linemate"
    if (player.get_deraumere() < 1):
        return "deraumere"
    if (player.get_phiras() < 2):
        return "phiras"
    if (player.get_sibur() < 2):
        return "sibur"
    return "player"

def we_need_lvl4(player):
    if (player.get_sibur() < 3):
        return "sibur"
    if (player.get_linemate() < 2):
        return "linemate"
    if (player.get_deraumere() < 3):
        return "deraumere"
    if (player.get_phiras() < 1):
        return "deraumere"
    if (player.get_mendiane() < 3):
        return "mendiane"
    return "player"

def we_need_lvl6(player):
    if (player.get_sibur() < 3):
        return "sibur"
    if (player.get_linemate() < 1):
        return "linemate"
    if (player.get_deraumere() < 2):
        return "deraumere"
    if (player.get_phiras() < 1):
        return "deraumere"
    return "player"

def we_need_lvl7(player):
    if (player.get_sibur() < 2):
        return "sibur"
    if (player.get_linemate() < 2):
        return "linemate"
    if (player.get_deraumere() < 2):
        return "deraumere"
    if (player.get_phiras() < 2):
        return "deraumere"
    if (player.get_mendiane() < 2):
        return "mendiane"
    return "player"

# Define what we need
def what_we_need(map, player, food_required):
    lvl = player.get_lvl()
    if (food_required == 0):
        return "food"

    if (lvl == 1):
        return "linemate"
    if (lvl == 2):
        return we_need_lvl2(player)
    if (lvl == 4):
        return we_need_lvl4(player)
    if (lvl == 6):
        return we_need_lvl6(player)
    if (lvl == 7):
        return we_need_lvl7(player)
    return "food"

def urgent_food_stock(player, actual):
    if (player.get_food() >= 30):
        return 1
    elif (player.get_food() <= 8):
        return 0
    return actual

# Base of the program
def ai_model(client):
    food_required = 0
    player = Player(client)
    client.set_player(player)
    while(1):
        map = client.look()
        print("===== LEVEL: " + str(player.get_lvl()))
        print("=== Map: " + map)
        food_required = urgent_food_stock(player, food_required)
        need = what_we_need(map, player, food_required)
        need = move_to_precise_location(map, need, player, client)

        map2 = client.look()
        print("Map after move: " + map2)
        if (need != "player"):
            take_object_on_tile(client)
        inventory_call(client, player)
        elevation(client, map2, player, food_required)

        if (player.get_food() == 0):
            client.dead()
            print("Bahaha ratio t'es mort sale noob")
            return
    return 0
