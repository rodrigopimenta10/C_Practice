/*
 *	Name: Rodrigo Pimenta
 *	UID: 113359873
 *  Directory ID: rpimenta
 *
 */

#include <stdio.h>
#include <math.h>

/*Prototypes*/

static double meanfunction(double *a, int Number_of_Assignments);
static void printingfunction(double numeric_score,
		int Points_Penalty_Per_Day_Late);
int main() {

	int i, j;

	/*Input first 4 values.*/
	int Points_Penalty_Per_Day_Late, Drop_N_Lower_Value_Assignments,
			Number_of_Assignments;
	char Stats;
	/*Input 4 assignment information values.*/
	int assignment_number[50], assignment_score[50], assignment_weight[50],
			days_late[50];
	double weight_sum = 0;
	int temp;
	double actual_score[50];
	double lowest;
	int lowest_assignment;
	double actual_scores_wpenalty[50];
	double relevant_sum_weight = 0;
	double numeric_score = 0;
	double scores_wpenalty[50];
	double mean = 0;
	double tempArray[50];
	double standard_deviation = 0;
	double mean_squared_differences = 0;

	scanf("%d %d %c", &Points_Penalty_Per_Day_Late,
			&Drop_N_Lower_Value_Assignments, &Stats);
	scanf(" %d", &Number_of_Assignments);

	for (i = 0; i < Number_of_Assignments; i++) {
		scanf(" %d, %d, %d, %d", &assignment_number[i], &assignment_score[i],
				&assignment_weight[i], &days_late[i]);
	}

	/*Weights must add up to 100, if not: error message and end program.*/
	for (i = 0; i < Number_of_Assignments; i++) {
		weight_sum = weight_sum + assignment_weight[i];
	}
	if (weight_sum != 100) {
		printf("ERROR: Invalid values provided");
		return 0;
	}

	/*Sort all arrays containing assignment information by assignment number.*/
	for (i = 0; i < Number_of_Assignments; ++i) {
		for (j = i + 1; j < Number_of_Assignments; ++j) {
			if (assignment_number[i] > assignment_number[j]) {
				/*Number*/
				temp = assignment_number[i];
				assignment_number[i] = assignment_number[j];
				assignment_number[j] = temp;

				/*Score/*/
				temp = assignment_score[i];
				assignment_score[i] = assignment_score[j];
				assignment_score[j] = temp;

				/*Weight/*/
				temp = assignment_weight[i];
				assignment_weight[i] = assignment_weight[j];
				assignment_weight[j] = temp;

				/*Days late/*/
				temp = days_late[i];
				days_late[i] = days_late[j];
				days_late[j] = temp;

			}
		}
	}

	/*Calculation for Numeric Score.

	 Calculate actual score: score * weight.*/
	for (i = 0; i < Number_of_Assignments; i++) {
		actual_score[i] = assignment_score[i] * assignment_weight[i];
	}

	/*First drop the lowest Drop_N_Lower_Value_Assignments from the calculation.
	 The lowest score is just the lowest actual_score.

	 I set the value of the lowest N scores in the actual_score array to
	 10001.
	 Setting the value to 10001 will be used as a marker and is equivalent
	 to dropping the value.*/

	for (i = 0; i < Drop_N_Lower_Value_Assignments; i++) {

		lowest = actual_score[0];
		lowest_assignment = 0;
		/*Finds current lowest score in actual_score array.*/
		for (j = 1; j < Number_of_Assignments; j++) {
			if (lowest > actual_score[j]) {
				lowest = actual_score[j];
				/*Since the arrays are sorted, I just use j to determine which
				has a higher assignment value,
				 //in the case that the current lowest == actual_score.*/
				lowest_assignment = j;
			}
			if (lowest == actual_score[j]) {
				/*If they equal, the assignment with the lowest assignment
				number is dropped.*/
				if (lowest_assignment > j) {
					/*lowest = actual_score[j];/*/
					lowest_assignment = j;
				}
			}
		}
		/*At this point the current lowest score in the acutal_score array
		is found.
		I drop the current lowest score by making this score 101 in the
		actual_score array.*/

		actual_score[lowest_assignment] = 10001;

		/*The loop runs again to drop the next lowest score until N lowest
		scores have been dropped.*/
	}

	/*Now that the lowest scores have been dropped, you can calculate the
	actual_score with the days late penalty.*/
	for (i = 0; i < Number_of_Assignments; i++) {
		if (actual_score[i] == 10001) {
			/*Dropped score.*/
			actual_scores_wpenalty[i] = 0;
		} else {
			if ((assignment_score[i]
					- (days_late[i] * Points_Penalty_Per_Day_Late)) < 0) {
				actual_scores_wpenalty[i] = 0;
				/*I add all the weights of scores that were not dropped.*/
				relevant_sum_weight = relevant_sum_weight
						+ assignment_weight[i];
			} else {
				actual_scores_wpenalty[i] = ((assignment_score[i]
						- (days_late[i] * Points_Penalty_Per_Day_Late))
						* assignment_weight[i]);
				/*I add all the weights of scores that were not dropped.*/
				relevant_sum_weight = relevant_sum_weight
						+ assignment_weight[i];
			}
		}

	}

	/*I add all the actual_scores_wpenalty values.*/
	for (i = 0; i < Number_of_Assignments; i++) {
		numeric_score = numeric_score + actual_scores_wpenalty[i];
	}

	/*Final numeric score calculated.*/
	numeric_score = numeric_score / relevant_sum_weight;

	if (Stats == 'Y' || Stats == 'y') {
		/*Mean and Standar deviation computed.

		 I calculate the Mean.
		 First I get the scores_wpenalty and I don't overlook dropped scores.*/
		for (i = 0; i < Number_of_Assignments; i++) {
			if ((assignment_score[i]
					- (days_late[i] * Points_Penalty_Per_Day_Late)) < 0) {
				scores_wpenalty[i] = 0;
			} else {
				scores_wpenalty[i] = assignment_score[i]
						- (days_late[i] * Points_Penalty_Per_Day_Late);
			}
		}

		mean = meanfunction(scores_wpenalty, Number_of_Assignments);

		/*Calculate the standard deviation.*/

		for (i = 0; i < Number_of_Assignments; i++) {
			tempArray[i] = (scores_wpenalty[i] - mean)
					* (scores_wpenalty[i] - mean);
		}

		mean_squared_differences = meanfunction(tempArray,
				Number_of_Assignments);

		/*Finally take square root of the mean_squared_differences and you get
		the standard deviation.*/

		standard_deviation = sqrt(mean_squared_differences);

		/*Use Function to print regular stuff.*/
		printingfunction( numeric_score,
				Points_Penalty_Per_Day_Late);

		/*
		 printf("Numeric Score: %5.4f\n", numeric_score);
		 printf("Points Penalty Per Day Late: %d\n",
		 Points_Penalty_Per_Day_Late);
		 */
		 printf("Number of Assignments Dropped: %d\n",
		 Drop_N_Lower_Value_Assignments);
		 printf("Values Provided:\n");
		 printf("Assignment, Score, Weight, Days Late\n");
		 for (i = 0; i < Number_of_Assignments; i++) {
		 printf("%d, %d, %d, %d\n", assignment_number[i],
		 assignment_score[i], assignment_weight[i], days_late[i]);
		 }


		printf("Mean: %5.4f, Standard Deviation: %5.4f", mean,
				standard_deviation);

	} else {
		/*Mean and Standard deviation not computed.
		 //Use Function to print regular stuff.*/

		printingfunction( numeric_score,
				Points_Penalty_Per_Day_Late);

		/*
		 printf("Numeric Score: %5.4f\n", numeric_score);
		 printf("Points Penalty Per Day Late: %d\n",
		 Points_Penalty_Per_Day_Late);
		 */
		 printf("Number of Assignments Dropped: %d\n",
		 Drop_N_Lower_Value_Assignments);
		 printf("Values Provided:\n");
		 printf("Assignment, Score, Weight, Days Late\n");
		 for (i = 0; i < Number_of_Assignments; i++) {
		 printf("%d, %d, %d, %d\n", assignment_number[i],
		 assignment_score[i], assignment_weight[i], days_late[i]);
		 }

	}
	return 0;
}

/*	This funcitons takes one array parameter and one int parameter. It simply
 adds all of the values in the arrary together and then it divides that sum
 by the total number of assignments parameter. Then it returns this
 calculated mean.
 */
static double meanfunction(double *a, int Number_of_Assignments) {
	int i;
	double mean = 0;
	for (i = 0; i < Number_of_Assignments; i++) {
		mean = mean + a[i];
	}
	mean = mean / Number_of_Assignments;
	return mean;

	/*
	 double mean = 0;
	 for(i = 0; i<Number_of_Assignments; i++){
	 mean = mean + scores_wpenalty[i];
	 }
	 mean = mean/Number_of_Assignments;
	 */

	/*
	 for(i = 0; i<Number_of_Assignments; i++){
	 mean_squared_differences = mean_squared_differences + tempArray[i];
	 }
	 mean_squared_differences = mean_squared_differences/Number_of_Assignments;
	 */
}

/* This function simply takes in the double numeric_score and the int
Points_Penalty_Per_Day_Late and printes them out.
*/
static void printingfunction(double numeric_score,
		int Points_Penalty_Per_Day_Late){
	printf("Numeric Score: %5.4f\n", numeric_score);
	printf("Points Penalty Per Day Late: %d\n", Points_Penalty_Per_Day_Late);

}

