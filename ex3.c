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
#define NONE -1
#define UNSELECTED 0
#define addOne  1
#define addAll  2  
#define stats  3
#define print  4
#define insights  5
#define deltas  6
#define done  7

// most ind
#define AMOUNT 0
#define BRAND 1
#define mSIZE 2
// most arrs
int mostSales[DAYS_IN_YEAR][mSIZE];
int mostType[DAYS_IN_YEAR][mSIZE];

char brands[NUM_OF_BRANDS][BRANDS_NAMES]={"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES]={"SUV", "Sedan", "Coupe", "GT"};
int days[NUM_OF_BRANDS];
int choice;

long long enterNumber(int task){
	switch(task){
		case UNSELECTED:{
			printMenu();
			break;
		}
		case addOne:{
			printf("What brand?\n");
			break;
		}
		default:{
			break;
		}
	}
	long long number=0, temp=0;
	int input=0;
	while((input=scanf(" %lld", &temp))!=1 || temp<0 || task==UNSELECTED){
		if(input==EOF){
			return EOF;
		}
		scanf("%*[^\n]");
		switch(task){
			case UNSELECTED:{
				if(temp==done){
					return done;
				}
				if(temp>=addOne && temp <= done){
					number=temp;
					return number;
				}
				break;
			}
			default:{
				break;
			}
		}
	}
	scanf("%*[^\n]");
	number=temp;
	return number;
}

void printMenu(){
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1.Enter Daily Data For A Brand\n"
           "2.Populate A Day Of Sales For All Brands\n"
           "3.Provide Daily Stats\n"
           "4.Print All Data\n"
           "5.Provide Overall(simple) Insights\n"
           "6.Provide Average Delta Metrics\n"
           "7.exit\n");
}

void displayDay(int brand){
	int day=NONE;
	while(++day<=days[brand]){
		printf("Day %d-", day+1);
		for(int i=0; i<DAYS_IN_YEAR; i++){
			for(int j=0; j<NUM_OF_BRANDS; j++){
				for(int k=0; k<NUM_OF_TYPES; k++){
					printf(" %s: ", types[i]);
				}
			}
		}
	}
}

int getDay(int latestDay){
	int day = NONE;
	printf("What day would you like to analyze?\n");
	day = enterNumber(stats);
	if (day<0 || day>latestDay){
		printf("Please enter a valid day.\n");
		getDay(latestDay);
	}
	return day;
}

void express(int focus){
	switch(focus){
		case addOne:{
			return;
		}
		case addAll:{
			printf("No data for brands");

			for(int i=0; i<NUM_OF_BRANDS; i++){
				for(int j=0; j<; j++){
					for(int k=0; k<NUM_OF_TYPES; k++){
						printf(" %s");
					}
				}
			}
			
			printf("Please complete the data\n");
			return;
		}
		case stats:{
			int day=NONE, latestDay=NONE, totalSum=NONE;
			for(int i; i<NUM_OF_BRANDS; i++){
				if(days[i]>latestDay){
					latestDay=days[i];
				}
			}
			if (latestDay==NONE){
				return;
			}
			day=getDay(latestDay);
			printf("In day number %d:\n", day);
			// conditional
			printf("The sales total was %d\n", totalSum);
			printf("The best sold brand with %d sales was %s\n", mostSales[day][AMOUNT], mostSales[day][BRAND]);
			printf("The best sold type with 9 sales was GT\n", mostType[day][AMOUNT], mostType[day][BRAND]);
			return;
		}
		case print:{
			int brand=NONE;
			while(brand<NUM_OF_BRANDS){
				printf("Sales for %s:\n", brands[brand]);
				if(days[brand]==NONE){
					continue;
				}
				displayDay(brand);
			}
			return;
		}
		case insights:{
			int bBrand=bestBrand();
			printf("The best-selling brand overall is %s: %d\n$", bBrand, sales(bBrand));
			int bType=bestType();
			printf("The best-selling type of car is %s: %d$\n", bType, sales(bType));
			int bDay=bestDay();
			printf("The most profitable day was day number %d: %d$\n", bDay, sales(bDay));
			return;
		}
		case deltas:{
			int brand=0;
			printf("Brand: %s, Average Delta: %1.6f\n", brands[brand], avgDelta(brand++));
			brand++;
			return;
		}
		case done:{
			printf("Goodbye!\n");
			return;
		}
		default:{
			return;
		}
	}
}

void init(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]){
	for(int i=0; i<DAYS_IN_YEAR; i++){
		mostSales[i][AMOUNT]=mostSales[i][BRAND]=NONE;
		mostType[i][AMOUNT]=mostType[i][BRAND]=NONE;
		for(int j=0; j<NUM_OF_BRANDS; j++){
			days[j]=NONE;
			for(int k=0; k<NUM_OF_TYPES; k++){
				cube[i][j][k]=NONE;
			}
		}
	}
}

int chosenAddOne(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]){
    int brandIndex=enterNumber(addOne);
    // program termination
    if(brandIndex==EOF){
        return EOF;
    }
    // invalid brand
    if(brandIndex<0 || brandIndex>=NUM_OF_BRANDS){
        printf("This brand is not valid\n");
		return UNSELECTED;
    }
    // make function
    return 1;
}

int main(){
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    init(cube);
    while(choice!=done){
        if((choice=enterNumber(UNSELECTED))==EOF || choice==done){
            break;
        }
        if(choice<addOne || choice>deltas){
            choice=UNSELECTED;
            scanf("%*[^\n]");
        }
        switch(choice){
            case addOne:{
                chosenAddOne(cube);
                break;
            }
            case addAll:{
                break;
            }
            default:{
                printf("Invalid input\n");
            }
        }
    }
    printf("Goodbye!\n");
    return 0;
}

