from .Shared import ask_install
from .Shared import command_expect_start
from .Shared import execute_command
from .Shared import ask_yn_question
from .Shared import request_restart

import sys
import subprocess
import os
import webbrowser
import platform

def check_pip():
    if not command_expect_start([sys.executable, "-m", "pip", "--version"]):
        if ask_install("python pip"):
            execute_command([sys.executable, "-m", "ensurepip"])

def check_npm():
    if not command_expect_start(["npm", "version"]):
        if ask_install("npm and fnm"):
            if not command_expect_start(["fnm", "-V",], "fnm"):
                if os.name == 'nt': # Windows
                    execute_command(["winget", "install", "Schniz.fnm"])
                else: # Linux / Mac
                    execute_command(["curl", "-o-", "https://fnm.vercel.app/install", "|", "bash"])

def open_docker_help():
    if platform.system() == "Windows":
        if not ask_yn_question("Do you know if you have CPU virtualization enabled on your PC?"):
            webbrowser.open('https://support.microsoft.com/en-us/windows/enable-virtualization-on-windows-c5578302-6e43-4b4b-a449-8ced115f58e1')
        webbrowser.open("https://docs.docker.com/desktop/setup/install/windows-install/#install-docker-desktop-on-windows")
    elif platform.system() == "Darwin":
        webbrowser.open("https://docs.docker.com/desktop/setup/install/mac-install/")
    else:
        webbrowser.open("https://docs.docker.com/engine/install/")

def check_docker():
     if not command_expect_start(["docker", "-v"]):
        if ask_install("docker"):
            open_docker_help()
        request_restart()

def main():
    check_pip()
    check_npm()
    check_docker()

if __name__ == "__main__":
    main()