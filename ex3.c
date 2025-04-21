/******************
Name: Samantha Newmark
ID: 
Assignment: ex3
*******************/
#include <stdio.h>


#define NONE -1

#define UNSELECTED 0

#define addOne  1

#define addAll  2  

#define stats  3

#define print  4

#define insights  5

#define deltas  6

// menu terminates program
#define done  7

#define DAYS_IN_YEAR 365

#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15

#define NUM_OF_TYPES 4
#define TYPES_NAMES 10

int menuChoice;

int earliestDay = NONE;

int latestDay = NONE;

int days[NUM_OF_BRANDS];

int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];

char brands[NUM_OF_BRANDS][BRANDS_NAMES]={"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};

char types [NUM_OF_TYPES][TYPES_NAMES]={"SUV", "Sedan", "Coupe", "GT"};

int printMenu();

int inputDay();

int inputChoice();

int inputData();

int noticeNoData();

int addAllChosen();

int salesTotal(int day);

void statsChosen(int day);

void mostProfitableDay();

void getEarliestDay();

void getLatestDay();

void init();

void printChosen();

void insightsChosen();

void deltasChosen();

void displayData(int brand);

int checkBest(int day, int a, int b, int i, int j);

void getBest(int path, int day, int i, int j);

void getEarliestDay(){
	earliestDay = DAYS_IN_YEAR;
	for(int brand=0; brand<NUM_OF_BRANDS; brand++){
		if(days[brand]<earliestDay){
			earliestDay=days[brand];
}}}

void getLatestDay(){
	for(int brand=0; brand<NUM_OF_BRANDS; brand++){
		if(days[brand]>latestDay){
			latestDay=days[brand];
}}}

void displayData(int brand){
	for(int day=0; day<=days[brand]; day++){
		printf("Day %d-", day+1);
		for(int type=0; type<NUM_OF_TYPES; type++){
			printf(" %s: %d" ,types[type] ,cube[day][brand][type]);
		}
		printf("\n");
}}

void init(){
	for(int day=0; day<DAYS_IN_YEAR; day++){
		for(int brand=0; brand<NUM_OF_BRANDS; brand++){
			if(day==0){
				days[brand] = NONE;
			}
			for(int type=0; type<NUM_OF_TYPES; type++){
				cube[day][brand][type]=NONE;
}}}}

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

int inputChoice(){
	menuChoice=UNSELECTED;
	int input=UNSELECTED, temp=UNSELECTED;
	while(printMenu()
	&&((input=scanf(" %d", &temp)) != 1
	||temp<addOne
	||temp>done)){
		if(input==EOF) return done;
		scanf("%*[^\n]");
		printf("Invalid input\n");
		temp=UNSELECTED;
	}
	scanf("%*[^\n]");
	menuChoice=temp;
	return menuChoice;
}

int inputDay(){
	int day=NONE, temp=0, input=UNSELECTED, min=1, max=latestDay+1;
	while(printf("What day would you like to analyze?\n")
	&&((input=scanf(" %d", &temp))!=1
	||temp<min
	||temp>max)){
		if(input==EOF){
			return EOF;
		}
		scanf("%*[^\n]");
		printf("Please enter a valid day.\n");
		temp=NONE;
	}
	scanf("%*[^\n]");
	day=temp-1;
	return day;
}

int noticeNoData(){
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
	}}}
	return (foundMissing)?printf("\nPlease complete the data\n"):0;
}

int addAllChosen(){
	for(int brand=0; brand<NUM_OF_BRANDS; brand++){
		if(days[brand]<DAYS_IN_YEAR-1){
			while(noticeNoData()){
				if(inputData()==EOF){
					return EOF;
	}}}}
	return 1;
}

int inputData(){
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

void printChosen(){
	printf("*****************************************\n");
	int brand=0;
	while(brand<NUM_OF_BRANDS){
		printf("Sales for %s:\n", brands[brand]);
		if(days[brand]>NONE){
			displayData(brand);
		} brand++;
	}
	printf("*****************************************\n");
}

void statsChosen(int day){
	printf("In day number %d:\nThe sales total was %d\n", day+1, salesTotal(day));
	getBest(stats, day, NUM_OF_BRANDS, NUM_OF_TYPES);
	getBest(stats, day, NUM_OF_TYPES, NUM_OF_BRANDS);
}

void insightsChosen(){
	getBest(insights, latestDay, NUM_OF_BRANDS, NUM_OF_TYPES);
	getBest(insights, latestDay, NUM_OF_TYPES, NUM_OF_BRANDS);
	mostProfitableDay();
}

int salesTotal(int day){
	int temp=0;
	for(int i=0; i<NUM_OF_TYPES; i++){
		for(int j=0; j<NUM_OF_BRANDS; j++){
			if(cube[day][j][i]>NONE){
				temp+=cube[day][j][i];
	}}}
	return temp;
}

void mostProfitableDay(){
	int temp=0, best=0, sales=0;
	for(int i=0; i<latestDay; i++){
		if((temp=salesTotal(i))>sales){
			sales=temp;
			best=i;
	}}
	printf("The most profitable day was day number %d: %d$\n", best+1, sales);
}

void getBest(int path, int day, int subject, int items){
	int temp=0, best=0, sales=0, x=0, y=0;
	int start=(path==stats)?day:0;
	for(int a=0; a<subject; a++, temp=0){
		for(int numDay=start; numDay<=day; numDay++){
			for(int b=0; items==NUM_OF_TYPES?(x=a, y=b):(y=a, x=b), b<items; b++){
				if(cube[numDay][x][y]>NONE){
					temp+=cube[numDay][x][y];
				}
			}
			if(path==stats){
				break;
			}
		}
		if(temp>sales){
			sales=temp;
			best=a;
		}
	}
	path==stats ?subject==NUM_OF_BRANDS
		?printf("The best sold brand with %d sales was %s\n",sales,brands[best])
		:printf("The best sold type with %d sales was %s\n",sales,types[best])
	:subject==NUM_OF_BRANDS // path==insights
		?printf("The best-selling brand overall is %s: %d$\n",brands[best],sales)
		:printf("The best-selling type of car is %s: %d$\n",types[best],sales);
}

void deltasChosen(){
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
		}}}
		for(int brand=0; brand<NUM_OF_BRANDS; brand++){
			printf("Brand: %s, Average Delta: %1.6f\n", brands[brand], daySum[brand]/latestDay);
}}}

int main(){
	init();
	while((inputChoice())!=done){
		getLatestDay();
		getEarliestDay();
		switch(menuChoice){
			case addOne:
				{if(inputData()==EOF){
					goto term;
				}
				break;}
			case addAll:
				{if (addAllChosen()==EOF){
					goto term;
				}
				break;}
			case stats:
				{int day=inputDay();
				if(day==EOF){
					goto term;
				}
				statsChosen(day);
				break;}
			case print:
				{printChosen();
				break;}
			case insights:
				{if(latestDay>NONE){
					insightsChosen();
				}
				break;}
			case deltas:
				{deltasChosen();
				break;}
			case done:
				{goto term;}
			default:
				{printf("Invalid input\n");
				break;}
	}}term:
	printf("Goodbye!\n");
	return 0;
}