## EncriptPassNodejsCPP

Este proyecto proporciona una API en Node.js que utiliza un addon en C++ para cifrar contraseñas. La contraseña se cifra y se devuelve en formato Base64 a través de un endpoint API.

### Estructura del Proyecto

src/: Contiene el código fuente del addon en C++.
encrypt.cpp: Implementación del cifrado y codificación Base64.
base64.cpp y base64.h: Implementación de la codificación Base64.
index.js: Servidor de la API en Node.js que expone el endpoint para cifrar contraseñas.
binding.gyp: Configuración de node-gyp para construir el addon en C++.

1. **Requisitos**

Node.js (v12 o superior)
node-gyp (v10 o superior)
OpenSSL (para la funcionalidad de cifrado en C++)
Herramientas de desarrollo de C++ (Visual Studio en Windows)

2. **Instalación**

Clona el Repositorio

```bash

git clone https://github.com/tu-usuario/encript-pass-nodejs-cpp.git
cd encript-pass-nodejs-cpp

```

3. **Instala Dependencias de Node.js**

```bash

npm install

```

4. **Configura y Construye el Addon**

```bash

Copiar código
node-gyp configure
node-gyp build

```

Instala Dependencias de C++ (si es necesario)

Asegúrate de tener OpenSSL instalado y configurado en tu entorno.

### Uso

1. **Inicia el Servidor**

```bash
Copiar código
node index.js
```
El servidor se iniciará en `http://localhost:3000.`

Envía una Solicitud para Cifrar una Contraseña

Puedes usar curl o Postman para enviar una solicitud POST al endpoint /api/encrypt.

    - Con curl:

```bash

Copiar código
curl -X POST http://localhost:3000/api/encrypt -H "Content-Type: application/json" -d '{"password":"miContraseñaSecreta"}'

```

    - Con Postman:

Configura una solicitud POST a `http://localhost:3000/api/encrypt`.

En la pestaña de "Body", selecciona "raw" y "JSON" y proporciona el siguiente cuerpo:

```bash

{
    "password": "miContraseñaSecreta"
}

```
Envía la solicitud y recibirás una respuesta JSON con el campo encrypted que contiene la contraseña cifrada en Base64.

Ejemplo de Respuesta

```bash

{
    "encrypted": "BZ9AJH+PcHPMbuy6hUN8UBb+WeDgRmzyPCxDl8cLee8="
}

```