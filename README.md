### Trabalho de Algoritmos e Estrutura de Dados 2
##### Lista estática de registros em arquivo binário. 
O intuito do projeto foi exercitar a orientação a objetos e práticar a programação orientada a objetos e C++.

### Compilar

#### Windowns com CMake e MinGW
``` 
cmake -S . -B build/ -G"MinGW Makefiles"
cmake --build build
```
#### Linux e derivados 
``` 
cmake -S . -B build
cmake --build build
```
##### Usando o Ninja
``` 
cmake -S . -B build -G Ninja
cmake --build build
```
