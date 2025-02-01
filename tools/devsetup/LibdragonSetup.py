from .Shared import ask_install
from .Shared import command_expect_start
from .Shared import execute_command

def main():
    if not command_expect_start(['libdragon', 'version']):
        if ask_install("libdragon docker"):
            execute_command(['npm', 'install', '-g', 'libdragon'])

if __name__ == "__main__":
    main()