#!/usr/bin/bash
# Download gcc-arm-none-eabi
TOOLCHAIN_DIR="./toolchain"
GCC_VERSION="10.3-2021.10"
ARCH="x86_64"
TOOLCHAIN_NAME="gcc-arm-none-eabi-$GCC_VERSION-$ARCH"
GCC_LINK="https://developer.arm.com/-/media/Files/downloads/gnu-rm/$GCC_VERSION/$TOOLCHAIN_NAME-linux.tar.bz2"
DOWNLOAD_DIR="/tmp"
TMP_PATH="$DOWNLOAD_DIR/$TOOLCHAIN_NAME.tar.bz2"

if [[ "$EUID" != 0 ]]; then
    echo "Execute as root"
    exit
fi

mkdir -p "$TOOLCHAIN_DIR/$TOOLCHAIN_NAME/"
mkdir "$TOOLCHAIN_DIR/gcc-arm-none-eabi"
curl -L "$GCC_LINK" --output "$TMP_PATH"

tar -xvf "$TMP_PATH" -C "$DOWNLOAD_DIR"
cp -r "$DOWNLOAD_DIR/gcc-arm-none-eabi-$GCC_VERSION/"* "$TOOLCHAIN_DIR/$TOOLCHAIN_NAME/"

ln -s "$(pwd)/$TOOLCHAIN_DIR/$TOOLCHAIN_NAME/bin/"* "$TOOLCHAIN_DIR/gcc-arm-none-eabi/"
ln -s "$(pwd)/$TOOLCHAIN_DIR/$TOOLCHAIN_NAME/bin/"* "/usr/bin/"
