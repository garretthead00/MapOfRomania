/**
*	Garrett Head

*	This program will find the shortest path on the map of Romania using both the Greedy and A* algorithms (separately).
*
*/


#include <stdio.h>
#include "stdafx.h"

#define NA  -1
#define TOTAL_CITIES 20

int getNearestCityByGreedyTechnique(int city);
int getNearestCityByAStarTechnique(int city);

int distanceToBucharestFromEachCity[TOTAL_CITIES] = { 366, 0, 160, 242, 161, 176, 77, 151, 226, 244, 241, 234, 380, 100, 193, 253, 329, 80, 199, 374 };
int distanceBetweenCities[TOTAL_CITIES][TOTAL_CITIES] = {
	{ 0, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, 140, 118, NA, NA, 75 },
	{ NA, 0, NA, NA, NA, 211, 90, NA, NA, NA, NA, NA, NA, 101, NA, NA, NA, 85, NA, NA },
	{ NA, NA, 0, 120, NA, NA, NA, NA, NA, NA, NA, NA, NA, 138, 146, NA, NA, NA, NA, NA },
	{ NA, NA, 120, 0, NA, NA, NA, NA, NA, NA, 75, NA, NA, NA, NA, NA, NA, NA, NA, NA },
	{ NA, NA, NA, NA, 0, NA, NA, 86, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA },
	{ NA, 211, NA, NA, NA, 0, NA, NA, NA, NA, NA, NA, NA, NA, NA, 99, NA, NA, NA, NA },
	{ NA, 90, NA, NA, NA, NA, 0, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA },
	{ NA, NA, NA, NA, 86, NA, NA, 0, NA, NA, NA, NA, NA, NA, NA, NA, NA, 98, NA, NA },
	{ NA, NA, NA, NA, NA, NA, NA, NA, 0, NA, NA, 87, NA, NA, NA, NA, NA, NA, 92, NA },
	{ NA, NA, NA, NA, NA, NA, NA, NA, NA, 0, 70, NA, NA, NA, NA, NA, 111, NA, NA, NA },
	{ NA, NA, NA, 75, NA, NA, NA, NA, NA, 70, 0, NA, NA, NA, NA, NA, NA, NA, NA, NA },
	{ NA, NA, NA, NA, NA, NA, NA, NA, 87, NA, NA, 0, NA, NA, NA, NA, NA, NA, NA, NA },
	{ NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, 0, NA, NA, 151, NA, NA, NA, 71 },
	{ NA, 101, 138, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, 0, 97, NA, NA, NA, NA, NA },
	{ NA, NA, 146, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, 97, 0, 80, NA, NA, NA, NA },
	{ 140, NA, NA, NA, NA, 99, NA, NA, NA, NA, NA, NA, 151, NA, 80, 0, NA, NA, NA, NA },
	{ 118, NA, NA, NA, NA, NA, NA, NA, NA, 111, NA, NA, NA, NA, NA, NA, 0, NA, NA, NA },
	{ NA, 85, NA, NA, NA, NA, NA, 98, NA, NA, NA, NA, NA, NA, NA, NA, NA, 0, 142, NA },
	{ NA, NA, NA, NA, NA, NA, NA, NA, 92, NA, NA, NA, NA, NA, NA, NA, NA, 142, 0, NA },
	{ 75, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, 71, NA, NA, NA, NA, NA, NA, 0 }
};

char cityNames[TOTAL_CITIES][TOTAL_CITIES] = { "Arad", "Bucharest", "Craiova", "Drobeta", "Eforie", "Fagaras", "Giurgiu", "Hirsova", "Iasi",
"Lugoj", "Mehadia", "Neamt", "Oradea", "Pitesti", "Rimnicu Vilcea", "Sibiu", "Timisoara",
"Urziceni", "Vaslui", "Zerind" };

int greedyRoute[TOTAL_CITIES], aStarRoute[TOTAL_CITIES];
int currentCityVisited, citiesVisitedCount = 0;

/**
* The main function will continuesly loop throught the program execution prompting the user to enter one of several commands
* to the console.
* Commands: (1) Greedy Method
*			 (2) A* Algorithm
*			 (3) Quit
*
*/
int main()
{

	bool loop = true; // main loop control variable

	while (loop) {

		// Reset all variables before each command
		int originCity = 0, destinationCity = 1, lastCityVisited = 0;
		int greedyDistance = 0, aStarDistance = 0;
		int citiesVisitedCount = 0, numberOfAdjacentCities = 0;
		int technique;
		greedyRoute[0] = originCity;
		aStarRoute[0] = originCity;
		currentCityVisited = originCity;

		// Prompt the user for command code
		printf("\n\n Please select a technique to calculate shortest path : \n");
		printf("(1) : Greedy Technique \n");
		printf("(2) : A* Technique \n");
		printf("(3) : Quit Program \n");
		scanf_s("%d", &technique);
		

		// This switch will take the command and assigne the task to be executed accordingly
		switch (technique){

			// GREEDY
		case 1:
			while (currentCityVisited != destinationCity){
				lastCityVisited = currentCityVisited;
				currentCityVisited = getNearestCityByGreedyTechnique(currentCityVisited);
				greedyDistance += distanceBetweenCities[lastCityVisited][currentCityVisited];
				greedyRoute[citiesVisitedCount] = currentCityVisited;
				citiesVisitedCount++;
			}
			printf("\n\nShortest Distance using Greedy Technique : %d \n", greedyDistance);
			for (int cityCounter = 0; cityCounter < citiesVisitedCount; cityCounter++) {
				printf("%s", cityNames[greedyRoute[cityCounter]]);
				if (citiesVisitedCount != cityCounter + 1)
					printf("->");
			}
			
			break;

			// A*
		case 2:
			while (currentCityVisited != destinationCity){
				lastCityVisited = currentCityVisited;
				currentCityVisited = getNearestCityByAStarTechnique(currentCityVisited);
				aStarDistance += distanceBetweenCities[lastCityVisited][currentCityVisited];
				aStarRoute[citiesVisitedCount] = currentCityVisited;
				citiesVisitedCount++;
			}
			printf("\n\nShortest Distance using A* Technique : %d \n", aStarDistance);
			for (int cityCounter = 0; cityCounter < citiesVisitedCount; cityCounter++) {
				printf("%s", cityNames[aStarRoute[cityCounter]]);
				if (citiesVisitedCount != cityCounter + 1)
					printf("->");
			}
			break;

			// Quit
		case 3: loop = false; break;

			// Wrong input, dum dum
		default: printf("Command Error....Please enter 1, 2, or 3!"); break;
		}

	}


	printf("Goodbye!");
	getchar(); getchar();
	return 0;
}

/**
* This function will control the Greedy Method for our program.
* The function will take in the currentCity (Node) as a parameter and will run through the map to find the shortest path
*/
int getNearestCityByGreedyTechnique(int currentCity)
{
	// declare any variables being used
	int citiesNearBy[TOTAL_CITIES], nearByCitiesCount = 0, nearestCity;
	int cityAlreadyVisitedFlag = 0; // no cities have been visited

	// This loop will run through the map and check any cities that have been visited.
	// NOTE!!! the greedy method does NOT visit every city on the map
	for (int nearbyCityCounter = 0; nearbyCityCounter < TOTAL_CITIES; nearbyCityCounter++) {
		for (int cityVisitedCounter = 0; cityVisitedCounter < citiesVisitedCount; cityVisitedCounter++) {
			if (greedyRoute[cityVisitedCounter] == currentCity)
				cityAlreadyVisitedFlag = 1;
		}

		// If the distance is not 0 and not NA and the city has NOT been visited
		if (distanceBetweenCities[currentCity][nearbyCityCounter] != 0 && distanceBetweenCities[currentCity][nearbyCityCounter] != NA && cityAlreadyVisitedFlag == 0){
			citiesNearBy[nearByCitiesCount] = nearbyCityCounter; // the city near by is labeled as the current nearby city from the for loop above
			nearByCitiesCount++; // increment the nearby city count if the unvisited city has been checked
		}
	}

	nearestCity = citiesNearBy[0];
	// This loop will compare the distance of all of the visited cities; if the distance to bucharest from the nearest city from the loop is shorter
	// than the distance of the nearest city the new nearest city will be modified.
	for (int nearestCityCounter = 0; nearestCityCounter < nearByCitiesCount; nearestCityCounter++) {
		if (distanceToBucharestFromEachCity[citiesNearBy[nearestCityCounter]] < distanceToBucharestFromEachCity[nearestCity]) {
			nearestCity = citiesNearBy[nearestCityCounter]; // Update nearest city to the newly found nearest city
		}
	}
	return nearestCity;
}


/**
* This function will control the A* Algorithm for our program.
* The function will take in the currentCity (Node) as a parameter and will run through the map to find the shortest path
* comparing the shortest path and the weight each city
*/
int getNearestCityByAStarTechnique(int currentCity){
	int citiesNearBy[TOTAL_CITIES], nearByCitiesCount = 0, nearestCity;
	int cityAlreadyVisitedFlag = 0;

	// This loop will run through the map and check any cities that have been visited.
	// NOTE!!! the A* Alogrithm does NOT visit every city on the map
	for (int nearbyCityCounter = 0; nearbyCityCounter < TOTAL_CITIES; nearbyCityCounter++) {
		for (int cityVisitedCounter = 0; cityVisitedCounter < citiesVisitedCount; cityVisitedCounter++) {
			if (greedyRoute[cityVisitedCounter] == currentCity)
				cityAlreadyVisitedFlag = 1;
		}

		// If the distance is not 0 and not NA and the city has NOT been visited
		if (distanceBetweenCities[currentCity][nearbyCityCounter] != 0 && distanceBetweenCities[currentCity][nearbyCityCounter] != NA && cityAlreadyVisitedFlag == 0){
			citiesNearBy[nearByCitiesCount] = nearbyCityCounter;// the city near by is labeled as the current nearby city from the for loop above
			nearByCitiesCount++; // increment the nearby city count if the unvisited city has been checked
		}
	}

	nearestCity = citiesNearBy[0];
	int distanceCovered = 0;

	// This loop will compare the distance of all of the visited cities; This will take the sum of the distance and weight of the city
	for (int nearestCityCounter = 0; nearestCityCounter < nearByCitiesCount; nearestCityCounter++) {

		int initialDistance = distanceCovered + distanceBetweenCities[currentCity][nearestCity];
		int heuristicDistance = distanceToBucharestFromEachCity[nearestCity];

		int newInitialDistance = distanceCovered + distanceBetweenCities[currentCity][citiesNearBy[nearestCityCounter]];
		int newHeuristicDistance = distanceToBucharestFromEachCity[citiesNearBy[nearestCityCounter]];

		// the sum distance is less than the initial summed distance
		if (newInitialDistance + newHeuristicDistance < initialDistance + heuristicDistance) {
			nearestCity = citiesNearBy[nearestCityCounter]; // update the nearest city
		}
	}
	return nearestCity;
}
