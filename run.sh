#!/usr/bin/env bash

command -v gcc >/dev/null 2>&1 || { echo >&2 "Require \`gcc\` but it's not installed. Aborting."; exit 1; }

trg=$1

if [ ! $trg ]; then
  echo "Please specify directory to run."
  exit 1;
fi

if [ ! -d $trg ]; then
  # Control will enter here if $DIRECTORY doesn't exist.
  echo "Directory \`$trg\` dosen't exist. Aborting."
  exit 1;
fi


src=$1"/main.c"

if [ ! -f $src ]; then
  # Control will enter here if $DIRECTORY doesn't exist.
  echo "File \`$src\` dosen't exist. Aborting."
  exit 1;
fi


bin=$1"/main.out"

if [ -f $bin ] && [ $(date +%s -r $src) -lt $(date +%s -r $bin) ]; then
  echo -e "Run exist one.\n"
else
  printf "build..."
  gcc -w -o $trg/main.out $src -pthread 2>&1 || { echo >&2 "Failed to compile $src. Aborting"; exit 1; }
  echo -e "done\n"
fi


./$trg/main.out
