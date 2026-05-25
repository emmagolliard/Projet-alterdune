#include "Game.h"
#include <iostream>
using namespace std;

/// Point d'entrée du programme.
/// Crée le jeu, charge les fichiers CSV puis lance le menu principal.
int main() {

    /// Demande du nom du joueur.
    string nom;
    cout << "Nom du joueur: ";
    cin >> nom;

    /// Création de l'objet Game avec le nom du joueur.
    Game jeu(nom);

    /// Chargement des données du jeu.
    jeu.chargerItems();
    jeu.chargerMonstres();

    /// Lancement du menu principal.
    jeu.menuPrincipal();

    return 0;
}