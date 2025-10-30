# Gestor de Líneas de Colectivos (C)

Aplicación de consola en C que gestiona líneas de colectivo usando un archivo de texto ("lineas.txt") como “base de datos”.

## Requisitos
- Dev-C++ (proyecto de Consola C) o MinGW-w64 (gcc) si compilas por línea de comandos.
- Windows (probado en entorno Windows).

## Estructura del proyecto
```
GestorColectivos/
  include/
    linea.h
    menu.h
  src/
    main.c
    menu.c
    linea.c
  lineas.txt           # archivo de datos (junto al ejecutable)
```

`lineas.txt` usa formato CSV simple separado por punto y coma `;`:
```
<id>;<nombre>;<recorrido>
```
Ejemplo:
```
1;Linea 1;Terminal A - Centro - Terminal B
2;Linea 2;Barrio Norte - Centro - Barrio Sur
3;Linea 3;Estacion - Universidad - Parque
```

## Cómo ejecutar en Dev-C++ (recomendado por la cátedra)
1. Abre Dev-C++ y crea un “Proyecto de Consola” en C (NO C++).
2. Agrega estos archivos al proyecto:
   - src/main.c
   - src/menu.c
   - src/linea.c
3. Asegúrate de que los headers se incluyan correctamente desde el código (ya se usan rutas relativas `../include/...`, no hace falta configurar directorios de includes).
4. Estándar del compilador: en Opciones del Proyecto → Compilador, selecciona C99 o GNU C99.
5. Compila y ejecuta.
6. Coloca `lineas.txt` en la misma carpeta donde se genera el `.exe` (o configura el “Directorio de trabajo” del proyecto para que apunte a la carpeta del proyecto donde está `lineas.txt`).

Sugerencia: si al ejecutar dice que el archivo no existe, copia `lineas.txt` al mismo directorio del `.exe` que genera Dev-C++.

## Compilar por línea de comandos (opcional)
Abrir PowerShell o CMD en la carpeta del proyecto y ejecutar:
```
gcc -Iinclude src\main.c src\menu.c src\linea.c -o gestor.exe
./gestor.exe
```
Asegúrate de que `gcc` esté en el PATH (instala MinGW-w64 si no lo está). Coloca `lineas.txt` junto a `gestor.exe` antes de ejecutar.

## Uso básico
- “Mostrar todas las lineas” lista el contenido de `lineas.txt`.
- “Consultar una linea” permite buscar por ID o por nombre (insensible a mayúsculas/minúsculas).
- “Agregar una linea” pide ID, nombre y recorrido, y lo agrega al final de `lineas.txt`.
- “Eliminar una linea” pide un ID y reescribe `lineas.txt` sin ese registro.

## Solución de problemas
- Error “no encuentra menu.h/linea.h”: ya se corrigieron includes a `../include/...`. Revisa que añadiste los `.c` desde `src` y que mantienes la estructura de carpetas.
- “No hay datos. El archivo lineas.txt no existe.”: coloca `lineas.txt` junto al `.exe` o ajusta el “Directorio de trabajo”.
- Acentos se ven raros (�): es un tema de codificación de consola. Puedes ignorar los acentos o ejecutar `chcp 65001` antes de correr para usar UTF-8.

## Notas técnicas
- Ruta de datos configurable en `include/linea.h` mediante `#define LINEAS_FILE "lineas.txt"`.
- Archivo temporal para eliminación: `lineas.tmp` (se crea junto al ejecutable).
