import subprocess
from pathlib import Path

def get_project_root():
    return Path(__file__).parent.parent.parent.resolve()

def request_restart():
    print("Please follow the instructions and re-run the command")
    input("Press Enter to Exit...")
    exit(0)

def execute_command(command : list, dir=None):
    print(str(subprocess.check_output(command, shell=True, cwd=dir, encoding='utf-8', start_new_session=True)))

def command_expect_start(command : list):
    try:
        result = str(subprocess.check_output(command, shell=True, encoding='utf-8', start_new_session=True))
        return True
    except FileNotFoundError:
        return False
    except subprocess.CalledProcessError:
        return False
    
def ask_yn_question(question : str):
    response = str(input(f"{question} (y/n)")).lower()
    return response == 'y' or response == 'yes'

def ask_install(name : str):
    return ask_yn_question(f"Install {name}")