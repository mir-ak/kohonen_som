
#include<SDL2/SDL.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<stdbool.h>

#define row_data 150 
#define column_data_nb 4
#define Max_ligne 50 
#define lenght_phase 2 

#define first_rayon 3 
#define second_rayon 1 

#define first_iteration 500 
#define second_iteration 1500

// structure de vecteur database

struct vect { 	
	double *vec;
	char *etiquette;
	double norm ;
	int row; //150 ligne
	int column; // 4 colonne
};
typedef struct vect Vect_Data_t;


// structure de vecteur de donnees pour la matrice 

struct node{
	double *weight;
	double act;
	char *id;
};
typedef struct node node_t;

// structure bmu (liste chainee) 

struct bmu{
	int index_row;
	int index_col;
	struct bmu *next;
};
typedef struct bmu bmu_t;

// structure phase (change iteration) 

struct phase{
	int nb_iteration ; 
	int rayon ;	
};
typedef struct phase phase_t;

// structure N_CFG_t (Reseau) 

struct N_CFG {
	int row;
	int column;
	double alpha;
	phase_t *phases;
	node_t **map;
	bmu_t  *bmu;
};
typedef struct N_CFG N_CFG_t;

// Database 
FILE *Open_file();
int Number_line_to_file(FILE* file);
Vect_Data_t* Init_data(int size);
void Add_data_to_vect(FILE* file_opened, Vect_Data_t* vect_data);
void Display_data(Vect_Data_t* vect_data);
void Normalize(Vect_Data_t *vect_data);
double *Moyenne(Vect_Data_t *vect);
void Display_vect_moy(double *vect_moy);
int *Init_tab(int size);
void Shuffle_index(int *tab,int size);

// Bmu (liste chainne)
bmu_t *Init_bmu(int n,int m);
bmu_t *Add_index_bmu_start(bmu_t *liste, int row, int column);
int Length_list(bmu_t  *liste_bmu);
bmu_t *Random_bmu(bmu_t * liste_bmu , int lenght);
void Display_bmu(bmu_t *bmu	);

// Map (Reseau)
double Random(double min,double max);
N_CFG_t* Init_Map (int row, int column);
void Add_values_to_map(N_CFG_t *_map,Vect_Data_t *vect);
void Display_map(N_CFG_t *_map);
double Distance_euclidienne(double *vect ,double *vect2, int dim);
void Learning(N_CFG_t *_map,Vect_Data_t *vect, int rayon, int nb_iteration);
void Call_learning(N_CFG_t *_map,Vect_Data_t *vect);
void Display_label(N_CFG_t *_map,Vect_Data_t *vect);
void Count_neuron_ative(N_CFG_t *_map);

// Sdl2
SDL_Rect Init_Rect(int xs, int ys, int widths, int heights);
void Display_label_in_SDL(SDL_Renderer* renderer, N_CFG_t *_map);
void Window(N_CFG_t *_map);

// Free 
void Free_list(bmu_t *liste);
void Free_Vect_Data(Vect_Data_t* vect);
void Free_Map(N_CFG_t *_map);
    
