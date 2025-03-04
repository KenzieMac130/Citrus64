from .Shared import ask_install
from .Shared import command_expect_start
from .Shared import execute_command
from pathlib import Path

def main():
    if True or not command_expect_start(['libdragon', 'version']):
        if ask_install("libdragon docker"):
            print(execute_command(['npm', 'install', '-g', 'libdragon']))
            print(execute_command(['libdragon', 'install'], dir="./libs/libdragon"))
    if True or not Path('./libs/tiny3d/build/t3d.o').exists():
        if ask_install("t3d"):
            print(execute_command(['libdragon', 'exec', './build.sh'], dir="./libs/tiny3d"))
            #print(execute_command(['libdragon', 'make'], dir="./libs/tiny3d/tools/gltf_importer"))

if __name__ == "__main__":
    main()