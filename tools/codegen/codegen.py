# By Kenzie Wright - SPDX-License-Identifier: Apache-2.0

from pathlib import Path
import os.path

from . import Hasher


def get_dst_path(src_path: Path, input_path: Path, output_path: Path):
    return output_path / f"{src_path.relative_to(input_path)}.gen.h"


def needs_generate(src_path: Path, dst_path: Path):
    if not dst_path.exists():
        return True
    src_time = os.path.getmtime(src_path)
    dst_time = os.path.getmtime(dst_path)
    if src_time > dst_time:
        return True
    return False


def check_for_gen_include(text: str, src_path: Path, dst_path: Path):
    root = dst_path.parent
    # Note: we could technically end up with a false warn where the user creates a build folder
    while root.stem != "build":
        root = root.parent
    dst_path = dst_path.relative_to(root).as_posix()
    includer = f'#include "{str(dst_path)}"'
    idx = text.find(includer)
    if idx == -1:
        print(f"Warning! ({includer}) not found in {str(src_path)}")
    else:
        if text.find("#include", idx + len(includer)) != -1:
            print(f"Warning! ({includer}) was not the last include in {str(src_path)}")


def generate_file(src_path: Path, dst_path: Path):
    out_text = "#pragma once\n"
    in_text = src_path.read_text(encoding='utf-8')
    check_for_gen_include(in_text, src_path, dst_path)
    if "Hash.h" not in str(src_path):  # avoid including macro definition
        out_text += Hasher.generate_hashes(in_text)
    dst_path.write_text(out_text)


def generate_code_recursive(input_path: Path, output_path: Path):
    src_files = [p.resolve() for p in input_path.glob("**/*")
                 if p.suffix in {".c", ".h"}]
    for src_path in src_files:
        dst_path = get_dst_path(src_path, input_path, output_path)
        if needs_generate(src_path, dst_path):
            dst_path.parent.mkdir(parents=True, exist_ok=True)
            generate_file(src_path, dst_path)
