from . import RawAsset
from . import SpriteAsset
from . import AudioAsset
from . import MusicSequenceAsset
from . import ModelAsset
from . import FontAsset
from . import TranslationAsset
from . import SceneAsset

task_types = [
    RawAsset.RawAssetTask,
    SpriteAsset.SpriteAssetTask,
    AudioAsset.AudioAssetTask,
    MusicSequenceAsset.YMAssetTask,
    MusicSequenceAsset.XMAssetTask,
    ModelAsset.ModelAssetTask,
    FontAsset.FontAssetTask,
    TranslationAsset.TranslationAssetTask,
    SceneAsset.SceneAssetTask
]