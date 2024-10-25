# GPS en C
Programme en C réalisé dans le cadre des SAÉs 1.01 & 1.02 de l'IUT informatique d'Amiens.

# Build
```console
gcc src/*.c -o main # use -DDEBUG to have the special `d` command, useful to display debug infos
./main tests/data.csv
```

# Structure du projet
```console
│   .gitignore
│   LICENSE
│   README.md
│
├───src
│       city.c
│       city.h
│       csv.c
│       csv.h
│       defines.h
│       main.c
│       repl.c
│       repl.h
│
└───tests
        data.csv
```
Avant d'ajouter une fonction dans un fichier `.c`, il est impératif de la déclarer dans le fichier d'en-tête correspondant, avec un commentaire expliquant ce qu'elle fait.

# Documentation
