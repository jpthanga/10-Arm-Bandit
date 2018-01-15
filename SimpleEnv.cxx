/*
 * Author: Adam White
 * Purpose: for use of Rienforcement learning course Indiana University Spring 2016
 *
 * env transitions *ignore* actions, state transitions, rewards, and terminations are all random
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include "rlglue/Environment_common.h" /* Required for RL-Glue interface*/
#include "utils.h"

/*** IMPORTANT: 
 * Any private variables to the environment must be declared static
 * Otherwise they are default public global variables that can be 
 * accessed in other files 
 ***/

static gsl_vector* local_observation;
static reward_observation_terminal_t this_reward_observation;
static const int nStatesSimpleEnv = 20;
static double banditV[10];
static int steps;

void env_init() 
{
	local_observation = gsl_vector_calloc(1);
	
	this_reward_observation.observation=local_observation;
	this_reward_observation.reward=0;
	this_reward_observation.terminal=0;
	
	//intialise arms
	for(int i=0;i<10;i++){
		banditV[i] = 10;
	}
	//step count
	steps = 0;
	return;
}

const observation_t* env_start()
{
  gsl_vector_set(local_observation,0,0);
  return this_reward_observation.observation;
}

const reward_observation_terminal_t *env_step(const action_t *this_action)
{

  int atp1 = gsl_vector_get(this_action,0); /* how to extact action */

  //find it action is best action
  int flag = 1;
  int truMax = banditV[atp1];

  for(int i = 0 ; i< 10; i++){
	  if(i!=atp1){
	  if(truMax <= banditV[i]){
		  flag=0;
	  }
	  }
  }

  //create random walk
  if(steps%10 == 1){
	  for(int i=0;i<10;i++){
		  float r = 10;
		  int rnd = rand()%10;
		  if(rnd <= 5){
			  banditV[i]+=r;
	  }else{
		  banditV[i]-=r;
	  }
  }
 }
  double the_reward=banditV[atp1];


  gsl_vector_set(local_observation, 0,flag);
  this_reward_observation.observation=local_observation;
  this_reward_observation.reward = the_reward;
  
  steps++;
  return &this_reward_observation;
}

void env_cleanup()
{
  gsl_vector_free(local_observation);
}

const char* env_message(const char* inMessage) 
{
  if(strcmp(inMessage,"what is your name?")==0)
  return "my name is skeleton_environment!";
  
  /* else */
  return "I don't know how to respond to your message";
}
