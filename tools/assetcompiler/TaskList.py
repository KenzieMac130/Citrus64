from . import RawAsset
from . import SpriteAsset
from . import AudioAsset
from . import MusicSequenceAsset
from . import ModelAsset
from . import FontAsset

task_types = [
    RawAsset.RawAssetTask,
    SpriteAsset.SpriteAssetTask,
    AudioAsset.AudioAssetTask,
    MusicSequenceAsset.YMAssetTask,
    MusicSequenceAsset.XMAssetTask,
    ModelAsset.ModelAssetTask,
    FontAsset.FontAssetTask
]