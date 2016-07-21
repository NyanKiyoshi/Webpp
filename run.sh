#!/usr/bin/env bash

TARGET="main_webpp"
DEST_PATH="/tmp/cmake/generated/${TARGET}/Debug"
DEST_PATH="/home/sayuri/.CLion2016.2/system/cmake/generated/Webpp-8eaf02d3/8eaf02d3/Debug/"
mkdir -p ${DEST_PATH}


cmake \
    --build ${DEST_PATH} \
    --target ${TARGET} \
    -- \
    -j 8 \
&& \
spawn-fcgi -p 8000 \
    -n ${DEST_PATH}${TARGET}
