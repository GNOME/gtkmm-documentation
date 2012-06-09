#!/bin/sh

# gtkmm-documentation/tools/make_screenshots/make_screenshots.sh

SCREENSHOT_DIR=newfigures
if [ ! -d $SCREENSHOT_DIR ]
then
  mkdir -p $SCREENSHOT_DIR
fi
./make_screenshots.pl --program-prefix=../../examples/ --figure-prefix=$SCREENSHOT_DIR/ progs-and-figs.txt

