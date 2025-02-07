from .TaskBase import TaskBase
from pathlib import Path
from .Libdragon import libdragon_asset_path
from .Libdragon import libdragon_build_path

class YMAssetTask(TaskBase):
	name = "music_sequence_ym"
	out_extension = ".ym64"

	def poll_file_path(path : Path) -> bool:
		return path.suffix in ['.ym']

	def run(self):
		input_path = libdragon_asset_path(self.inputs[0].relpath())
		output_path = libdragon_build_path(Path(self.outputs[0].relpath()).parent)
		final_args = ['-o', str(output_path), '-v']
		final_args += ['--ym-compress', str(self.get_arg('compress', False)).lower()]
		final_args += [str(input_path)]
		return self.exec_libdragon_command(['audioconv64'] + final_args)

class XMAssetTask(TaskBase):
	name = "music_sequence_xm"
	out_extension = ".xm64"

	def poll_file_path(path : Path) -> bool:
		return path.suffix in ['.xm']

	def run(self):
		input_path = libdragon_asset_path(self.inputs[0].relpath())
		output_path = libdragon_build_path(Path(self.outputs[0].relpath()).parent)
		# todo: sound mix sidecar info
		final_args = ['-o', str(output_path), '-v']
		final_args += [str(input_path)]
		return self.exec_libdragon_command(['audioconv64'] + final_args)