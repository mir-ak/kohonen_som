#include"../include/iris_data.h"

/**
 * supprimer la memoire de la structure bmu (liste chainee) 
 * @param list_bmu la structure bmu (liste chainee) 
 */

void Free_list(bmu_t *list_bmu){
    bmu_t* tmp;
    while(list_bmu != NULL){
        tmp = list_bmu->next;
        free(list_bmu);
        list_bmu = tmp;
    }
    free(list_bmu);
}

/**
 * supprimer la memoire de la structure vecteur
 * @param vect_data la structure vecteur
 */

void Free_Vect_Data(Vect_Data_t* vect_data){
    int i;
    for (i = 0; i < vect_data->row; i++){
        free(vect_data[i].vec);
        free(vect_data[i].etiquette);
    }
    free(vect_data);
}

/**
 * supprimer la memoire de la structure N_CFG_t (Reseau) 
 * @param _map la structure N_CFG_t (Reseau) 
 */

void Free_Map(N_CFG_t *_map){
    int i,j;
    for ( i = 0; i < _map->row; i++){
        for (j = 0; j < _map->column; j++){
            free(_map->map[i][j].weight);
        }
        free(_map->map[i]);
    }
    free(_map);   
}











































