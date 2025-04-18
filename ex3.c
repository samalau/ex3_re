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
int earliestDay = NONE;
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

void getEarliestDay(){
	earliestDay = DAYS_IN_YEAR;
	for(int brand=INITIAL; brand<NUM_OF_BRANDS; brand++){
		if(days[brand]<earliestDay){
			earliestDay=days[brand];
		}
	}
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
			if(day==INITIAL){days[brand] = NONE;}
			for(int type=INITIAL; type<NUM_OF_TYPES; type++){
				cube[day][brand][type]=NONE;
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
		getLatestDay();
		getEarliestDay();
		switch(choice){
			case addOne:
			{
				if(inputData(cube)==EOF){goto term;}
			break;
			}
			case addAll:
			{
				for(int brand=0; brand<NUM_OF_BRANDS; brand++){
					if(days[brand]<DAYS_IN_YEAR-1){
						while(noticeNoData(cube)){
							if(inputData(cube)==EOF){goto term;}
						}
					}
				}
			break;
			}
			case stats:
			{
				if(latestDay<=NONE){break;}
				int day=inputDay();
				if(day==EOF){goto term;}

				printf("In day number %d:\n", day+1);
				int total=0;
				for(int brand=0; brand<NUM_OF_BRANDS; brand++){
					for(int type=0; type<NUM_OF_TYPES; type++){
						total+=cube[day][brand][type];
						if(brand==NUM_OF_BRANDS-1 &&type==NUM_OF_TYPES-1){
							printf("The sales total was %d\n", total);
						}
					}
				}
				// int bestBrand=0, salesBrand=0;
				for(int brand=0, bestBrand=0, salesBrand=0; brand<NUM_OF_BRANDS; brand++){
					int tempSales=0;
					for(int type=0; type<NUM_OF_TYPES; type++){
						tempSales+=cube[day][brand][type];
						if(type==NUM_OF_TYPES-1){
							if(tempSales>salesBrand){
								salesBrand=tempSales;
								bestBrand=brand;
							}
							if(brand==NUM_OF_BRANDS-1){
								printf("The best sold brand with %d sales was %s\n",
									salesBrand,
									brands[bestBrand]);
							}
						}
					}
				}
				
				// printf("The best sold type with %d sales was %s\n",
				// 	mostType[day][mAMOUNT], types[mostType[day][mBRAND]]);
			break;
			}
			case print:
			{
				int brand=INITIAL;
				while(brand<NUM_OF_BRANDS){
					printf("Sales for %s:\n", brands[brand]);
					if(days[brand]>NONE){displayData(brand, cube);}
					brand++;
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
				if(latestDay<1){
					for(int brand=INITIAL; brand<NUM_OF_BRANDS; brand++){
						printf("Brand: %s, Average Delta: 0.000000\n", brands[brand]);
					}
				}else{
					float daySum[NUM_OF_BRANDS] = {0};
					for(int b=1, a=0; a<latestDay; b++, a++){
						for(int j=0; j<NUM_OF_TYPES; j++){
							for(int k=0; k<NUM_OF_BRANDS; k++){
								daySum[k]+=cube[b][k][j]-cube[a][k][j];
							}
						}
					}
					for(int brand=INITIAL; brand<NUM_OF_BRANDS; brand++){
						printf("Brand: %s, Average Delta: %1.6f\n", brands[brand], daySum[brand]/latestDay);
					}
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
	}
	term:
	printf("Goodbye!\n");
	return 0;
}

int printMenu(){
	return printf("Welcome to the Cars Data Cube! What would you like to do?\n"
	"1.Enter Daily Data For A Brand\n"
	"2.Populate A Day Of Sales For All Brands\n"
	"3.Provide Daily Stats\n"
	"4.Print All Data\n"
	"5.Provide Overall (simple) Insights\n"
	"6.Provide Average Delta Metrics\n"
	"7.exit\n");
}

/********************************************
input funcs
*******************************************/
int inputChoice(){
	choice=UNSELECTED;
	int input=UNSELECTED, temp=UNSELECTED;
	while(printMenu() &&((input=scanf(" %d", &temp)) != 1
	||temp<addOne ||temp>done)){
		if(input==EOF){
			return done;
		}
		scanf("%*[^\n]");
		printf("Invalid input\n");
		temp=UNSELECTED;
	}
	scanf("%*[^\n]");
	choice=temp;
	return choice;
}

int inputDay(){
	int day=NONE, temp=NONE, input=UNSELECTED, min=1, max=latestDay+1;
	while(printf("What day would you like to analyze?\n")
	&&((input=scanf(" %d", &temp))!=1
	||temp<min ||temp>max)){
		if(input==EOF) return EOF;
		scanf("%*[^\n]");
		printf("Please enter a valid day.\n");
		temp=NONE;
	}
	scanf("%*[^\n]");
	day=temp-1;
	return day;
}

int noticeNoData(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]){
	int today=earliestDay+1, foundMissing=0;
	if (today<DAYS_IN_YEAR){
		for(int brand=INITIAL; brand<NUM_OF_BRANDS; brand++){
			if(cube[today][brand][INITIAL]==NONE){
				if(!foundMissing){
					printf("No data for brands");
					printf(" %s", brands[brand]);
					foundMissing=1;
					continue;
				}
				printf(" %s", brands[brand]);
			}	
		}
	}
	return (foundMissing)?printf("\nPlease complete the data\n"):0;
}

int inputData(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]){
	int input=0, today=earliestDay+1, tempBrand=NONE, tempST[NUM_OF_TYPES];
	for(int type=INITIAL; type<NUM_OF_TYPES; type++){
		tempST[type]=NONE;
	}
	while((input=scanf(" %d %d %d %d %d", &tempBrand,
	&tempST[0], &tempST[1], &tempST[2], &tempST[3]))!=5  // 5 = 1 (brand id) + 4 (types)
	||tempBrand<0 ||tempBrand>=NUM_OF_BRANDS
	||tempST[0]<0 ||tempST[1]<0 ||tempST[2]<0 ||tempST[3]<0
	||cube[today][tempBrand][INITIAL]!=NONE){
		if(input==EOF) return EOF;
		scanf("%*[^\n]");
		printf("This brand is not valid\n");
		tempBrand=tempST[0]=tempST[1]=tempST[2]=tempST[3]=NONE;
	}
	scanf("%*[^\n]");
	int brand=tempBrand;
	int sales=NONE;
	for(int type=INITIAL; type<NUM_OF_TYPES; type++){
		sales=tempST[type];
		cube[today][brand][type]=sales;
	}
	days[brand]++;
	return 1;
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

/*
2
0
1 1 1 1
1
2 1 1 1
2
1 1 1 3
3
1 1 1 1
4
1 1 1 1
2
0
1 1 1 1
1
2 1 1 4
2
1 1 1 3
3
20 1 1 1
4
1 1 1 1
2
0
1 1 1 1
1
2 1 3 1
2
1 1 1 3
3
1 1 1 1
4
1 1 1 1
2
0
1 1 1 1
1
2 2 3 3
2
1 1 1 3
3
1 1 1 1
4
1 1 1 1
3
5
4
4
END_INPUT
*/