#!/bin/bash
set -e

KS="$(cat sources.txt)"
EXTS="c asm"

if [ "$1x" == "--ksx" ]; then
	echo $KS
	exit
fi

for x in $KS; do
	for ext in $EXTS; do
		if [ -f $x.$ext ]; then echo $x.$ext; break; fi
	done
done
