#ifndef MONSTER_H
#define MONSTER_H

#include "Entity.h"
#include <string>
using namespace std;

/// Classe abstraite représentant un monstre du jeu.
/// Elle hérite de Entity et ajoute les mécaniques de combat, Mercy et ACT.
class Monster : public Entity {
protected:

    /// Informations principales du monstre : catégorie/ attaque/ défense/ Mercy actuelle/ objectif Mercy
    string categorie;
    int attaque;
    int defense;
    int mercy;
    int mercyObjectif;

    /// Liste des actions ACT disponibles pour le monstre.
    string actionsDisponibles[4];

public:

    /// Initialise un monstre avec ses statistiques.
    Monster(string cat, string n, int hp, int atk, int def, int m);

    /// Attaque le joueur et inflige des dégâts.
    void attaquer(Entity& cible);

    /// Modifie la Mercy selon l'action ACT utilisée.
    void recevoirAct(int impact);

    /// Vérifie si le monstre peut être épargné.
    bool peutEpargner();

    /// Définit une action ACT du monstre.
    void setAction(int index, string action);

    /// Getters des informations du monstre.
    string getNom();
    string getCategorie();
    int getAttaque();
    int getDefense();
    int getMercy();
    int getMercyObjectif();
    string getAction(int index);

    /// Méthode virtuelle pure : chaque catégorie possède un nombre d'actions différent.
    virtual int getNbActions() = 0;

    /// Affiche les informations du monstre.
    void afficher();

    /// Remet les HP et la Mercy à zéro pour un nouveau combat.
    void reset();
};

/// Monstre classique possédant 2 actions ACT.
class MonstreNormal : public Monster {
public:
    MonstreNormal(string n, int hp, int atk, int def, int m);

    /// Retourne 2 actions ACT.
    int getNbActions();
};

/// MiniBoss possédant 3 actions ACT.
class MiniBoss : public Monster {
public:
    MiniBoss(string n, int hp, int atk, int def, int m);

    /// Retourne 3 actions ACT.
    int getNbActions();
};

/// Boss principal possédant 4 actions ACT.
class Boss : public Monster {
public:
    Boss(string n, int hp, int atk, int def, int m);

    /// Retourne 4 actions ACT.
    int getNbActions();
};

#endif