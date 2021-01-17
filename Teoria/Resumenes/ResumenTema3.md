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

## Implementación de la tabla de páginas

La tabla de páginas se mantiene en memoria principal. Además, el registro base de la tabla de páginas apunta a la tabla de páginas (suele contener el PCB).

En este esquema:
- Cada acceso a una instrucción o dato requiere dos accesos a memoria, uno a la tabla de páginas y otro a la memoria
- Un problema adicional viene dado por el tamaño de la tabla de páginas

## Tamaño de la tabla de páginas

> Dirección virtual: 32 bits
>
> Tamaño de página: 4 Kbytes (2^12 bytes)
>
> Tamaño del campo de desplazamiento: 12 bits
>
> Tamaño número de página virtual: 20 bits
>
> Nº de páginas virtuales: 2^20 = 1048576

Solución para reducir el tamaño de la tabla de páginas: **paginación multinivel**

## Paginación multinivel

La idea es paginar las tablas de páginas. La partición de la tabla de páginas permite al sistema operativo dejar particiones no usadas sin cargar hasta que sean necesarias. De esta forma, aquellas porciones del espacio de direcciones que no se usen no necesitan tener tabla de página.

## Paginación a dos niveles

La idea es dividir la tabla de páginas en partes del tamaño de una página.

Por tanto, la dirección lógica se divide en:
- Número de página (n bits):
  - Un número de página p1
  - Desplazamiento de página p2
- Desplazamiento de página d (m bits)

Entonces, una dirección lógica quedaría de la siguiente forma:

|p1|p2|d|
| -- | -- | -- |

## Páginas compartidas

Se tiene una copia de sólo lectura compartido entre varios procesos.

## Segmentación

Esquema de organización de memoria que soporta mejor la visión de memoria del usuario. Esto hace que un programa sea una sucesión de segmentos que tienen procedimientos, pilas, etc.

## Tabla de segmentos

Una dirección lógica es una tupla:

> <numeroDeSegmento, desplazamiento>

La tabla de segmentos aplica direcciones bidimensionales definidas por el usuario en direcciones físicas. Cada entrada tiene los siguientes elementos (a parte de bit de presencia y de protección):

- Base: dirección física donde reside el inicio del segmento en memoria
- Tamaño: longitud del segmento

## Implementación de la tabla de segmentos

Esta tabla se mantiene en memoria principal. Además, el registro base de la tabla de segmentos o RBTS apunta a la tabla de segmentos. Éste suele almacenarse en el PCB del proceso.

El registro longitud de la tabla de segmentos o STLR indica el número de segmentos del proceso

## Segmentación paginada

La variabilidad de tamaños en los segmentos y el requisito de memoria contigua complica la gestión de memoria principal y memoria secundaria.

Por otro lado, la paginación simplifica esta gestión, pero complica más los temas de compartición y protección.

Algunos sistemas combinan ambos enfoques, obteniendo la mayoría de las ventajas de la segmentación y eliminando los problemas de una gestión de memoria compleja.

## Memoria virtual: Gestión

- Gestión de memoria virtual con paginación
- Criterios de clasificación respecto a:
  - Políticas de asignación: fija o variable
  - Políticas de búsqueda (recuperación):
    - Paginación por demanda
    - Paginación anticipada (no es lo mismo que prepaginación)
  - Políticas de sustitución (reemplazo):
    - Sustitución local
    - Sustitución global

## Gestión de la memoria virtual

Independientemente de la política de sustitución utilizada, existen ciertos criterios que siempre deben cumplirse:
- Páginas limpias frente a sucias: para minimizar el coste de transferencia
- Páginas compartidas: se pretende reducir el número de faltas de página
- Páginas especiales: algunos marcos pueden estar bloqueados, por ejemplo en búferes de E/S

## Influencia del tamaño de página

Cuanto más pequeña es una página:
- Aumento del tamaño de las tabals de páginas
- Aumento del número de transferencias entre memoria principal y disco
- Reducen la fragmentación interna

Cuanto más grandes:
- Grandes cantidades de información que no serán usadas están ocupando la memoria principal
- Aumenta la fragmentación interna

Por tanto, la idea es buscar un equilibrio en el tamaño de página.

## Algoritmos de sustitución

Podemos tener las siguientes combinaciones:
- Asignación fija y sustitución local
- Asignación variable y sustitución local
- Asignación variable y sustitución global

A lo largo del tema vamos a ver distintos algoritmos:
- Óptimo: sustituye la página que no se va a referenciar en el futuro o que se referencie más tarde
- FIFO: sustituye la página más antigua
- LRU: sustituye la página que fue referenciada más tarde
- Algoritmo del reloj

## Algoritmo del reloj

Cada página tiene asociado un bit de referencia R (lo pone a 1 el hardware).

Los marcos de página se representan por una lista circular y un puntero a la página visitada hace más tiempo.

Para seleccionar una página se sigue este proceso:
- Consultar el marco actual
- ¿Es R=0?
  - No: R=0; ir al siguiente marco y volver al paso 1
  - Si: seleccionar para sustituir e incrementar posición

## Comparación

Nos damos cuenta que a la que la memoria principal sea grande, la diferencia entre estos algoritmos es más bien mínima, influyendo más la cantidad de memoria principal de la que dispongamos que del algoritmo de sustitución utilizado.

## Comportamiento de los programas

Viene definido por la secuencia de referencias a página que realiza el proceso.

Es importante para maximizar el rendimiento del sistema de memoria virtual.

## Propiedad de localidad

Hay distintos tipos:

- Temporal: una posición de memoria referenciada recientemente tiene una probabilidad alta de ser referenciada en un futuro próximo
- Espacial: si cierta posición de memoria ha sido referenciada, es probable que otras adyacentes también lo sean (array, ejecución secuencial, etc)

## Conjunto de trabajo

Teniendo en cuenta las siguientes observaciones:
- Mientras el conjuto de páginas necesarias puedan residir en memoria principal, el número de faltas de página no crece mucho
- Si eliminamos de memoria principal páginas de ese conjunto, la activación de páginas crece mucho

El conjunto de trabajo (Working Set) de un proceso es el conjunto de páginas que son referenciadas frecuentemente en un intervalo de tiempo.

> WS(t,z) = páginas referenciadas en el intervalo de tiempo t-z

## Conjunto de trabajo: propiedades

Las propiedades serían las siguientes:

- Los conjuntos de trabajo son transitorios
- No se puede predecir el tamaño futuro de un conjunto de trabajo
- Difieren unos de otros sustancialmente

## Teoría del conjunto de trabajo

Un proceso sólo puede ejecutarse si su conjunto de trabajo está en memoria principal.

Una página no puede retirarse de memoria principal si está dentro de un conjunto de trabajo del proceso en ejecución.

## Hiperpaginación

Si un proceso no tiene "suficientes" páginas, la tasa de faltas es alta:

- Bajo uso de la CPU
- El sistema operativo aumenta el grado de multiprogramación
- Más faltas de página

Por tanto, cuando esto sucede, decimos que estamos ante un caso de hiperpaginación, en el que el SO está ocupado en resolver faltas de página.

Para evitar la hiperpaginación, hay dos formas posibles:
- Asegurar que cada proceso existente tenga asignado un espacio en relación a su comportamiento -> Algoritmos de asignación variables
- Actuar directamente sobre el grado de multiprogramación -> Algoritmos de regulación de carga

## Algoritmo basado en el modelo del WS

En cada referencia, determina el conjunto de trabajo: páginas referenciadas en el intervalo [t - x, t] y sólo esas páginas son mantenidas en memoria principal.

## Algoritmo FPP (Frecuencia de falta de página)

La idea es, que para ajustar el conjunto de págians de un proceso, usa los intervalos de tiempo entre dos faltas de página consecutivas:

  - Si el intervalo de tiempo grande es mayor que Y, todas las páginas no referenciadas en dicho intervalo son retiradas de memoria principal
  - En otro caso, la nueva página es incluida en el conjunto de páginas residentes

Formalmente:
- tc = instante de t0 de la actual falta de página
- tc-1 = instante de t0 de la anterior falta de página
- Z = conjunto de páginas referenciadas en un intervalo de t0
- R = conjunto de páginas residentes en memoria principal

## Gestión de memoria en linux

- Gestión de memoria a bajo nivel
- El espacio de direcciones del proceso
- La caché de páginas y la escritura de páginas a disco

## Gestión de memoria a bajo nivel

La página física es la unidad básica de gestión de memoria: struct_page

> struct page {
>
> unsigned long flags; //PG_dirty, PG_locked
>
> atomic_t_count;
>
> struct address_space *mapping;
>
> void *virtual;
>
> ...
>
> }

Una página puede ser utilizada como:

- La caché de páginas
- Datos privados
- Una proyección de la tabla de páginas de un proceso
- El espacio de direcciones de un proceso
- Los datos del kernel alojados dinámicamente
- El código del kernel

Las interfaces para la asignación de memoria en páginas:

- struct page * alloc_pages(gfp_t gfp_mask, unsigned int order)
  - La función asigna 2^order páginas físicas contiguas y devuelve un puntero a la struct page de la primera página, o null si falla.
- unsigned long __get_free_pages(gfp_t gfp_mask, unsigned int order)
  - Esta función asigna 2^order páginas físicas contiguas y devuelve la dirección lógica de la primera página

Las interfaces para la liberación de memoria en páginas:
- void __free_pages(struct page *page, unsigned int order)
- void free_pages(unsigned long addr, unsigned int order)

Ambas funciones liberan 2^order páginas a partir de la estructura de página o de la página que coincide con la dirección lógica.

Las interfaces para la asignación/liberación de memoria en bytes:

- void * kmalloc(size_t size, gfp_t flags)
- void kfree(const void *ptr)

Estas funciones son similares a las que proporciona C en espacio de usuario malloc() y free().
