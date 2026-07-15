#!/bin/bash

set -e  # Exit on any error
PROJECT_ROOT="$(pwd)"
BOARD="N/A"

if [ $BOARD == "N/A" ]; then
    echo "Make sure to apply the patches in respect to your board FIRST."
    exit 1
fi

# Detect OS
OS="$(uname -s)"
case "$OS" in
    Linux*)     MACHINE=Linux;;
    Darwin*)    MACHINE=Mac;;
    CYGWIN*|MINGW*|MSYS*) MACHINE=Windows;;
    *)          MACHINE="UNKNOWN"
esac

echo "==> Detected OS: $MACHINE"

echo "==> Checking prerequisites..."
command -v python3 >/dev/null 2>&1 || { echo >&2 "python3 not found. Aborting."; exit 1; }
command -v git >/dev/null 2>&1 || { echo >&2 "git not found. Aborting."; exit 1; }

# Check and create virtual environment
if [ -d "fprime-venv" ]; then
  echo "==> Virtual environment already exists. Skipping creation."
else
  echo "==> Creating fprime virtual environment..."
  python3 -m venv fprime-venv
fi

# Activate virtual environment
if [ "$MACHINE" == "Windows" ]; then
  ACTIVATE_PATH="fprime-venv/Scripts/activate"
else
  ACTIVATE_PATH="fprime-venv/bin/activate"
fi

if [ ! -f "$ACTIVATE_PATH" ]; then
  echo "❌ Virtual environment activation script missing at $ACTIVATE_PATH!"
  exit 1
fi

echo "==> Activating virtual environment..."
source "$ACTIVATE_PATH"

echo "==> Installing west version 1.4.0..."
pip install west==1.4.0

echo "==> Current Directory:"
pwd

echo "==> Fetching git submodules..."
git submodule sync --recursive
git submodule update --recursive --init

# Check subdirectory
if [ ! -d "lib/zephyr-workspace" ]; then
  echo "❌ Directory lib/zephyr-workspace does not exist!"
  exit 1
fi

echo "==> Installing Python requirements (this includes fprime-util)..."
pip install -r requirements.txt

cd lib/zephyr-workspace
echo "==> Entered Directory:"
pwd

echo "==> Updating Zephyr workspace..."
# START: CubeSTEP CERBERUS SPECIFIC
west config manifest.project-filter -- "-.*,+hal_stm32,+cmsis,+cmsis_6,+littlefs,+mcuboot"
# END
west update
west zephyr-export
west sdk install

# START
# END



cd "$PROJECT_ROOT" 
echo "==> Returned to Directory:"
pwd

echo "==> Preparing for the build system"
fprime-util purge -f

echo "==> Generating F´ build system..."
fprime-util generate

echo "==> Building F´ project..."
fprime-util build -j4

echo "✅ Setup complete."
