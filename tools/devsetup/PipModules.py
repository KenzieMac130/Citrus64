from .Shared import ask_install
from .Shared import execute_command

import subprocess
import sys

def ensure_pip_module(name : str):
    execute_command([sys.executable, "-m", "pip", "install", name])

def main():
    if ask_install("python dependencies"):
        ensure_pip_module("polib")
        ensure_pip_module("send2trash")

if __name__ == "__main__":
    main()