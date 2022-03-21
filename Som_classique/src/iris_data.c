#include"../include/iris_data.h"

/**
 * ouvrir un fichier 
 * @param name nom de fichier 
 * @param modes mode d'ouverteur
 * @return le fichier ouvert  
 */

FILE *Open_file(char *name_file,char *modes){
    FILE * file = fopen(name_file,modes);
	if (!file) {
		printf("Impossible d'ouvrir ce fichier ou bien il n'existe pas \n");
		exit(1);
	};
    return file;   
}

/**
 * initialiser (allocation mémoire) la structure vectors de database 
 * @param size la taille de vecteur 
 * @return la structure de vecteurs alloué   
 */

Vect_Data_t *Init_data(int size) {
	Vect_Data_t *vect_data = (Vect_Data_t*) malloc(size * sizeof(Vect_Data_t));
	int i;
	if(vect_data == NULL){     
		printf("Échec de l'allocation\n");
    	exit(0);
  	}
	vect_data->row = size;
	vect_data->column = column_data_nb;
	for(i = 0; i < size; i++) {
		vect_data[i].vec =(double*) malloc(vect_data->column * sizeof(double));
		vect_data[i].etiquette = (char*) malloc(sizeof(char));
	}
	return vect_data;
}

/**
 * remplir les vectors de database a l'aide d'un fichier (iris.data)
 * @param file_opened le fichier (iris.data)
 * @param vect_data la structure vecteur 
 */

void Add_data_to_vect(FILE* file_opened, Vect_Data_t* vect_data) {
  	int i = 0, j = 0;
	char *token; 
	char * data_line = (char*) malloc(Max_ligne * sizeof(char));
	if (data_line == NULL){
		printf("Échec de l'allocation\n");
    	exit(0);
  	}
	
	while (fgets(data_line, Max_ligne, file_opened) != NULL) {
		token = strtok(data_line, ",");
		for(j = 0; j < vect_data->column  ; j++) {
			vect_data[i].vec[j] = strtod(token,NULL);
			token = strtok(NULL, ",");	
		}
		vect_data[i].etiquette = strtok(strdup(token),"\n");
		i++;
	}

	free(data_line);
}

/**
 * affiche les donnees de vectors de database en notation scientifique (%e)
 * @param vect_data la structure vecteur
 */

void Display_data(Vect_Data_t* vect_data) {
	int i, j;
	for(i = 0; i < vect_data->row; i++) { 
		printf("%d: ",i);
		for (j = 0; j < vect_data->column; j++) {	
			printf("%e ",vect_data[i].vec[j]);
		}
		printf(" %s\n", vect_data[i].etiquette); 
	}
}

/**
 * normaliser les vectors de database 
 * @param vect_data la structure vecteur 
 */

void Normalize(Vect_Data_t *vect_data) {
	int i,j;
	for (i = 0; i < vect_data->row; i++) {
		for (int j = 0; j <vect_data->column ; j++){
			vect_data[i].norm += pow(vect_data[i].vec[j], 2);
		}
		vect_data[i].norm = sqrt(vect_data[i].norm);
	}
    for (i = 0; i <vect_data->row; i++) {
		for (j = 0; j < vect_data->column; j++) {
			vect_data[i].vec[j] /= vect_data[i].norm; 
		}
		
	}
}

/**
 * initialiser (allocation mémoire) d'un tableau puis
 * calculer la moyenne de database colonne par colonne 4*
 * @param vect_data la structure vecteur 
 * @return un tableau de 4 valeur   
 */

double *Moyenne(Vect_Data_t *vect){
	int i,j;
	double *tab_moy = (double*) malloc(vect->column * sizeof(double));
	if(tab_moy == NULL){
		printf("Échec de l'allocation\n");
		exit(0);
	}
	for (i = 0; i <vect->column ; i++){
		for (j = 0; j < vect->row; j++){
			tab_moy[i] += vect[j].vec[i];
		}
		tab_moy[i] /= vect->row; 
	}
	return tab_moy;
}

/**
 * afficher la moyenne 
 * @param tab_moy un tableau de 4 valeur
 */

void Display_tab_moy(double *tab_moy){
	int i = 0;
	for (i = 0; i < column_data_nb; i++)
	{
		printf("%f \n", tab_moy[i]);
	}
}

/**
 * main
 */

int main(int argc, char const *argv[]){
    Vect_Data_t *vect_data; 
	N_CFG_t *map;
	//double *tab_moy;
	int row_map = 6 , col_map = 10;
	FILE * file = Open_file("./data/iris.data","r"); 
	vect_data = Init_data(row_data);
	Add_data_to_vect(file, vect_data);
	Normalize(vect_data);
	//Display_data(vect_data);
	//tab_moy = Moyenne(vect_data);
	//Display_tab_moy(tab_moy);


	map = Init_Map (row_map, col_map);
	Add_values_to_map(map,vect_data);
	//Display_map(map);

	Call_learning(map,vect_data);

	//Display_bmu(map->bmu);
	Display_label(map,vect_data);
	Count_neuron_ative(map);

 	//Window(map);
	
	fclose(file);
	Free_list(map->bmu);
	Free_Vect_Data(vect_data);
	Free_Map(map);
	
	printf("Free memory ok ツ \n");
    
    return 0;
}
