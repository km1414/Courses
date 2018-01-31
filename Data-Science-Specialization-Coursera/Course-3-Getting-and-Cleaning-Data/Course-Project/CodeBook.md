# CodeBook for Coursera - Getting and Cleaning Data Course Project

## Data

* Data for the project:
https://d396qusza40orc.cloudfront.net/getdata%2Fprojectfiles%2FUCI%20HAR%20Dataset.zip

* A full description of data:
http://archive.ics.uci.edu/ml/datasets/Human+Activity+Recognition+Using+Smartphones

## Features 
*The repository contains two different data sets - the original output and output, averaged over each subject. Nevertheless, used variable names are the same.*

The features selected for this database come from the accelerometer and gyroscope 3-axial raw signals tAccXYZ and tGyroXYZ. These time domain signals (prefix 't' to denote time) were captured at a constant rate of 50 Hz. Then they were filtered using a median filter and a 3rd order low pass Butterworth filter with a corner frequency of 20 Hz to remove noise. Similarly, the acceleration signal was then separated into body and gravity acceleration signals (tBodyAccXYZ and tGravityAccXYZ) using another low pass Butterworth filter with a corner frequency of 0.3 Hz. Subsequently, the body linear acceleration and angular velocity were derived in time to obtain Jerk signals (tBodyAccJerkXYZ and tBodyGyroJerkXYZ). Also the magnitude of these three-dimensional signals were calculated using the Euclidean norm (tBodyAccMag, tGravityAccMag, tBodyAccJerkMag, tBodyGyroMag, tBodyGyroJerkMag). Finally a Fast Fourier Transform (FFT) was applied to some of these signals producing fBodyAccXYZ, fBodyAccJerkXYZ, fBodyGyroXYZ, fBodyAccJerkMag, fBodyGyroMag, fBodyGyroJerkMag. (Note the 'f' to indicate frequency domain signals). These signals were used to estimate variables of the feature vector for each pattern: 'XYZ' is used to denote 3-axial signals in the X, Y and Z directions.

* tBodyAccXYZ
* tGravityAccXYZ
* tBodyAccJerkXYZ
* tBodyGyroXYZ
* tBodyGyroJerkXYZ
* tBodyAccMag
* tGravityAccMag
* tBodyAccJerkMag
* tBodyGyroMag
* tBodyGyroJerkMag
* fBodyAccXYZ
* fBodyAccJerkXYZ
* fBodyGyroXYZ
* fBodyAccMag
* fBodyAccJerkMag
* fBodyGyroMag
* fBodyGyroJerkMag

The set of variables that were estimated from these signals are: 

* Mean: Mean value
* Std: Standard deviation

Notes: 
* Features are normalized and bounded within [-1,1].
* Each feature vector is a row on the text file.

Data set also contain two more variables:

* activity - the activity, that was performed during experiment.
* subject - the ID of person, who performed activity

## Data tranformations

Data tranformations, performed to clean up the data:

* Merged the training and the test sets to create one data set.
* Extracted only the measurements on the mean and standard deviation for each measurement.
* Used descriptive activity names to name the activities in the data set.
* Relabeled the data with descriptive variable names.
* From the data set in step 4, created a second, independent tidy data set with the average of each variable for each activity and each subject.

More info about repository could be found in README.md

