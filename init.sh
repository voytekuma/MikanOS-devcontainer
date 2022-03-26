#!/bin/bash

MIKAN="/workspaces/MikanOS-devcontainer/mikanos"
export MIKAN

workspace=/workspaces/MikanOS-devcontainer/mikanos
edk2=/home/vscode/edk2
current=$(pwd)

ln -sf ${workspace}/MikanLoaderPkg ${edk2}

# configure edk2
cd ${edk2}
source edksetup.sh
cd ${current}

# configure clang (kernel build)
source /home/vscode/osbook/devenv/buildenv.sh

unset -v edk2 current