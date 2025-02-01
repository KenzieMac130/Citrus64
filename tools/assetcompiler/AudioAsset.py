from .TaskBase import TaskBase
from pathlib import Path
from .Libdragon import libdragon_asset_path
from .Libdragon import libdragon_build_path

class AudioAssetTask(TaskBase):
	name = "audio"
	out_extension = ".wav64"

	def poll_file_path(path : Path) -> bool:
		return path.suffix in ['.wav']

	def run(self):
		input_path = libdragon_asset_path(self.inputs[0].relpath())
		output_path = libdragon_build_path(Path(self.outputs[0].relpath()).parent)
		final_args = ['-o', str(output_path), '-v']
		if self.get_arg('mono', True):
			final_args += ['--wav-mono']
		if self.get_arg('opus', False):
			final_args += ['--wav-compress', str(self.get_arg('compress', 3))]
		final_args += [
			'--wav-resample', str(self.get_arg('resample', 8000)),
			'--wav-loop', str(self.get_arg('loop', False)).lower(),
			'--wav-loop-offset', str(self.get_arg('loop offset', 0)),
			str(input_path)
		]
		return self.exec_libdragon_command(['audioconv64'] + final_args)