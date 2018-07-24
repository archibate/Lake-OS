#!/bin/bash
set -e

rm -rf obj bin
mkdir -p /tmp/obj /tmp/bin
ln -p /tmp/obj /tmp/bin ./
