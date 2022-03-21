

#include"../include/iris_data.h"

/**
 * initialiser un rectangle avec la postion de x et y et ca taille 
 * @param xs la postion en x
 * @param xy la postion en y
 * @param widths la taille de rectangle en largeur
 * @param heights la taille de rectangle en langue
 * @return le rectangle 
 */

SDL_Rect Init_Rect(int xs, int ys, int widths, int heights) {
    SDL_Rect rectangular;
    rectangular.x = xs;
    rectangular.y = ys;
    rectangular.w = widths;
    rectangular.h = heights;
    return rectangular;
}

/**
 * affiche les rectanges dans la interface graphique de chaque etiquette avec des couleur différente 
 * d'abore on declare un matrice de rectange puis a chaque fois on trouve une etiquette on stocke 
 * le rectange dans la matric puis on affiche cette matrice dans notre renderer
 * (pour moi c'est des carres je leur donne la meme taille en W & H)
 * @param renderer l'espace où nous allons pour pouvoir dessiner (c'est comme un canavs)
 * @param _map la structure N_CFG_t (Reseau) 
 */
void Display_label_in_SDL(SDL_Renderer* renderer, N_CFG_t *_map){
    int row_map , col_map ;
    SDL_Rect rects[_map->column][_map->row];
    for(col_map = 0; col_map <_map->row; col_map++){
        for( row_map= 0; row_map <_map->column; row_map++){
            if(strcmp(_map->map[col_map][row_map].id,"Iris-setosa") == 0){
                rects[row_map][col_map]   = Init_Rect(20 + row_map*42, 20 + col_map*42, 40, 40);
                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 0);
                SDL_RenderFillRect(renderer, &rects[row_map][col_map]  );
			}
			if(strcmp(_map->map[col_map][row_map].id,"Iris-versicolor") == 0){
                rects[row_map][col_map]   = Init_Rect(20 + row_map*42, 20 + col_map*42, 40, 40);
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
                SDL_RenderFillRect(renderer, &rects[row_map][col_map]  );
			}
			if(strcmp(_map->map[col_map][row_map].id,"Iris-virginica") == 0){
                rects[row_map][col_map] = Init_Rect(20 + row_map*42, 20 + col_map*42, 40, 40);
                SDL_SetRenderDrawColor(renderer, 0, 255, 255, 0);
                SDL_RenderFillRect(renderer, &rects[row_map][col_map]);
			}
		}
	}
}

/**
 * initialiser la fenetre (l'interface graphique) avec une condtion pour quelle ce ferme pas 
 * jusqu'on clique sur la touche ferme puis on dessinge nous rectnagle dans le renderer 
 * @param _map la structure N_CFG_t (Reseau) 
 */
void Window(N_CFG_t *_map){

    SDL_Window *window = NULL;
    SDL_Renderer* renderer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        exit(0);
    }
   
    window = SDL_CreateWindow("SOM", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,40+_map->column*42,40+_map->row*42,0);
    if (window == NULL){
        SDL_Log("Erreur : creation fenetre echouee > %s \n", SDL_GetError());  
        exit(0); 
    }

    renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 50, 10, 10, 255);
    SDL_RenderClear(renderer);
    bool running = true;
    SDL_Event event;
    while (running){
        while (SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                running = false ;
            }
        }
        Display_label_in_SDL(renderer,_map);
        SDL_RenderPresent(renderer);
    }
 
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
