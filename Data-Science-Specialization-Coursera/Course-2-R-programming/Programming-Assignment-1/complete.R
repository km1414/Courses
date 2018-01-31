
complete <- function(directory, id = 1:332) {
    
    # empty vector for values
    output <- data.frame()
    
    for (index in id) {
        
        # convert id to string
        index_str <- paste(paste(rep(0, 3-nchar(index)), collapse=""), index, sep="")
        
        # read tada from file
        data_all <- read.csv(paste(directory, "/", index_str, ".csv", sep = ""))
        
        # get number of observetions
        observations <- sum(complete.cases(data_all))
        
        # save value to data frame
        output <- rbind(output, data.frame(id=index, nobs=observations))
    }
    
    output
}



# complete("specdata", 1)
# complete("specdata", c(2, 4, 8, 10, 12))
# complete("specdata", 30:25)
# complete("specdata", 3)



