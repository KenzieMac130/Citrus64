import subprocess
import json
from pathlib import Path

def get_project_root():
    return Path(__file__).parent.parent.parent.resolve()

def request_restart():
    print("Please follow the instructions and re-run the command")
    input("Press Enter to Exit...")
    exit(0)

def execute_command(command : list, dir=None):
    return str(subprocess.check_output(command, shell=True, cwd=dir, encoding='utf-8', start_new_session=True))

def command_expect_start(command : list):
    try:
        execute_command(command=command)
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

default_data = {
    "ares_path": "",
    "blender_path": ""
}

def get_dev_env_data():
    try:
        with open(get_project_root() / "devsetup.json") as jsonfile:
            data = json.load(jsonfile)
            return data
    except FileNotFoundError:
        return default_data
    except json.JSONDecodeError:
        return default_data
    
def save_dev_env_data(data):
    with open(get_project_root() / "devsetup.json", "w") as jsonfile:
        json.dump(data, jsonfile)