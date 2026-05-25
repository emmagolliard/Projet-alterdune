#include "Entity.h"
#include <iostream>
using namespace std;

/// Constructeur : initialise le nom et les HP de l'entité.
Entity::Entity(string n, int hp) {
    nom = n;
    hpActuel = hp;
    hpMax = hp;
}

/// Retire des points de vie à l'entité.
/// Les HP ne peuvent pas devenir négatifs.
void Entity::recevoirDegats(int degats) {
    hpActuel = hpActuel - degats;

    if (hpActuel < 0) {
        hpActuel = 0;
    }
}

/// Vérifie si l'entité est encore en vie.
bool Entity::estVivant() {
    return hpActuel > 0;
}

/// Affiche le nom et les HP de l'entité.
void Entity::afficher() {
    cout << nom << " HP: " << hpActuel << "/" << hpMax << endl;
}