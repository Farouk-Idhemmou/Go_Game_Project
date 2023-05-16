#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD 9
#include <windows.h>    // pour



char b[BOARD][BOARD];

// grid
//prototypes


///// declaration pour capturer un groupe PLEIN
int n=0;                    //size du group  detecté.
int group[81][2];          // group pour stocker les position deja dans la capture
int visited[9][9];        //  on test si le la position est deja visité ou non .
///// de meme declaration pour capturer un groupe VIDE pour le territoire.
int n1=0;                     //size du group vide detecté.
int group_vide[81][2];       // group pour stocker les position deja dans le group
int visited_vides[9][9];    //  on test si le la position est deja visité ou non .
///////

int white_stones=0,black_stones=0;   //
int b_captured=0;                   //
float w_captured=6.5;              //
float white_final_score=0;
int black_final_score=0;
int b_territoire=0;
int w_territoire=0;


////pour le KO
int dernier[9][9];           //  pour le cas du regle ko
int avant_dernier[9][9];     //  aussi  pour le cas du regle ko
/////


// comme  flag pour alterner les deux palyers pour entrer 99 pour quitter .



// couleur
void color(int t,int f)     //  fonction
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,f*16+t);
}
// color of stones creer un box.
void rectangle_color(char player)         //
{
    if(player==' '){printf(" ");}
    if(player=='.'){printf(".");}
    if(player=='B'){color(6,6);printf("x");color(6,0);printf("");}   // console pixels colored 6,6 cad  le texte le back.
    if(player=='W'){color(15,15);printf("a");color(15,0);printf("");}
}

void  FirstInterface(){
    color(3,0);
   printf("\n\n");
   printf("\t\t\t\t\t\t               _                  _          _______    ______ \n");
   printf("\t\t\t\t\t\t              | |                | |        |  _____|  |  __  |     \n");
   printf("\t\t\t\t\t\t              | | ___ _   _    __| | ___    | |        | |  | |\n");
   printf("\t\t\t\t\t\t          _   | |/ _ \\ | | |  / _` |/ _ \\   | |    _   | |  | |\n");
   printf("\t\t\t\t\t\t         | |__| |  __/ |_| | | (_| |  __/   | |___| |  | |__| |\n");
   printf("\t\t\t\t\t\t          \\____/ \\___|\\__,_|  \\__,_|\\___|   |_______|  |______| \n");
    printf("\n \n \n");
    printf("\t\t\t\t\t\t                            _______________________\n");
    printf("\t\t\t\t\t\t                           |    1 >   P L A Y       \\\n");
    printf("\t\t\t\t\t\t                           |_______________________ /\n");
    printf("\t\t\t\t\t\t                            _______________________\n");
    printf("\t\t\t\t\t\t                           |    2 >   R U L E S     \\\n");
    printf("\t\t\t\t\t\t                           |_______________________ /\n");
    printf("\t\t\t\t\t\t                            _______________________\n");
    printf("\t\t\t\t\t\t                           |    3 >   E X I T       \\\n");
    printf("\t\t\t\t\t\t                           |_______________________ /\n");
}
void  SecondInterface(){
    color(3,0);
    printf("\n\n");
    printf("\t\t\t\t\t\t               _                  _          _______    ______ \n");
    printf("\t\t\t\t\t\t              | |                | |        |  _____|  |  __  |     \n");
    printf("\t\t\t\t\t\t              | | ___ _   _    __| | ___    | |        | |  | |\n");
    printf("\t\t\t\t\t\t          _   | |/ _ \\ | | |  / _` |/ _ \\   | |    _   | |  | |\n");
    printf("\t\t\t\t\t\t         | |__| |  __/ |_| | | (_| |  __/   | |___| |  | |__| |\n");
    printf("\t\t\t\t\t\t          \\____/ \\___|\\__,_|  \\__,_|\\___|   |_______|  |______| \n");
    printf("\n \n \n");
    printf("\t\t\t\t\t\t                            _______________________\n");
    printf("\t\t\t\t\t\t                           | 1 >   1  VS  1         \\\n");
    printf("\t\t\t\t\t\t                           |_______________________ /\n");
    printf("\t\t\t\t\t\t                            _______________________\n");
    printf("\t\t\t\t\t\t                           | 2 >   1 VS EASY MACHINE\\\n");
    printf("\t\t\t\t\t\t                           |_______________________ /\n");
    printf("\t\t\t\t\t\t                            _______________________\n");
    printf("\t\t\t\t\t\t                           | 3 >   1 VS HARD MACHINE\\\n");
    printf("\t\t\t\t\t\t                           |_______________________ /\n");
    printf("\t\t\t\t\t\t                            _______________________\n");
    printf("\t\t\t\t\t\t                           | 4 >   B A C K          \\\n");
    printf("\t\t\t\t\t\t                           |_______________________ /\n");
}
void game_rules(){
    color(4,0);
printf("\n");
printf("\t\t                                                            -------------\n");
printf("\t\t                                                           /General Rules\\\n");
printf("\t\t      .  .---------------------------------------------------------------------------------------------------------------------.\n");
printf("\t\t        /                                                                                                                       \\  \n");
printf("\t\t       /         -  Le go se joue a deux joueurs.                                                                                \\  \n");
printf("\t\t      /                                                                                                                           \\\n");
printf("\t\t      |         - Un joueur joue avec les pierres noires, l’autre avec les pierres blanches. Les joueurs                           |\n");
printf("\t\t      |           jouent leurs coups un par un par un à tour de rôle.                                                              |\n");
printf("\t\t      |                                                                                                                            |\n");
printf("\t\t      |         - Un coup consiste a placer une pierre sur une intersection du quadrillage.                                        |\n");
printf("\t\t      |           Les pierres peuvent egalement etre placées sur les bords de celui-ci.                                            |\n");
printf("\t\t      |                                                                                                                            |\n");
printf("\t\t      |         - Une fois qu’une pierre est placée sur une intersection, elle ne peut plus etre deplacee.                         |\n");
printf("\t\t      |                                                                                                                            |\n");
printf("\t\t      |         - Quand il y a une différence de force entre les deux adversaires, le joueur le plus faible                        |\n");
printf("\t\t      |           place des pierres supplémentaires sur le plateau pour compenser cette différence de niveau.                      |\n");
printf("\t\t      |                                                                                                                            |\n");
printf("\t\t      \\         - Dans une partie a egalite, le joueur ayant les pierres noires joue toujours le premier                          / \n");
printf("\t\t       \\          mais dans une partie a handicap, c’est le Blanc qui commence.                                                  /  \n");
printf("\t\t        \\                                                                                                                       /  \n");
printf("\t\t         '---------------------------------------------------------------------------------------------------------------------'\n");
printf("\n");
printf("\t\t                                                            ---------------\n");
printf("\t\t                                                           /Technical Rules\\\n");
printf("\t\t        .----------------------------------------------------------------------------------------------------------------------.\n");
printf("\t\t       /                                                                                                                        \\      \n");
printf("\t\t      /         - Détermination du resultat                                                                                      \\    \n");
printf("\t\t      |                                                                                                                           |\n");
printf("\t\t      |         - Capture des pierres                                                                                             |\n");
printf("\t\t      |                                                                                                                           |\n");
printf("\t\t      |         - Coups interdits                                                                                                 |\n");
printf("\t\t      |                                                                                                                           |\n");
printf("\t\t      |         - Ko                                                                                                              |\n");
printf("\t\t       \\                                                                                                                         / \n");
printf("\t\t        \\      - Fin de partie                                                                                                  /\n");
printf("\t\t         '---------------------------------------------------------------------------------------------------------------------'\n");
}


// main
void winner_white(){
   printf("THE WINNER IS THE WHITE  PLAYER");


}
void winner_black(){
    printf("THE WINNER IS THE BLACK PLAYER ");
}



int ko_cas(){   // return flag si egale à 1 ssi on a une cas du KO  et 0 sinon
    int flag=1;   // cad on suppose que la grille==grille avant derninier -> KO
    for(int r=0;r<BOARD;r++){
        for(int h=0;h<BOARD;h++){
                if (b[r][h]!=avant_dernier[r][h]){
                    flag=0;
                    break;
                }
        }}
    return flag;
}

void copy_tables(){     // fct aide pour le KO_CAS  :copie  dernier  dans avant_dernier  | et grille à dernier.
    for(int r=0;r<BOARD;r++){
        for(int h=0;h<BOARD;h++){
            avant_dernier[r][h]=dernier[r][h];
            dernier[r][h]=b[r][h];
        }}
    }

void rejouer(){  // comme le main pour simplifier le main.
    int c=1;    // alterner les turns
    // initialize la grille par des vides
    for (int i = 0; i < BOARD; i++) {
    for (int j = 0; j < BOARD; j++) {
        b[i][j] = ' ';
    }}
    FirstInterface();
    printf("\t\t\t\t\t\t\t\t\t\t\t");
    int h,i1;
    scanf("\n%d",&h);
                if(h==1){
                     system("cls");
                     SecondInterface();
                     printf("\t\t\t\t\t\t\t\t\t\t\t");
                     scanf("\n%d",&i1);
                    if(i1==1){
                            system("cls");

                        while(1){
                                random_joueur();
                                break;
                            }}
                        else if(i1==2){
                            system("cls");
                            while(1){
                                random_player_vs_computer();  // j_vs_cpu_simple
                                break;
                                    }}
                        else if(i1==3){
                            system("cls");
                            while(1){
                                random_player_hard_computer();  //j_vs_cpu_hard
                                break;
                                    }}
                        else if(i1==4){        // back
                             system("cls");
                             rejouer();}
                }
                else if(h==2){   // rules
                    system("cls");
                    game_rules();
                    printf("\t\t\t\t\t       \t\t\tENTRER UN NOMBRE POUR REVENIR EN ARRIERE ");
                    int f;
                    scanf("%d",&f);
                    system("cls");
                    rejouer();   // back
                }
                else if(h==3){  // exit
                    goto exit;
                    exit:
                    system("cls");
                    printf("\n\n\n\n\t\t\t\t\t\t\t\t\tVous avez quitter !\n\n");
                }
}











// algorithme recherche_profondeur capture group  :recherche  en profondeur pour detecter et stocker les position des pierres dans  le tableau group
void recherche_profondeur(char b[BOARD][BOARD],int x ,int y){
    if(visited[x][y]==1){    // cad deja visite donc deja dans le groupe.
        return;
    }
    else{
        visited[x][y]=1;
        group[n][0]=x;          //stocker les position non visite donc les ajouter dans le le groupe
        group[n][1]=y;          //stocker les position  non visite donc les ajouter dans le le groupe
        n++;  // stocker le nbr des position ajoutee.
        if( x-1>=0 && b[x][y]==b[x-1][y]){recherche_profondeur(b,x-1,y);}        //de meme  genre donc recurssion.
        if( x+1<BOARD && b[x][y]==b[x+1][y]){recherche_profondeur(b,x+1,y);}    //de meme  genre donc recurssion.
        if( y-1>=0 && b[x][y]==b[x][y-1]){recherche_profondeur(b,x,y-1);}       //de meme  genre donc recurssion.
        if(y+1>=0 && b[x][y]==b[x][y+1] ){recherche_profondeur(b,x,y+1);}
        else{return;}
    }
}

void remplir_group_visited(){  // remplir visited en marquant non visite par des -1
n=0;
for(int i=0;i<BOARD;i++){
    for(int j=0;j<BOARD;j++){
            visited[i][j]=-1;
            } // cad non visites
}
}

////////
// Regle du capture chaine.
void capture_group(int group[81][2],char b[9][9]){      //  capturer le group entouree!!
    int capture=1;  // falg pour indiquer si le group est capturee (flag==1) ou non  (flag==0)
    int x;
    int y;
    for(int i=0;i<n;i++){
        x=group[i][0];         // c'est temps pour recuperer les positions stockee dans group afin de capture la chaine
        y=group[i][1];        //c'est temps pour recuperer les positions stockee dans group afin de capture la chaine


        // cherche s ill ya des dEgrés de libértés pour la chaine . si oui  capture = 0  and sort cad ne va pas etre capturée
        if(x-1>=0 && x>=0 && x<BOARD && y>=0 && y<BOARD){       //conditions au extrimités
                if (b[x-1][y]==' '){        //cote haut
                    capture=0;
                    break;
                }}
        // same
        if(x+1<BOARD && x>=0 && x<BOARD && y>=0 && y<BOARD){
                if (b[x+1][y]==' '){         //cote bas
                    capture=0;
                    break;
                }}
        // same
        if(y-1>=0 && x>=0 && x<BOARD && y>=0 && y<BOARD){
                if (b[x][y-1]==' '){        //cote gauche
                    capture=0;
                    break;
                }}
        // same
        if(y+1<=BOARD && x>=0 && x<BOARD && y>=0 && y<BOARD){
                if (b[x][y+1]==' '){         //cote droit
                    capture=0;
                    break;
                }}
    }
    if(capture==1){    // cad la chaine n'a pas de degrees de libertees donc sera capturée

            //CAPTURE
            if(b[group[0][0]][group[0][1]]=='B'){   // test un seul element du groupe pour savoir le genre du chainequi va etre capturée
                w_captured+=n;
            }
            else if(b[group[0][0]][group[0][1]]=='W'){ // test un seul element du groupe pour savoir le genre du chainequi va etre capturée
                b_captured+=n;
            }
            for(int i=0;i<n;i++){   // une cas est capturée donc sera remplacer par vide !!
                 x=group[i][0];
                 y=group[i][1];
                b[x][y]=' ';       // !! une cas est capturée donc sera remplacer par vide !!
            }

    }
    else{return ;}
    }


//meme algorithm de recherche mais cette fois ci checher  un groupe vide pour le territoire  == dfs group territoire et stocke de ce groupe les non visités.
void cherche_group_vide(char b[BOARD][BOARD],int x ,int y){    //// DFS 2
    if(visited_vides[x][y]==1){
        return;
    }
    else{
        visited_vides[x][y]=1;
        group_vide[n1][0]=x;   // stocker dans le groupe_vide les position non visite(dans visited vide) donc les ajouter dans group vide.
        group_vide[n1][1]=y;    // stocker dans le groupe_vide les position non visite(dans visited vide) donc les ajouter dans group vide.
        n1++;
        if( x-1>=0 && b[x][y]==b[x-1][y]){cherche_group_vide(b,x-1,y);}
        if( x+1<BOARD && b[x][y]==b[x+1][y]){cherche_group_vide(b,x+1,y);}
        if( y-1>=0 && b[x][y]==b[x][y-1]){cherche_group_vide(b,x,y-1);}
        if(y+1<=BOARD && b[x][y]==b[x][y+1] ){cherche_group_vide(b,x,y+1);}
    }
}
//equivalent de capture pour le regle chaine :mais ici on ajoute le size du groupe vide soit au whithe_territory ou au black_territory.
void calcul_territoire(int group,char b[BOARD][BOARD]){  // group des position d


    b_territoire=0;           // toujours initialiser pour des autres territoires
    w_territoire=0;          // toujours initialiser pour des autres territoires
    int adjacent_w=0,adjacent_b=0;          // si on trouve un adjacent du group vide white fw=1 danc le territoire est de white sinon de black.
    int x;                 //
                           //  pour stocker les positions dans visited_vide.
    int y;
    remplir_group_visited_vides();   // par des -1 == non visité au premier temps.
    for(int a=0;a<9;a++){
        for(int d=0;d<9;d++){
                if(visited_vides[a][d]!=1 && b[a][d]==' '){     //  cad non visité et égale le vide    !=1  cad ==-1 donc meme chose
                            n1=0 ;                         //  size of the empty  group
                            adjacent_w=0,adjacent_b=0;                    //   tester les adjacents du group vide   si on trouve un adjacent white don adjacent_w=1 de m pour adjacent_b
                            cherche_group_vide(b,a,d);   // cherche un territoire vide.
                for (int index=0;index<n1;index++){
                    x=group_vide[index][0];   //c'est temps pour recuperer les positions stockee dans group_vide afin de capture la chaine
                    y=group_vide[index][1];     //c'est temps pour recuperer les positions stockee dans group_vide afin de capture la chaine
                    // test pour les blacks.
                    if(x-1>=0){if(b[x-1][y]=='B'){adjacent_b=1;}}  // tester si l' adjacent du group vide   si on trouve un adjacent white don adjacent_w = 1
                    if(y-1>=0){if(b[x][y-1]=='B'){adjacent_b=1;}}
                    if(x+1<9){if(b[x+1][y]=='B'){adjacent_b=1;}}
                    if(y+1<9){if(b[x][y+1]=='B'){adjacent_b=1;}}

                    // de meme test pour les whites .
                    if(x-1>=0){if(b[x-1][y]=='W'){adjacent_w=1;}}
                    if(y-1>=0){if(b[x][y-1]=='W'){adjacent_w=1;}}
                    if(x+1<9){if(b[x+1][y]=='W'){adjacent_w=1;}}
                    if(y+1<9){if(b[x][y+1]=='W'){adjacent_w=1;}}
                    }
                    // fin for
                    if ( adjacent_w==0 && adjacent_b==1){b_territoire+=n1;}     //  si on trouve  adjacent_b  = 1 et adjacent_w = 0 donc territoire du black.
                    if ( adjacent_w==1 && adjacent_b==0){w_territoire+=n1;}     // si on trouve    adjacent_w = 1 et adjacent_b = 0 donc territoire du while.
                }
        }
    }


}
void remplir_group_visited_vides(){  // remplir visited_vides  pour les territoire  en marquant non visitée par des -1
n1=0;
for(int i=0;i<BOARD;i++){
    for(int j=0;j<BOARD;j++){
            visited_vides[i][j]=-1;}
}
}
///////

//////


// CALCUL  et affichege des pierre dans la grille a l'instant t.
void number_stones(char b[BOARD][BOARD]){
    int i,j;
    white_stones=0;
    black_stones=0;
    for(i=0;i<BOARD;i++){
    for(j=0;j<BOARD;j++){
        if(b[i][j]=='W'){white_stones++;}
        else if(b[i][j]=='B'){black_stones++;}
    }}

    black_final_score=b_captured+black_stones+b_territoire;    //score finel
    white_final_score=w_captured+white_stones+w_territoire;  //score finel

    color(4,0);
    printf("\n\n\t\t\t\t\t\t\t     ------------------------------------------------------------\n");
    color(6,0);// 10 red    15 white  6 yellow
    printf("\t\t\t\t\t\t\t    | w_captures : %.1f VS b_captures :%d  |  ENTRER 99 POUR PASSER| \n",w_captured,b_captured);
    color(15,0);
    color(4,0);
    printf("\t\t\t\t\t\t\t     ------------------------------------------------------------\n");
    color(15,0);
    printf("\t\t\t\t\t\t\t    |     white stones  = %d              |  ENTRER 99 POUR PASSER|\n",white_stones);
    color(4,0);
    printf("\t\t\t\t\t\t\t     ------------------------------------------------------------\n");
    color(15,0);
    printf("\t\t\t\t\t\t\t    |     white territoire  = %d          |  ENTRER 99 POUR PASSER|\n",w_territoire);
    color(4,0);
    printf("\t\t\t\t\t\t\t     ------------------------------------------------------------\n");
    color(15,0);
    color(6,0);
    printf("\t\t\t\t\t\t\t    |     black stones  = %d              |  ENTRER 99 POUR PASSER|\n",black_stones);
    color(15,0);
    printf("\t\t\t\t\t\t\t     ------------------------------------------------------------\n");
    color(6,0);
    printf("\t\t\t\t\t\t\t    |     black territoire  = %d          |  ENTRER 99 POUR PASSER|\n",b_territoire);
     color(4,0);
    printf("\t\t\t\t\t\t\t     ------------------------------------------------------------\n");
    color(15,0);
    printf("\t\t\t\t\t\t\t    |            WHITE_SCORE = %.1f",white_final_score);
    color(4,0);printf("     VS\t");
    color(6,0);
    printf("BLACK_SCORE = %d  |\n",black_final_score);
    color(4,0);
    printf("\t\t\t\t\t\t\t     ------------------------------------------------------------");

}






void random_joueur(){  //  toujours white sera commencer le premier RANDOM
    char jou1,jou2;
    srand( time(NULL) );
    int TURN=rand()%2;
    if(TURN%2==0){
	jou1='W';jou2='B';
	color(6,0);
    printf("\n \t\t\t\t\tJOUR1 first: YOU GOT BLACK\n");
    color(6,0);
    getch();
    j_j(jou1,jou2,TURN);
    }
    else{
	jou1='B';jou2='W';
    color(6,0);
    printf("\n \t\t\t\t\tJOU2 first :YOU GOT BLACK\n");
    color(6,0);
    getch();
    j_j(jou1,jou2,TURN);
    }
    getch();
}





//////////////////////////////////////////////////////////////// JOUEUR_VS_JOUEUR////////////////////////////////////////
int pass_recent=0;   // comme un flag  pour que les passe
void j_j(int jou1,int jou2 ,int c){
    int i,j;

    color(15,0);

    //pour capturer    group  chaine

    for(int t1=0;t1<9;t1++){                        //applle des fonctions du recherche des chaines et des territoires .
    for(int u1=0;u1<9;u1++){if (  b[t1][u1]!=' '){    // cad ne peut pas capturer une chaine vides !!!
                             remplir_group_visited();
                             recherche_profondeur(b,t1,u1);
                             capture_group(group,b);

                            }
    }}
    //group des vides (territoire)
    for(int t2=0;t2<9;t2++){
    for(int u2=0;u2<9;u2++){if ( b[t2][u2]==' '){    // pour partir d'une chaine vide cad territoire
                             remplir_group_visited_vides();
                             calcul_territoire(group_vide,b);  // group_vide qu'on va stocker

                            }
    }}//
    // afficher des scores !
    number_stones(b);

////////////////////////////////////////////////////Affichage de la grille !.///////////////////////////////////////////////////////////
    color(15,0);
    printf("\n\n");color(15,0);
    printf("\t\t\t\t\t\t\t\t     1    2    3    4    5    6    7    8    9    \n");
    for (int i = 0; i < BOARD; i++) {
        color(15,0);printf("\t\t\t\t\t\t\t\t     |    |    |    |    |    |    |    |    |    \n");
        color(15,0);printf("\t\t\t\t\t\t\t\t%d----",i+1);
    for (int j = 0; j < BOARD; j++) {
                rectangle_color(b[i][j]);
                color(15,0);printf("----");
    }printf("\n");
    }
   // couleur blache
   color(15,0);printf("\t\t\t\t\t\t\t\t     |    |    |    |    |    |    |    |    |    ");
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // ENTRER LES JOUEURS
    printf("\n\t\t\t\t\t\t\t\t");
    scanf("%d%d",&i,&j);

    // pass pour les players.
    if(pass_recent==1 && (i==99 || j==99)){           //pour  passer entrer 99 pour i ou j.

        system("cls");
        printf("\t\t\tVOUS AVEZ  PASSEE . CLIQUER POUR SAVOIRE THE WINNER");
        getch();
        system("cls");
        if(white_final_score>black_final_score){// comparer les resulatat finales

            winner_white();}
        if(black_final_score>white_final_score){

            winner_black();
        }
        sleep(7);//7 sconds.
        system("cls");
        printf("\t\t\t\t\t\t\t\tVOULEZ VOUS REJOUER (Y/N)  ");
        getch();
        system("cls");

        rejouer();

        }

    if (i==99 ){            // pour que le 2eme pass
            pass_recent=1;
            printf("\t\t\t\t\t\t\t\t    VOUS AVEZ PASSEE \n\n");

            printf("\t\t\t\t\t\t\t\tTAPER UN CARACHTERE POUR REJOUER ");
            system("cls");
            system("pause");
            goto passe;  // pour donner a l'adversaire the turn  pour
    }
    if(i<1 || i>9 || j<1 || j>9 ){          //check if the entered move dans la grille et ssi the position is legal pour ne pas absorber the players turn.
        printf("\t\t\t\t\t\t\t\t     invlid inputs");
        printf("\n cliquer n umporte quoi pour continuer ");
        system("pause");
        system("cls");j_j(jou1,jou2,c);}
    else if(b[i-1][j-1]!=' '  ){     //check if the entered move dans la grille est occupee ou non
        printf("\t\t\t\t\t\t\t\t\t\t\t     occupied !");
        printf("\n\n\n cliquer n'umporte quoi pour continuer ");
        system("pause");
        system("cls");j_j(jou1,jou2,c);}

    else{
	if(c%2!=0){
        b[i-1][j-1]=jou1;}
    else{
        b[i-1][j-1]=jou2;}
    if(ko_cas()==1){   // testter si KO CAS OU NON
        printf("is ko position \n");
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                b[i][j]=dernier[i][j];
            }
        }
        system("cls");j_j(jou1,jou2,c);
    }
    copy_tables();
    //  RESERVE TURN
    }
    system("cls");
    passe:              //TURNS OF PLAYERS.
        c++;
    j_j(jou1,jou2,c);
}
///////////////////////////////////////////////////////////////////////////////
                                                            //JOUEUR COMPUTER ////////

////////////////////  TERRITOIRE /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////


///////

// SIMPLE MAIN MAIS IMPORTANT !!!!
int main()
{
    rejouer();
    return 0;

}




// random  FIRST PLAYER humain:machine.   EASY
void random_player_vs_computer(){  //  toujours white sera commencer le premier   |pour determiner le premier qui va jouer
    char humain,machine;
    srand( time(NULL) );
    int TURN=rand()%2;
    if(TURN%2==0){
	humain='W';machine='B';
    color(7,0);printf("\n \t\t\t\t\tHumain first: YOU GOT WHITE\n");color(7,0);
    getch();
    grid_easy_cpu(humain,machine,TURN);
    }
    else{
	humain='B';machine='W';
    color(6,0);
    printf("\n \t\t\t\t\tmachine first : AND THE HUMAN IS BLACK\n");
    color(6,0);    getch();
    grid_easy_cpu(humain,machine,TURN);
    }
    getch();
}

////////////// ///////////////////////////SIMPLE MACHINE///////////////////////////////
void grid_easy_cpu(int humain,int machine,int c){    ///// c'est la meme fonction joueur vs jouer sauf pour le deuxieme joueur on fait  i=rand()%9+1;j=rand()%9+1; +1 car j'appelle b[i-1][j-1]
    int i,j;
    color(15,0);
    //group  chaine pour capture
    for(int t1=0;t1<9;t1++){
    for(int u1=0;u1<9;u1++){if (  b[t1][u1]!=' '){    // cad on part d un point 'B' ou 'W' et on commence la recherche du group.
                             remplir_group_visited();
                             recherche_profondeur(b,t1,u1);
                             capture_group(group,b);

                            }
    }}
    //group des vides (territoire)
    for(int t2=0;t2<9;t2++){
    for(int u2=0;u2<9;u2++){if ( b[t2][u2]==' '){    // cad on part d un point 'B' ou 'W' et on commence la recherche
                             remplir_group_visited_vides();
                             calcul_territoire(group_vide,b);  // group_vide qu'on va stocker

                            }
    }}//
/////Affichage de la grille !.
    number_stones(b);
    //calcul_territoire(group_vide,b);
    color(15,0);
    printf("\n\n");color(15,0);
    printf("\t\t\t\t\t\t\t\t     1    2    3    4    5    6    7    8    9    \n");
    for (int i = 0; i < BOARD; i++) {
        color(15,0);printf("\t\t\t\t\t\t\t\t     |    |    |    |    |    |    |    |    |    \n");
        color(15,0);printf("\t\t\t\t\t\t\t\t%d----",i+1);
    for (int j = 0; j < BOARD; j++) {
                rectangle_color(b[i][j]);
                color(15,0);printf("----");
    }printf("\n");
    }
   // couleur blache
   color(15,0);printf("\t\t\t\t\t\t\t\t     |    |    |    |    |    |    |    |    |    ");

//////////////////////////////////
    // ENTRER LES JOUEURS
    printf("\n\t\t\t\t\t\t\t\t");
    if(c%2==0){  //// turn humain
    scanf("%d%d",&i,&j);

    //// PASS  : SI L'HUMAIN  DECIDE DE PASSER DONC FIN JEU .
    if(i==99){
        system("cls");
        printf("\t\t\tVOUS AVEZ PASSEE . CLIQUER POUR SAVOIRE THE WINNER");
        getch();
        system("cls");
        if(white_final_score>black_final_score){
                printf("\t\t\t\t");
            winner_white();}
        if(black_final_score>white_final_score){
            printf("\t\t\t\t");
            winner_black();
        }
        sleep(7);//7 sconds.
        system("cls");
        printf("\t\t\t\t\t\t\t\tVOULEZ VOUS REJOUER (Y/N)  ");
        getch();
        system("cls");

        rejouer();
    }
    }  //// turn machine
    else{
        i=rand()%9+1;
        j=rand()%9+1;
    }

    if(i<1 || i>9 || j<1 || j>9 ){          //check if the position is legal pour ne pas absorber the players turn.
        printf("\t\t\t\t\t\t\t\t     invlid inputs");
        printf("\n cliquer n umporte quoi pour continuer ");
        system("pause");
        system("cls");grid_easy_cpu(humain,machine,c);}
    else if(b[i-1][j-1]!=' '  ){
        printf("\t\t\t\t\t\t\t\t\t\t\t     occupied !");
        printf("\n\n\n cliquer n'umporte quoi pour continuer ");
        system("pause");
        system("cls");grid_easy_cpu(humain,machine,c);}

    else{
	if(c%2==0)
        b[i-1][j-1]=humain;
    else
        b[i-1][j-1]=machine;
    if(ko_cas()==1){
        printf("is ko position \n");
        system("pause");

        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                b[i][j]=dernier[i][j];
            }
        }
        system("cls");grid_easy_cpu(humain,machine,c);
    }
    copy_tables();   //// /  pour qu'on puisse verifier le ko par les tableuw copiéés
    //  RESERVE TURN
    }
    system("cls");
    //c++;            //TURNS OF PLAYERS.

    grid_easy_cpu(humain,machine,c+1);
}


////////////////////




/////////////////////////////////////////  HARD CPU   /////////////////////////




void random_player_hard_computer(){  //  toujours white sera commencer le premier RANDOM
    char humain,machine;
    srand( time(NULL) );
    int TURN=rand()%2;
    if(TURN%2==0){
	humain='W';machine='B';
    color(7,0);
    printf("\n \t\t\t\t\tHumain first: YOU GOT WHITE\n");
    color(7,0);    getch();
    grid_hard_cpu(humain,machine,TURN);
    }
    else{
	humain='B';machine='W';
color(6,0);
    printf("\n\t\t\t\t\t Machine first : AND THE HUMAN IS BLACK\n");
    color(6,0);    getch();
    grid_hard_cpu(humain,machine,TURN);
    }
    getch();
}









void grid_hard_cpu(int humain,int machine,int C){   //MEME QUE grid_hard_cpu SAUF dans le turn machine on fiat un chgt
    int i,j;
    color(15,0);
    //group  chaine pour capture
    for(int t1=0;t1<9;t1++){
    for(int u1=0;u1<9;u1++){if (  b[t1][u1]!=' '){    // cad on part d un point 'B' ou 'W' et on commence la recherche du group.
                             remplir_group_visited();
                             recherche_profondeur(b,t1,u1);
                             capture_group(group,b);
                            }
    }}
    //group des vides (territoire)
    for(int t2=0;t2<9;t2++){
    for(int u2=0;u2<9;u2++){if ( b[t2][u2]==' '){    // cad on part d un point 'B' ou 'W' et on commence la recherche
                             remplir_group_visited_vides();
                             calcul_territoire(group_vide,b);  // group_vide qu'on va stocker

                            }
    }}//
/////Affichage de la grille !.
    number_stones(b);
    //calcul_territoire(group_vide,b);
    color(15,0);
    printf("\n\n");color(15,0);
    printf("\t\t\t\t\t\t\t\t     1    2    3    4    5    6    7    8    9    \n");
    for (int i = 0; i < BOARD; i++) {
        color(15,0);printf("\t\t\t\t\t\t\t\t     |    |    |    |    |    |    |    |    |    \n");
        color(15,0);printf("\t\t\t\t\t\t\t\t%d----",i+1);
    for (int j = 0; j < BOARD; j++) {
                rectangle_color(b[i][j]);
                color(15,0);printf("----");
    }printf("\n");
    }
   // couleur blache
   color(15,0);printf("\t\t\t\t\t\t\t\t     |    |    |    |    |    |    |    |    |    ");

//////////////////////////////////
    // ENTRER LES JOUEURS
    printf("\n\t\t\t\t\t\t\t\t");
    i=rand()%9+1;       /////eror du input ;
    j=rand()%9+1;
    if(C%2==0){  //// turn humain
    scanf("%d%d",&i,&j);

    //// PASS  : SI L'HUMAIN  DECIDE DE PASSER DONC FIN JEU .
    if(i==99){
        system("cls");
        printf("\t\t\tVOUS AVEZ PASSEE . CLIQUER POUR SAVOIRE THE WINNER");
        getch();
        system("cls");
        if(white_final_score>black_final_score){
                printf("\t\t\t\t");
            winner_white();}
        if(black_final_score>white_final_score){
            printf("\t\t\t\t");
            winner_black();
        }
        sleep(7);//7 sconds.
        system("cls");
        printf("\t\t\t\t\t\t\t\tVOULEZ VOUS REJOUER (Y/N)  ");
        getch();
        system("cls");

        rejouer();
    }
    }
    ////////////////////////////////////// //// turn machine  /////HARD./////////////////////////////////////////////////////////

    else{

        //////////////////// difference is here
        int flag1=0;  // indique la complexite du computer hard  la prmier position trouver sera poser par la cpu!!!!!
        for(int t3=0;t3<9 && flag1==0;t3++){
        for(int u3=0;u3<9;u3++){
                if(b[t3][u3]==humain){
                    if(t3-1>=0 && b[t3-1][u3]==' '){
                            i=t3;j=u3+1;
                            flag1=1;
                            break;
                    }
                    if(t3+1<9 && b[t3+1][u3]==' '){
                            i=t3+2;j=u3+1;
                            flag1=1;
                            break;
                    }
                    if(u3-1>=0 && b[t3][u3-1]==' '){
                            i=t3+1;j=u3;
                            flag1=1;
                            break;
                    }
                    if(u3+1<9 && b[t3][u3+1]==' '){
                            i=t3+1;j=u3+2;
                            flag1=1;
                            break;
                    }

                }
                }}
    }


    //////////////////////////  meme que cpu simple   //////////////////////////////

    if(i<1 || i>9 || j<1 || j>9 ){          //check if the position is legal pour ne pas absorber the players turn.
        printf("\t\t\t\t\t\t\t\t     invlid inputs");
        printf("\n cliquer n umporte quoi pour continuer ");
        system("pause");
        system("cls");grid_hard_cpu(humain,machine,C);}
    else if(b[i-1][j-1]!=' '  ){
        printf("\t\t\t\t\t\t\t\t\t\t\t     occupied !");
        printf("\n\n\n cliquer n'umporte quoi pour continuer ");
        system("pause");
        system("cls");grid_hard_cpu(humain,machine,C);}

    else{
	if(C%2==0)
        b[i-1][j-1]=humain;
    else
        b[i-1][j-1]=machine;
    if(ko_cas()==1){
        printf("is ko position \n");
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                b[i][j]=dernier[i][j];
            }
        }
        system("cls");grid_hard_cpu(humain,machine,C);
    }
    copy_tables();
    //  RESERVE TURN
    }
    system("cls");
    // c++;            TURNS OF PLAYERS.

    grid_hard_cpu(humain,machine,C+1);//
}

