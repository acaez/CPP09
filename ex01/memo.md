# CPP06 - Ex01 : Serialization

## But de l'exercice
Interpreter une adresse en decimal et revenir a cette adresse sans changer l objet original

## Fonctionnement
```
Data original (id=42, name="Flash")
        │
        ▼
   ┌─────────────┐
   │ 0x16d9ff0f0 │  ←── adresse (hexadécimal)
   └─────────────┘
        │
   serialize()  ←── reinterpret_cast<uintptr_t>
        │
        ▼
   ┌─────────────┐
   │ 6134165744  │  ←── même valeur en décimal
   └─────────────┘
        │
   deserialize()  ←── reinterpret_cast<Data*>
        │
        ▼
   ┌─────────────┐
   │ 0x16d9ff0f0 │  ←── retour à l'adresse
   └─────────────┘
        │
        ▼
Data original (id=42, name="Flash")  ←── MÊME objet, jamais touché
```

## Code clé
```cpp
uintptr_t Serializer::serialize(Data* ptr) {
    return reinterpret_cast<uintptr_t>(ptr);  // pointeur → entier
}

Data* Serializer::deserialize(uintptr_t raw) {
    return reinterpret_cast<Data*>(raw);      // entier → pointeur
}
```

## Points clés pour la défense

### Pourquoi `reinterpret_cast` ?
C'est le **seul cast** qui permet de convertir entre pointeur et entier. Il réinterprète les bits
sans les modifier.

### C'est quoi `uintptr_t` ?
Un type entier **non-signé** garanti assez grand pour stocker n'importe quelle adresse mémoire.
Défini dans `<stdint.h>`.

### Pourquoi ça marche ?
Un pointeur c'est juste un nombre (une adresse). On change pas la valeur, on change juste comment le
compilateur l'interprète :
```
0x16d9ff0f0 (pointeur) == 6134165744 (entier)  // même valeur !
```

### Pourquoi la classe Serializer est non-instanciable ?
Elle ne stocke rien. C'est juste un conteneur pour des fonctions utilitaires statiques.

### Pourquoi `Data` doit être non-empty ?
Pour **prouver** que la désérialisation fonctionne. Si on peut accéder aux membres
(`id`, `name`, `value`) après désérialisation, ça prouve qu'on pointe bien vers le même objet.

### Question piège : l'objet est copié ?
**Non !** L'objet ne bouge jamais. On manipule uniquement son adresse.

### Utilité dans la vraie vie ?
Sauvegarder des pointeurs dans un fichier, les envoyer sur le réseau, ou les stocker dans des
structures qui n'acceptent que des entiers.
