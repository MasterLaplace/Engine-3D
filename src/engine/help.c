/*
** ME PROJECT, 2022
** DEN-GINER-Master-Laplace
** File description:
** help
*/

#include "engine.h"

#ifdef COMPILED_AS_SHARED_LIBRARY
static const char *help[] = {
    "UTILISATION\n\t./bin/engine.out [-h | --help]\n\nDESCRIPTION\n",
    "\t-h\tafficher ce guide.\n",
    "ENGINE-3D est un moteur de jeu d'aventures. Des assets personnalisés peuvent être importés.\n\n",
    "INTERACTIONS\n",
    "\tESC: fermer la fenêtre.",
    "\tZ: aller en avant.",
    "\tS: aller en arrière.",
    "\tQ: regarder vers la gauche.",
    "\tD: regarder vers la droite.",
    "\tR: regarder vers le haut.",
    "\tF: regarder vers le bas.",
    "\tUP: aller vers le haut.",
    "\tDOWN: aller vers le bas.",
    "\tCTRL + Z|S: courrir.",
    "\tSPACE: sauter.\n",
    "Engine programmé en C avec la librairie graphique CSFML.",
    "Plus d'informations sur la page github du projet: https://github.com/MasterLaplace/Engine-3D\n",
    "Réalisé par MasterLaplace.",
    NULL
};

bool print_help(int ac, char const *av[])
{
    if (ac != 2)
        return false;
    if (strcmp(av[1], "-h") && strcmp(av[1], "--help"))
        return false;
    two_put(help);
    return true;
}
#endif
