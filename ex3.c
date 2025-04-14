/******************
Name:
ID:
Assignment: ex3
*******************/

#include <stdio.h>

#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 365
#define UNSELECTED 0
#define addOne  1
#define addAll  2  
#define stats  3
#define print  4
#define insights  5
#define deltas  6
#define done  7

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};
int days[NUM_OF_BRANDS];
int choice;

long long enterNumber(int task) {
	switch(task) {
		case UNSELECTED: {
			printMenu();
			break;
		}
		case addOne: {
			printf("What brand?\n");
			break;
		}
		default: {
			break;
		}
	}
	long long number = 0, temp = 0;
	int input = 0;
	while ((input = scanf(" %lld", &temp)) != 1 || temp < 0 || task == UNSELECTED) {
		if (input == EOF) {
			return EOF;
		}
		scanf("%*[^\n]");
		switch(task) {
			case UNSELECTED: {
				if (temp == done) {
					return -1;
				}
				if (temp >= addOne && temp <= done) {
					number = temp;
					return number;
				}
				break;
			}
			default: {
				break;
			}
		}
	}
	scanf("%*[^\n]");
	number = temp;
	return (task == UNSELECTED && number == done)
					? terminate()
				: number;
}

void printMenu(){
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1.Enter Daily Data For A Brand\n"
           "2.Populate A Day Of Sales For All Brands\n"
           "3.Provide Daily Stats\n"
           "4.Print All Data\n"
           "5.Provide Overall (simple) Insights\n"
           "6.Provide Average Delta Metrics\n"
           "7.exit\n");
}

void initCube(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]) {
	for (int i = 0; i < DAYS_IN_YEAR; i++) {
		for (int j = 0; j < NUM_OF_BRANDS; j++) {
			for (int k = 0; k < NUM_OF_TYPES; k++) {
				cube[i][j][k] = -1;
			}
		}
	}
}

int chosenAddOne(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]) {
    int brandIndex = enterNumber(addOne);
    if (brandIndex == EOF) {
        return EOF;
    }
    if (brandIndex < 0 || brandIndex >= NUM_OF_BRANDS) {
        printf("This brand is not valid\n");
		return UNSELECTED;
    }

    return 1;
}

int main() {
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    initCube(cube);
    while(choice != done){
        if ((choice = enterNumber(UNSELECTED)) == EOF || choice == done) {
            break;
        }
        if (choice < addOne || choice > deltas) {
            choice = UNSELECTED;
            scanf("%*[^\n]");
        }
        switch(choice){
            case addOne: {
                chosenAddOne(cube);
                break;
            }
            case addAll: {
                break;
            }
            default: {
                printf("Invalid input\n");
            }
        }
    }
    printf("Goodbye!\n");
    return 0;
}


