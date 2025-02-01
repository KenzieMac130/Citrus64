from .Shared import get_project_root
from .Shared import execute_command
import sys

def main():
    asset_dir = get_project_root() / "assets"
    build_dir = get_project_root() / "build"
    build_dir.mkdir(exist_ok=True)
    data_dir = build_dir / "data"
    data_dir.mkdir(exist_ok=True)
    execute_command([sys.executable, 'waf', 'configure', '-o', str(build_dir.resolve())], dir=asset_dir)
    pass

if __name__ == "__main__":
    main()