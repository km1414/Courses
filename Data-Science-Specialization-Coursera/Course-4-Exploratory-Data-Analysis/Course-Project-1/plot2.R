# Exploratory Data Analysis - Course Project 1
# Plot 2


# load and subset data
hpc <- read.table('household_power_consumption.txt', header=T, sep=';', stringsAsFactors=F)
hpc <- subset(hpc, Date=='1/2/2007'| Date=='2/2/2007')

# convert useful data to numeric
hpc[,3:9] <- sapply(hpc[,3:9], as.numeric)

# add datetime column
hpc$datetime <- strptime(paste(hpc$Date, hpc$Time, sep=" "), "%d/%m/%Y %H:%M:%S") 

# open device
png('plot2.png')

# make plot
with(hpc, (plot(datetime,
                Global_active_power,
                type='l',
                xlab='',
                ylab='Global Active Power (kilowatts)')))


# close device
dev.off()
