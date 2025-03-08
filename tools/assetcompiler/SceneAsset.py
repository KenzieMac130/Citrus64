from .TaskBase import TaskBase
from . import Codegen
from pathlib import Path


def generate_code(input_path : Path, input: dict) -> str:
    text = Codegen.add_boilerplate()
    text += Codegen.add_resource_boilerplate()
    text += 'extern void ctRendererSetBackgroundModel(ctResourceHandle model);\n'

    text += "ctResourceHandle gBackgroundModel;\n"

    text += 'void OnLibraryLoad(void) {\n'
    backgroundPath = Codegen.asset_path_to_resource_path(input_path, input["backgroundModel"])
    text += f'ctResourceGetOrLoad(&gBackgroundModel, CT_RESOURCE_MODEL, "{backgroundPath}");\n'
    text += '}\n'

    text += 'void OnSceneSetup(void) {\n'
    text += 'ctRendererSetBackgroundModel(gBackgroundModel);\n'
    text += '}\n'

    text += 'void OnLibraryUnload(void) {\n'
    text += 'ctResourceRelease(gBackgroundModel);\n'
    text += '}\n'
    return text


class SceneAssetTask(TaskBase):
    name = "scene"
    out_extension = ".c"
    use_codegen = True

    def poll_file_path(path: Path) -> bool:
        return path.suffix in ['.ctscn']

    def run(self):
        self.outputs[0].write(generate_code(self.inputs[0].relpath(), self.inputs[0].read_json()))
