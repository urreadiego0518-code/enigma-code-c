# EnigmaCode en C

> Versión de consola del sistema de nómina de EnigmaCode, escrita en C puro.
> La misma idea que la app de Android, pero sin interfaz: menú de texto, archivo
> `.txt` como "base de datos" y los algoritmos de ordenamiento hechos a mano.

[![C](https://img.shields.io/badge/C-C99-A8B9CC?logo=c&logoColor=white)](https://es.wikipedia.org/wiki/C99)
[![CMake](https://img.shields.io/badge/CMake-3.31-064F8C?logo=cmake&logoColor=white)](https://cmake.org)
[![Licencia](https://img.shields.io/badge/Licencia-MIT-green.svg)](LICENSE)

---

## Qué hace

Es un CRUD de empleados por consola. Cada empleado guarda número, nombre, RFC,
días trabajados y localidad. Con esos datos el programa calcula su sueldo.

| Opción del menú | Qué hace |
|---|---|
| 1 | Mostrar todos los empleados |
| 2 | Agregar empleados |
| 3 | Buscar (por número o por localidad) |
| 4 | Modificar un empleado |
| 5 | Eliminar un empleado |
| 6 | Ordenar (por número, por localidad o por sueldo final) |
| 7 | Guardar cambios en el archivo |
| 0 | Salir |

Los datos se guardan en `empleados.txt`, así que al volver a abrir el programa
sigues teniendo lo que capturaste.

---

## Cómo se calcula el sueldo

```
sueldoBase   = díasTrabajados × 200
bono         = porcentaje según la localidad
sueldoNeto   = sueldoBase + bono
percepciones = sueldoNeto × 0.20 + horasExtra × 50
deducciones  = sueldoNeto × 0.22 + faltas × 200
sueldoFinal  = sueldoNeto + percepciones − deducciones
```

Bonos por localidad: Yucatán 40 %, Puebla 30 %, Veracruz 20 %, Chiapas 10 %,
Campeche +$400.

---

## Compilar y ejecutar

Con CMake:

```bash
cmake -B build
cmake --build build
./build/programacion
```

Con gcc directo (más rápido para probar):

```bash
gcc -Wall -Wextra -o enigmacode main.c
./enigmacode
```

Compila sin warnings con `-Wall -Wextra` en GCC.

> El programa trabaja sobre `empleados.txt` en la carpeta donde lo ejecutes. Si
> quieres empezar con datos de ejemplo, copia el archivo que viene incluido:
> `cp empleados.ejemplo.txt empleados.txt`.

---

## Estructura

```
enigma-code-c/
├── main.c                 # Todo el programa: estructuras, CRUD, ordenamientos y archivo
├── CMakeLists.txt         # Build con CMake (C99)
├── empleados.ejemplo.txt  # Datos de muestra
├── LICENSE
└── README.md
```

---

## Lo que se practica

- **Estructuras (`struct`)** para modelar al empleado.
- **Arreglos de estructuras** con un contador de cuántos hay ocupados.
- **Archivos** con `fopen` / `fprintf` / `fscanf` para guardar y recuperar.
- **Funciones** separadas por responsabilidad (agregar, buscar, modificar,
  eliminar, ordenar).
- **Ordenamientos escritos a mano**: burbuja por número, por localidad y por
  sueldo final.
- **Búsqueda** por campo exacto y por localidad.
- **`enum`-style** con `switch` para traducir el número de localidad a su nombre.

---

## Lo que le falta (si quieres mandar un PR)

Esto es código de clase y tiene cosas mejorables. Las que ya identifiqué:

- **Validación de entrada**: si escribes letras donde va un número, `scanf` deja
  el buffer sucio y el menú se queda ciclado. Falta limpiar el buffer o leer con
  `fgets` + `strtol`.
- **El arreglo está fijo en 10 empleados.** Se puede cambiar por memoria
  dinámica (`malloc` / `realloc`) o por una lista ligada.
- **No valida el RFC** ni los rangos (días negativos, localidad inexistente).
- **Los montos son `float`.** Para dinero conviene guardar centavos en enteros o
  usar `double` con cuidado.
- **Todo vive en un solo archivo.** Se puede separar en `empleado.c`,
  `archivo.c` y `main.c`.

Si ves otra cosa, abre un issue o mándame el PR.

---

## Licencia

MIT. Úsalo, modifícalo y compártelo. Ver [LICENSE](LICENSE).

---

<div align="center">
  <sub>Hecho por <a href="https://github.com/urreadiego0518-code">Diego Urrea</a></sub>
</div>
