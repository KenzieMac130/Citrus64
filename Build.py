import argparse

from .libs import ares
from .libs import libdragon

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('-s', 'setup', help="setup dev environment")
    parser.add_argument('-c', 'clean', help="delete the build directory")
    parser.add_argument('-b', 'build', help="build the project")

def setup():
    libdragon.setup()

if __name__ == "__main__":
    main()