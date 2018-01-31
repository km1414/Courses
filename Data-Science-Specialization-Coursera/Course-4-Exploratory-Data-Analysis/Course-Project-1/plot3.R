# Exploratory Data Analysis - Course Project 1
# Plot 3


# load and subset data
hpc <- read.table('household_power_consumption.txt', header=T, sep=';', stringsAsFactors=F)
hpc <- subset(hpc, Date=='1/2/2007'| Date=='2/2/2007')

# convert useful data to numeric
hpc[,3:9] <- sapply(hpc[,3:9], as.numeric)

# add datetime column
hpc$datetime <- strptime(paste(hpc$Date, hpc$Time, sep=" "), "%d/%m/%Y %H:%M:%S") 

# open device
png('plot3.png')

# make plot
plot(hpc$datetime, hpc$Sub_metering_1, type='l',xlab='',ylab='Energy sub metering')
lines(hpc$datetime, hpc$Sub_metering_2, type='l', col='red')
lines(hpc$datetime, hpc$Sub_metering_3, type='l', col='blue')
legend("topright", names(hpc)[7:9], col=c('black', 'red', 'blue'), lty=1)

# close device
dev.off()
