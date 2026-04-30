# OnexExplorer

OnexExplorer es una herramienta de código abierto para desempaquetar y volver a empaquetar archivos `.NOS` del juego NosTale. Permite abrir la mayoría de estos archivos, ver su contenido y exportarlo o reemplazarlo según sea necesario.

## Compilación

### Requisitos previos

- **Qt 5.15.2** o **Qt 6.9.1** con el kit **MinGW 64-bit** (instalable desde [qt.io](https://www.qt.io/download-qt-installer))
- **FreeGLUT** (necesario para la previsualización de modelos 3D)
  - Descargar desde [freeglut.sourceforge.net](https://freeglut.sourceforge.net/) o [transmissionzero.co.uk](https://www.transmissionzero.co.uk/software/freeglut-devel/)
  - Extraer de forma que quede `C:/freeglut/include/` y `C:/freeglut/lib/x64/` (la ruta está fija en el proyecto)

### Con Qt Creator (recomendado)

1. Abrir **Qt Creator** e ir a `File > Open File or Project...`
2. Seleccionar `OnexExplorer.pro`
3. Elegir el kit **Desktop Qt 5.15.2 MinGW 64-bit** (o 6.9.1 si está disponible)
4. Para compilar en **Release**: en la barra lateral izquierda, hacer clic en el icono del monitor y cambiar de *Debug* a *Release*
5. Pulsar **Build** (Ctrl+B) o el botón de play sin depuración (Ctrl+R)

El ejecutable se genera en:
```
build/Desktop_Qt_5_15_2_MinGW_64_bit-Release/release/OnexExplorer.exe
```

### Despliegue (ejecutar fuera de Qt Creator)

Para distribuir el `.exe` o ejecutarlo en una máquina sin Qt instalado, hay que copiar las DLLs de Qt junto al ejecutable usando `windeployqt`:

```bash
cd build/Desktop_Qt_5_15_2_MinGW_64_bit-Release/release/
windeployqt OnexExplorer.exe
```

Esto copia automáticamente las DLLs necesarias de Qt y MinGW. Además hay que copiar manualmente `freeglut.dll` (de `C:/freeglut/bin/x64/`) junto al ejecutable.

### Por línea de comandos (qmake)

```bash
cd C:\Users\Usuario\Documents\OnexExplorer
qmake OnexExplorer.pro CONFIG+=release
mingw32-make -j4
```

---

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
- Puedes aplicar varios parches a diferentes archivos `.NOS` de forma simultánea eligiendo varios JSON y usar la opción **[3rJoselu] Save all .NOS (CTRL+S)** para guardar todos los archivos abiertos de una sola vez.
- Se eliminaron los botones de invitaci\u00f3n a Discord y Ko-fi para una interfaz m\u00e1s limpia.
- La lista de archivos en el árbol ahora se ordena de forma natural para que elementos como `31439_2` aparezcan en el orden correcto.
- La combinación **CTRL+S** ahora ejecuta el guardado masivo de todos los archivos abiertos.
