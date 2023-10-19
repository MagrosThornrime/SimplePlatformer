import json

if __name__ == "__main__":
    with open("sample_map.txt", "r") as f:
        text = f.read()

    tiles = []
    lights = []
    for y, line in enumerate(text.split("\n")):
        for x, digit in enumerate(line.split(" ")):
            true_y = 300.0 + y * 50.0
            true_x = x * 50.0
            tile = {
                "positionX": true_x,
                "positionY": true_y,
                "sizeX": 50.0,
                "sizeY": 50.0,
                "colorR": 1.0,
                "colorG": 1.0,
                "colorB": 1.0,
            }
            if digit == "1":
                tile["sprite"] = "bricks"
                tile["inBackground"] = False
            elif digit == "0":
                tile["sprite"] = "back"
                tile["inBackground"] = True
            elif digit == "2":
                light = {key: val for key, val in tile.items()}
                light["lightPositionX"] = true_x
                light["lightPositionY"] = true_y
                light["ambientR"] = 1.0
                light["ambientG"] = 1.0
                light["ambientB"] = 1.0
                light["quadratic"] = 0.0001
                light["linear"] = 0.0
                light["constant"] = 1.0
                light["sprite"] = "lamp1"
                lights.append(light)
                tile["sprite"] = "back"
                tile["inBackground"] = True

            tiles.append(tile)

    with open("../res/map/generated_map.json", "w") as f:
        json.dump(tiles, f, indent=2)

    with open("../res/map/generated_lights.json", "w") as f:
        json.dump(lights, f, indent=2)

