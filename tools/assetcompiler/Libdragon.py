from pathlib import Path
import subprocess

def libdragon_init(ctx, project_root):
   ctx.env.libdragon_container_id = str(subprocess.check_output(['libdragon', 'start'], stdin=None, stderr=None, shell=True, cwd=project_root, encoding='utf-8')).strip()

def libdragon_asset_path(path : Path) -> Path:
	return Path(Path("assets") / path).as_posix()

def libdragon_build_path(path : Path) -> Path:
   if path:
      return Path(Path("build") / path).as_posix()