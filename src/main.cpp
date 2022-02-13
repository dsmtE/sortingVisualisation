#include "core/SortingArrayApp.hpp"
#include "core/PrimitiveWrapper.hpp"

#include <vector>
#include <algorithm>

// un vector est une classe de la librairie standard se manipule comme un tableau (https://en.cppreference.com/w/cpp/container/vector)
// Plus exactement c'est un tableau dynamique(qui peut s'agrandir) mais nous nous en préoccupons pas ici.
// Vous pouvez donc acceder aux valeurs en faisant tableau[i] par exemple.

// PrimitiveWrapper<float> est une class custom que j'ai faite qui permet à la visualisation de fonctionner.
// Ne vous en preoccupez pas, vous pouvez le manipuler comme si c'était un float directement et cela va marcher.
// La visualisation fonctionne de sorte à marquer un petit temps de pause à chaque assignation (un égal: changement d'une des valeurs dans le tableau)
// la méthode swap est un raccourci que j'ai fait pour vous qui permet directement d'échanger deux valeurs
// (et marquer qu'un temps de pause au lieu de deux si vous le faisiez à la main(voir exemple dans le bubble sort))

// Voilà un exemple du bubble sort (un algo de tri très connu)

void BubbleSort(std::vector<PrimitiveWrapper<float>>& array) {
    std::cout << "Bubble Sort" << std::endl;
    const size_t size = array.size();
    for (size_t i = 1; i < size; i++) {
        for (size_t j = 0; j < size - i; j++) {
            if (array[j] > array[j + 1]) {
                // float temp = array[j];
                // array[j] = array[j + 1];
                // array[j + 1] = temp;

                // fonction de la librairie standard qui revient à faire la même chose que ci-dessus
                // std::swap(array[j] , array[j + 1]);

                // fonction custom pour swap avec un seul temps de pause pour la visualisation
                array[j].swap(array[j + 1]);
            }
        }
    }
}

// A vous de jouer et écrire vos fonctions de tri ici :

// il vous suffit d'écrire votre propre fonction de tri et remplacer juste ici
// appuyer sur la touche "s" permet de lancer la fonction de tri
// appuyer sur "g" permet de générer de nouvelles valeurs aléatoires.

int main() {

    const int arraySize = 500;
    const double nsDelay = 0.00005;
    SortingArrayApp app(arraySize, nsDelay, BubbleSort);
}
