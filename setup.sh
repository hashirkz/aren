#!/bin/bash
sudo apt update
sudo apt install libsdl2-dev
sudo apt install libsdl2-image-dev

make aren
sudo cp ./aren /usr/bin/aren