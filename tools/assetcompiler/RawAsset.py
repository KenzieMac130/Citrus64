from .TaskBase import TaskBase
from pathlib import Path
import shutil

class RawAssetTask(TaskBase):
	name = "raw"

	def poll_file_path(path : Path) -> bool:
		return path.suffix in ['.txt', '.bin', '.sprite', '.wav64', '.xm64', '.ym64', '.m1v', '.t3dm', '.t3ds']
		
	def run(self):
		shutil.copyfile(self.inputs[0].abspath(), self.outputs[0].abspath())