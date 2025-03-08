import argparse
import json
from pathlib import Path
import subprocess
import os

def launch_ares(settings):
    rom_path = Path(os.getcwd()) / "game.z64"
    ares_path = Path(settings["ares_path"])
    subprocess.run([str(ares_path), str(rom_path), "--terminal"], cwd=ares_path.parent)

def main():
    with open("devsetup.json") as f:
        settings = json.load(f)
    parser = argparse.ArgumentParser()
    parser.add_argument('-m', '--method', default="ares", help="ares or n64", action='store_true')
    args = parser.parse_args()
    if args.method == "ares":
        launch_ares(settings)

if __name__ == "__main__":
    main()