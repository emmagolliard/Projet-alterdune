#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <iostream>
using namespace std;

/// Classe abstraite représentant une entité du jeu.
/// Une entité possède un nom et des points de vie.
/// Cette classe sert de base pour Player et Monster.
class Entity {
protected:

    /// Informations principales de l'entité : nom/ HP actuels/ HP maximum
    string nom;
    int hpActuel;
    int hpMax;

public:

    /// Initialise une entité avec un nom et des HP.
    Entity(string n, int hp);

    /// Méthode virtuelle pure : chaque classe dérivée doit définir sa propre attaque.
    virtual void attaquer(Entity& cible) = 0;

    /// Gestion des dégâts et de l'état de vie.
    void recevoirDegats(int degats);
    bool estVivant();

    /// Affiche les informations de l'entité.
    void afficher();

    /// Getters des HP.
    int getHpMax() {
        return hpMax;
    }

    int getHpActuel() {
        return hpActuel;
    }
};

#endif