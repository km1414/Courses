rankhospital <- function(state, outcome, num) {
    
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
    
    # remove hospitals with NA rate
    hospitals_all <- hospitals_all[complete.cases(hospitals_all),]
    
    # sort hospitals by rate and name
    hospitals_all <- hospitals_all[order(hospitals_all[,outcome], hospitals_all[,'Hospital.Name']),]
    
    # output answer
    if (num == 'best') return(hospitals_all[1, 'Hospital.Name'])
    if (num == 'worst') return(hospitals_all[nrow(hospitals_all), 'Hospital.Name'])
    
    return(hospitals_all[num, 'Hospital.Name'])
    
}

