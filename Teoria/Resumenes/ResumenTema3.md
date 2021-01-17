# Tema 3. Gestión de Memoria

## Jerarquía de Memoria

Hay dos principios:

- Menor cantidad, acceso más rápido
- Mayor cantidad, menor coste por byte

Así, los elementos que se accede más a menudo se ponen en memoria más pequeña y cara, y el resto en memoria lenta y barata.

## Conceptos sobre Cachés

La caché es una copia que puede ser accedida más rápido que la orinal. La idea es hacer los casos frecuentes mucho más eficientes.

Por tanto, el tiempo de acceso efectivo o TAE será:

> TAE = ProbabilidadAcierto * CosteAcierto + ProbabilidadFallo * CosteFallo

Esto funciona debido a que los programas no son aleatorios y explotan la localidad, llamado el principio de localidad.

## Espacio de direcciones lógico y espacio de direcciones físico

El espacio de direcciones lógico es el conjunto de direcciones lógicas o virtuales generadas por un programa.

El espacio de direcciones físico es el conjunto de direcciones físicas correspondientes a las direcciones lógicas en un instante dado.

## Mapa de memoria de un proceso

La imagen de un proceso está compuesta del mapa de memoria y su PCB.

## Objetivos generales de la gestión de memoria

La pregunta que nos hacemos es cómo está dividida la memoria y qué estrategias se pueden seguir:

- Estrategia de asignación: contigua y no contigua
- Estrategias de sustitución o reemplazo
- Estrategias de búsqueda o recuperación

## Asignación contigua y no contigua

- Contigua: La asignación de almacenamiento para un programa se hace en un único bloque de posiciones continuas de la memoria. Ej: Particiones fijas y variables.
- No contigua: Permitir dividir el programa en bloques o segmentos que se pueden colocar en distintas zonas de la memoria principal. Ej: Paginación, segmentación y segmentación paginada.

## Intercambio (Swapping)

La idea es intercambiar procesos entre memoria y un almacenamiento auxiliar. Este almacenamiento auxiliar debe ser rápido con espacio para albergar las imágenes de la memoria de los procesos de usuario. 

Por tanto, el factor principal es el tiempo de transferencia.

## Memoria virtual: Organización

El tamaño de un programa puede exceder la cantidad de memoria física de la que dispone. Por tanto, se usa un almacén a dos niveles:

- Memoria principal: partes del proceso necesarias en un momento dado
- Memoria secundaria: espacio de direcciones completo del proceso

## Concepto de memoria virtual

Es necesario saber qué se encuentra en memoria principal y tener una política de movimiento entre memoria principal y memoria secundaria. Además, la memoria virtual resuelve el problema del crecimiento dinámico de procesos y permite aumentar el grado de multiprogramación.

## Unidad de gestión de memoria (MMU)

Es un dispositivo hardware que traduce direcciones virtuales a direcciones físicas, siendo gestionado por el SO.

El programa de usuario sólo trata con direcciones lógicas y nunca con direcciones reales.

Además de traducir, el MMU deberá:

- Detectar si la dirección aludida se encuentra o no en memoria principal
- Generar una excepción si no está

## Paginación

El problema que tenemos es que el espacio de direcciones físicas de un proceso puede ser no contiguo. Por tanto, la memoria física se divide en bloques de tamaño fijo, denominados marcos de página. El tamaño suele ser potencia de dos (de 0.5 a 8 Kb).

El espacio lógico de un proceso se divide en bloques del mismo tamaño, denominados páginas.

Los marcos de páginas contendrán páginas de los procesos.

- Las direcciones lógicas, que son las que genera la CPU, se dividen en número de página (p) y desplazamiento dentro de la página (d)
- Las direcciones físicas se dividen en número de marco (m) y desplazamiento (d)

Cuando la CPU genere una dirección lógica será necesario traducirla a la dirección física, y la tabla de páginas mantiene la información necesaria para realizar dicha traducción. Hay una tabla de páginas por proceso.

- Tabla de ubicación en disco (una por proceso), que indica la ubicación de cada página en el almacenamiento secundario
- Tabla de marcos de página, usada por el SO y contiene información sobre cada marco de página

## Contenido de la tabla de páginas

Una entrada por cada página del proceso:

- Número de marco en el que está almacenada la página si está en memoria principal
- Bit de presencia o bit válido
- Bit de modificación
- Modo de acceso autorizado a la página o bit de protección

## Falta de página

1. Bloquear proceso
2. Encontrar la ubicación en disco de la página solicitada
3. Encontrar un marco libre. Si no hubiera, se puede optar por desplazar una página de memoria principal
4. Cargar la página desde disco al marco de memoria principal
5. Actualizar tablas y poner su bit de presencia a 1
6. Desbloquear proceso
7. Reiniciar la instrucción que originó la falta de página


