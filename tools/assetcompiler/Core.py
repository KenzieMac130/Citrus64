from pathlib import Path
from . import Build
from . import Libdragon

def options(ctx):
	ctx.add_option('--build', default='', action='store', help='path to build dir')

def configure(ctx):
	pass

def build(ctx):
	print('Building: ' + ctx.path.abspath())
	Libdragon.libdragon_init(ctx, Path(ctx.path.abspath()).parent.resolve())
	Build.build_step_checkin_all_assets(ctx)
	Build.build_step_compile(ctx)