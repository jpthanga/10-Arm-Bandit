/*
 * Author: Adam White, Matthew Schlegel
 * Purpose: for use of Rienforcement learning course Indiana University Spring 2016
 * Last Modified by: Matthew Schlegel
 * Last Modified on: 1/6/2017
 *
 * experiment runs 200 episodes, averaging the cummulative reward per episode over 30 independent runs.
 * Results are saved to file.
 */

#include <stdio.h>
#include <math.h>
#include <string.h>
#include "rlglue/RL_glue.h" /* Required for RL-Glue  */


void saveResults(double* data, int dataSize, const char* filename);

int main(int argc, char *argv[]) {
  int k,i;
  int numSteps = 1000;
  int numRuns = 2000;

  //for reward
  double result[numSteps];
  memset(result, 0, sizeof(result));
  
  //for avg times right arm pulled
  double rightCounter[numSteps];
  memset(rightCounter, 0, sizeof(rightCounter));

  const reward_observation_action_terminal_t *rl_step_result=0;

  //experiment for sample avg
  for (int k = 0 ; k <numRuns ; k++ ){
  	RL_init();
    RL_start();

    //runs number of steps
    for (i =0; i<numSteps; i++) {
    	RL_agent_message("avg");
    	rl_step_result = RL_step();
    	//get reward from agent
    	result[i] += rl_step_result->reward;
    	//get "right" detail from environment
    	rightCounter[i] += gsl_vector_get(rl_step_result->observation,0);
    	}
    RL_cleanup();
    fflush( stdout );
  }

  printf("\n Sample Avg Done\n");

  /* average over runs */
  for (i =0; i<numSteps; i++){
    result[i] = result[i]/numRuns;
    rightCounter[i] = rightCounter[i]/numRuns;
  }
  
  /* Save data to a file  */
  /* Save data to a file  Use this for alpha = 1/n*/
  saveResults(result, numSteps, "RL_EXP_OUT_avgResult.dat");
  saveResults(rightCounter, numSteps, "RL_EXP_OUT_avgRight.dat");


  //experiment for alpha 0.1
  for (int k = 0 ; k <numRuns ; k++ ){
    	RL_init();
      RL_start();

      //runs number of steps
      for (i =0; i<numSteps; i++) {
      	RL_agent_message("step");
      	rl_step_result = RL_step();
      	//get reward from agent
      	result[i] += rl_step_result->reward;
      	//get "right" detail from environment
      	rightCounter[i] += gsl_vector_get(rl_step_result->observation,0);
      	}
      RL_cleanup();
      fflush( stdout );
    }

    printf("\n Constant Step Size Done\n");

    /* average over runs */
    for (i =0; i<numSteps; i++){
      result[i] = result[i]/numRuns;
      rightCounter[i] = rightCounter[i]/numRuns;
    }


  /* Save data to a file  */
  /* Save data to a file  Use this for alpha = 0.1*/
  saveResults(result, numSteps, "RL_EXP_OUT_stepResult.dat");
  saveResults(rightCounter, numSteps, "RL_EXP_OUT_stepRight.dat");
  
  return 0;
}

void saveResults(double* data, int dataSize, const char* filename) {
  FILE *dataFile;
  int i;
  dataFile = fopen(filename, "w");
  for(i = 0; i < dataSize; i++){
    fprintf(dataFile, "%lf\n", data[i]);
  }
  fclose(dataFile);
}
