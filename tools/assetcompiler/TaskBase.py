import waflib
import time
from pathlib import Path

class TaskBase(waflib.Task.Task):
	# Name of the task
	name = ""
	out_extension = None
	shell = True

	# Check if task is responsible for file path (before checkin)
	def poll_file_path(path : Path) -> bool:
		return False
	
	# Load metadata for this resource
	def setup(self, ctx, ctac_node, metadata):
		# Metadata
		self.metadata = metadata

		# Input
		path = Path(ctac_node.relpath()).with_suffix('')
		inputs = [
			ctx.path.find_resource(str(path)),
			ctac_node
		]
		self.set_inputs(inputs)

		# Sanitize Output
		out_path = str(path).replace(' ', '_')
		out_path = str(out_path).encode("ascii", errors="replace").decode()
		out_path = str(out_path).replace('?', '_')
		out_path = str(Path("data") / out_path)
		if self.out_extension:
			out_path = str(Path(out_path).with_suffix(self.out_extension))

		# Outputs
		outputs = []
		outputs.append(ctx.path.find_or_declare(out_path))
		self.set_outputs(outputs)

	def run(self): # Logic that runs the command
		return 0
	
	def scan(self): # Find all input files
		return (self.inputs, time.time())

	def runnable_status(self): # Gets the runnable status
		return super(TaskBase, self).runnable_status()
	
	def get_arg(self, name, default):
		if name not in self.metadata.args:
			return default
		return self.metadata.args[name]

	def exec_libdragon_command(self, args):
		final_args = ['docker', 'exec', self.env.libdragon_container_id]
		final_args += args
		return self.exec_command(final_args)