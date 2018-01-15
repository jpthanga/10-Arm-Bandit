# run for rewards plot
dat_avg = read.table("C:\\Users\\Jeshuran\\Documents\\RL\\RL-glue\\RLClass_dist\\RL_EXP_OUT_avgResult.dat")
dat_step = read.table("C:\\Users\\Jeshuran\\Documents\\RL\\RL-glue\\RLClass_dist\\RL_EXP_OUT_stepResult.dat")

plot(x = 1:length(dat_avg[,1]), y = dat_step[,1], type="l", ylab="Average reward", xlab="Steps", col="red")
lines(x = 1:length(dat_step[,1]), y = dat_avg[,1], col="purple")


# run for best action taken plot
dat_avg = read.table("C:\\Users\\Jeshuran\\Documents\\RL\\RL-glue\\RLClass_dist\\RL_EXP_OUT_avgRight.dat")
dat_step = read.table("C:\\Users\\Jeshuran\\Documents\\RL\\RL-glue\\RLClass_dist\\RL_EXP_OUT_stepRight.dat")

plot(x = 1:length(dat_step[,1]), y = dat_step[,1], type="l", ylab="Percentage Right Arm Chosen", xlab="Steps", col="red")
lines(x = 1:length(dat_avg[,1]), y = dat_avg[,1], col="purple")





