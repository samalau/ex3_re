/******************
Name: Samantha Newmark
ID:
Assignment: ex3
*******************/

#include <stdio.h>

// no data
#define NONE -1

// menu unselected
#define UNSELECTED 0

// task/menu selection 1: single day entry
#define addOne 1

// task/menu selection 2: full day entry
#define addAll 2

// task/menu selection 3: daily stats
#define stats 3

// task/menu selection 4: print data
#define	print 4

// task/menu selection 5: overall insights
#define insights 5

// task/menu selection 6: average deltas
#define	deltas 6

// menu selection 7: exit
#define	done 7

// index: 0 to 364
#define DAYS_IN_YEAR 365

// number of car brands
#define NUM_OF_BRANDS 5

// max brand name length
#define BRANDS_NAMES 15

// number of car types
#define NUM_OF_TYPES 4

// max type name length
#define TYPES_NAMES 10


// current main menu selection
int menuSelection;

// earliest entered day overall
int earliestDay = NONE;

// latest entered day overall
int	latestDay = NONE;


// latest day per brand
int	days[NUM_OF_BRANDS];
	
// sales data cube
int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];

// names
char brands[NUM_OF_BRANDS][BRANDS_NAMES]={"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types [NUM_OF_TYPES][TYPES_NAMES]={"SUV", "Sedan", "Coupe", "GT"}; 		


// initialize data cube cells to -1
void initCube();

// display main menu options
void printMenu();

// select option from main menu, update menuSelection global
void inputSelection();

// update (overall) earliest day global with valid data
void getEarliestDay();

// update (overall) latest day global with valid data
void getLatestDay();

// task 2: user selected to complete data for earliest incomplete day
int addAllChosen();

// get sales data per type per brand of earliest incomplete day
int inputData();

// identify what data for current day remains incomplete during input
int noticeNoData();

// task 3: user selected to display stats of chosen day
void statsChosen(int day);

// choose day to display stats
int inputDay();

// task 4: user selected to display all data
void printChosen();

// display all data
void displayData(int brand);

// get total sales of chosen day
int salesTotal(int day);

// get day with highest total sales 
void mostProfitableDay();

// get highest value of brand or type
void getBest(int path, int day, int subject, int items);

// task 5: user selected to display overall stats
void insightsChosen();

// task 6: user selected to display average delta of each brand
void deltasChosen();


/* INITIALIZE DATA CUBE */
void initCube(){
	for(int day=0; day<DAYS_IN_YEAR; day++){
		for(int brand=0; brand<NUM_OF_BRANDS; brand++){
			if(day==0){
				days[brand]=NONE;
			}
			for(int type=0; type<NUM_OF_TYPES; type++){
				cube[day][brand][type]=NONE;
			}
		}
	}
}


/* DISPLAY MAIN MENU */
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


/* MAIN MENU SELECTION WITH VALIDATION */
void inputSelection(){
	menuSelection=UNSELECTED;
	int input=UNSELECTED, temp=UNSELECTED;
	while(printMenu(), (input=scanf(" %d",&temp))!=1 ||temp<addOne ||temp>done){
		if(input==EOF){
			menuSelection=done;
			return;
		}
		scanf("%*[^\n]");
		printf("Invalid input\n");
	}
	scanf("%*[^\n]");
	menuSelection=temp;
}


/* MAIN */
int main(){
	initCube();
	while(menuSelection!=done){
		/* MAIN UPDATES */
		inputSelection();
		getLatestDay();
		getEarliestDay();

		/* MAIN MENU */
		switch(menuSelection){
			case done: break;
			case addOne: {
				if(inputData()==EOF){
					menuSelection=done;
				}
			break;
			}
			case addAll: {
				if(addAllChosen()==EOF){
					menuSelection=done;
				}
			break;
			}
			case stats: {
				int day=NONE;
				day=inputDay();
				day==EOF ?menuSelection=done :statsChosen(day);
			break;
			}
			case print: {
				printChosen();
			break;
			}
			case insights: {
				if(latestDay>NONE){
					insightsChosen();
				}
			break;
			}
			case deltas: {
				deltasChosen();
			break;
			}
			default: printf("Invalid input\n");
		}
	}
	/* EXIT POINT*/
	printf("Goodbye!\n");
	return 0;
}


/* USE TO CHECK IF OVERALL EARLIEST DAY MISSING DATA*/
void getEarliestDay(){
	earliestDay=DAYS_IN_YEAR;
	for(int brand=0; brand<NUM_OF_BRANDS; brand++){
		if(days[brand]<earliestDay){
			earliestDay=days[brand];
		}
	}
}


/* USE TO CHECK IF OVERALL LATEST DAY IS EXISTING AND VALID */
void getLatestDay(){
	for(int brand=0; brand<NUM_OF_BRANDS; brand++){
		if(days[brand]>latestDay){
			latestDay=days[brand];
		}
	}
}


/* INPUT DATA WITH VALIDATION */
int inputData(){
	int input=0, today=earliestDay+1, tempBrand=NONE, tempST[NUM_OF_TYPES];
	for(int type=0; type<NUM_OF_TYPES; type++){
		tempST[type]=NONE;
	}

	// (brand index) + ($ of each type)
	int validInput=1+NUM_OF_TYPES;

	while(
		tempBrand=tempST[0]=tempST[1]=tempST[2]=tempST[3]=NONE,
		(input=scanf(" %d %d %d %d %d", &tempBrand, &tempST[0], &tempST[1], &tempST[2], &tempST[3])) !=validInput
		||tempBrand<0 ||tempBrand>=NUM_OF_BRANDS
		||tempST[0]<0 ||tempST[1]<0 ||tempST[2]<0 ||tempST[3]<0
		||cube[today][tempBrand][0]!=NONE
	){
		if(input==EOF){
			menuSelection=done;
			return EOF;
		}
		scanf("%*[^\n]");
		printf("This brand is not valid\n");
	}
	scanf("%*[^\n]");
	int brand=tempBrand;
	int sales=NONE;

	/* UPDATE CUBE */
	for(int type=0; type<NUM_OF_TYPES; type++){
		sales=tempST[type];
		cube[today][brand][type]=sales;
	}
	/* UPDATE LATEST DAY FOR BRAND*/
	days[brand]++;
	return 1;
}


/* SELECT DAY TO VIEW STATS*/
int inputDay(){
	int day=NONE, temp=NONE, input=UNSELECTED, last=latestDay+1;
	while(
		temp=NONE,
		printf("What day would you like to analyze?\n"),
		(input=scanf(" %d",&temp))!=1
		||temp<1 ||temp>last
	){
		if(input==EOF){
			menuSelection=done;
			return EOF;
		}
		scanf("%*[^\n]");
		if(temp==UNSELECTED){
			return NONE-1;
		}
		printf("Please enter a valid day.\n");
	}
	scanf("%*[^\n]");
	day=temp-1;
	return day;
}


/* DAY WITH PARTIAL DATA IDENTIFICATION AND NOTIFICATION */
int noticeNoData(){
	int today=earliestDay+1, foundMissing=0;

	if(today<DAYS_IN_YEAR){
		for(int brand=0; brand<NUM_OF_BRANDS; brand++){

			if(cube[today][brand][0]==NONE){
				
				if(!foundMissing){
					printf("No data for brands %s", brands[brand]);
					foundMissing=1;
					continue;
				}
				printf(" %s", brands[brand]);
			}
		}
	}
	return (foundMissing)?printf("\nPlease complete the data\n") :0;
}


/* HELPER FOR TASK 3 & 5*/
int salesTotal(int day){
	int temp=0;

	for(int i=0; i<NUM_OF_TYPES; i++){
		for(int j=0; j<NUM_OF_BRANDS; j++){
			
			if(cube[day][j][i]>NONE){
				temp+=cube[day][j][i];
			}
		}
	}
	return temp;
}


/* HELPER FOR TASK 5 */
void mostProfitableDay(){
	int temp=0, best=0, sales=0;

	for(int i=0; i<latestDay; i++){
		if((temp=salesTotal(i))>sales){
			sales=temp;
			best=i;
		}
	}
	printf("The most profitable day was day number %d: %d$\n", best+1, sales);
}


/* HELPER FOR TASKS 3 & 5 */
void getBest(int path, int day, int subject, int items){
	int isStats=(path==stats), isBrand=(subject==NUM_OF_BRANDS), temp=0, best=0, sales=0, x=0, y=0;
	int start=isStats?day:0;

	for(int a=0; a<subject; temp=0, a++){
		for(int numDay=start; numDay<=day; numDay++){

			for(int b=0; isBrand?(x=a, y=b):(y=a, x=b), b<items; b++){
				if(cube[numDay][x][y]>NONE){
					temp+=cube[numDay][x][y];
				}
			}
			if(isStats){
				break;
			}

		}
		if(temp>sales){
			sales=temp;
			best=a;
		}
	
	}
	
	isStats ? isBrand
		? printf("The best sold brand with %d sales was %s\n", sales, brands[best])
		: printf("The best sold type with %d sales was %s\n", sales, types[best])
	: isBrand
		? printf("The best-selling brand overall is %s: %d$\n", brands[best], sales)
		: printf("The best-selling type of car is %s: %d$\n", types[best], sales);
}


/* TASK 2 CHECKPOINT */
int addAllChosen(){
	for(int brand=0; brand<NUM_OF_BRANDS; brand++){
		if(days[brand]<DAYS_IN_YEAR-1){
			while(noticeNoData()){
				if(inputData()==EOF){
					menuSelection=done;
					return EOF;
				}
			}
		}
	}
	return 1;
}


/* TASK 3 CHECKPOINT */
void statsChosen(int day){
	if(day==NONE-1){
		printf("In day number 0:\nThe sales total was 0\n"
			"The best sold brand with 0 sales was Toyoga\n"
			"The best sold type with 0 sales was SUV\n");
		return;
	}
	printf("In day number %d:\nThe sales total was %d\n", day+1, salesTotal(day));
	getBest(stats, day, NUM_OF_BRANDS, NUM_OF_TYPES);
	getBest(stats, day, NUM_OF_TYPES, NUM_OF_BRANDS);
}


/* TASK 4 HELPER */
void displayData(int brand){
	for(int day=0; day<=days[brand]; day++){
		printf("Day %d-", day+1);
		for(int type=0; type<NUM_OF_TYPES; type++){
			printf(" %s: %d", types[type], cube[day][brand][type]);
		}
		printf("\n");
	}
}


/* TASK 4 CHECKPOINT */
void printChosen(){
	printf("*****************************************\n");
	int brand=0;
	while(brand<NUM_OF_BRANDS){
		printf("Sales for %s:\n", brands[brand]);
		if(days[brand]>NONE){
			displayData(brand);
		}
		brand++;
	}
	printf("*****************************************\n");
}


/* TASK 5 CHECKPOINT */
void insightsChosen(){
	getBest(insights, latestDay, NUM_OF_BRANDS, NUM_OF_TYPES);
	getBest(insights, latestDay, NUM_OF_TYPES, NUM_OF_BRANDS);
	mostProfitableDay();
}


/* TASK 6 CHECKPOINT */
void deltasChosen(){
	if(latestDay<1){
		for(int brand=0; brand<NUM_OF_BRANDS; brand++){
			printf("Brand: %s, Average Delta: 0.000000\n", brands[brand]);
		}
	}else{
		float daySum[NUM_OF_BRANDS]={0};
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