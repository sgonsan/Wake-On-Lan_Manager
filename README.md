# Wake-on-LAN (WOL) Manager

Este proyecto es una herramienta sencilla en C++ para gestionar y enviar paquetes de Wake-on-LAN (WOL) a dispositivos de tu red. Permite registrar direcciones MAC de tus dispositivos, guardarlas en una base de datos local y despertarlos cuando lo necesites.

## Funcionalidades

- **Añadir dispositivo**: Registra un nuevo dispositivo en la base de datos con un nombre y su dirección MAC.
- **Eliminar dispositivo**: Elimina un dispositivo registrado de la base de datos.
- **Listar dispositivos**: Muestra todos los dispositivos registrados en la base de datos.
- **Enviar paquete WOL**: Despierta un dispositivo registrado enviando un paquete WOL a su dirección MAC.

## Instalación

### Dependencias

Este proyecto depende de la biblioteca [nlohmann/json](https://github.com/nlohmann/json) para la manipulación de archivos JSON. Asegúrate de tenerla disponible en tu sistema.

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
  sudo ./wake add <nombre> <direccion_mac>
  ```

  Ejemplo:

  ```bash
  sudo ./wake add MiPC 00:11:22:33:44:55
  ```

- **Eliminar un dispositivo**:

  ```bash
  sudo ./wake remove <nombre>
  ```

  Ejemplo:

  ```bash
  sudo ./wake remove MiPC
  ```

- **Listar los dispositivos registrados**:

  ```bash
  ./wake list
  ```

- **Despertar un dispositivo**:

  ```bash
  ./wake <nombre>
  ```

  Ejemplo:

  ```bash
  ./wake MiPC
  ```

### Base de Datos

La base de datos se almacena en formato JSON en el archivo `/etc/wol/database.json`. Para realizar cambios en la base de datos, como añadir o eliminar dispositivos, se requieren permisos de superusuario, por lo que deberás usar `sudo` para esos comandos.

## Seguridad

El archivo de la base de datos está ubicado en `/etc/wol/database.json` para asegurar que solo usuarios con permisos adecuados puedan modificar la lista de dispositivos. Puedes cambiar la ubicación de este archivo si prefieres otra ruta o si deseas evitar el uso de `sudo` para cada operación.

## Ejemplo de Uso

1. **Añadir un dispositivo**:

```bash
sudo ./wake add Server1 01:23:45:67:89:AB
```

2. **Despertar un dispositivo**:

```bash
./wake Server1
```

## Contribuciones

Si deseas contribuir a este proyecto, siéntete libre de hacer un fork del repositorio, realizar tus cambios y enviar un pull request. También puedes abrir issues para reportar bugs o sugerir mejoras.

## Licencia

Este proyecto está bajo la Licencia MIT. Consulta el archivo `LICENSE` para más detalles.
