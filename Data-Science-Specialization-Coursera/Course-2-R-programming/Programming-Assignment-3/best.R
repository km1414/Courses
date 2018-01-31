best <- function(state, outcome) {
    
    # load data
    data <- read.csv('data/outcome-of-care-measures.csv', colClasses='character')
    
    # check validility of state
    if (!state %in% data$State) stop('invalid state')
    
    # prepare outcome name
    outcome <- gsub(' ', '.', stringr::str_to_title(outcome)) 
    outcome <- paste("Hospital.30.Day.Death..Mortality..Rates.from.", outcome, sep='')
    
    # check validility of outcome
    if (!outcome %in% names(data)) stop('invalid outcome')
    
    # get list of hospitals in state
    hospitals_all <- data[data$State == state, c('Hospital.Name', outcome)]
    
    # change rate values to numeric
    hospitals_all[,outcome] <- suppressWarnings(as.numeric(hospitals_all[,outcome]))
    
    # get best mortality rate
    rate <- min(hospitals_all[, outcome], na.rm=T)
    
    # get hospitals with bets mortality rate
    hospitals_best <- hospitals_all[hospitals_all[,outcome] == rate, ]
    
    # get first name of best hospitals 
    name <- hospitals_best$Hospital.Name[order(hospitals_best$Hospital.Name)][1]
    
    return(name)
}





