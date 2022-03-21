# kohonen_som
#
> Som : 

* Chaque point de données dans l'ensemble de données se reconnaît en se disputant la représentation. 
Les étapes de mappage SOM commencent par l'initialisation des vecteurs de poids. 
À partir de là, un vecteur d'échantillon est sélectionné au hasard et la carte des vecteurs de poids est recherchée pour trouver quel poids représente le mieux cet échantillon. 
Chaque vecteur de poids a des poids voisins qui lui sont proches. Le poids choisi est récompensé en pouvant ressembler davantage à ce vecteur d'échantillon sélectionné au hasard. 
Les voisins de ce poids sont également récompensés en pouvant ressembler davantage au vecteur échantillon choisi. Cela permet à la carte de se développer et de former différentes formes. 
Le plus généralement, ils forment des formes carrées/rectangulaires/hexagonales/L dans l'espace des caractéristiques 2D

#    
 

> L'algorithme : 

* Les poids de chaque nœud sont initialisés.
* Un vecteur est choisi au hasard dans l'ensemble des données d'apprentissage.
* Chaque nœud est examiné pour calculer lequel de ses poids ressemble le plus au vecteur d'entrée. Le nœud gagnant est communément appelé la meilleure unité correspondante (BMU).
* Ensuite, le voisinage de la BMU est calculé. Le nombre de voisins diminue avec le temps.
* Le poids gagnant est récompensé en devenant plus comme le vecteur échantillon. Les voisins deviennent également plus comme le vecteur échantillon. Plus un nœud est proche du BMU, plus ses poids sont modifiés et plus le voisin est éloigné du BMU, moins il apprend.
* Répétez les étapes pour N itérations.

#

> Installation :
    
    Requirements: SDL
    
    Run SOM:   
        compilation : make
        execution : make run 
#
> Démonstration :

![Alt Text](https://github.com/mir-ak/kohonen_som/blob/main/Som_classique/image_som.png)
![Alt Text](https://github.com/mir-ak/kohonen_som/blob/main/Som_version_Graphique_SDL/image_som.png)
