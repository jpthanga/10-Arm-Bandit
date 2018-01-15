/*
 * Author: Adam White, Matthew Schlegel
 * Purpose: for use of Rienforcement learning course Indiana University Spring 2016
 *
 * agent does *no* learning, selects actions randomly from the set of legal actions, ignores observation/state
 *
 */

#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <ctime>


#include "rlglue/Agent_common.h" /* Required for RL-Glue */

/*** IMPORTANT: 
 * Any private variables to the environment must be declared static
 * Otherwise they are default public global variables that can be 
 * accessed in other files 
 ***/

static gsl_vector* local_action;
static action_t* this_action;
static gsl_vector* last_observation;
static gsl_vector* last_action;
static double bandit[10];
static int numActions = 10;
static int numStates = 1;
static float alpha = 0;
static float num = 1;
static int flag = 1;

void agent_init()
{
  //Allocate Memory
  local_action = gsl_vector_calloc(1);
  this_action = local_action;
  last_action = local_action;
  last_observation = gsl_vector_calloc(1);
  //Q star
  memset(bandit, 0, sizeof(bandit));
  //step count
  num = 1;
}

const action_t *agent_start(const observation_t *this_observation) {
  
  int stp1 = (int)gsl_vector_get(this_observation,0); /* how you convert observation to a int, if state is tabular */
  int atp1=randInRange(numActions);
  gsl_vector_set(local_action,0,atp1);
  gsl_vector_memcpy(last_action,local_action);
  gsl_vector_memcpy(last_observation,this_observation);/*save observation, might be useful on the next step */
  
  return this_action;
}

const action_t *agent_step(double reward, const observation_t *this_observation) {
  
  int stp1 = (int)gsl_vector_get(this_observation,0);
  int atp1=randInRange(numActions);

  //choosing alpha value
  if (flag == 1){
	  alpha = 1/num;
  }else{
	  alpha = 0.1;
  }

  int a = (int)gsl_vector_get(last_action,0);
  bandit[a] += alpha*(reward - bandit[a]);

  // epsilon = 0.1
  int greedy = rand() % 10;
  int action = 0;
  if(greedy < 1){
	  double max = bandit[0];

	  for(int i = 1;i<10;i++){
	  if(bandit[i] > max){
		  action = i;
	  	 }
	  }
  }else{
	  action = randInRange(numActions);
  }

  gsl_vector_set(local_action,0,action);
  gsl_vector_memcpy(last_action,local_action);
  num++;
  return this_action;
}

void agent_end(double reward) {
  /* final learning update at end of episode */
}

void agent_cleanup() {
  /* clean up mememory */
  gsl_vector_free(local_action);
  gsl_vector_free(last_observation);
}

const char* agent_message(const char* inMessage) {
	if(strcmp(inMessage,"step") == 0){
		flag = 0;
	}else{
		flag = 1;
	}

  /* might be useful to get information from the agent */
  if(strcmp(inMessage,"what is your name?")==0)
  return "my name is skeleton_agent!";
  
  /* else */
  return "I don't know how to respond to your message";
}
