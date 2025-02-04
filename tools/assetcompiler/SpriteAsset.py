from .TaskBase import TaskBase
from pathlib import Path
from .Libdragon import libdragon_asset_path
from .Libdragon import libdragon_build_path

class SpriteAssetTask(TaskBase):
	name = "sprite"
	out_extension = ".sprite"

	def poll_file_path(path : Path) -> bool:
		return path.suffix in ['.png'] and 'bmfont_pages' not in str(path)

	def run(self):
		input_path = libdragon_asset_path(self.inputs[0].relpath())
		output_path = libdragon_build_path(Path(self.outputs[0].relpath()).parent)
		final_args = ['-o', str(output_path), '-v']
		final_args += [
			'--format', str(self.get_arg('format', 'AUTO')),
			'--dither', str(self.get_arg('dither', 'NONE')),
			'--compress', str(self.get_arg('compress', 1)),
			str(input_path)
		]
		return self.exec_libdragon_command(['mksprite'] + final_args)