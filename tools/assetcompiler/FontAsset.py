import fontTools.merge
from .TaskBase import TaskBase
from pathlib import Path
from .Libdragon import libdragon_asset_path
from .Libdragon import libdragon_build_path
import subprocess
import fontTools
import uuid

class FontAssetTask(TaskBase):
	name = "font"
	out_extension = ".font64"

	def poll_file_path(path : Path) -> bool:
		return path.suffix in ['.fcon']
	
	def get_font_arg(self, name, default):
		try:
			return self.font_settings[name]
		except KeyError:
			return default
		
	def make_cmd_arg(self, argname, default = None, true_is_flag=True, true_value="true", false_value="false"):
		value = self.get_font_arg(argname, default)
		if value is None:
			return []
		elif isinstance(value, bool):
			if true_is_flag:
				if value:
					return [f"--{argname}"]
				else:
					return []
			else:
				if value:
					return [f"--{argname}", true_value]
				else:
					return [f"--{argname}", false_value]
		else:
			return [f"--{argname}", str(value)]

	def run(self):
		self.font_settings = self.inputs[0].read_json()

		input_path = libdragon_asset_path(Path(self.inputs[0].relpath()).parent)
		output_path = libdragon_build_path(Path(self.outputs[0].relpath()).parent)

		if self.get_font_arg("font", None):
			input_path = (Path(input_path) / str(self.get_font_arg("font", "ERROR"))).as_posix()
		else:
			raise RuntimeError(f"font not defined in {output_path}")

		final_args = ['-o', str(output_path), '-v']
		final_args += self.make_cmd_arg("ellipsis")
		final_args += self.make_cmd_arg("no-kerning")
		final_args += self.make_cmd_arg("compress")
		final_args += self.make_cmd_arg("debug")
		final_args += self.make_cmd_arg("size")
		final_args += self.make_cmd_arg("monochrome")
		final_args += self.make_cmd_arg("outline")
		final_args += self.make_cmd_arg("char-spacing")
		final_args += self.make_cmd_arg("format")
		for range in self.get_font_arg("ranges", ["20-7F"]):
			final_args += ["--range", str(range)]
		final_args += [str(input_path)]
		print(final_args)
		result = self.exec_libdragon_command(['mkfont'] + final_args)
		return result