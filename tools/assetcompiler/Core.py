from . import Build

def options(ctx):
	ctx.add_option('--build', default='', action='store', help='path to build dir')

def configure(ctx):
	pass

def build(ctx):
	print('Building: ' + ctx.path.abspath())
	ctx.add_pre_fun(Build.build_step_checkin_all_assets)
	Build.build_step_compile(ctx)