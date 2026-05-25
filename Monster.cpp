#include "Monster.h"
#include <iostream>
#include <cstdlib>
using namespace std;

/// Constructeur de Monster.
/// Initialise les statistiques du monstre,sa catégorie, sa Mercy et ses actions ACT.
Monster::Monster(string cat, string n, int hp, int atk, int def, int m)
    : Entity(n, hp) {

    categorie = cat;
    attaque = atk;
    defense = def;
    mercy = 0;
    mercyObjectif = m;

    actionsDisponibles[0] = "";
    actionsDisponibles[1] = "";
    actionsDisponibles[2] = "";
    actionsDisponibles[3] = "";
}

/// Attaque la cible avec des dégâts aléatoires.
/// Les dégâts sont limités pour équilibrer le jeu.
void Monster::attaquer(Entity& cible) {
    int degats = rand() % 41;

    cout << "Le monstre inflige " << degats << " degats !" << endl;

    cible.recevoirDegats(degats);
}

/// Réinitialise le monstre avant un nouveau combat.
/// Les HP reviennent au maximum et la Mercy revient à 0.
void Monster::reset() {
    hpActuel = hpMax;
    mercy = 0;
}

/// Modifie la Mercy du monstre selon une action ACT.
/// La Mercy reste toujours entre 0 et mercyObjectif.
void Monster::recevoirAct(int impact) {
    mercy = mercy + impact;

    if (mercy < 0) {
        mercy = 0;
    }

    if (mercy > mercyObjectif) {
        mercy = mercyObjectif;
    }
}

/// Vérifie si le monstre peut être épargné.
bool Monster::peutEpargner() {
    return mercy >= mercyObjectif;
}

/// Définit une action ACT disponible pour le monstre.
void Monster::setAction(int index, string action) {
    if (index >= 0 && index < 4) {
        actionsDisponibles[index] = action;
    }
}

/// Getters des informations principales du monstre.
string Monster::getNom() {
    return nom;
}

string Monster::getCategorie() {
    return categorie;
}

int Monster::getAttaque() {
    return attaque;
}

int Monster::getDefense() {
    return defense;
}

int Monster::getMercy() {
    return mercy;
}

int Monster::getMercyObjectif() {
    return mercyObjectif;
}

/// Retourne une action ACT selon son index.
string Monster::getAction(int index) {
    if (index >= 0 && index < 4) {
        return actionsDisponibles[index];
    }
    return "";
}

/// Affiche les informations du monstre.
void Monster::afficher() {
    cout << nom << " (" << categorie << ") HP: "
        << hpActuel << "/" << hpMax
        << " Mercy: " << mercy << "/" << mercyObjectif << endl;
}

/// Constructeur d'un monstre normal.
MonstreNormal::MonstreNormal(string n, int hp, int atk, int def, int m)
    : Monster("NORMAL", n, hp, atk, def, m) {
}

/// Un monstre normal possède 2 actions ACT.
int MonstreNormal::getNbActions() {
    return 2;
}

/// Constructeur d'un miniboss.
MiniBoss::MiniBoss(string n, int hp, int atk, int def, int m)
    : Monster("MINIBOSS", n, hp, atk, def, m) {
}

/// Un miniboss possède 3 actions ACT.
int MiniBoss::getNbActions() {
    return 3;
}

/// Constructeur d'un boss.
Boss::Boss(string n, int hp, int atk, int def, int m)
    : Monster("BOSS", n, hp, atk, def, m) {
}

/// Un boss possède 4 actions ACT.
int Boss::getNbActions() {
    return 4;
}