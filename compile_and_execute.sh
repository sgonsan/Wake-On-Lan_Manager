#!/bin/bash

clear
# Load variables from config
source "./config"

# echo -e "${COLOR_YELLOW}Generating documentation...${COLOR_RESET}"

# doxygen ../Doxyfile
# sleep 0.5 # Pause for 1 second to simulate an animation

# echo -e "${COLOR_GREEN}Documentation generated.${COLOR_RESET}"

echo -e "${COLOR_YELLOW}Cleaning and compiling...${COLOR_RESET}"

make clean
make

if [ $? -ne 0 ]; then
  echo -e "${COLOR_RED}Compile error.${COLOR_RESET}"
else
  echo -e "${COLOR_GREEN}Successful build.${COLOR_RESET}"
  sudo cp build/$PROGRAM_NAME /bin/$PROGRAM_NAME
  echo -e "${COLOR_YELLOW}Executable copied to /bin/$PROGRAM_NAME.${COLOR_RESET}"
fi
