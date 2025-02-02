import urllib.request
from .Shared import ask_install
from .Shared import ask_yn_question
from .Shared import get_project_root
from .Shared import get_dev_env_data
from .Shared import save_dev_env_data
import webbrowser
import urllib
import json
import platform
import zipfile

def get_ares_path():
    return get_dev_env_data()["ares_path"]

def set_ares_path(ares_path : str = ""):
    if not ares_path:
        ares_path = input("Please enter the path/variable to your ares executable (or leave blank to discard changes)")
    if ares_path:
        data = get_dev_env_data()
        data["ares_path"] = str(ares_path)
        save_dev_env_data(data)

def install_ares_windows():
    ares_path = get_project_root() / "ares"
    ares_path.mkdir(exist_ok=True)
    if platform.machine() == "AMD64":
        ares_zip = ares_path / "ares-windows.zip"
        urllib.request.urlretrieve("https://github.com/ares-emulator/ares/releases/download/v141/ares-windows.zip", str(ares_zip))
    else:
        ares_zip = ares_path / "ares-windows-msvc-arm64.zip"
        urllib.request.urlretrieve("https://github.com/ares-emulator/ares/releases/download/v141/ares-windows-msvc-arm64.zip", str(ares_zip))
    with zipfile.ZipFile(ares_zip) as zip:
        zip.extractall(ares_path)
    ares_zip.unlink()
    ares_exe = next(ares_path.glob("ares*")) / "ares.exe"
    set_ares_path(str(ares_exe))

def install_ares_manual():
    webbrowser.open("https://ares-emu.net/download")
    print("Please install...")
    set_ares_path()

def install_ares():
    if platform.system() == "Windows":
        install_ares_windows()
    else:
        install_ares_manual()

def main():
    if not get_ares_path():
        if ask_install("ares hardware emulator"):
            install_ares()
    elif ask_yn_question("Change ares executable path"):
        set_ares_path()

if __name__ == "__main__":
    main()