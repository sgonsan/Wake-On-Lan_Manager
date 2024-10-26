# Wake-on-LAN Manager

This project is a simple C++ tool to manage and send Wake-on-LAN (WOL) packets to devices on your network. It allows you to register MAC addresses of your devices, store them in a local database, and wake them up when needed.

## Features

-**Send WOL packet**: Wake up a registered device by sending a WOL packet to its MAC address.

- **Add device**: Register a new device in the database with a name and its MAC address.

- **Edit device**: Modify the name or MAC address of a registered device.

- **Remove device**: Delete a registered device from the database.

- **List devices**: Show all registered devices in the database.

## Installation

### Dependencies

This project requires the following dependencies:

- **wakeonlan**: A command-line tool to send WOL packets. You can install it using the following command:

  ```bash
  sudo apt install wakeonlan
  ```

- **[nlohmann/json](https://github.com/nlohmann/json)**: A JSON library for C++. You can download the single header file from the [releases page](https://github.com/nlohmann/json/releases) and place it in the project directory.

### Compilation

To compile the project, you can use the following command:

```bash
g++ -o wake main.cpp -std=c++11
```

## Usage

The `wake` program provides a simple command-line interface to manage devices and send WOL packets. You can use the following commands:

### Commands

- **Send WOL packet**: Wake up a device by its name.

  ```bash
  ./wake <device>
  ```

- **Add device**: Register a new device in the database.

  ```bash
  sudo ./wake add
  ```

- **Edit device**: Modify the name or MAC address of a registered device.

  ```bash
  sudo ./wake edit
  ```

- **Remove device**: Delete a registered device from the database.

  ```bash
  sudo ./wake remove
  ```

- **List devices**: Show all registered devices in the database.

  ```bash
  ./wake list
  ```

### Database

The device database is stored in a JSON file called `database.json` in the /etc/wol directory. If the file does not exist, it will be created automatically the first time a device is added. If you want to manually modify the database, you can do so by editing the `database.json` file directly.

### Superuser

To run the `wake` program with superuser privileges, you need to use `sudo` for the `add`, `edit`, and `remove` commands:

```bash
sudo ./wake <command>
```

## Examples

Here are some examples of how to use the `wake` program:

1. Wake up a device called "MyPC":

   ```bash
   ./wake MyPC
   ```

   ```output
   Waking up device MyPC (00:11:22:33:44:55)...
   Sending magic packet to 255.255.255.255:9 with 00:11:22:33:44:55
   ```

2. Add a new device called "MyPC" with MAC address "00:11:22:33:44:55":

   ```bash
   sudo ./wake add
   ```

   ```output
   Enter the name of the device: MyPC
   Enter the MAC address of the device: 00:11:22:33:44:55
   Device MyPC (00:11:22:33:44:55) has been added with ID 1
   ```

3. Edit the device "MyPC" to change its name to "MyComputer":

   ```bash
   sudo ./wake edit
   ```

   ```output
   Select the device you want to edit:
   1: MyPC (00:11:22:33:44:55)
   Enter the ID of the device to edit: 1
   Enter the new name for the device [MyPC]: MyComputer
   Enter the new MAC address for the device [00:11:22:33:44:55]:
   The device has been updated successfully
   ```

4. Remove the device "MyPC":

   ```bash
   sudo ./wake remove
   ```

   ```output
   Select the device you want to remove:
   1: MyPC (00:11:22:33:44:55)
   Enter the ID of the device to remove: 1
   Do you want to remove the device MyPC (00:11:22:33:44:55)? [y/N] y
   The device has been removed successfully
   ```

5. List all registered devices:

   ```bash
   ./wake list
   ```

   ```output
   1. MyPC (00:11:22:33:44:55)
   ```

## Contributing

If you have any suggestions, improvements, or bug fixes, feel free to open an issue or create a pull request.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
