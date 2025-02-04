import argparse
import subprocess
from pathlib import Path
from send2trash import send2trash
import sys

import tools.devsetup

def setup():
    tools.devsetup.package_setup()

def send2trash_lazy(path):
    try:
        send2trash(path)
    except FileNotFoundError:
        pass

def clean():
    send2trash_lazy(Path("build").resolve())
    send2trash_lazy(Path("game.z64").resolve())

def build():
    subprocess.run([sys.executable, 'waf'], cwd=Path("assets").resolve(), shell=True)
    subprocess.run(['libdragon', 'make'], shell=True)

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--setup', help="setup dev environment", action='store_true')
    parser.add_argument('--clean', help="delete the build directory", action='store_true')
    parser.add_argument('-b', '--build', help="build the project", action='store_true')
    dhelp = parser.add_argument_group("build options", "Pass these to --build/-b to help with debugging")
    dhelp.add_argument('-a', '--asset', default="", help="name of asset to preview", type=str)
    dhelp.add_argument('-l', '--level', default="", help="starter level name", type=str)
    dhelp.add_argument('-c', '--checkpoint', default="", help="starter checkpoint name", type=str)
    dhelp.add_argument('-d', '--define', default="", nargs="*", help="list of C defines", type=str)
    args = parser.parse_args()
    if args.clean:
        clean()
    if args.setup:
        setup()
    if args.build:
        build()

if __name__ == "__main__":
    main()