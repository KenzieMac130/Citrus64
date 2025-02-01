from . import AresSetup
from . import LibdragonSetup
from . import PipModules
from . import PrereqCheck
from . import WafConfigure

def package_setup():
    PrereqCheck.main()
    PipModules.main()
    LibdragonSetup.main()
    AresSetup.main()