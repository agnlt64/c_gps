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
│       main.c
│       repl.c
│       repl.h
│       sorting.c
│       sorting.h
│       utils.c
│       utils.h
│
└───tests
        capitales.csv
        data.csv
```
Avant d'ajouter une fonction dans un fichier `.c`, il est impératif de la déclarer dans le fichier d'en-tête correspondant, avec un commentaire expliquant ce qu'elle fait.

# Documentation
`city.c`, `city.h` 
Ces fichiers sont en charge de la gestion des données du fichier CSV. Chaque ligne du fichier CSV est représentée par une instance de la structure `City`, et l'ensemble du fichier est représenté par un tableau dynamique d'objets `City`.  
Structure `City` :
```c
typedef struct {
    int    code;
    char*  name;
    double latitude;
    double longitude;
} City;

```
Structure du tableau dynamique : 
```c
typedef struct {
    City* items;
    size_t count;
    size_t capacity;
} City_Array;
```
`items` contient les instances de la structure `City`, `count` indique le nombre d'éléments dans le tableau dynamique et `capacity` indique la taille maximale du tableau. Si le tableau est plein, `capacity` est doublée.  

`sorting.c`, `sorting.h`  
Ces fichiers contiennent des algorithmes de tri pour trier les villes de différentes manières. Les fonctions préfixées d'un `_` sont uniquement à usage interne. Deux algorithmes de tri sont implémentés : le `merge_sort` et le `cocktail_shaker_sort`. Par défaut, le `merge_sort` est utilisé. Pour utiliser le `cocktail_shaker_sort`, il faut définir la macro `COCKTAIL_SHAKER` lors de la compilation. Pour simplifier le code, les deux algorithmes sont réunis sous la même macro `sort(arr, cmp)`. `arr` est le tableau à trier et `cmp` est une ville (type `City`). Voir le code de test de ce module dans `sorting.c` pour plus de détails d'utilisation. Pour tester ce module, compiler avec la commande suivante :
```console
gcc src/sorting.c src/city.c src/utils.c -o sorting -DTESTING # -DCOCKTAIL_SHAKER pour le cocktail shaker sort
```

`repl.c`, `repl.h`  
Ces fichiers sont en charge de l'interaction avec l'utilisateur en ligne de commande. La fonction principale est `repl()`, elle est en charge de l'interprétation des commandes. Liste des commandes :
```console
a - Ajoute une ville
s - Supprime une ville
m - Modifie les données d'une ville
l - Liste les villes
o - Calcule la distance à vol d'oiseau entre 2 villes
e - Exporte les données dans un fichier CSV
t - Trie les villes par rapport à leur distance au Pole Nord
r - Affiche la latitude et longitude d'une ville
h - Affiche l'aide
q - Quitte le programme
```
Si le programme est compilé avec le flag `DEBUG`, la commande `d` affiche des informations de debug dans la console.  
Les commandes qui modifient les données fonctionnent avec la fonction standard `scanf`, elles récupèrent les informations directement depuis la console.  

`utils.c`, `utils.c`  
Ces fichiers contiennent des constantes et des fonction utiles partout dans le projet. La macro `len(x)` renvoie la taille du tableau `x` et la fonction `int_len(n)` renvoie le nombre de chiffres du nombre `n` sans passer par des chaines de caractères (pour des raisons de performance).

`csv.c`, `csv.h`  
Ces fichiers servent à manipuler des fichiers CSV.

# Contribuer
Avant d'ajouter des fonctions au projet, il faut d'abord les déclarer dans le fichier d'en-tête correspondant (par exemple ajouter la déclaration d'une fonction de tri dans `city.h`). Pour les commits, les messages doivent ressembler à ça : `[module modifié] courte explication en anglais`. Exemple : `[city] add quicksort algorithm`.