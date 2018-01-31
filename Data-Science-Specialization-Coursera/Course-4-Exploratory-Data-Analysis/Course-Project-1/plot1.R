# Exploratory Data Analysis - Course Project 1
# Plot 1 


# load and subset data
hpc <- read.table('household_power_consumption.txt', header=T, sep=';', stringsAsFactors=F)
hpc <- subset(hpc, Date=='1/2/2007'| Date=='2/2/2007')

# convert useful data to numeric
hpc[,3:9] <- sapply(hpc[,3:9], as.numeric)

# open device
png('plot1.png')

# make plot
hist(hpc$Global_active_power, 
     col='red',
     xlab='Global Active Power (kilowatts)',
     ylab='Frequency',
     main='Global Active Power')

# close device
dev.off()
