from . import RawAsset
from . import SpriteAsset
from . import AudioAsset
from . import MusicSequenceAsset

task_types = [
    RawAsset.RawAssetTask,
    SpriteAsset.SpriteAssetTask,
    AudioAsset.AudioAssetTask,
    MusicSequenceAsset.YMAssetTask,
    MusicSequenceAsset.XMAssetTask
]