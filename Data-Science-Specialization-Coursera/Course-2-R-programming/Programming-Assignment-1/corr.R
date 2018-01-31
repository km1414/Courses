
corr <- function(directory, threshold = 0) {
    
    # empty numeric vector for values
    output <- numeric(0)
    
    for (index in 1:332) {
        
        # convert id to string
        index_str <- paste(paste(rep(0, 3-nchar(index)), collapse=""), index, sep="")
        
        # read tada from file
        data_all <- read.csv(paste(directory, "/", index_str, ".csv", sep = ""))
        
        # get number of observetions
        observations <- sum(complete.cases(data_all))
        
        
        if (observations > threshold) {
            
            # get  completely observed cases
            data_all <- data_all[complete.cases(data_all),]
            
            # add correlation value to vector
            output <- c(output, cor(data_all$sulfate, data_all$nitrate))
        }
        
    }
    
    output
}

# 
# cr <- corr("specdata", 150)
# head(cr)
# summary(cr)
# 
# cr <- corr("specdata", 400)
# head(cr)
# summary(cr)
# 
# cr <- corr("specdata", 5000)
# head(cr)
# summary(cr)
# 
# cr <- corr("specdata")
# head(cr)
# summary(cr)







