# Exploratory Data Analysis - Course Project 1
# Plot 4


# load and subset data
hpc <- read.table('household_power_consumption.txt', header=T, sep=';', stringsAsFactors=F)
hpc <- subset(hpc, Date=='1/2/2007'| Date=='2/2/2007')

# convert useful data to numeric
hpc[,3:9] <- sapply(hpc[,3:9], as.numeric)

# add datetime column
hpc$datetime <- strptime(paste(hpc$Date, hpc$Time, sep=" "), "%d/%m/%Y %H:%M:%S") 

# open device
png('plot4.png')

# change graph parameters - 2 x 2
par(mfrow=c(2,2))

# make plot - part 1
with(hpc, (plot(datetime,
                Global_active_power,
                type='l',
                xlab='',
                ylab='Global Active Power')))

# make plot - part 2
with(hpc, (plot(datetime,
                Voltage,
                type='l',
                xlab='datetime',
                ylab='Voltage')))

# make plot - part 3
plot(hpc$datetime, hpc$Sub_metering_1, type='l', xlab='',ylab='Energy sub metering')
lines(hpc$datetime, hpc$Sub_metering_2, type='l', col='red')
lines(hpc$datetime, hpc$Sub_metering_3, type='l', col='blue')
legend("topright", names(hpc)[7:9], col=c('black', 'red', 'blue'), lty=1, bty='n')

# make plot - part 4
with(hpc, (plot(datetime,
                Global_reactive_power,
                type='l',
                xlab='datetime',
                ylab='Global_reactive_power')))

# close device
dev.off()
