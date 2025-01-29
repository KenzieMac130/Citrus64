import io
import json
import uuid
from pathlib import Path

class AssetMetaData:
    args = {}
    type = "unknown"
    raw_json = {}

    def __init__(self, fp = None, dict = None) -> None:
        if fp:
            data = json.load(fp)
            self.read(data)
        if dict:
            self.read(dict)
        
    def read(self, data):
        self.raw_json = data
        if "args" in data:
            self.args = data["args"]
        if "type" in data:
            self.type = data["type"]

    def dump(self, fp):
        fp.write(self.dumps())

    def dumps(self) -> str:
        dump = self.raw_json
        dump["args"] = self.args
        for key, value in self.guids.items():
            dump[key] = value.hex
        dump["type"] = self.type
        return json.dumps(dump, indent=2)