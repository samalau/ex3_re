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
#define NUM_OF_TYPES 4
#define insights  5
#define NUM_OF_BRANDS 5
#define deltas  6
#define done  7
#define TYPES_NAMES 10
#define BRANDS_NAMES 15
#define DAYS_IN_YEAR 365

int choice;
int earliestDay = NONE;
int latestDay = NONE;

int days[NUM_OF_BRANDS];
char brands[NUM_OF_BRANDS][BRANDS_NAMES]={"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types [NUM_OF_TYPES][TYPES_NAMES]={"SUV", "Sedan", "Coupe", "GT"};

int printMenu();
int inputDay();
int inputChoice();
int inputData(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);
int noticeNoData(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);
int addAllChosen(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);
int statsChosen(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);
int getSum(int day, int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);
int salesTotal(int path, int day, int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);
void getEarliestDay();
void getLatestDay();
void init(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);
void printChosen(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);
void insightsChosen(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);
void deltasChosen(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);
void displayData(int brand, int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);
int getBest(int path, int i, int j, int k, int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);

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

void init(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]){
	for(int day=0; day<DAYS_IN_YEAR; day++){
		for(int brand=0; brand<NUM_OF_BRANDS; brand++){
			if(day==0){
				days[brand] = NONE;
			}
			for(int type=0; type<NUM_OF_TYPES; type++){
				cube[day][brand][type]=NONE;
	}  }  }	
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
	for(int brand=0; brand<NUM_OF_BRANDS; brand++){
		if(days[brand]<DAYS_IN_YEAR-1){
			while(noticeNoData(cube)){
				if(inputData(cube)==EOF){
					return EOF;
				}
			}
		}
	}
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

void printChosen(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]){
	printf("*****************************************\n");
	int brand=0;
	while(brand<NUM_OF_BRANDS){
		printf("Sales for %s:\n", brands[brand]);
		if(days[brand]>NONE){
			displayData(brand, cube);
		}
		brand++;
	}
	printf("*****************************************\n");
}

int statsChosen(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]){
	int day=inputDay();
	if(day==EOF)
		{return EOF;}
	printf("In day number %d:\n", day+1);
	salesTotal(stats, day, cube);
	getBest(stats, NUM_OF_BRANDS, NUM_OF_TYPES, day, cube);
	getBest(stats, NUM_OF_TYPES, NUM_OF_BRANDS, day, cube);
	return 1;
}

void insightsChosen(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]){
	getBest(insights, NUM_OF_BRANDS, NUM_OF_TYPES, latestDay, cube);
	getBest(insights, NUM_OF_TYPES, NUM_OF_BRANDS, latestDay, cube);
	salesTotal(insights, latestDay, cube);
}

int getSum(int day, int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]){
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

int salesTotal(int path, int day, int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]){
	switch(path){
		case stats:{
			printf("The sales total was %d\n", getSum(day, cube));
		break;
		}
		case insights:{
			int temp=0, best=0, sales=0;
			for(int i=0; i<day; i++){
				if((temp=getSum(i, cube))>sales){
					sales=temp;
					best=i;
				}
			}
			printf("The most profitable day was day number %d: %d$\n", best+1, sales);
		break;
		}
		default:{
			return -1;  // undefined
		}
	}
	return -1;
}

int getBest(int path, int i, int j, int day, int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]){
	int best=0, sales=0;
	for(int a=0; a<i; a++){
		int temp=0;
		for(int b=0; b<j; b++){
			switch(path){
				case stats:{
					if(cube[day][a][b]>NONE &&j==NUM_OF_TYPES){
						temp+=cube[day][a][b];
						break;
					}
					if(cube[day][b][a]>NONE &&i==NUM_OF_TYPES){
						temp+=cube[day][b][a];
						break;
					}
				break;
				}
				case insights:{
					for(int k=0; k<=day; k++){
						if(cube[k][a][b]>NONE &&j==NUM_OF_TYPES){
							temp+=cube[k][a][b];
							continue;
						}
						if(cube[k][b][a]>NONE &&i==NUM_OF_TYPES){
							temp+=cube[k][b][a];
							continue;
						}
					}
				break;
				}
				default:
					return NONE;  // todo: fix undefined
			}
		}
		if(temp>sales){
			sales=temp;
			best=a;
		}
	}
	return  path==stats? (i == NUM_OF_BRANDS?
					printf("The best sold brand with %d sales was %s\n" ,sales ,brands[best]):
					printf("The best sold type with %d sales was %s\n" ,sales ,types[best])):
				i == NUM_OF_BRANDS?
					printf("The best-selling brand overall is %s: %d$\n" ,brands[best] ,sales):
					printf("The best-selling type of car is %s: %d$\n" ,types[best] ,sales);
}

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
