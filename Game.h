#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Monster.h"
#include <vector>
#include <string>
using namespace std;

/// Classe principale qui gère le déroulement du jeu.
/// Elle s'occupe du menu, des combats, du chargement des fichiers,du bestiaire, des statistiques et de la fin de partie.
class Game {
private:

    /// Joueur principal de la partie.
    Player joueur;

    /// Liste des monstres chargés depuis monsters.csv.
    /// Les pointeurs permettent de gérer plusieurs types de monstres.
    vector<Monster*> monstres;

    /// Données du bestiaire : on garde les informations des monstres déjà vaincus.
    vector<string> nomsVaincus;
    vector<string> categoriesVaincus;
    vector<int> hpVaincus;
    vector<int> attaquesVaincus;
    vector<int> defensesVaincus;
    vector<string> resultatsVaincus;

public:

    /// Initialise le jeu avec le nom du joueur.
    Game(string nom);

    /// Chargement des données depuis les fichiers CSV.
    void chargerItems();
    void chargerMonstres();

    /// Menu principal et affichages hors combat.
    void menuPrincipal();
    void afficherBestiaire();
    void afficherStats();
    void afficherItems();

    /// Gestion du combat tour par tour.
    void lancerCombat(Monster* monstre);
    void tourJoueur(Monster* monstre);
    void tourMonstre(Monster* monstre);

    /// Ajoute un monstre vaincu au bestiaire avec son résultat.
    void ajouterAuBestiaire(Monster* monstre, string resultat);

    /// Catalogue des actions ACT : donne l'effet sur Mercy et le texte affiché.
    int effetAction(string action);
    string texteAction(string action);

    /// Affiche la fin selon les choix du joueur.
    void finJeu();
};

#endif