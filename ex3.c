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

/********************************************
brand assigns
*******************************************/
#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
char brands[NUM_OF_BRANDS][BRANDS_NAMES]={"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};

/********************************************
time assigns
*******************************************/
#define DAYS_IN_YEAR 365
int days[NUM_OF_BRANDS];
int earliestDay = NONE;
int latestDay = NONE;
int inputDay();

/********************************************
type assigns
*******************************************/
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
char types[NUM_OF_TYPES][TYPES_NAMES]={"SUV", "Sedan", "Coupe", "GT"};
int mostType[DAYS_IN_YEAR][2];

/********************************************
sales assigns
*******************************************/
int mostSales[DAYS_IN_YEAR][2];

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
int addAllChosen(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);
int statsChosen(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);
void printChosen(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);
void insightsChosen(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);
void deltasChosen(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);
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
time funcs
*******************************************/
void getEarliestDay(){
	earliestDay = DAYS_IN_YEAR;
	for(int brand=0; brand<NUM_OF_BRANDS; brand++){
		if(days[brand]<earliestDay){
			earliestDay=days[brand];
		}
	}
}

void getLatestDay(){
	for(int brand=0; brand<NUM_OF_BRANDS; brand++){
		if(days[brand]>latestDay){
			latestDay=days[brand];
		}
	}
}

void displayData(int brand, int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]){
	for(int day=0; day<=days[brand]; day++){
		printf("Day %d-", day+1);
		for(int type=0; type<NUM_OF_TYPES; type++){
			printf(" %s: %d",
				types[type],
				cube[day][brand][type]);
		}
		printf("\n");
	}
}

/********************************************
initialize funcs
*******************************************/
void init(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]){
	for(int day=0; day<DAYS_IN_YEAR; day++){
		mostSales[day][0]=mostSales[day][1]=NONE;
		mostType[day][0]=mostType[day][1]=NONE;
		for(int brand=0; brand<NUM_OF_BRANDS; brand++){
			if(day==0){days[brand] = NONE;}
			for(int type=0; type<NUM_OF_TYPES; type++){
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
				if(inputData(cube)==EOF)
					goto term;
			break;
			}
			case addAll:
			{
				if (addAllChosen(cube)==EOF)
					goto term;
			break;
			}
			case stats:
			{
				if(latestDay>NONE
				&&statsChosen(cube)==EOF){
					goto term;
				}
			break;
			}
			case print:
			{
				printChosen(cube);
			break;
			}
			case insights:
			{
				if(latestDay>NONE){
					insightsChosen(cube);
				}
				break;
			}
			case deltas:
			{
				deltasChosen(cube);
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
	int day=NONE, temp=0, input=UNSELECTED, min=1, max=latestDay+1;
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

/********************************************
add funcs
*******************************************/
int noticeNoData(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]){
	int today=earliestDay+1, foundMissing=0;
	if (today<DAYS_IN_YEAR){
		for(int brand=0; brand<NUM_OF_BRANDS; brand++){
			if(cube[today][brand][0]==NONE){
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

int addAllChosen(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]){
	for(int brand=0; brand<NUM_OF_BRANDS, days[brand]<DAYS_IN_YEAR-1; brand++){
		while(noticeNoData(cube)){
			if(inputData(cube)==EOF){
				return EOF;
	}}}
	return 1;
}

int inputData(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]){
	int input=0, today=earliestDay+1, tempBrand=NONE, tempST[NUM_OF_TYPES];
	for(int type=0; type<NUM_OF_TYPES; type++){
		tempST[type]=NONE;
	}
	while((input=scanf(" %d %d %d %d %d", &tempBrand,
	&tempST[0], &tempST[1], &tempST[2], &tempST[3]))!=5  // 5 = 1 (brand id) + 4 (types)
	||tempBrand<0 ||tempBrand>=NUM_OF_BRANDS
	||tempST[0]<0 ||tempST[1]<0 ||tempST[2]<0 ||tempST[3]<0
	||cube[today][tempBrand][0]!=NONE){
		if(input==EOF) return EOF;
		scanf("%*[^\n]");
		printf("This brand is not valid\n");
		tempBrand=tempST[0]=tempST[1]=tempST[2]=tempST[3]=NONE;
	}
	scanf("%*[^\n]");
	int brand=tempBrand;
	int sales=NONE;
	for(int type=0; type<NUM_OF_TYPES; type++){
		sales=tempST[type];
		cube[today][brand][type]=sales;
	}
	days[brand]++;
	return 1;
}

/********************************************
print funcs
*******************************************/
void printChosen(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]){
	int brand=0;
	while(brand<NUM_OF_BRANDS){
		printf("Sales for %s:\n", brands[brand]);
		if(days[brand]>NONE){
			displayData(brand, cube);
		}
		brand++;
	}
}

/********************************************
stats/insights funcs
*******************************************/

// int best(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day, int focus){
// 	int total=0;
// 	for(int brand=0; brand<NUM_OF_BRANDS; brand++){
// 		for(int type=0; type<NUM_OF_TYPES; type++){
// 			total+=cube[day][brand][type];
// 		}
// 	}
// 	for(int brand=0, bestBrand=0, salesBrand=0; brand<NUM_OF_BRANDS; brand++){
// 		int tempSales=0;
// 		for(int type=0; type<NUM_OF_TYPES; type++){
// 			tempSales+=cube[day][brand][type];
// 			if(type==NUM_OF_TYPES-1){
// 				if(tempSales>salesBrand){
// 					salesBrand=tempSales;
// 					bestBrand=brand;
// 				}
// 				if(brand==NUM_OF_BRANDS-1){
// 					printf("The best sold brand with %d sales was %s\n",
// 						best(cube, SALES),
// 						best(cube, BRAND));
// 						// salesBrand,
// 						// brands[bestBrand]);
// 				}
// 			}
// 		}
// 	}
// 	for(int type=0, bestType=0, salesType=0; type<NUM_OF_TYPES; type++){
// 		int tempSales=0;
// 		for(int brand=0; brand<NUM_OF_BRANDS; brand++){
// 			tempSales+=cube[day][brand][type];
// 			if(brand==NUM_OF_BRANDS-1){
// 				if(tempSales>salesType){
// 					salesType=tempSales;
// 					bestType=type;
// 				}
// 				if(type==NUM_OF_TYPES-1){
// 					printf("The best sold type with %d sales was %s\n",
// 						salesType,
// 						types[bestType]);
// 				}
// 			}
// 		}
// 	}
// }

int statsChosen(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]){
	int day=inputDay();
	if(day==EOF)
		{return EOF;}
	printf("In day number %d:\n", day+1);
	int total=0;
	for(int brand=0; brand<NUM_OF_BRANDS; brand++){
		for(int type=0; type<NUM_OF_TYPES; type++){
			total+=cube[day][brand][type];
		}
	}
	printf("The sales total was %d\n", total);
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
	for(int type=0, bestType=0, salesType=0; type<NUM_OF_TYPES; type++){
		int tempSales=0;
		for(int brand=0; brand<NUM_OF_BRANDS; brand++){
			tempSales+=cube[day][brand][type];
			if(brand==NUM_OF_BRANDS-1){
				if(tempSales>salesType){
					salesType=tempSales;
					bestType=type;
				}
				if(type==NUM_OF_TYPES-1){
					printf("The best sold type with %d sales was %s\n",
						salesType,
						types[bestType]);
				}
			}
		}
	}
	return 1;
}
// combine redundant: stats, insights
void insightsChosen(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]){
	int best=0, sales=0;
	for(int brand=0; brand<NUM_OF_BRANDS; brand++){
		int temp=0;
		for(int day=0; day<DAYS_IN_YEAR; day++){
			for(int type=0; type<NUM_OF_TYPES; type++){
				temp+=cube[day][brand][type];
			}
		}
		if(temp>sales){
			sales=temp;
			best=brand;
		}
	}
	printf("The best-selling brand overall is %s: %d$\n", brands[best], sales);

	best=0, sales=0;
	for(int type=0; type<NUM_OF_TYPES; type++){
		int temp=0;
		for(int day=0; day<DAYS_IN_YEAR; day++){
			for(int brand=0; brand<NUM_OF_BRANDS; brand++){
				temp+=cube[day][brand][type];
			}
		}
		if(temp>sales){
			sales=temp;
			best=type;
		}
	}
	printf("The best-selling type of car is %s: %d$\n", types[best], sales);

	best=0, sales=0;
	for(int day=0; day<DAYS_IN_YEAR; day++){
		int temp=0;
		for(int type=0; type<NUM_OF_TYPES; type++){
			for(int brand=0; brand<NUM_OF_BRANDS; brand++){
				temp+=cube[day][brand][type];
			}
		}
		if(temp>sales){
			sales=temp;
			best=day;
		}
	}
	printf("The most profitable day was day number %d: %d$\n", best, sales);
}

/********************************************
deltas funcs
*******************************************/
void deltasChosen(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]){
	if(latestDay<1){
		for(int brand=0; brand<NUM_OF_BRANDS; brand++){
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
		for(int brand=0; brand<NUM_OF_BRANDS; brand++){
			printf("Brand: %s, Average Delta: %1.6f\n", brands[brand], daySum[brand]/latestDay);
		}
	}
}

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