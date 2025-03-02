# By Kenzie Wright - SPDX-License-Identifier: Apache-2.0

from pathlib import Path
import xxhash


def generate_hashes(contents: str) -> str:
    result = ""
    next_found = contents.find("CT_XXH32_STRING(")
    while (next_found >= 0):
        next_found += len("CT_XXH32_STRING(")

        separator = contents.find(",", next_found)
        identifier = contents[next_found:separator]

        str_begin = contents.find('"', separator) + 1
        str_end = contents.find('"', str_begin)
        while contents[str_end - 1] == '\\':
            str_end = contents.find('"', str_end) + 1

        next_found = contents.find("CT_XXH32_STRING(", next_found)
        
        str_contents = bytes(
            contents[str_begin:str_end], encoding="utf-8").decode("unicode-escape")
        value = xxhash.xxh32(str_contents, 0).hexdigest()
        result += f"#define {identifier} 0x{value}\n"
    return result
