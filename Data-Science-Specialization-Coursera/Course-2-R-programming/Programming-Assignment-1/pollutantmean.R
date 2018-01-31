
pollutantmean <- function(directory, pollutant, id = 1:332) {
    
    # empty vector for values
    values_all <- c()
  
    for (index in id) {

        # convert id to string
        index <- paste(paste(rep(0, 3-nchar(index)), collapse=""), index, sep="")
        
        # read tada from file
        data_all <- read.csv(paste(directory, "/", index, ".csv", sep = ""))
        
        # save the useful values
        values_all <- c(values_all, data_all[pollutant][!is.na(data_all[pollutant])])
    }
    
    # compute mean
    mean(values_all)
}

# pollutantmean("specdata", "sulfate", 1:10)
# pollutantmean("specdata", "nitrate", 70:72)
# pollutantmean("specdata", "nitrate", 23)


