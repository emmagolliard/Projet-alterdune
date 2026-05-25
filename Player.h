#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Item.h"
using namespace std;

/// Représente le joueur principal du jeu.
/// Cette classe hérite de Entity et gère l'inventaire, les combats et les statistiques.
class Player : public Entity {
private:

    /// Inventaire du joueur contenant jusqu'à 20 items.
    Item inventaire[20];

    /// Informations de progression du joueur :  nombre d'items/ monstres tués/ monstres épargnés/ nombre total de victoires
    int nombreItems;
    int monstresTues;
    int monstresEpargnes;
    int victoires;

public:

    /// Initialise le joueur avec son nom et ses HP.
    Player(string n);

    /// Attaque une cible et inflige des dégâts.
    void attaquer(Entity& cible);

    /// Gestion de l'inventaire : ajout et utilisation des objets.
    void ajouterItem(Item item);
    void utiliserItem(int index);

    /// Retourne un pointeur vers un item de l'inventaire.
    Item* getItem(int index);

    /// Affiche le contenu de l'inventaire.
    void afficherInventaire();

    /// Vérifie si le joueur possède encore des items.
    bool aDesItems();

    /// Mise à jour des statistiques après les combats.
    void ajouterMonstreTue();
    void ajouterMonstreEpargne();
    void ajouterVictoire();

    /// Getters des statistiques du joueur.
    int getMonstresTues();
    int getMonstresEpargnes();
    int getVictoires();

    /// Affiche les statistiques du joueur.
    void afficherStats();

    /// Remet les HP du joueur au maximum.
    void reset();
};

#endif