# quadratic_asigment_problem
### Requerimientos
    - c++23
    - python 3 -> 3.10.6

### Ejecución Recomendada
```bash
make run
```
esto ejecutará el script de python `run.py` y te mostrará un menu con el que podrás interactuar. Las opciones que te piden un path, esperan que lo ingreses relativo al directorio actual. Por ejemplo, si quisieras entregar el path al archivo matrix.cpp deberías entregar `/modules/matrix/matrix.cpp`. En el caso, de que quieras ejecutar varias instancias dentro de un directorio, dicho directorio tambien debe estar en el directorio actual, es decir al mismo nivel que main.cpp, ejemplo: `/data/pequenas`. Por defecto, todos los resultados generados en esta opción se almacenarán dentro del directorio results.

### Ejecución Normal
1. Para compilar los archivos
```bash
make all
```

2. Para ejecutar una instancia, se debe especificar el path a dicha instancia desde el directorio actual. Esto mostrará los resultados como un print en el terminal. Ejemplo: 
```bash
./main ./data/pequenas/instance4A.dat
``` 

3. Para generar el archivo .out de salida, se debe incluir el path en el comando de ejecución de la siguiente forma. Ejemplo: 
```bash
./main ./data/pequenas/instance4A.dat > ./results/instance4A.out
```
se debe comprobar que el directorio de destino existe.