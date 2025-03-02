# By Kenzie Wright - SPDX-License-Identifier: Apache-2.0

from pathlib import Path
import xxhash


def generate_translation(contents: str) -> str:
    result = ""
    has_translation = False
    tset = set()
    next_found = contents.find("CT_TEXT(")
    while (next_found >= 0):
        if not has_translation:
            result += "#include \"engine/core/Translation.h\"\n"
            has_translation = True

        next_found += len("CT_TEXT(")

        separator = contents.find(")", next_found)
        identifier = contents[next_found:separator]

        next_found = contents.find("CT_TEXT(", next_found)

        if identifier in tset:
            continue
        tset.add(identifier)

        str_contents = bytes(identifier, encoding="utf-8").decode("unicode-escape")
        value = xxhash.xxh32(str_contents, 0).hexdigest()
        result += f"#ifndef __CT_MSGID_GET_TEXT_{identifier}\n#define __CT_MSGID_GET_TEXT_{identifier} ctGetTextHashed(0x{value})\n#endif\n"
    return result
