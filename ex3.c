/******************
Name:
ID:
Assignment: ex3
*******************/
#include <stdio.h>

/********************************************
misc. mess assigns
*******************************************/
#define NONE -1
#define UNSELECTED 0
#define INITIAL 0
#define mAMOUNT 0
#define mBRAND 1
#define mSIZE 2

/********************************************
navigation assigns
*******************************************/
int inputChoice();
int choice;

/********************************************
path assigns
*******************************************/
#define addOne  1
#define addAll  2  
#define stats  3
#define print  4
#define insights  5
#define deltas  6
#define done  7

/********************************************
brand assigns
*******************************************/
#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
char brands[NUM_OF_BRANDS][BRANDS_NAMES]={"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
int bestBrand();

/********************************************
time assigns
*******************************************/
#define DAYS_IN_YEAR 365
int days[NUM_OF_BRANDS];
int latestDay = NONE;
int bestDay();

/********************************************
type assigns
*******************************************/
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
char types[NUM_OF_TYPES][TYPES_NAMES]={"SUV", "Sedan", "Coupe", "GT"};
int bestType();
int mostType[DAYS_IN_YEAR][mSIZE];

/********************************************
sales assigns
*******************************************/
int sales(int x);
int mostSales[DAYS_IN_YEAR][mSIZE];
float avgDelta(int brand);

/********************************************
data cube assigns
*******************************************/
int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];

/********************************************
brand funcs
*******************************************/
int bestBrand(){
	return 0;
}

/********************************************
time funcs
*******************************************/
int bestDay(){
	return 0;
}

int getLatestDay(){
	int temp = NONE;
	for(int brand=INITIAL; brand<NUM_OF_BRANDS; brand++){
		if(days[brand]>latestDay) latestDay=days[brand]; temp = days[brand];  
	} return temp;
}

int inputDay(){
	int day = NONE;
	printf("What day would you like to analyze?\n");
	day = enterNumber(stats);
	if (day<INITIAL || day>latestDay){
		printf("Please enter a valid day.\n");
		inputDay();
	} return day;
}

void displayDay(int brand){
	int currentDay=NONE;
	while(++currentDay<=days[brand]){
		printf("Day %d-", currentDay+1);
		for(int day=INITIAL; day<DAYS_IN_YEAR; day++){
			for(int brand=INITIAL; brand<NUM_OF_BRANDS; brand++){
				for(int type=INITIAL; type<NUM_OF_TYPES; type++){
					printf(" %s: ", types[day]);
}}}}}

/********************************************
type funcs
*******************************************/
int bestType(){
	return 0;
}

/********************************************
sales funcs
*******************************************/
int sales(int x){
	x=0;
	return x;
}

float avgDelta(int brand){
	brand=0;
	return brand;
}

/********************************************
misc. mess funcs
*******************************************/
void express(int focus){switch(focus){
		case addOne: return;
		case addAll: int today = latestDay;
			printf("No data for brands");
			if (today==NONE){today=INITIAL;}
			for(int brand=INITIAL; brand<NUM_OF_BRANDS; brand++){
				if (cube[today][brand][INITIAL]==NONE) printf(" %s", brands[brand]);
			} printf("\nPlease complete the data\n"); return;
		case stats: int day=NONE, totalSum=NONE;
			if(getLatestDay()==NONE) return;
			day=inputDay();
			printf("In day number %d:\n", day);
			printf("The sales total was %d\n", totalSum);
			printf("The best sold brand with %d sales was %s\n",
				mostSales[day][mAMOUNT],
				brands[mostSales[day][mBRAND]]);
			printf("The best sold type with %d sales was %s\n",
				mostType[day][mAMOUNT],
				types[mostType[day][mBRAND]]
			); return;
		case print:{ int brand=NONE;
			while(brand<NUM_OF_BRANDS){
				printf("Sales for %s:\n", brands[brand]);
				if(days[brand]==NONE) continue;
				displayDay(brand);
			} return;
		}
		case insights: int bBrand=bestBrand(); int bType=bestType(); int bDay=bestDay();
			printf("The best-selling brand overall is %s: %d\n$",
				brands[bBrand],
				sales(bBrand));
			printf("The best-selling type of car is %s: %d$\n",
				types[bType],
				sales(bType));
			printf("The most profitable day was day number %d: %d$\n",
				bDay,
				sales(bDay)
			); return;
		case deltas:
			int brand=INITIAL;
			while(brand<NUM_OF_BRANDS){
				printf("Brand: %s, Average Delta: %1.6f\n",
					brands[brand],
					avgDelta(brand++));
			} return;
		case done: printf("Goodbye!\n"); return;
		default:{
			return;
		}
	}
}

// long long inputData(){
//     int value = NONE;
//     char confirm = '\0';
//     do {
//         printf("%s", prompt);
//         if (scanf(" %d%c", &value, &confirm) != 2 || confirm != '\n') {
//             scanf("%*[^\n]");
//             printf("Invalid\n");  
//             value=NONE;
//         }
//     } while (value==NONE);
//     return value;
// }

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
		case stats:{
			break;
		}
		default:{
			break;
		}
	}
	long long number=UNSELECTED, temp=UNSELECTED;
	int input=NONE;
	while((input=scanf(" %lld", &temp))!=1 || temp<UNSELECTED || task==UNSELECTED){
		if(input==EOF){
			return EOF;
		}
		scanf("%*[^\n]");
		switch(task){
			case UNSELECTED:{
				if(temp==done){
					return done;
				}
				if(temp>=addOne && temp<=done){
					number=temp;
					return number;
				}
				break;
			}
			case addOne:{
				scanf("%*[^\n]");
				if(temp<INITIAL || temp>=NUM_OF_BRANDS){
					continue;
				}
				// int iter = NUM_OF_TYPES;
				break;
			}
			case addAll:{

				break;
			}
			case stats:{
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

/********************************************
addOne funcs
*******************************************/
int chosenAddOne(){
    int brandIndex=enterNumber(addOne);
    if(brandIndex==EOF) return EOF;
    if(brandIndex<INITIAL || brandIndex>=NUM_OF_BRANDS){printf("This brand is not valid\n"); return UNSELECTED;}
    return 1;
}

/********************************************
initialize funcs
*******************************************/
void init(){
	for(int day=INITIAL; day<DAYS_IN_YEAR; day++){
		mostSales[day][mAMOUNT]=mostSales[day][mBRAND]=NONE;
		mostType[day][mAMOUNT]=mostType[day][mBRAND]=NONE;
		for(int brand=INITIAL; brand<NUM_OF_BRANDS; brand++){days[brand]=NONE;
			for(int type=INITIAL; type<NUM_OF_TYPES; type++){cube[day][brand][type]=NONE;}
		}
	}
}

/********************************************
navigate funcs
*******************************************/
int main(){
    init();
    while((inputChoice())!=done){
		getLatestDay();
		printf("choice = %d\n", choice);
        switch(choice){
            case addOne: chosenAddOne(); break;
            case addAll: express(addAll); break;
            default: printf("Invalid input\n");
        }
    } printf("Goodbye!\n"); return 0;
}

int printMenu(){  // temporarily int (void)
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1.Enter Daily Data For A Brand\n"
           "2.Populate A Day Of Sales For All Brands\n"
           "3.Provide Daily Stats\n"
           "4.Print All Data\n"
           "5.Provide Overall(simple) Insights\n"
           "6.Provide Average Delta Metrics\n"
           "7.exit\n");
	return 1; // temporary returns int (void)
}

/********************************************
input funcs
*******************************************/
int inputChoice(){choice=UNSELECTED; int temp=UNSELECTED, input=UNSELECTED;
    while((printMenu() && ((input=scanf(" %d", &temp)) != 1 || temp<addOne || temp>done))){
		if(input==EOF) return done;
		scanf("%*[^\n]"); printf("Invalid input\n"); temp=UNSELECTED;
	} scanf("%*[^\n]"); choice=temp; return choice;
}
