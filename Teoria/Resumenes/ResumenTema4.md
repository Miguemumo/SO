# Tema 4. Gestión de archivos

## Inerfaz de los sistemas de archivo: Concepto de archivo

Es una colección de información relacionada y almacenada en un dispositivo de alamcenamiento secundario.

Su estructura lógica es:
- Secuencia de bytes: el tipo de archivo determina su estructura
- Secuencia de registros de longitud fija
- Secuencia de registros de longitud variable

Los tipos de archivos pueden ser: regulares, directorios, de dispositivo.

Las formas de acceso pueden ser: secuencial, aleatorio, otros.

Los atributos o metadatos están formados por:
- Nombre: única información en formato legible
- Tipo: cuando el sistema soporte diferentes tipos
- Localización: información sobre su localización en el dispositivo
- Tamaño: tamaño actual del archivo
- Protección: controla quién puede leer, escribir y ejecutar
- Tiempo, fecha e identificación del usuario: necesario para protección, seguridad y monitorización

Las operaciones sobre archivos son:
- Gestión:
  - Crear
  - Borrar
  - Renombrar
  - Copiar
  - Establecer y obtener atributos
- Procesamiento:
  - Abrir y cerrar
  - Leer
  - Escribir (modificar, insertar, borrar información)

## Estructura de directorios

Consta de una colección de nodos conteniendo información acerca de todos los archivos. Esto le dota a los directorios de cierta organización.

Tanto la estructura de dirctorios como los archivos residen en el almacenamiento secundario.

La organización lógica de los directorios debe proporcionar:
- Eficiencia: localización rápida de un archivo
- Denominación: adecuada a los usuarios
  - Dos usuarios pueden tener el mismo nombre para diferentes archivos
  - El mismo archivo puede tener varios nombres
- Agrupación: agrupar los archivos de forma lógica según sus propiedades. Ej: todos los programas en C

Existen distintos casos de estructura de directorios:

- En árbol:
  - Necesidad de búsquedas eficientes
  - Posibilidad de agrupación
  - Directorio actual (de trabajo)
  - Nombres de camino absolutos y relativos
- En grafo:
  - Compartición de subdirectorios y archivos
  - Más flexibles y complejos

## Protección

Consiste en proporcionar un acceso controlado a los archivos, indicando qué puede hacerse y por quién.

Los tipos de acceso son:
- Leer
- Escribir
- Ejecutar
- Añadir
- Borrar
- Listar

## Protección: Listas y grupos de acceso

La principal solución en protección consiste en hacer el acceso dependiente de la identificación de usuario. No obstante, las listas de acceso de usuarios individuales tenían problemas de longitud, por lo que se soluciona con clases de usuario.

Para solucionarlo, se dividen en propietario, grupo y público.

Una propuesta alternativa consiste en asignar un password con el archivo. El problema es que hay que recordar todos, y si sólo se asigna un password es, o acceso total, o ningún acceso.

## Semánticas de consistencia

Especifican cuándo las modificaciones de datos por un usuario se observan por otros usuarios.

Ejemplos:
1. Semántica de Unix
   - La escritura de una archivo es directamente observable
   - Cuando un archivo se cierra, sus cambios sólo se observan en sesiones posteriores
2. Semánticas de sesión (Sistema de archivos de Andrew)
   - La escritura de un archivo no es directamente observable
   - Cuando un archivo se cierra, sus cambios sólo se observan en sesiones posteriores
3. Archivos inmutables
   - Cuando un archivo se declara como compartido, no se puede modificar

## Funciones básicas del sistema de archivos

Las funciones básicas serían:

- Tener conocimiento de todos los archivos del sistema
- Controlar la compartición y forzar la protección de archivos
- Gestionar el espacio del sistema de archivos
  - Asignación/liberación del espacio en disco
- Traducir las direcciones lógicas del archivo en direcciones físicas del disco
  - Los usuarios especifican las partes que quieren leer/escribir en términos de direcciones lógicas relativas al archivo

## Diseño software del sistema de archivos

Un SA posee dos problemas de diseño:

- Definir cómo debe ver el usuario el sistema de archivos
	- definir un archivo y sus atributos
	- definir las operaciones permitidas sobre un archivo
	- definir la estructura de directorios
- Definir los algoritmos y estructuras de datos que deben crearse para establecer la correspondencia entre el sistema de archivos lógico y los dispositivos físicos donde se almacena

## Estructura del sistema de archivos

Se organiza en niveles o capas.

Por eficiencia, el SO mantiene una tabla indexada (por descriptor de archivo) de archivos abiertos.

Bloque de control de archivo: estructura con información de un archivo en uso.

## Métodos de asignación de espacio: Contiguo

Cada archivo ocupa un conjunto de bloques contiguos en disco.

- Ventajas
	- Sencillo: sólo necesita la localización de comienzo (nº bloque) y la longitud
	- Buenos tanto en acceso secuencial como en el directo
- Desventajas
	- No se conoce inicialmente el tamaño
	- Derroche de espacio, produce fragmentación externa
	- Los archivos no pueden crecer, a no ser que se realice compactación, que es ineficiente

Asignación lógica a física:

Supongamos que los bloques de disco son de 512 bytes:

> Dirección lógica (DL)/512 -> C(cociente), R(resto)

- Bloque a acceder = C + dirección de comienzo
- Desplazamiento en bloque = R

## Métodos de asignación de espacio: No contiguo - Enlazado

Cada archivo es una lista enlazada de bloques en disco. Éstos pueden estar dispersos por el disco.

- Ventajas
	- Evita la fragmentación externa
	- El archivo puede crecer dinámicamente cuando hay bloques libres, sin compactar
	- Basta almacenar el puntero al primer bloque del archivo
- Desventajas
	- El acceso a disco no es efectivo (si el secuencial)
	- Espacio requerido para los punteros de enlace. Esto se soluciona agrupándolos en clústeres
	- Seguridad por la pérdida de punteros. Esto se soluciona con una lista doblemente enlazada

Asociación lógica a física (dirección = 1 byte)

> Dirección lógica (DL)/511 -> C(cociente), R(resto)

- Bloque a acceder = C-ésimo
- Desplazamiento en el bloque = R + 1

Tabla de Asignación de Archivos (FAT): variación del método enlazado

- Reserva una sección del disco al comienzo de la partición para la FAT
- Contiene una entrada por cada bloque del disco y está indexada por número de bloques de disco
- Simple y eficiente siempre que esté en caché
- Para localizar un bloque solo se necesita leer en el FAT -> se optimiza el acceso directo
- Problema: pérdida de punteros -> doble copia de la FAT

## Métodos de asignación de espacio: No contiguo - Indexado

Todos los punteros a los bloques están juntos en una localización concreta: bloque índice

El directorio tiene la localización a este bloque índice y cada archivo tiene asociado su propio bloque índice

Para leer el i-ésimo bloque buscamos el puntero en la i-ésima entrada del bloque índice

- Ventajas:
	- Buen acceso directo
	- No produce fragmentación externa
- Desventajas:
	- Posible desperdicio de espacio en los bloques índices
	- Tamaño del bloque índice. Soluciones:
		- Bloques índices enlazados
		- Bloques índices multinivel
			- Problema: acceso a disco necesario para recuperar la dirección del bloque para cada nivel de indexación
			- Solución: mantener algunos bloques índices en memoria principal
		- Esquema combinado (Unix)


## Gestión de espacio libre

El sistema mantiene una lista de los bloques que están libres: lista de espacio libre.

La FAT no necesita ningún método.

A pesar de su nombre, la lista de espacio libre tiene diferentes implementaciones:

- Mapa o vector de Bits
	- Cada bloque se representa con un bit
	- Fácil encontrar un bloque libre o n bloques libres consecutivos. Algunas máquinas tienen instrucciones específicas.
	- Fácil tener archivos en bloques contiguos
	- Ineficiente si no se mantiene en memoria principial
- Lista enlazada
	- Enlaza todos los bloques libres del disco, guarda un puntero al primer bloque en un lugar concreto
	- No derrocha espacio
	- Relativamente ineficiente -> No es normal atravesar bloques vacíos
- Lista enlazada con agrupación
	- Cada bloque de la lista almacena n-1 direcciones de bloques libres
	- Obtener muchas direcciones de bloques libres es rápido
- Cuenta
	- Cada entrada de la lista: una dirección de bloque libre y un contador del nº de bloques libres que le sigue

## Implementación de directorios

Contenido de una entrada de directorio:

- Nombre de Archivo + Atributos + Dirección de los bloques de datos (DOS)
- Nombre de Archivo + Puntero a una estructura de datos que contiene toda la información relativa al archivo (UNIX)

Cuando se abre un archivo:

- El SO busca en su directorio la entrada correspondiente
- Extrae sus atributos y la localización de sus bloques de datos y los coloca en una tabla en memoria principal
- Cualquier referencia posterior usa la información de dicha tabla

Implementación de archivos compartidos (o enlace):

- Enlaces simbólicos
	- Se crea una nueva entrada en el directorio, se indica que es de tipo enlace y se almacena el camino de acceso absoluto o relativo del archivo al cual se va a enlazar.
	- Se puede usar en entornos distribuidos
	- Gran número de accesos a disco
- Enlace absolutos (o hard)
	- Se crea una nueva entrada en el directorio y se copia la dirección de la estructura de datos con la información del archivo
	- Problema al borrar los enlaces. Se soluciona con el Contador de enlaces

## Distribución del sistema de archivos

Los sistemas de archivos se almacenan en discos que pueden dividirse en una o más particiones.

Formateo del disco:

- Físico: pone los sectores (cabecera y código de corrección de errores) por pista
- Lógico: escribe la información que el SO necesita para conocer y mantener los contenidos del disco (un directorio inicial vacío, FAT, lista de espacio libre, ...)

Bloque de arranque para inicializar el sistema localizado por bootstrap.

Métodos necesarios para detectar y manejar bloques dañados.

## Recuperación

Como los archivos y directorios se mantienen tanto en MP como en disco, el sistema debe asegurar que un fallo no genere una pérdida o inconsistencia de datos.

Hay distintas formas:

- Comprobador de consistencia:
	- Compara los datos de la estructura de directorios con los bloques de datos en disco y trata cualquier inconsistencia
	- Más fácil en listas enlazadas que con bloques índices
- Usar programas del sistema para realizar copias de seguridad de los datos de disco a otros dispositivos y de recuperación de los archivos perdidos

## Implementación de la gestión de archivos en Linux

- i-nodo: representación interna de un archivo
- Un archivo tiene asociado un único i-nodo, aunque éste puede tener distintos nombres (enlaces)
- Si un proceso:
	- Crear un archivo -> se le asigna un i-nodo
	- Referencia a un archivo por su nombre -> se analizan permisos y se llevan el i-nodo a memoria principal hasta que se cierre

## Sistema de archivos

SO implementa al menos un sistema de archivos estándar o nativo

En Linux: ext2, ext3 y ext4

Necesidad de dar soporte a otros SA distintos: el kernel incluye una capa entre los procesos de usuario y la implementación del SA -> Sistemas de archivos virtual (VFS)

Linux abstrae el acceso a los archivos y a los SA mediante una interfaz virtual que lo hace posible.

Flujo de operaciones/datos por las distintas partes del sistema en una llamada al sistema de escritura (write)

## Tipos de sistemas de archivos

Tres clases generales de SA:

- SA basados en disco: es la forma clásica de almacenar archivos en medio no volátiles
- SA Virtuales: generados por el kernel y constituyen una forma simple para permitir la comunicación entre los programas y los usuarios
- SA de Red: permiten acceder a los datos a través de la red

## Modelo de archivo común

Para un programa de usuario, un archivo se identifica por un descriptor de archivo usado como índice en la tabla de descriptores que identifica el archivo en las operaciones relacionadas con él.

El descriptor lo asigna el kernel cuando se abre el archivo y es válido sólo dentro de un proceso.

Dos procesos diferentes pueden usar el mismo descriptor pero no puntan al mismo archivo.

Un inodo es la estructura asociada a cada archivo y directorio y contiene metadatos.

## Contenido de un i-nodo

- Identificador del propietario de archivo: UID, GID
- Tipo de archivo (regular, directorio, dispositivo, cauce, link). Si es 0 -> el i-nodo está libre
- Permisos de acceso
- Tiempos de acceso: última modificación, último acceso y última vez que se modificó el i-nodo
- Contador de enlaces
- Tabla de contenidos para las direcciones de los datos en disco del archivo
- Tamaño

## Estructura VFS

VFS es orientado a objetos, consta de dos componentes, archivos y SA, que necesita gestionar y abstraer.

Se representa a un archivo y a un SA con una familia de estructuras de datos hechas en C. Existen 4 tipos de objetos primarios del VFS:

- Objeto superblock: representa a un SA montado
- Objeto inode: representa a un archivo (cualquier tipo)
- Objeto dentry: representa a uno entrada de un directorio
- Objeto file: representa a un archivo abierto y es una estructura por proceso. Las anteriores son de sistema.

Cada una de estos objetos primeros tiene un vector de "operations". Estas funciones describen los métodos que el kernel invoca sobre los objetos primarios.

- objeto super_operation: métodos que el kernel puede invocar sobre un SA concreto. Ej: write_inodo() y sync_fs()
- objeto inode_operations: métodos que el kernel puede invocar sobre un archivo concreto. Ej: create() y link()
- objeto dentry_operations: métodos que el kernel puede invocar sobre una entrada de directorio. Ej: d_compare() y d_delete()
- objeto file_operativos: métodos que un proceso puede invocar sobre un archivo abierto como read() y write()

Cada SA registrado está representado por una estructura file_system_type. Este objeto describe el SA y sus capacidades.

Cada punto de montaje está representado por la estructura vfsmount que contiene información acerca del punto de montaje, tal como sus localizaciones y flags de montaje.

Finalmente, existen dos estructuras por proceso que describen el SA y los archivos asociados con un proceso: fs_struct y file_struct.

## Sistema de archivos Ext2

Divide el disco duro en un conjunto de bloques de igual tamaño donde se almacenan los datos de los archivos y administración.

El elemento central de Ext2 es el "grupo de bloques"

Cada SA consta de un gran número de grupos de bloques secuenciales.

Boot sector: zona del disco duro cuyo contenido se carga automáticamente por la BIOS y se ejecuta cuando el sistema arranca.

Cuando se usa un SA (se monta), el superbloque, sus datos, se almacena en MP.

## Descripción de un grupo de bloques

- Superbloque: estructura central para almacenar meta-información del SA
- Descriptores de grupo: contienen información que refleja el estado de los grupos de bloques individuales del SA
- Mapa de bits de bloques de datos y de inodos: contiene un bit por bloque de datos y por inodo respectivamente para indicar si están libres o no
- Tabla de inodos: contiene todos los inodos del grupo de bloques. Cada inodo mantiene los metadatos asociados con un archivo o directorio del SA


## Estructuras del dispositivo

- Estructura para el superbloque:
	- struct ext2_super_block
- Estructura para el descriptor de grupo:
	- struct ext2_group_desc
- Estructura para el inodo:
	- struct ext2_inode
- Estructura para directorios y archivos:
	- struct ext2_dir_entry_2

## Información sobre los bloques de un archivo

Linux usa un método de asignación de bloques no contiguo y cada bloque de un SA se identifica por un número.

En el inodo se almacenan 12 direcciones directas a BD, un primer nivel de indexación, un segundo nivel de indexación y un tercer nivel de indexación (si es necesario)

## Montaje y desmontaje de un sistema de archivos

La llamada al sistema mount conecta un sistema de archivos existente y la llamada unmount lo desconecta.

> mount (caminoEspecial, caminoDirectorio, opciones)

El núcleo tiene una tabla de montaje con una entrada por cada sistema de archivos montado:

- número de dispositivos que identifica el SA montado
- puntero a un buffer que contiene una copia del superbloque
- puntero al i-nodo raíz del SA montado
- puntero al i-nodo del directorio punto de montaje