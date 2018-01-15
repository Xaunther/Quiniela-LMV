## Contenidos

Este repositorio contiene el código de la quiniela usada en http://ligamanagervirtual.com (LMV), en lenguaje C++.
Desde que se escribieron las primeras líneas hasta las últimas han pasado casi 5 años, en los cuales mi conocimiento sobre C++ ha aumentado considerablemente.

## Notas

Los parámetros de ambos scripts están hard-coded (nº de partidos de la quiniela, nº de jornadas, nombres de archivos, nombre clave que debe aparecer en el post, etc.).
El objetivo es adaptar el código para que gran parte de estos parámetros puedan configurarse fácilmente; bien desde un archivo de texto o con un archivo de constantes.

## Descripción
**Quiniela.cpp**: Es el script que lee el archivo con los posts copiados, analiza las apuestas de cada jugador, compara con los resultados de la jornada, devuelve un archivo con un post de resultados (html) y actualiza la clasificación de la quiniela. Usa los siguientes archivos con estos nombres:
		  1. **Quiniela.txt**: Aquí debe copiarse la página con las apuestas (usando seleccionar todo, no el código fuente de la página). El modelo de post se describe más adelante
		  2. **res.txt**: Aquí deben introducirse los resultados de la jornada de la quiniela. En cada línea se escribe (1/X/2), que corresponde al resultado de cada partido, en orden
		  3. **post.txt**: (generado automáticamente) aquí se genera el post con los resultados, que puede usarse directamente en el foro.
		  4. **table.txt**: Clasificación de la quiniela. Si el archivo no existe, el programa la crea de cero. Si existe, la actualiza.

**PostQuiniela.cpp**: Copiando el calendario de gesliga permite hacer los posts de cada jornada de quiniela automáticamente. Sin embargo, requiere manualmente especificar cuántos partidos de cada competición deben usarse y otras configuraciones. Lo incluyo en el repositorio porque ahorra mucho tiempo, aunque sólo se use una vez por temporada.

## Uso de la quiniela
Siguiendo el ejemplo encontrado en http://www.ligamanagervirtual.com/t22782-quiniela-j9:
El concepto importante es que puedes escribir cualquier cosa en este hilo, siempre y cuando tras la palabra clave "QuinielaLMV.txt" aparezca la quiniela perfectamente rellenada.
La primera vez que esta palabra aparece, el programa sabe que es el post de ejemplo y no hace nada.
A partir de la segunda aparición en adelante, la quiniela debe rellenarse escribiendo en la siguiente línea el nick para la quiniela (NO PUEDE CONTENER ESPACIOS EN BLANCO Y ES SENSIBLE A MAYÚSCULAS).
En las siguientes líneas (no importa que haya línas en blanco) deberá realizarse la apuesta (1/X/2), separada del equipo visitante por un espacio en blanco. Una vez se ha apostado en todos los partidos (15 en este ejemplo) se puede volver a escribir cualquier cosa.
Tampoco puede haber espacios en blanco en los nombres de los equipos.

## Contacto

Cualquier duda es bienvenida o problema son bienvenidos, pueden abrir un issue en github o contactar a través de alex.1993.24@gmail.com