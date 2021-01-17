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
