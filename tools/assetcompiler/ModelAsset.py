from .TaskBase import TaskBase
from pathlib import Path
from .Libdragon import libdragon_asset_path
from .Libdragon import libdragon_build_path
	

class ModelAssetTask(TaskBase):
	name = "model"
	out_extension = ".t3dm"

	def poll_file_path(path : Path) -> bool:
		return path.suffix in ['.gltf']

	@staticmethod
	# build/data makes its way into the output file for whatever reason... just patching it out here
	def patchup_sdata_paths(t3dm_path : Path):
		t3dm_path = Path('../') / t3dm_path
		with open(t3dm_path.resolve(), 'rb') as file:
			data = bytearray(file.read())
		while True:
			needle = b"build/data/"
			first = data.find(needle)
			if first < 0:
				break
			last = data.find(b'\0', first)
			if last < 0:
				break
			final_path = data[first + len(needle) : last]
			for i in range(first, last):
				try:
					data[i] = final_path[i - first]
				except IndexError:
					data[i] = 0
		with open(t3dm_path.resolve(), 'wb') as file:
			file.write(data)

	def run(self):
		input_path = libdragon_asset_path(self.inputs[0].relpath())
		output_path = libdragon_build_path(Path(self.outputs[0].relpath()))
		final_args = [str(input_path), str(output_path)]
		if self.get_arg('collision_mesh', False) or self.get_arg('bvh', False):
			final_args += ['--bvh']
		if self.get_arg('ignore_materials', False):
			final_args += ['--ignore-materials']
		final_args += [
			f"--base-scale={self.get_arg('base_scale', 64)}",
			"--asset-path=build/data"
			'--verbose'
		]
		result = self.exec_libdragon_command(['gltf_to_t3d'] + final_args)
		ModelAssetTask.patchup_sdata_paths(Path(output_path))
		return result