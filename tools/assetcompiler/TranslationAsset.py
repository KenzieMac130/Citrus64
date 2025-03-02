from .TaskBase import TaskBase
from pathlib import Path
import polib
import struct
from .EndianSwapper import *


class TranslationAssetTask(TaskBase):
    name = "translation"
    out_extension = ".mo"

    def poll_file_path(path: Path) -> bool:
        return path.suffix in ['.po']

    def endianswap(self, data):
        strCount = struct.unpack("I", data[8:12])[0]
        origOffset = struct.unpack("I", data[12:16])[0]
        transOffset = struct.unpack("I", data[16:20])[0]

        swap32(data, 0)
        swap32(data, 4)
        swap32(data, 8)
        swap32(data, 12)
        swap32(data, 16)
        swap32(data, 20)
        swap32(data, 24)

        # hash table is ignored
        for i in range(origOffset, origOffset + (strCount * 8), 8):
            swap32(data, i)
            swap32(data, i + 4)
#
        for i in range(transOffset, transOffset + (strCount * 8), 8):
            swap32(data, i)
            swap32(data, i + 4)
#
        return data

    def run(self):
        po_file = polib.pofile(self.inputs[0].read())
        po_file.save_as_mofile(self.outputs[0].abspath())
        self.outputs[0].write(self.endianswap(
            bytearray(self.outputs[0].read("rb"))), "wb")
