#!/usr/bin/env bash
set -ex

mpy-cross caravel_spi.py
mpy-cross modules/board.py
mpy-cross modules/myspi.py
cp ../output_files/bitstream.bin .

sync
mpremote mount . exec "import caravel_spi; caravel_spi.run()"
rm bitstream.bin
