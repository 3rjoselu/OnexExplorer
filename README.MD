# OnexExplorer

OnexExplorer es una herramienta de c\u00f3digo abierto para desempaquetar y volver a empaquetar archivos `.NOS` del juego NosTale. Permite abrir la mayor\u00eda de estos archivos, ver su contenido y exportarlo o reemplazarlo seg\u00fan sea necesario.

## Estructura del proyecto

- **Source/Converters**: conversores para modelos, im\u00e1genes y datos.
- **Source/Decryptors**: l\u00f3gica de descompresi\u00f3n y desencriptado.
- **Source/Openers**: clases encargadas de abrir archivos `.NOS` y leer configuraciones.
- **Source/Ui**: componentes de la interfaz gr\u00e1fica y previsualizadores.
- **resources.qrc** y **OnexExplorer.pro** definen recursos y configuraci\u00f3n de compilaci\u00f3n.
- El directorio **build** contiene ejemplos de proyectos generados con distintas versiones de Qt.

## Que puede hacer OnexExplorer

- Navegar y visualizar la mayor\u00eda de archivos `.NOS`.
- Previsualizar textos, im\u00e1genes y modelos 3D.
- Extraer archivos o carpetas completas.
- Reemplazar contenido existente y a\u00f1adir nuevos recursos.

## Archivos soportados actualmente

- NSgtdData (datos de objetos, misiones, habilidades y monstruos)
- NSlangData (_code_lang_list - ztsXXXe)
- NScliData (constring.dat)
- NSetcData (listas de palabras)
- NS4BbData (im\u00e1genes grandes)
- NSipData (iconos)
- NStpData (texturas de mapas y modelos)
- NStpeData (texturas de efectos)
- NStpuData (texturas de la interfaz)
- NStcData (cuadr\u00edculas de mapas)
- NSmpData (sprites de monstruos)
- NSppData (sprites de jugador)
- NSmnData (informaci\u00f3n de sprites de monstruos)
- NSpnData (informaci\u00f3n de sprites de jugador)
- NSmcData (kits de animaci\u00f3n de monstruos)
- NSpcData (kits de animaci\u00f3n de jugador)
- NStgData (modelos 3D)
- NStgeData (modelos 3D de efectos)

**En futuras actualizaciones se a\u00f1adir\u00e1n m\u00e1s archivos.**

### Archivos no soportados

- NStuData (configuraci\u00f3n de mapas)
- NSeffData (configuraci\u00f3n de efectos)
- NStsData
- NStkData
- NSemData
- NSesData
- NSedData
- NSgrdData
- NSpmData

## Notas

- Al importar parches JSON la ruta de cada archivo se determina desde la ubicación real del JSON, por lo que funciona igual en Windows o Linux.
- Puedes aplicar varios parches a diferentes archivos `.NOS` de forma simultánea eligiendo varios JSON y usar la opción **[3rJoselu] Save all .NOS** para guardar todos los archivos abiertos de una sola vez.
