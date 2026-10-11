#!/usr/bin/env python3
"""
Конвертер иконок Cerberus
--------------------------
Берёт папку с 16x16 PNG-иконками (Graphics/*.png) и конвертирует каждую
в компактный 1-битный формат .bin для хранения на microSD.

Формат файла:
  байты 0-1 : ширина  (uint16, little-endian)
  байты 2-3 : высота  (uint16, little-endian)
  далее     : пиксели построчно, 1 бит на пиксель, MSB первым,
              каждая строка выровнена на байт.
              бит = 1  -> "включённый" (тёмный) пиксель иконки
              бит = 0  -> фон

Такой формат даёт ровно 32 байта на 16x16 иконку (плюс 4 байта заголовка),
вместо 512+ байт в RGB565 — экономия почти в 16 раз, и его легко
читать на ESP32 без библиотеки декодирования PNG.

Запуск:
    pip install pillow
    python3 convert_icons.py <папка_с_png> <папка_назначения>

Пример:
    python3 convert_icons.py Graphics ../../sd_card_root/Images
"""

import os
import sys
import struct

try:
    from PIL import Image
except ImportError:
    print("Нужна библиотека Pillow: pip install pillow")
    sys.exit(1)

THRESHOLD = 128  # яркость ниже этого значения = "тёмный" пиксель (бит=1)


def convert_one(src_path, dst_path):
    im = Image.open(src_path).convert("L")  # в оттенки серого
    w, h = im.size
    row_bytes = (w + 7) // 8

    data = bytearray()
    for y in range(h):
        byte = 0
        bits_in_byte = 0
        for x in range(w):
            px = im.getpixel((x, y))
            bit = 1 if px < THRESHOLD else 0
            byte = (byte << 1) | bit
            bits_in_byte += 1
            if bits_in_byte == 8:
                data.append(byte)
                byte = 0
                bits_in_byte = 0
        if bits_in_byte:
            byte <<= (8 - bits_in_byte)
            data.append(byte)

    assert len(data) == row_bytes * h, "несовпадение размера строки"

    with open(dst_path, "wb") as f:
        f.write(struct.pack("<HH", w, h))
        f.write(bytes(data))


def main():
    if len(sys.argv) != 3:
        print(__doc__)
        sys.exit(1)

    src_dir, dst_dir = sys.argv[1], sys.argv[2]
    os.makedirs(dst_dir, exist_ok=True)

    count = 0
    for fname in sorted(os.listdir(src_dir)):
        if not fname.lower().endswith(".png"):
            continue
        # имя файла на SD-карте: нижний регистр, пробелы -> подчёркивание
        out_name = os.path.splitext(fname)[0].strip().lower().replace(" ", "_") + ".bin"
        convert_one(os.path.join(src_dir, fname), os.path.join(dst_dir, out_name))
        count += 1

    print(f"Готово: {count} иконок сконвертировано в {dst_dir}")


if __name__ == "__main__":
    main()
