#include "Player.h"
#include <iostream>
#include <cstdlib>
using namespace std;

/// Constructeur de Player.
/// Initialise le joueur avec 100 HP et remet toutes ses statistiques à 0.
Player::Player(string n) : Entity(n, 100) {
    nombreItems = 0;
    monstresTues = 0;
    monstresEpargnes = 0;
    victoires = 0;
}

/// Attaque une cible avec des dégâts aléatoires.
/// Les dégâts dépendent des HP maximum de la cible.
void Player::attaquer(Entity& cible) {
    int degats = rand() % (cible.getHpMax() + 1);
    cout << "Tu infliges " << degats << " degats !" << endl;
    cible.recevoirDegats(degats);
}

/// Réinitialise les HP du joueur avant un nouveau combat.
void Player::reset() {
    hpActuel = hpMax;
}

/// Ajoute un item dans l'inventaire s'il reste de la place.
void Player::ajouterItem(Item item) {
    if (nombreItems < 20) {
        inventaire[nombreItems] = item;
        nombreItems = nombreItems + 1;
    }
}

/// Utilise un item de soin selon son index.
void Player::utiliserItem(int index) {
    if (index >= 0 && index < nombreItems) {
        inventaire[index].consommer(hpActuel, hpMax);
    }
}

/// Retourne un pointeur vers un item de l'inventaire.
/// Retourne nullptr si l'index est invalide.
Item* Player::getItem(int index) {
    if (index >= 0 && index < nombreItems) {
        return &inventaire[index];
    }
    return nullptr;
}

/// Affiche tous les items présents dans l'inventaire.
void Player::afficherInventaire() {
    if (nombreItems == 0) {
        cout << "Inventaire vide" << endl;
    }

    int i = 0;
    while (i < nombreItems) {
        cout << i + 1 << ". ";
        inventaire[i].afficher();
        i = i + 1;
    }
}

/// Vérifie si le joueur possède au moins un item.
bool Player::aDesItems() {
    return nombreItems > 0;
}

/// Ajoute un monstre tué aux statistiques.
void Player::ajouterMonstreTue() {
    monstresTues = monstresTues + 1;
}

/// Ajoute un monstre épargné aux statistiques.
void Player::ajouterMonstreEpargne() {
    monstresEpargnes = monstresEpargnes + 1;
}

/// Ajoute une victoire au joueur.
void Player::ajouterVictoire() {
    victoires = victoires + 1;
}

/// Retourne le nombre de monstres tués.
int Player::getMonstresTues() {
    return monstresTues;
}

/// Retourne le nombre de monstres épargnés.
int Player::getMonstresEpargnes() {
    return monstresEpargnes;
}

/// Retourne le nombre de victoires.
int Player::getVictoires() {
    return victoires;
}

/// Affiche les statistiques principales du joueur.
void Player::afficherStats() {
    cout << "Nom: " << nom << endl;
    cout << "HP: " << hpActuel << "/" << hpMax << endl;
    cout << "Victoires: " << victoires << "/10" << endl;
    cout << "Monstres tues: " << monstresTues << endl;
    cout << "Monstres epargnes: " << monstresEpargnes << endl;
}