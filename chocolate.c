#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//structures and enums

struct chocolate{
    int length, height, matrix[100][100];
    struct coordinates {int row,column;} green;
    struct side {int left, right, up, down;} side;
}tablet;

enum turn {p, o} turn;

//function declarations

struct chocolate build_chocolate(struct chocolate); //initialise the chocolate
void print_chocolate(struct chocolate); //print the chocolate in the current state
int game_end(struct chocolate); //true if game has ended
struct chocolate player(struct chocolate); //player's turn
struct chocolate opponent(struct chocolate); //computer's turn
struct chocolate delete_row(struct chocolate, int); //deletes a row
int check_if_row_deletion_is_valid(struct chocolate, int); //verifies if you can delete that row
struct chocolate delete_column(struct chocolate, int); //deletes a column
int check_if_column_deletion_is_valid(struct chocolate, int); //verifies if you can delete that column
struct chocolate computer(struct chocolate); //computer's turn

//main

int main(){
    tablet = build_chocolate(tablet);
    turn=o;
    printf("Let the game begin!\n\n");
    print_chocolate(tablet);
    while(!game_end(tablet)){
        if(turn==o){
            turn=p;
            tablet=player(tablet);
        }
        else{
            turn=o;
            tablet=computer(tablet);
        }
        print_chocolate(tablet);
    }
    if(turn==p) {
        printf("You won!!!\n");
    }
    else{
        printf("A mindless computer beat you :(((\n");
    }
    return 0;
}

//function definitions

struct chocolate build_chocolate(struct chocolate tablet){
    int choice;
    printf("---------------------\n\nEnter lenght/height : ");
    scanf("%d %d", &tablet.length, &tablet.height);
    printf("\nWhere do you want the green 1x1 corner to be?\n(1) top left\n(2) top right\n(3) bottom right\n(4) bottom left\n\nChoice : ");
    scanf("%d", &choice);
    printf("\n");
    tablet.side.up=0;
    tablet.side.down=tablet.height-1;
    tablet.side.left=0;
    tablet.side.right=tablet.length-1;
    switch (choice)
    {
        case 1:
            tablet.green.row=0;
            tablet.green.column=0;
            break;
        case 2:
            tablet.green.row=0;
            tablet.green.column=tablet.length-1;
            break;
        case 3:
            tablet.green.row=tablet.height-1;
            tablet.green.column=tablet.length-1;
            break;
        case 4:
            tablet.green.row=tablet.height-1;
            tablet.green.column=0;
            break;
    }
    return tablet;
}

void print_chocolate(struct chocolate tablet){
    int i,j;
    for(i=0; i<tablet.height; i++){
        for(j=0; j<tablet.length; j++){
            if(i == tablet.green.row && j == tablet.green.column){
                printf("1");
            }
            else if(i>=tablet.side.up && i<=tablet.side.down && j>=tablet.side.left && j<=tablet.side.right){
                printf("0");
            }
            else{
                printf("-");
            }
        }
        printf("\n");
    }
    printf("\n");
}

int game_end(struct chocolate tablet){
    if(tablet.side.left == tablet.side.right && tablet.side.down == tablet.side.up){
        return 1;
    }
    return 0;
}

struct chocolate player(struct chocolate tablet){
    int choice, nr;
    while(1){
        printf("What do you want to delete?\n(1) row\n(2) column\n\nChoice : ");
        scanf("%d", &choice);
        printf("\n");
        if(choice == 1){
                printf("Which ROW do you want to delete?\n\nChoice : ");
                scanf("%d", &nr);
                if(check_if_row_deletion_is_valid(tablet,nr)){
                    tablet=delete_row(tablet, nr);
                    break;
                }
                else{
                    printf("Invalid choice!\n");
                }
        }
        else{
                printf("Which COLUMN do you want to delete?\n\nChoice : ");
                scanf("%d", &nr);
                if(check_if_column_deletion_is_valid(tablet,nr)){
                    tablet=delete_column(tablet, nr);
                    break;
                }
                else{
                    printf("Invalid choice!\n");
                }
        }
    }
    return tablet;
}

struct chocolate delete_row(struct chocolate tablet, int nr){
    if(tablet.green.row == 0){ //if green corner is at top
        tablet.side.down = nr-1;
    }
    else{ //green corner on bottom
        tablet.side.up = nr+1;
    }

    return tablet;
}

int check_if_row_deletion_is_valid(struct chocolate tablet, int nr){
    if(tablet.green.row == nr || nr < tablet.side.up || nr > tablet.side.down){
        return 0;
    }
    return 1;
}

struct chocolate delete_column(struct chocolate tablet, int nr){
    if(tablet.green.column == 0){ //if green corner is at left
        tablet.side.right = nr-1;
    }
    else{ //green corner at right
        tablet.side.left = nr+1;
    }

    return tablet;
}

int check_if_column_deletion_is_valid(struct chocolate tablet, int nr){
    if(tablet.green.column == nr || nr < tablet.side.left || nr > tablet.side.right){
        return 0;
    }
    return 1;
}

struct chocolate computer(struct chocolate tablet){
    srand(time(NULL));
    int choice1, choice2;
    while(1){
        choice1=rand()%2;
        if(choice1==0){ //if robot chooses ROW
                choice2=rand()%(tablet.height);
                if(check_if_row_deletion_is_valid(tablet, choice2)){
                    tablet=delete_row(tablet, choice2);
                    break;
                }
        }
        else{
                choice2=rand()%(tablet.length);
                if(check_if_column_deletion_is_valid(tablet, choice2)){
                    tablet=delete_column(tablet, choice2);
                    break;
                }
        }   
    }
    printf("Computer chose to delete ");
    if(choice1==0){
        printf("ROW ");
    }
    else{
        printf("COLUMN ");
    }
    printf("%d\n", choice2);
    return tablet;
}
