# Getting and Cleaning Data Course Project


# download and unzip data
download.file('https://d396qusza40orc.cloudfront.net/getdata%2Fprojectfiles%2FUCI%20HAR%20Dataset.zip', 
              destfile='UCI HAR Dataset.zip', method='curl')
unzip('UCI HAR Dataset.zip')


# load data
train_x <- read.table("UCI HAR Dataset/train/X_train.txt")
train_y <- read.table("UCI HAR Dataset/train/y_train.txt")
train_sub <- read.table("UCI HAR Dataset/subject_train.txt")
test_x <- read.table("UCI HAR Dataset/test/X_test.txt")
test_y <- read.table("UCI HAR Dataset/test/y_test.txt")
test_sub <- read.table("UCI HAR Dataset/test/subject_test.txt")
features <- read.table("UCI HAR Dataset/features.txt", as.is=T)[,2]
activities <- read.table("UCI HAR Dataset/activity_labels.txt", as.is=T)[,2]


### 1 - merge all data sets
full_data <- rbind(cbind(train_x, train_y, train_sub), cbind(test_x, test_y, test_sub))
names(full_data)<-c(features, 'activity', 'subject')


### 2 - extract useful columns
columns <- c(grep('mean()', features, value=T, fixed=T), 
             grep('std()', features, value=T, fixed=T),
             'activity', 'subject')
full_data <- full_data[columns]


### 3 - set activities names
full_data$activity <- sapply(full_data$activity, function(x) x <- activities[x])


### 4 - standartize variable names
columns <- gsub("mean()", "Mean", columns, fixed=T)
columns <- gsub("std()", "Std", columns, fixed=T)
columns <- gsub("-", "", columns, fixed=T)
names(full_data) <- columns


### 5 - new data set - averages for subjects
library(dplyr)
mean_data <- full_data[,names(full_data) != 'activity'] %>% 
             group_by(subject) %>% 
             summarize_all(mean)


# save data to files
write.table(full_data, file='full_data.txt', quote=F, row.names=F)
write.table(mean_data, file='mean_data.txt', quote=F, row.names=F)
