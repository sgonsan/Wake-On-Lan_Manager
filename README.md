# Wake-on-LAN Manager

Este proyecto es una herramienta sencilla en C++ para gestionar y enviar paquetes de Wake-on-LAN (WOL) a dispositivos de tu red. Permite registrar direcciones MAC de tus dispositivos, guardarlas en una base de datos local y despertarlos cuando lo necesites.

## Funcionalidades

- **Enviar paquete WOL**: Despierta un dispositivo registrado enviando un paquete WOL a su dirección MAC.
- **Añadir dispositivo**: Registra un nuevo dispositivo en la base de datos con un nombre y su dirección MAC.
- **Editar dispositivo**: Modifica el nombre o la dirección MAC de un dispositivo registrado.
- **Eliminar dispositivo**: Elimina un dispositivo registrado de la base de datos.
- **Listar dispositivos**: Muestra todos los dispositivos registrados en la base de datos.

## Instalación

### Dependencias

Este proyecto tiene las siguientes dependencias:

- **wakeonlan**: Utilidad para enviar paquetes WOL en sistemas Linux.
- **[nlohmann/json](https://github.com/nlohmann/json)**: Librería de JSON para C++.

### Compilación

Para compilar el proyecto, utiliza un compilador C++ compatible con C++11 o superior. Puedes compilarlo usando `g++` de la siguiente manera:

```bash
g++ -o wake main.cpp -std=c++11
```

## Uso

El programa `wake` ofrece varios comandos para interactuar con la base de datos y gestionar los dispositivos. Aquí te explicamos cómo usarlos:

### Comandos

- **Añadir un dispositivo**:

  ```bash
  sudo ./wake add
  ```

  A continuación, se te pedirá que ingreses el nombre y la dirección MAC del dispositivo que deseas añadir. Si el nombre ya está en uso o la dirección MAC es inválida, se mostrará un mensaje de error.

- **Editar un dispositivo**:

  ```bash
  sudo ./wake edit
  ```

  A continuación, se te pedirá que ingreses el ID del dispositivo que deseas editar, que se muestra en ese momento. Si el ID no es válido, se mostrará un mensaje de error. Luego, se te pedirá que ingreses el nuevo nombre y la nueva dirección MAC del dispositivo. Si dejas un campo vacío, se mantendrá el valor actual. Si el nombre ya está en uso o la dirección MAC es inválida, se mostrará un mensaje de error.

- **Eliminar un dispositivo**:

  ```bash
  sudo ./wake remove
  ```

  A continuación, se te pedirá que ingreses el ID del dispositivo que deseas eliminar, que se muestra en ese momento. Si el ID no es válido, se mostrará un mensaje de error.

- **Listar los dispositivos registrados**:

  ```bash
  ./wake list
  ```

  Se mostrará una lista de todos los dispositivos registrados en la base de datos, con su ID, nombre y dirección MAC, con un formato similar a este:

  ```
  1. MiPC (00:11:22:33:44:55)
  2. MiLaptop (AA:BB:CC:DD:EE:FF)
  ```

- **Despertar un dispositivo**:

  ```bash
  ./wake <nombre>
  ```

  Donde `<nombre>` es el nombre del dispositivo que deseas despertar, enviado un paquete WOL a su dirección MAC. Si el nombre no coincide con ningún dispositivo registrado, se mostrará un mensaje de error.

### Base de Datos

La base de datos de dispositivos se guarda en un archivo JSON llamado `database.json` en el directorio /etc/wol. Si el archivo no existe, se creará automáticamente la primera vez que se añada un dispositivo. Si deseas modificar manualmente la base de datos, puedes hacerlo editando el archivo `database.json` directamente.

### Permisos de Administrador

Para añadir o eliminar dispositivos, es necesario ejecutar el programa como superusuario. Puedes hacerlo de la siguiente manera:

```bash
sudo ./wake <comando>
```

## Ejemplo de Uso

A continuación, te mostramos un ejemplo de cómo usar el programa `wake` para gestionar dispositivos y enviar paquetes WOL:

1. Despertar el dispositivo "MiPC":

   ```bash
   ./wake MiPC
   ```

   ```
   Waking up device MiPC (00:11:22:33:44:55)...
   Sending magic packet to 255.255.255.255:9 with 00:11:22:33:44:55
   ```

2. Añadir un dispositivo llamado "MiPC" con la dirección MAC "00:11:22:33:44:55":

   ```bash
   sudo ./wake add
   ```

   ```
   Enter the name of the device: MiPC
   Enter the MAC address of the device: 00:11:22:33:44:55
   Device MiPC (00:11:22:33:44:55) has been added with ID 1
   ```

3. Editar el dispositivo "MiPC" para cambiar su nombre a "MiOrdenador":

   ```bash
   sudo ./wake edit
   ```

   ```
   Select the device you want to edit:
   1: MiPC (00:11:22:33:44:55)
   Enter the ID of the device to edit: 1
   Enter the new name for the device [MiPC]: MiOrdenador
   Enter the new MAC address for the device [00:11:22:33:44:55]:
   The device has been updated successfully
   ```

4. Eliminar el dispositivo "MiPC":

   ```bash
   sudo ./wake remove
   ```

   ```
   Select the device you want to remove:
   1: mipc (00:11:22:33:44:55)
   Enter the ID of the device to remove: 1
   Do you want to remove the device MiPC (00:11:22:33:44:55? [y/N] y
   The device has been removed successfully
   ```

5. Listar los dispositivos registrados:

   ```bash
   ./wake list
   ```

   ```
   1. MiPC (00:11:22:33:44:55)
   ```

## Contribuciones

Si deseas contribuir a este proyecto, siéntete libre de hacer un fork del repositorio, realizar tus cambios y enviar un pull request. También puedes abrir issues para reportar bugs o sugerir mejoras.

<!-- ## Licencia

Este proyecto está bajo la Licencia MIT. Consulta el archivo `LICENSE` para más detalles. -->
