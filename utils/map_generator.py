import json

if __name__ == "__main__":
    with open("sample_map.txt", "r") as f:
        text = f.read()

    tiles = []
    for y, line in enumerate(text.split("\n")):
        for x, digit in enumerate(line.split(" ")):
            if digit == "1":
                true_y = 300.0 + y * 50.0
                true_x = x * 50.0
                tile = {
                    "sprite": "bricks",
                    "positionX": true_x,
                    "positionY": true_y,
                    "sizeX": 50.0,
                    "sizeY": 50.0,
                    "rotation": 0.0,
                    "colorR": 1.0,
                    "colorG": 1.0,
                    "colorB": 1.0,
                }
                tiles.append(tile)

    with open("../res/generated_map.json", "w") as f:
        json.dump(tiles, f, indent=2)

