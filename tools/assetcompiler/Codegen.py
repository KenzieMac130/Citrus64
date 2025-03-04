# todo: add dependency on Config.h

def asset_path_to_resource_path(path: str) -> str:
    return path


def add_boilerplate() -> str:
    text = '#define CT_IS_SCRIPT 1'
    text += '#include "engine/utilities/Utilities.h"\n'
    return text


def add_resource_boilerplate() -> str:
    return '#include "engine/resource/Resource.h"\n'
