#!/bin/bash
echo "Compiling...."
arduino-cli compile -p /dev/ttyACM1 -b arduino:avr:uno $1
echo "Done!"
echo "Uploading..."
arduino-cli upload -p /dev/ttyACM1 -b arduino:avr:uno $1
echo "Done!"
