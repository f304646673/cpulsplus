#!/bin/bash

# 获取当前目录
CURRENT_DIR=$(pwd)

# 设置构建目录路径
BUILD_DIR="$CURRENT_DIR/build"

# 将构建目录添加到 PYTHONPATH
export PYTHONPATH=$PYTHONPATH:$BUILD_DIR

# 输出当前的 PYTHONPATH
echo "PYTHONPATH is set to: $PYTHONPATH"