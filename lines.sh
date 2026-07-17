#!/bin/bash

cloc \
    common \
    util \
    core \
    ParagonApp \
    ParagonEditorApp \
    config \
    data \
    CMakeLists.txt \
    --exclude-dir=build \
    --exclude-dir=external \
    --exclude-dir=.git \
    --exclude-ext=txt,md,xml
