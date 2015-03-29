#!/bin/bash

convert -size 64x64 xc:white +antialias -depth 8 -type Grayscale mask_full.png
convert -size 64x64 xc:black +antialias -depth 8 -type Grayscale -fill white -stroke white -draw "rectangle 16,16 47,47" groundtruth.png
convert -size 64x64 xc:black +antialias -depth 8 -type Grayscale -fill white -stroke white -draw "rectangle 16,16 39,39" result.png
convert -size 64x64 xc:black +antialias -depth 8 -type Grayscale -fill white -stroke white -draw "rectangle 0,0 31,31" mask_partial.png
