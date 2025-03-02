def swap16(buffer: bytearray, offset: int):
    buffer[offset:offset+2] = buffer[offset:offset+2][::-1]


def swap32(buffer: bytearray, offset: int):
    buffer[offset:offset+4] = buffer[offset:offset+4][::-1]

def swap64(buffer: bytearray, offset: int):
    buffer[offset:offset+8] = buffer[offset:offset+8][::-1]
