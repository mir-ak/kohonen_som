#include "../include/iris_data.h"

/**
 * génére une valeur aleatoire entre deux valeur donner 
 * @param min la valeur min 
 * @param max la valeur min 
 * @return la valeur générer
 */

double Random(double min, double max)
{
	double val = 0.0;
	val = (double)rand() / (double)RAND_MAX * (max - min) + min;
	return val;
}

/**
 * initialiser (allocation mémoire) la structure N_CFG_t (Reseau) et aussi la structure node_t (map)
 * @param row la taille de la matrice (ligne) 
 * @param column lla taille de la matrice (colonne)
 * @return la structure N_CFG_t (Reseau) alloué 
 */

N_CFG_t *Init_Map(int row, int column)
{
	int i;
	N_CFG_t *_map = (N_CFG_t *)malloc(sizeof(N_CFG_t));
	_map->phases = (phase_t *)malloc(lenght_phase * sizeof(phase_t));
	if (_map == NULL && _map->phases == NULL)
	{
		printf("Échec de l'allocation\n");
		exit(0);
	}
	_map->row = row;
	_map->column = column;
	// 500
	_map->phases[0].rayon = first_rayon;
	_map->phases[0].nb_iteration = first_iteration;
	// 1500
	_map->phases[1].rayon = second_rayon;
	_map->phases[1].nb_iteration = second_iteration;
	_map->map = (node_t **)malloc(row * sizeof(node_t *));
	for (i = 0; i < row; i++)
	{
		_map->map[i] = (node_t *)malloc(column * sizeof(node_t));
		for (int j = 0; j < column; j++)
		{
			_map->map[i][j].weight = (double *)malloc(column_data_nb * sizeof(double));
		}
	}
	return _map;
}

/**
 * initialiser (allocation mémoire) la structure bmu (liste chainee)
 * @param index_row l'indice ligne de la matrice a stocker dans la liste 
 * @param index_col l'indice colonne de la matrice a stocker dans la liste 
 * @return la structure bmu (liste chainee)
 */

bmu_t *Init_bmu(int index_row, int index_col)
{
	bmu_t *bmu = (bmu_t *)malloc(sizeof(bmu_t));
	if (bmu == NULL)
	{
		printf("Échec de l'allocation\n");
		exit(0);
	}
	bmu->index_row = index_row;
	bmu->index_col = index_col;
	bmu->next = NULL;
	return bmu;
}

/**
 * ajouter (par devant ) les indice a la liste chainee a cote des anciens indice
 * cette fonction elle est utliser juste si on a deux ou plus de bmu exp : []->[]->[]->null
 * @param index_row l'indice ligne de la matrice a stocker dans la liste 
 * @param index_col l'indice colonne de la matrice a stocker dans la liste 
 * @return la structure bmu (liste chainee)
 */

bmu_t *Add_index_bmu_start(bmu_t *list_bmu, int row, int column)
{
	bmu_t *bmu = Init_bmu(row, column);
	bmu->next = list_bmu;
	return bmu;
}

/**
 * calculer la taille de la liste chainee
 * @param list_bmu la structure bmu (liste chainee) 
 * @return la taille de la liste 
 */

int Length_list(bmu_t *list_bmu)
{
	int nb = 0;
	while (list_bmu != NULL)
	{
		nb++;
		list_bmu = list_bmu->next;
	}
	return nb;
}

/**
 * génére un bmu (index_row & index_col) aleatoire entre 0 et la taille de la liste 
 * @param list_bmu la structure bmu (liste chainee)
 * @param lenght la taille de la liste  
 * @return la structure bmu (liste chainee) qui contient seulement un index_row & index_col
 */

bmu_t *Random_bmu(bmu_t *list_bmu, int lenght)
{
	int i;
	int val = rand() % (lenght - 1);
	bmu_t *copy_list_bmu;
	for (i = 0; i <= val; i++)
	{
		copy_list_bmu = Init_bmu(list_bmu->index_row, list_bmu->index_col);
		list_bmu = list_bmu->next;
	}
	return copy_list_bmu;
}

/**
 * affiche les donnees de la structure bmu (liste chainee)
 * @param list_bmu la structure bmu (liste chainee)
 */

void Display_bmu(bmu_t *bmu)
{
	bmu_t *copy_bmu = NULL;
	copy_bmu = bmu;
	while (copy_bmu != NULL)
	{
		printf("(bmb[i]= %d ; bmb[j] = %d) \n", copy_bmu->index_row, copy_bmu->index_col);
		copy_bmu = copy_bmu->next;
	}
}

/**
 * ajoute les valeurs dans la matrice de vecteur de notre structur node_t (map)
 * les valeurs sont generer aléatoirement avec notre moyenne de vecteur database et l'intervalle donner 
 * @param _map la structure N_CFG_t (Reseau)
 * @param vect la structure vecteur 
 */

void Add_values_to_map(N_CFG_t *_map, Vect_Data_t *vect)
{
	int i, j, value;
	double *tab_moy = Moyenne(vect);
	for (i = 0; i < _map->row; i++)
	{
		for (j = 0; j < _map->column; j++)
		{
			for (value = 0; value < vect->column; value++)
			{
				_map->map[i][j].weight[value] = Random(tab_moy[value] - 0.0002, tab_moy[value] + 0.0002);
			}

			_map->map[i][j].id = "X";
		}
	}
	free(tab_moy);
}

/**
 * affiche les donnees de la structure node_t (map) en notation scientifique (%e)
 * @param _map la structure N_CFG_t (Reseau)
 */
void Display_map(N_CFG_t *_map)
{
	int i, j, value;
	for (i = 0; i < _map->row; i++)
	{
		printf(" i = %d \n", i);
		for (j = 0; j < _map->column; j++)
		{
			printf(" j = %d \n", j);
			for (value = 0; value < column_data_nb; value++)
			{
				printf(" %e\n", _map->map[i][j].weight[value]);
			}
			printf(" %s\n", _map->map[i][j].id);
		}
	}
}

/**
 * initialiser (allocation mémoire) d'un tableau puis
 * remplir le tabaleu de 0 -> 149
 * @param size la taile de tableau
 * @return un tableau de 150 valeur (indice)
 */

int *Init_tab(int size)
{
	int i;
	int *tab_shuffle = (int *)malloc(size * sizeof(int));
	if (tab_shuffle == NULL)
	{
		printf("Échec de l'allocation\n");
		exit(0);
	}
	for (i = 0; i < size; i++)
	{
		tab_shuffle[i] = i;
	}
	return tab_shuffle;
}

/**
 * génére une valeur aleatoire entre deux valeur donner 
 * @param min la valeur min 
 * @param max la valeur min 
 * @return la valeur générer 
 */
int rand_int(int min, int max)
{
	return rand() % (max - min) + min;
}

/**
 * melanger les valeurs (indice) de tableau aléatoirement
 * @param tab tableau de 150 valeurs (indice)
 * @param size la taile de tableau
 */
void Shuffle_index(int *tab, int size)
{
	int tmp, i, Rand;
	srand(time(NULL));
	for (i = 0; i < size; i++)
	{
		Rand = rand_int(i, size);
		tmp = tab[i];
		tab[i] = tab[Rand];
		tab[Rand] = tmp;
	}
}

/**
 * calculer la distance euclidienne entre deux vecteur 
 * @param vect vecteur de donnees de la map 
 * @param vect2 vecteur de donnees de database
 * @param size la taille de ces vecteurs (taille = 4)
 * @return la distance 
 */

double Distance_euclidienne(double *vect, double *vect2, int size)
{
	int i;
	double distance = 0.0;
	for (i = 0; i < size; i++)
	{
		distance += (vect[i] - vect2[i]) * (vect[i] - vect2[i]);
	}
	distance = sqrt(distance);
	return distance;
}

int rayon_(N_CFG_t *_map, Vect_Data_t *vect, int rayon, int new_rayon, int count)
{

	if (count == new_rayon && rayon >= 1)
	{
		printf("rayon = %d \n\n", rayon);
		Display_label(_map, vect);
		count = 0;
		return rayon - 1;
	}
	return rayon;
}

/**
 * dans un premier temp c'est de trouve la distance plus petit entre la map et le vecteur database (melanger)
 * une fois la distance trouve on stocke les indice de la map (le bmu ) dans une liste chainee puis on regarde 
 * la taille de la liste si elle est supérieur a 1 dans ce cas on a plusieurs bmu donc on genere un aleatoirement 
 * sinon on calcule les extrémités (voisinage) de la nouvelle map a l'aide du bmu trouve et le rayon de voisinage
 * une fois on a determine le voisinage on parcourt les vecteur de cette nouvelle map et on change leur valeur 
 * a l'aide du la formule  wij_t1 = wij_t + alpha( xi - wij_t) sachant que alpha = alpha_initial*(1-(double)(t/t_total))
 * et alpha_init = 0.9 et aussi le rayon de voisingae decrement puis tout ca ce deroule dans une boucle for d'itération (500 puis 1500) 	
 * @param _map la structure N_CFG_t (Reseau)
 * @param vect la structure vecteur 
 * @param nb_iteration nombre d'itération pour la boucle for 
 */

void Learning(N_CFG_t *_map, Vect_Data_t *vect, int rayon, int nb_iteration)
{
	int t, row_vect, row_map, col_map;
	double min_distance;
	int length;
	int line_start, line_end;
	int column_start, column_end;
	int row, col, value;
	double alpha_init = 0.9;
	int new_rayon = (int)nb_iteration / rayon;
	int count = 0;
	int *tab = Init_tab(vect->row);
	for (t = 0; t < nb_iteration; t++)
	{
		Shuffle_index(tab, vect->row);
		_map->alpha = alpha_init * (1.0 - ((double)t / (double)nb_iteration));
		if (count == new_rayon && rayon >= 1)
		{
			printf("rayon = %d \n\n", rayon);
			Display_label(_map, vect);
			rayon -= 1;
			count = 0;
		}
		for (row_vect = 0; row_vect < vect->row; row_vect++)
		{
			min_distance = 100.0;
			for (row_map = 0; row_map < _map->row; row_map++)
			{
				for (col_map = 0; col_map < _map->column; col_map++)
				{
					_map->map[row_map][col_map].act = Distance_euclidienne(_map->map[row_map][col_map].weight, vect[tab[row_vect]].vec, vect->column);
					if (_map->map[row_map][col_map].act <= min_distance)
					{
						if (_map->map[row_map][col_map].act < min_distance)
						{
							Free_list(_map->bmu);
							_map->bmu = Init_bmu(row_map, col_map);
						}
						if (min_distance == _map->map[row_map][col_map].act)
						{
							_map->bmu = Add_index_bmu_start(_map->bmu, row_map, col_map);
						}
						min_distance = _map->map[row_map][col_map].act;
					}
				}
			}
			length = Length_list(_map->bmu);
			if (length > 1)
			{
				_map->bmu = Random_bmu(_map->bmu, length);
			}

			if (_map->bmu->index_row - rayon < 0)
			{
				line_start = 0;
			}
			else
			{
				line_start = _map->bmu->index_row - rayon;
			}

			if (_map->bmu->index_row + rayon < _map->row)
			{
				line_end = _map->bmu->index_row + rayon;
			}
			else
			{
				line_end = _map->row - 1;
			}

			if (_map->bmu->index_col - rayon < 0)
			{
				column_start = 0;
			}
			else
			{
				column_start = _map->bmu->index_col - rayon;
			}

			if (_map->bmu->index_col + rayon < _map->column)
			{
				column_end = _map->bmu->index_col + rayon;
			}
			else
			{
				column_end = _map->column - 1;
			}
			for (row = line_start; row <= line_end; row++)
			{
				for (col = column_start; col <= column_end; col++)
				{
					for (value = 0; value < vect->column; value++)
					{
						_map->map[row][col].weight[value] += _map->alpha * (vect[tab[row_vect]].vec[value] - _map->map[row][col].weight[value]);
					}
				}
			}
		}
		count++;
	}
	free(tab);
}

/**
 * on appelle la fonction Learning avec deux phases 
 * 1er phase avec r = 3 et nb_iteratipn = 500 
 * 2em phase avec r = 1 et nb_iteratipn = 1500
 * @param _map la structure N_CFG_t (Reseau)
 * @param vect iteration actual 
 */

void Call_learning(N_CFG_t *_map, Vect_Data_t *vect)
{
	int i;
	for (i = 0; i < lenght_phase; i++)
	{
		Learning(_map, vect, _map->phases[i].rayon, _map->phases[i].nb_iteration);
	}
}

/**
 * on affiche les etiquette de notre map apres avoir fait l'apprentissage  dans un premier temp c'est de trouve la distance plus petit entre la map et le vecteur database
 * une fois la distance trouve on stocke les indice de vecteur puis on recuper etiquette de ce veteur 
 * a l'aide de l'indice qu'on a trouve puis on met cette etiquette a notre vecteur de ID de la map 
 * puis a chaque fois qu'on rencontre une etiquette de:
 * - Iris-setosa on affiche S 
 * - Iris-versicolor on affiche C
 * - Iris-virginica on affiche V
 * @param _map la structure N_CFG_t (Reseau)
 * @param vect la structure vecteur 
 */

void Display_label(N_CFG_t *_map, Vect_Data_t *vect){
	int row_vect, row_map, col_map;
	for (row_map = 0; row_map < _map->row; row_map++)
	{
		for (col_map = 0; col_map < _map->column; col_map++)
		{
			double min_dist = 100.0;
			int index = 0;
			for (row_vect = 0; row_vect < vect->row; row_vect++)
			{
				double distance = Distance_euclidienne(_map->map[row_map][col_map].weight, vect[row_vect].vec, vect->column);
				if (distance < min_dist)
				{
					index = row_vect;
					min_dist = distance;
				}
			}
			_map->map[row_map][col_map].id = vect[index].etiquette;
			if (strcmp(_map->map[row_map][col_map].id, "Iris-setosa") == 0)
			{
				printf("\033[1;33m");
				printf("S");
				printf("\033[0m");
			}
			if (strcmp(_map->map[row_map][col_map].id, "Iris-versicolor") == 0)
			{
				printf("\033[0;31m");
				printf("C");
				printf("\033[0m");
			}
			if (strcmp(_map->map[row_map][col_map].id, "Iris-virginica") == 0)
			{
				printf("\033[1;34m");
				printf("V");
				printf("\033[0m");
			}
		}
		printf("\n");
	}
	printf("\n\033[1;33m");
	printf("S : Iris-setosa");
	printf("\033[0m \n");

	printf("\033[0;31m");
	printf("C : Iris-versicolor");
	printf("\033[0m\n");

	printf("\033[1;34m");
	printf("V : Iris-virginica");
	printf("\033[0m\n\n");
}

/**
 * on affiche le nombre de neuron active pour chaque etiquette 
 * @param _map la structure N_CFG_t (Reseau)
 */

void Count_neuron_ative(N_CFG_t *_map){
	int count_Iris_setosa = 0, count_Iris_versicolor = 0, count_Iris_virginica = 0;
	int row_map, col_map;
	for (row_map = 0; row_map < _map->row; row_map++){
		for (col_map = 0; col_map < _map->column; col_map++){
			if (strcmp(_map->map[row_map][col_map].id, "Iris-setosa") == 0){
				count_Iris_setosa++;
			}
			if (strcmp(_map->map[row_map][col_map].id, "Iris-versicolor") == 0){
				count_Iris_versicolor++;
			}
			if (strcmp(_map->map[row_map][col_map].id, "Iris-virginica") == 0){
				count_Iris_virginica++;
			}
		}
	}
	printf("les neurones active en tant que \033[1;33m Iris-setosa = %d \033[0m \n", count_Iris_setosa);
	printf("les neurones active en tant que \033[0;31m Iris-versicolor = %d \033[0m \n", count_Iris_versicolor);
	printf("les neurones active en tant que \033[1;34m Iris-virginica = %d \033[0m \n", count_Iris_virginica);
}
