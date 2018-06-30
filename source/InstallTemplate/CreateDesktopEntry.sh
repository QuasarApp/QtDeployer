#!/bin/bash

IS_INSTALL=$1
TARGET_DIR= $2 
APP_NAME=$3
VERSION=$4
ICONS_DIR="~/.local/share/applications"
DESKTOP_FILE="$ICONS_DIR/$APP_NAME.desktop"
EXE="$TARGET_DIR/$APP_NAME.sh"
ICON="$TARGET_DIR/$5"

if [ "$IS_INSTALL" == "install" ]; then

    echo "Version=$VERSION\n">>$DESKTOP_FILE
    echo "Type=Application\n">>$DESKTOP_FILE
    echo "Terminal=false\n">>$DESKTOP_FILE
    echo "Exec=$EXE\n">>$DESKTOP_FILE
    echo "Name=$APP_NAME\n">>$DESKTOP_FILE
    echo "Icon=$ICON\n">>$DESKTOP_FILE
    echo "Name[en_US]=$APP_NAME\n">>$DESKTOP_FILE

else

    rm -drf $DESKTOP_FILE

fi

echo "All done!"


