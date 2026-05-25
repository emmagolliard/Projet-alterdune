#include "Game.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
using namespace std;

/// Constructeur de Game.
/// Initialise le joueur et prépare l'aléatoire utilisé dans les combats.
Game::Game(string nom) : joueur(nom) {
    srand(time(0));
}

/// Charge les items depuis le fichier items.csv.
/// Chaque ligne valide crée un Item ajouté à l'inventaire du joueur.
void Game::chargerItems() {
    ifstream fichier("items.csv");

    if (!fichier.is_open()) {
        cout << "Erreur : items.csv introuvable." << endl;
        return;
    }

    string ligne;
    getline(fichier, ligne);

    while (getline(fichier, ligne)) {
        stringstream ss(ligne);

        string nom, type, valeur, quantite;

        getline(ss, nom, ';');
        getline(ss, type, ';');
        getline(ss, valeur, ';');
        getline(ss, quantite, ';');

        if (nom != "" && type != "" && valeur != "" && quantite != "") {
            joueur.ajouterItem(Item(nom, type, stoi(valeur), stoi(quantite)));
        }
    }

    fichier.close();
}

/// Charge les monstres depuis le fichier monsters.csv.
/// Selon la catégorie, le programme crée un MonstreNormal, un MiniBoss ou un Boss.
void Game::chargerMonstres() {
    ifstream fichier("monsters.csv");

    if (!fichier.is_open()) {
        cout << "Erreur : monsters.csv introuvable." << endl;
        return;
    }

    string ligne;
    getline(fichier, ligne);

    while (getline(fichier, ligne)) {
        stringstream ss(ligne);

        string categorie, nom, hp, atk, def, mercy;
        string act1, act2, act3, act4;

        getline(ss, categorie, ';');
        getline(ss, nom, ';');
        getline(ss, hp, ';');
        getline(ss, atk, ';');
        getline(ss, def, ';');
        getline(ss, mercy, ';');
        getline(ss, act1, ';');
        getline(ss, act2, ';');
        getline(ss, act3, ';');
        getline(ss, act4, ';');

        if (categorie == "" || nom == "" || hp == "" || atk == "" || def == "" || mercy == "") {
            continue;
        }

        Monster* monstre = nullptr;

        if (categorie == "NORMAL") {
            monstre = new MonstreNormal(nom, stoi(hp), stoi(atk), stoi(def), stoi(mercy));
        }
        else if (categorie == "MINIBOSS") {
            monstre = new MiniBoss(nom, stoi(hp), stoi(atk), stoi(def), stoi(mercy));
        }
        else if (categorie == "BOSS") {
            monstre = new Boss(nom, stoi(hp), stoi(atk), stoi(def), stoi(mercy));
        }

        if (monstre != nullptr) {
            monstre->setAction(0, act1);
            monstre->setAction(1, act2);
            monstre->setAction(2, act3);
            monstre->setAction(3, act4);

            monstres.push_back(monstre);
        }
    }

    fichier.close();
}

/// Affiche le menu principal du jeu.
/// Permet de lancer un combat, voir le bestiaire, consulter les statistiques, l'inventaire ou quitter.
void Game::menuPrincipal() {
    int choix = 0;

    while (joueur.getVictoires() < 10 && choix != 5) {
        cout << endl;
        cout << "        ***JEU***" << endl;
        cout << "1. Demarrer un combat" << endl;
        cout << "2. Bestiaire" << endl;
        cout << "3. Statistiques" << endl;
        cout << "4. Inventaire" << endl;
        cout << "5. Quitter" << endl;
        cout << "Choix : ";
        cin >> choix;

        cout << endl;

        if (choix == 1) {
            if (monstres.size() == 0) {
                cout << "Aucun monstre charge." << endl;
            }
            else {
                int index = rand() % monstres.size();

                /// On réinitialise le monstre et le joueur avant chaque combat.
                monstres[index]->reset();
                joueur.reset();

                if (joueur.getVictoires() >= 10) {
                    finJeu();
                    return;
                }

                lancerCombat(monstres[index]);
            }
        }
        else if (choix == 2) {
            afficherBestiaire();
        }
        else if (choix == 3) {
            afficherStats();
        }
        else if (choix == 4) {
            afficherItems();
        }
        else if (choix == 5) {
            cout << "Fin du programme." << endl;
        }
        else {
            cout << "Choix invalide." << endl;
        }
    }

    if (joueur.getVictoires() >= 10) {
        finJeu();
    }
}

/// Affiche le bestiaire des monstres déjà vaincus.
/// Le bestiaire indique aussi si le monstre a été tué ou épargné.
void Game::afficherBestiaire() {
    cout << "BESTIAIRE" << endl;

    if (nomsVaincus.size() == 0) {
        cout << "Aucun monstre vaincu pour le moment." << endl;
        return;
    }

    for (int i = 0; i < nomsVaincus.size(); i++) {
        cout << endl;
        cout << "Nom : " << nomsVaincus[i] << endl;
        cout << "Categorie : " << categoriesVaincus[i] << endl;
        cout << "HP max : " << hpVaincus[i] << endl;
        cout << "Attaque : " << attaquesVaincus[i] << endl;
        cout << "Defense : " << defensesVaincus[i] << endl;
        cout << "Resultat : " << resultatsVaincus[i] << endl;
    }
}

/// Affiche les statistiques du joueur.
void Game::afficherStats() {
    cout << "STATISTIQUES" << endl;
    joueur.afficherStats();
}

/// Affiche l'inventaire du joueur.
void Game::afficherItems() {
    cout << "INVENTAIRE" << endl;
    joueur.afficherInventaire();
}

/// Ajoute un monstre vaincu dans le bestiaire.
/// Le résultat indique si le monstre a été tué ou épargné.
void Game::ajouterAuBestiaire(Monster* monstre, string resultat) {
    nomsVaincus.push_back(monstre->getNom());
    categoriesVaincus.push_back(monstre->getCategorie());
    hpVaincus.push_back(monstre->getHpMax());
    attaquesVaincus.push_back(monstre->getAttaque());
    defensesVaincus.push_back(monstre->getDefense());
    resultatsVaincus.push_back(resultat);
}

/// Lance un combat contre un monstre.
/// Le combat continue tant que le joueur et le monstre sont vivants.
void Game::lancerCombat(Monster* monstre) {
    int numeroCombat = joueur.getVictoires() + 1;

    if (numeroCombat > 10) {
        numeroCombat = 10;
    }

    cout << endl;
    cout << "*** COMBAT " << numeroCombat << " / 10 ***" << endl;

    cout << "Un monstre apparait !" << endl;
    monstre->afficher();

    while (monstre->estVivant() && joueur.estVivant()) {
        cout << endl;
        joueur.afficher();
        monstre->afficher();

        tourJoueur(monstre);

        if (!monstre->estVivant()) {
            return;
        }

        if (monstre->peutEpargner()) {
            cout << "La Mercy est pleine. Tu peux epargner ce monstre." << endl;
        }

        tourMonstre(monstre);

        if (!joueur.estVivant()) {
            cout << "Tu as perdu..." << endl;
            return;
        }
    }
}

/// Gère le tour du joueur pendant un combat.
/// Le joueur peut choisir FIGHT, ACT, ITEM ou MERCY.
void Game::tourJoueur(Monster* monstre) {
    int choix;

    cout << endl;
    cout << "Que veux-tu faire ?" << endl;
    cout << "1. FIGHT" << endl;
    cout << "2. ACT" << endl;
    cout << "3. ITEM" << endl;
    cout << "4. MERCY" << endl;
    cout << "Choix : ";
    cin >> choix;

    if (choix == 1) {
        cout << "Tu attaques le monstre." << endl;
        joueur.attaquer(*monstre);

        if (!monstre->estVivant()) {
            joueur.ajouterMonstreTue();
            joueur.ajouterVictoire();
            ajouterAuBestiaire(monstre, "Tue");
            cout << "Victoire ! Le monstre est vaincu." << endl;
        }
    }

    else if (choix == 2) {
        cout << "Actions disponibles :" << endl;

        int nb = monstre->getNbActions();

        for (int i = 0; i < nb; i++) {
            cout << i + 1 << ". " << monstre->getAction(i) << endl;
        }

        int choixAct;
        cout << "Choix ACT : ";
        cin >> choixAct;

        if (choixAct >= 1 && choixAct <= nb) {
            string action = monstre->getAction(choixAct - 1);
            cout << texteAction(action) << endl;
            monstre->recevoirAct(effetAction(action));
        }
        else {
            cout << "Action invalide." << endl;
        }
    }

    else if (choix == 3) {
        joueur.afficherInventaire();

        int index;
        cout << "Choisis un item : ";
        cin >> index;

        Item* item = joueur.getItem(index - 1);

        if (item == nullptr) {
            cout << "Item invalide." << endl;
            return;
        }

        if (!item->estDisponible()) {
            cout << "Il ne reste plus cet item." << endl;
            return;
        }

        /// Les items ont des effets différents selon leur type.
        if (item->getType() == "HEAL") {
            joueur.utiliserItem(index - 1);
            cout << "Tu utilises " << item->getNom() << " et tu recuperes des HP." << endl;
        }
        else if (item->getType() == "DAMAGE") {
            cout << "Tu utilises " << item->getNom() << " et tu infliges "
                << item->getValeur() << " degats." << endl;

            monstre->recevoirDegats(item->getValeur());
            item->diminuerQuantite();
        }
        else if (item->getType() == "MERCY") {
            cout << "Tu utilises " << item->getNom()
                << " et la Mercy augmente de " << item->getValeur() << "." << endl;

            monstre->recevoirAct(item->getValeur());
            item->diminuerQuantite();
        }
        else if (item->getType() == "BUFF") {
            cout << "Tu utilises " << item->getNom()
                << ", mais l'effet BUFF sera ajoute plus tard." << endl;

            item->diminuerQuantite();
        }
        else {
            cout << "Type d'item inconnu." << endl;
        }
    }

    else if (choix == 4) {
        if (monstre->peutEpargner()) {
            joueur.ajouterMonstreEpargne();
            joueur.ajouterVictoire();
            ajouterAuBestiaire(monstre, "Epargne");
            monstre->recevoirDegats(9999);
            cout << "Tu epargnes le monstre." << endl;
        }
        else {
            cout << "Impossible de l'epargner pour le moment." << endl;
        }
    }

    else {
        cout << "Choix invalide." << endl;
    }
}

/// Gère le tour du monstre.
/// Si le monstre est encore vivant, il attaque le joueur.
void Game::tourMonstre(Monster* monstre) {
    cout << "Le monstre attaque !" << endl;
    monstre->attaquer(joueur);
}

/// Catalogue des effets des actions ACT.
/// Certaines actions augmentent la Mercy, d'autres la diminuent.
int Game::effetAction(string action) {
    if (action == "COMPLIMENT") return 50;
    if (action == "BLAGUE") return 45;
    if (action == "DANSE") return 40;
    if (action == "OBSERVE") return 35;
    if (action == "CONVERSATION") return 50;
    if (action == "CONFORT") return 45;
    if (action == "OEIL") return 30;

    if (action == "MARTEAU") return -25;
    if (action == "INSULTE") return -35;
    if (action == "POING") return -20;
    if (action == "CLAQUE") return -30;

    return 25;
}

/// Catalogue des textes affichés lors des actions ACT.
string Game::texteAction(string action) {
    if (action == "COMPLIMENT") return "Tu complimentes le monstre. Il rougit un peu.";
    if (action == "BLAGUE") return "Tu racontes une blague nulle. Le monstre hesite entre rire et pleurer.";
    if (action == "DANSE") return "Tu fais une danse bizarre. Le monstre est perturbe.";
    if (action == "OBSERVE") return "Tu observes calmement le monstre.";
    if (action == "CONVERSATION") return "Tu lances une conversation profonde.";
    if (action == "CONFORT") return "Tu rassures le monstre.";
    if (action == "MARTEAU") return "Tu sors un marteau imaginaire. Mauvaise idee.";
    if (action == "INSULTE") return "Tu insultes le monstre. Il s'enerve.";
    if (action == "POING") return "Tu menaces avec ton poing. Ambiance tendue.";
    if (action == "CLAQUE") return "Tu fais semblant de donner une claque.";
    if (action == "OEIL") return "Tu fixes le monstre sans cligner des yeux.";

    return "Tu fais une action etrange.";
}

/// Affiche la fin du jeu selon les choix du joueur.
void Game::finJeu() {
    cout << endl;
    cout << "FIN DU JEU" << endl;

    if (joueur.getMonstresTues() == 10) {
        cout << "Fin genocidaire" << endl;
    }
    else if (joueur.getMonstresEpargnes() == 10) {
        cout << "Fin pacifiste" << endl;
    }
    else {
        cout << "Fin neutre" << endl;
    }
}