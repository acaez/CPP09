# CPP06 - Ex00 : ScalarConverter

## But de l'exercice
Créer une classe `ScalarConverter` avec une méthode statique `convert` qui prend un littéral C++ en
string et l'affiche converti en `char`, `int`, `float`, `double`.

## Contraintes clés
- Classe **non-instanciable** (constructeurs privés)
- Orthodox Canonical Form
- C++98, pas de STL

## Théorie : Les casts C++

### `static_cast<T>(expr)` ← UTILISÉ ICI
- Conversions "normales" entre types compatibles
- Conversions numériques (int↔float↔double↔char)

### `dynamic_cast<T>(expr)`
- Pour les hiérarchies polymorphiques (classes avec virtual)
- Retourne nullptr si échec (pointeurs) ou throw bad_cast (références)

### `const_cast<T>(expr)`
- Ajouter/retirer const ou volatile
- Seul cast qui peut retirer const

### `reinterpret_cast<T>(expr)`
- Réinterprète les bits bruts
- Dangereux, bas niveau
- Ex: pointeur → int

## Flow de l'algorithme

```
Input string
     │
     ▼
┌─────────────────┐
│ Detect type:    │
│ 1. pseudo?      │ → nan, inf, etc.
│ 2. char?        │ → single char (not digit)
│ 3. int?         │ → digits only (± prefix ok)
│ 4. float?       │ → has '.' AND ends with 'f'
│ 5. double?      │ → has '.' (no 'f')
│ 6. invalid      │
└─────────────────┘
     │
     ▼
Convert to double (valeur intermédiaire)
     │
     ▼
┌─────────────────┐
│ Print each:     │
│ • char          │ → impossible si hors [0,127] ou nan/inf
│ • int           │ → impossible si overflow ou nan/inf
│ • float         │ → toujours possible (precision loss ok)
│ • double        │ → toujours possible
└─────────────────┘
```

## Cas spéciaux à gérer

| Input | char | int | float | double |
|-------|------|-----|-------|--------|
| `0` | Non displayable | 0 | 0.0f | 0.0 |
| `42` | '*' | 42 | 42.0f | 42.0 |
| `nan` | impossible | impossible | nanf | nan |
| `+inf` | impossible | impossible | +inff | +inf |
| `a` | 'a' | 97 | 97.0f | 97.0 |
| `2147483648` | impossible | impossible | ok | ok |

## Headers importants
```cpp
#include <limits>    // numeric_limits, INT_MIN/MAX
#include <cmath>     // isnan(), isinf()
#include <iomanip>   // setprecision()
#include <cstdlib>   // atof(), atoll()
```

## Pour la défense
**Q: Pourquoi `static_cast` ?**
→ C'est le cast pour les conversions standard entre types numériques. Il est vérifié à la compilation
et exprime clairement l'intention de convertir.

**Q: Pourquoi la classe est non-instanciable ?**
→ Elle ne stocke rien, elle a juste une fonction utilitaire statique. Pas besoin d'objet.

**Q: Comment tu détectes le type ?**
→ Par ordre de spécificité : pseudo-literals → char → int → float → double
