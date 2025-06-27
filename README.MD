# OnexExplorer

OnexExplorer es una herramienta de código abierto para desempaquetar y volver a empaquetar archivos `.NOS` del juego NosTale. Permite abrir la mayoría de estos archivos, ver su contenido y exportarlo o reemplazarlo según sea necesario.

## Estructura del proyecto

- **Source/Converters**: conversores para modelos, imágenes y datos.
- **Source/Decryptors**: lógica de descompresión y desencriptado.
- **Source/Openers**: clases encargadas de abrir archivos `.NOS` y leer configuraciones.
- **Source/Ui**: componentes de la interfaz gráfica y previsualizadores.
- **resources.qrc** y **OnexExplorer.pro** definen recursos y configuración de compilación.
- El directorio **build** contiene ejemplos de proyectos generados con distintas versiones de Qt.

## Que puede hacer OnexExplorer

- Navegar y visualizar la mayoría de archivos `.NOS`.
- Previsualizar textos, imágenes y modelos 3D.
- Extraer archivos o carpetas completas.
- Reemplazar contenido existente y añadir nuevos recursos.

## Archivos soportados actualmente

- NSgtdData (datos de objetos, misiones, habilidades y monstruos)
- NSlangData (_code_lang_list - ztsXXXe)
- NScliData (constring.dat)
- NSetcData (listas de palabras)
- NS4BbData (imágenes grandes)
- NSipData (iconos)
- NStpData (texturas de mapas y modelos)
- NStpeData (texturas de efectos)
- NStpuData (texturas de la interfaz)
- NStcData (cuadrículas de mapas)
- NSmpData (sprites de monstruos)
- NSppData (sprites de jugador)
- NSmnData (información de sprites de monstruos)
- NSpnData (información de sprites de jugador)
- NSmcData (kits de animación de monstruos)
- NSpcData (kits de animación de jugador)
- NStgData (modelos 3D)
- NStgeData (modelos 3D de efectos)

**En futuras actualizaciones se añadirán más archivos.**

### Archivos no soportados

- NStuData (configuración de mapas)
- NSeffData (configuración de efectos)
- NStsData
- NStkData
- NSemData
- NSesData
- NSedData
- NSgrdData
- NSpmData

## Notas

- Al importar parches JSON la ruta de cada archivo se determina desde la ubicación real del JSON, por lo que funciona igual en Windows o Linux.
- Todas las rutas devueltas respetan el separador del sistema.
- Puedes aplicar varios parches a diferentes archivos `.NOS` de forma simultánea eligiendo varios JSON y usar la opción **[3rJoselu] Save all .NOS** para guardar todos los archivos abiertos de una sola vez.
