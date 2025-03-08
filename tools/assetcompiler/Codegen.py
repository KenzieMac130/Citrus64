from pathlib import Path
# todo: add dependency on Config.h

project_root = ""

def asset_path_to_resource_path(input_path : str, path: str) -> str:
    input_path = Path(input_path)
    if path.startswith("./"):
        result = (input_path.parent / path.removeprefix("./"))
        result = result.resolve().relative_to(project_root)
    else:
        result = path
    result = str(Path(result).with_suffix("").as_posix())
    return result


def add_boilerplate() -> str:
    text = '#define CT_IS_SCRIPT 1\n'
    text += '#include "engine/utilities/Utilities.h"\n'
    return text


def add_resource_boilerplate() -> str:
    return '#include "engine/resource/Resource.h"\n'
