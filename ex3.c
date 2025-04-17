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
int inputDay();
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
// int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
void init(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);
int inputData(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);
int noticeNoData(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);
void displayData(int brand, int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);

/********************************************
navigation assigns
*******************************************/
int inputChoice();
int addOneChosen(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);
int addAllChosen(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);
void statsChosen();
void printChosen();
void insightsChosen();
void deltasChosen();
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

void getLatestDay(){
	for(int brand=INITIAL; brand<NUM_OF_BRANDS; brand++){
		if(days[brand]>latestDay){
			latestDay=days[brand];
		}
	}
}

void displayData(int brand, int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]){
	for(int day=INITIAL; day<=days[brand]; day++){
		printf("Day %d-", day+1);
		for(int type=INITIAL; type<NUM_OF_TYPES; type++){
			printf(" %s: %d",
				types[type],
				cube[day][brand][type]);
		}
		printf("\n");
	}
}

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
initialize funcs
*******************************************/
void init(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]){
	for(int day=INITIAL; day<DAYS_IN_YEAR; day++){
		mostSales[day][mAMOUNT]=mostSales[day][mBRAND]=NONE;
		mostType[day][mAMOUNT]=mostType[day][mBRAND]=NONE;
		for(int brand=INITIAL; brand<NUM_OF_BRANDS; brand++){
			days[brand]=NONE;
			for(int type=INITIAL; type<NUM_OF_TYPES; type++){
				cube[day][brand][type]=NONE;
				// printf("DEBUG: (init) cube[day][brand][type] = %d\n", cube[day][brand][type]);
		}  }
	}
}

/********************************************
navigate funcs
*******************************************/
int main(){
	int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
	init(cube);
	while((inputChoice())!=done){
		// printf("DEBUG: (0)latestDay is %d\n", latestDay);
		getLatestDay();
		// printf("DEBUG: (1)latestDay is %d\n", latestDay);
		// printf("choice = %d\n", choice);
		switch(choice){
			case addOne:
			{
				// int today=(latestDay==NONE) ?INITIAL :latestDay;
				if(addOneChosen(cube)==EOF) goto term;
			break;
			}
			case addAll:
			{
				for(int brand=0; brand<NUM_OF_BRANDS; brand++){
					if(days[brand]<DAYS_IN_YEAR-1)
						if(addAllChosen(cube)==EOF) goto term;
				// printf("DEBUG: FULL DAYS\n");
				}
			break;
			}
			case stats:
			{
				int day=NONE; // totalSum=NONE;
				if(latestDay==NONE) break;
				day=inputDay();
				if(day==EOF) goto term;

				printf("DEBUG: In day number _:\n");
				// printf("In day number %d:\n", day);
				
				printf("DEBUG: The sales total was _\n");
				// printf("The sales total was %d\n", totalSum);

				printf("DEBUG: The best sold brand with _ sales was _\n");
				// printf("The best sold brand with %d sales was %s\n",
				// 	mostSales[day][mAMOUNT], brands[mostSales[day][mBRAND]]);

				printf("DEBUG: The best sold type with _ sales was _\n");
				// printf("The best sold type with %d sales was %s\n",
				// 	mostType[day][mAMOUNT], types[mostType[day][mBRAND]]);
			break;
			}
			case print:
			{
				int brand=0;  // MAGIC
				while(brand<NUM_OF_BRANDS){
					printf("Sales for %s:\n", brands[brand]);
					if(days[brand]>NONE) {
						displayData(brand, cube);
					} brand++;
				}
			break;
			}
			case insights:
			{
				// int bBrand=bestBrand(), bType=bestType(), bDay=bestDay();
				printf("DEBUG: The best-selling brand overall is fuckyou: fuckyoudie$\n");
				// printf("The best-selling brand overall is %s: %d$\n",
				// 	brands[bBrand],
				// 	sales(bBrand));

				printf("DEBUG: The best-selling type of car is f: u$\n");
				// printf("The best-selling type of car is %s: %d$\n",
				// 	types[bType],
				// 	sales(bType));

				printf("DEBUG: The most profitable day was day number fuck: youdie$\n");
				// printf("The most profitable day was day number %d: %d$\n",
				// 	bDay,
				// 	sales(bDay));
			break;
			}
			case deltas:
			{
				int brand=NONE;
				while(++brand<NUM_OF_BRANDS){
					printf("DEBUG: Brand: f u c k, Average Delta: y o u\n");
					// printf("Brand: %s, Average Delta: %1.6f\n",
					// 	brands[brand],
					// 	avgDelta(brand));
				}
			break;
			}
			case done:
			{
				goto term;
			break;
			}
			default:
			{
				printf("Invalid input\n");
			break;
			}
		}
	} term:
	printf("Goodbye!\n");
	return 0;
}

int printMenu(){  // temporarily int (void)
	printf("Welcome to the Cars Data Cube! What would you like to do?\n"
		   "1.Enter Daily Data For A Brand\n"
		   "2.Populate A Day Of Sales For All Brands\n"
		   "3.Provide Daily Stats\n"
		   "4.Print All Data\n"
		   "5.Provide Overall (simple) Insights\n"
		   "6.Provide Average Delta Metrics\n"
		   "7.exit\n");
	return 1; // temporary returns int (void)
}

/********************************************
input funcs
*******************************************/
int inputChoice(){
	choice=UNSELECTED; int temp=UNSELECTED, input=UNSELECTED;
	while(printMenu() &&((input=scanf(" %d", &temp)) != 1 ||temp<addOne ||temp>done)){
		if(input==EOF) return done;
		scanf("%*[^\n]"); printf("Invalid input\n"); temp=UNSELECTED;
	} scanf("%*[^\n]"); choice=temp; return choice;
}

int inputDay(){
	int day=NONE, temp=NONE, input=UNSELECTED;
	while(printf("What day would you like to analyze?\n") &&((input=scanf(" %d", &temp)) != 1 ||temp<INITIAL ||temp>latestDay)){
		if(input==EOF) return EOF;
		scanf("%*[^\n]"); printf("Please enter a valid day.\n"); temp=NONE;
	} scanf("%*[^\n]"); day=temp; return day;
}

int noticeNoData(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]){
	printf("No data for brands");
	for(int brand=INITIAL; brand<NUM_OF_BRANDS; brand++){
		if(cube[days[brand]+1][brand][INITIAL]==NONE)
			printf(" %s", brands[brand]);
	}
	printf("\nPlease complete the data\n");
	return 1;
}

int inputData(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]){
	int input=0, tempBrand=NONE, tempST[NUM_OF_TYPES];
	for(int i=0; i<NUM_OF_TYPES; i++){
		tempST[i] = NONE;
	}
	// MAGIC: !=5
	while(noticeNoData(cube)
		&&((input=scanf(" %d %d %d %d %d", &tempBrand, &tempST[0], &tempST[1], &tempST[2], &tempST[3])) !=5
		||tempBrand<0 ||tempBrand>=NUM_OF_BRANDS ||tempST[0]<0 ||tempST[1]<0 ||tempST[2]<0 ||tempST[3]<0
	)){
		if(input==EOF) return EOF;
		scanf("%*[^\n]"); printf("This brand is not valid\n");
		tempBrand=tempST[0]=tempST[1]=tempST[2]=tempST[3]=-1;
	}
	scanf("%*[^\n]");
	int brand=tempBrand;
	int sales=0;  // MAGIC
	for(int type=0; type<NUM_OF_TYPES; type++){
		// printf("DEBUG: (0)tempST[type] = %d\n", tempST[type]);
		sales = tempST[type];
		// printf("DEBUG: (0)sales = %d\n", sales);
		// printf("DEBUG: (0)cube[latestDay][brand][type] = %d\n", cube[days[brand]+1][brand][type]);
		// make days[brand]+1 actually minimum
		cube[days[brand]+1][brand][type] = sales;
		// printf("DEBUG: (1)cube[latestDay][brand][type] = %d\n", cube[days[brand]+1][brand][type]);
	}
	return 1;
}

/********************************************
addOne funcs
*******************************************/
int addOneChosen(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]){
	// return (inputData(cube, today)==EOF) ?EOF :1;  // MAGIC
	int input=0, tempBrand=NONE, tempST[NUM_OF_TYPES];
	for(int i=0; i<NUM_OF_TYPES; i++){
		tempST[i] = NONE;
	}
	// MAGIC: !=5
	while(
		((input=scanf(" %d %d %d %d %d", &tempBrand, &tempST[0], &tempST[1], &tempST[2], &tempST[3])) !=5
		||tempBrand<0 ||tempBrand>=NUM_OF_BRANDS ||tempST[0]<0 ||tempST[1]<0 ||tempST[2]<0 ||tempST[3]<0
	)){
		if(input==EOF) return EOF;
		scanf("%*[^\n]"); printf("This brand is not valid\n");
		tempBrand=tempST[0]=tempST[1]=tempST[2]=tempST[3]=-1;
	}
	scanf("%*[^\n]");
	int brand=tempBrand;
	int sales=0;  // MAGIC
	for(int type=0; type<NUM_OF_TYPES; type++){
		sales = tempST[type];
		cube[days[brand]+1][brand][type] = sales;
	}
	days[brand]++;
	return 1;
}

/********************************************
addAll funcs
*******************************************/
int addAllChosen(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]){
	int types=NUM_OF_TYPES;
	while(types>0){
		if(inputData(cube)==EOF){
			return EOF;
	}  }
	return 1;  // MAGIC
}

/********************************************
stats funcs
*******************************************/
void statsChosen(){}

/********************************************
print funcs
*******************************************/
void printChosen(){}

/********************************************
insights funcs
*******************************************/
void insightsChosen(){}

/********************************************
deltas funcs
*******************************************/
void deltasChosen(){}