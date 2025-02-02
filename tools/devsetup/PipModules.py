from .Shared import ask_install
from .Shared import execute_command

import subprocess
import sys

def ensure_pip_module(name : str):
    print(execute_command([sys.executable, "-m", "pip", "install", name]))

def has_pip_module(module):
    list_out = execute_command([sys.executable, "-m", "pip", "list"]).splitlines()
    for line in list_out:
        if line.startswith(module):
            return True
    return False

def has_pip_modules(modules):
    for module in modules:
        if not has_pip_module(module):
            return False
    return True

def main():
    modules = ["polib", "Send2Trash"]
    if not has_pip_modules(modules):
        if ask_install("python dependencies"):
            for module in modules:
                ensure_pip_module(module)

if __name__ == "__main__":
    main()