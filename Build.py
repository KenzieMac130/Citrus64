import argparse
import subprocess
from pathlib import Path
from send2trash import send2trash
import sys

import tools.devsetup
from tools.codegen import Codegen

def generate_build_config(args):
    Path("build/codegen").mkdir(exist_ok=True)

    # Setup Build Configuration
    text = "#pragma once\n"

    for define in args.define:
        define += f"#define {define} 1\n"

    if args.test:
        text += "#define CT_BUILD_UNIT_TESTS 1\n"
    else:
        text += "#define CT_BUILD_UNIT_TESTS 0\n"

    if args.wait:
        text += "#define CT_BUILD_WAIT_FOR_INPUT 1\n"
    else:
        text += "#define CT_BUILD_WAIT_FOR_INPUT 0\n"
    
    # Write Build Config
    try:
        with open(Path("build/codegen/BuildConfig.h"), "r") as f:
            old_text = f.read()
    except FileNotFoundError:
        old_text = ""
    if old_text != text:
        with open(Path("build/codegen/BuildConfig.h"), "w") as f:
            f.write(text)
    
    # Setup Game Start
    text = "#pragma once\n"

    # Write Game Start
    try:
        with open(Path("build/codegen/GameStart.h"), "r") as f:
            old_text = f.read()
    except FileNotFoundError:
        old_text = ""
    if old_text != text:
        with open(Path("build/codegen/GameStart.h"), "w") as f:
            f.write(text)


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

def build(args):
    Codegen.generate_code_recursive(Path("engine").resolve(), Path("build/codegen/engine").resolve())
    Codegen.generate_code_recursive(Path("game").resolve(), Path("build/codegen/game").resolve())
    generate_build_config(args)
    subprocess.run([sys.executable, 'waf'], cwd=Path("assets").resolve(), shell=True)
    build_args = []
    if args.config == "debug":
        build_args.append("D=1")
    subprocess.run(['libdragon', 'make'] + build_args, shell=True)

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--setup', help="setup dev environment", action='store_true')
    parser.add_argument('--clean', help="delete the build directory", action='store_true')
    parser.add_argument('-b', '--build', help="build the project", action='store_true')
    dhelp = parser.add_argument_group("build options", "Pass these to --build/-b to help with debugging")
    dhelp.add_argument('-c', '--config', help="(debug/release)", default="debug", type=str)
    dhelp.add_argument('-t', '--test', help="run unit tests", action='store_true')
    dhelp.add_argument('-w', '--wait', help="wait for user input", action='store_true')
    dhelp.add_argument('-d', '--define', default="", nargs="*", help="list of C defines", type=str)
    dhelp.add_argument('-a', '--asset', default="", help="name of asset to preview", type=str)
    dhelp.add_argument('-l', '--level', default="", help="starter level name", type=str)
    dhelp.add_argument('--checkpoint', default=None, help="starter checkpoint name", type=int)
    dhelp.add_argument('--position', nargs=3, default=None, help="starter position (meters XYZ)", type=float)
    dhelp.add_argument('--rotation', nargs=3, default=None, help="starter rotation (degrees euler XYZ)", type=float)
    dhelp.add_argument('--gfx', default=None, help="(0:ultra performance, 1:performance, 2:quality, 3:ultra quality)", type=int)
    dhelp.add_argument('--spkr', default=None, help="(0:mono, 1:stereo, 2:heaphones, 3:surround)", type=int)
    dhelp.add_argument('--mute', help="mute game", action='store_true')
    args = parser.parse_args()
    if args.clean:
        clean()
    if args.setup:
        setup()
    if args.build:
        build(args)

if __name__ == "__main__":
    main()