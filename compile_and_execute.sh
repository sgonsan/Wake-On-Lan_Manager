#!/bin/bash

# This script compiles the program and copies the executable to /usr/bin

clear
# Load variables from config
source "./config"

echo -e "${COLOR_YELLOW}Cleaning and compiling...${COLOR_RESET}"

make clean
make

if [ $? -ne 0 ]; then
  echo -e "${COLOR_RED}Compile error.${COLOR_RESET}"
else
  echo -e "${COLOR_GREEN}Successful build.${COLOR_RESET}"
  sudo cp ./build/${PROGRAM_NAME} /usr/bin/${PROGRAM_NAME}
  echo -e "${COLOR_YELLOW}Executable copied to /usr/bin/${PROGRAM_NAME}${COLOR_RESET}"
fi
