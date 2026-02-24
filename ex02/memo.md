# CPP06 - Ex02 : Identify real type

## But de l'exercice
Identifier le vrai type d'un objet polymorphique à runtime (A, B ou C) en ayant seulement un pointeur/référence vers la classe parente (Base).

## Hiérarchie de classes
```
        Base (virtual destructor)
       /  |  \
      A   B   C   (classes vides qui héritent de Base)
```

## Cast utilisé : `dynamic_cast`
C'est le cast pour les **hiérarchies polymorphiques**. Il vérifie le type à l'exécution (runtime).

## Code clé

### Avec pointeur → retourne `NULL` si échec
```cpp
void identify(Base* p) {
    if (dynamic_cast<A*>(p) != NULL)
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(p) != NULL)
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p) != NULL)
        std::cout << "C" << std::endl;
}
```

### Avec référence → throw exception si échec
```cpp
void identify(Base& p) {
    try {
        (void)dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
        return;
    } catch (...) {}

    try {
        (void)dynamic_cast<B&>(p);
        std::cout << "B" << std::endl;
        return;
    } catch (...) {}

    try {
        (void)dynamic_cast<C&>(p);
        std::cout << "C" << std::endl;
    } catch (...) {}
}
```

## Fonctionnement de `dynamic_cast`
```
Base* ptr = new A();  // ptr pointe vers un objet de type A

dynamic_cast<A*>(ptr)  → retourne le pointeur (cast réussi)
dynamic_cast<B*>(ptr)  → retourne NULL (cast échoué)
dynamic_cast<C*>(ptr)  → retourne NULL (cast échoué)
```

## Points clés pour la défense

### Pourquoi `virtual ~Base()` ?
`dynamic_cast` ne fonctionne **qu'avec des classes polymorphiques** (qui ont au moins une fonction virtuelle). Sans le destructeur virtuel, le code ne compile pas.

### Différence pointeur vs référence ?
| Type | En cas d'échec |
|------|----------------|
| `dynamic_cast<A*>(ptr)` | Retourne `NULL` |
| `dynamic_cast<A&>(ref)` | Throw `std::bad_cast` |

### Pourquoi on peut pas utiliser de pointeur dans `identify(Base& p)` ?
Le sujet l'interdit. On doit utiliser try/catch avec des références.

### Pourquoi `typeinfo` est interdit ?
Le sujet veut qu'on utilise `dynamic_cast` pour comprendre le RTTI (Run-Time Type Information). `typeid()` serait trop facile.

### C'est quoi le `(void)` devant le cast ?
```cpp
(void)dynamic_cast<A&>(p);
```
Ça évite le warning "unused value". On s'en fout de la valeur retournée, on veut juste savoir si ça throw ou pas.

### Pourquoi pas d'Orthodox Canonical Form ?
Le sujet dit explicitement que ce n'est pas requis pour cet exercice.

## Rappel des 4 casts C++

| Cast | Usage |
|------|-------|
| `static_cast` | Conversions standards (ex00) |
| `reinterpret_cast` | Réinterpréter les bits (ex01) |
| `dynamic_cast` | Hiérarchies polymorphiques (ex02) |
| `const_cast` | Ajouter/retirer const |
