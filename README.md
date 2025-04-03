Aquí tienes un ejemplo de `README.md` para tu **interfaz gráfica de chat en C++ con Qt y WebSockets**, basado en los archivos que compartiste:

---

# 🖥️ Interfaz Gráfica de Chat WebSocket

Este proyecto es una **interfaz gráfica de cliente** para un sistema de chat basado en el protocolo **WebSocket**. Fue desarrollado usando **Qt (C++)** como framework para la GUI, y se conecta a un servidor en C mediante comunicación en tiempo real.

---

## 🚀 Características

- Conexión a servidor WebSocket personalizado
- Lista de usuarios conectados y sus estados
- Envío y recepción de mensajes privados o generales (`~`)
- Solicitud y visualización del historial de mensajes
- Actualización de estado (activo, ocupado, inactivo)
- Protección contra múltiples conexiones con el mismo nombre de usuario

---

## 🧠 Dependencias

- **Qt 5/6**
- **CMake** o qmake (según configuración)
- Proyecto de servidor WebSocket en C (adjunto en repositorio)

---

## 🔧 Compilación

### Usando Qt Creator:

1. Abre el `.pro` o `CMakeLists.txt`
2. Presiona *Run* o *Build*

### Usando terminal:

```bash
qmake && make
./chat_gui
```

---

## 🧭 Uso

1. Ejecuta el servidor con:
   ```bash
   ./server <puerto>
   ```

2. Inicia el cliente:
   ```bash
   ./chat_gui
   ```

3. Ingresa IP, puerto y nombre de usuario
4. Usa la GUI para:
   - Ver usuarios (`Listar`)
   - Cambiar estado (`Estado`)
   - Enviar mensaje (`Enviar`)
   - Ver historial (`Historial`)
   - Salir (`Desconectar`)

---

## 📌 Estados disponibles

- **Activo (1)**: Usuario disponible
- **Ocupado (2)**: Usuario en actividad
- **Inactivo (3)**: Usuario no disponible
- **Desconectado (0)**: No conectado

---

## 🚫 Restricciones

- No se permiten múltiples usuarios conectados con el mismo nombre
- No se puede utilizar `~` como nombre de usuario
- El mensaje y nombre deben ser menores a 255 caracteres

---
![image](https://github.com/user-attachments/assets/01065d08-3788-40bf-a9a4-9ae3064e39a5)
