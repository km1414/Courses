rankall <- function(outcome, num) {
    
    # load data
    data <- read.csv('data/outcome-of-care-measures.csv', colClasses='character')
    
    # # check validility of state
    # if (!state %in% data$State) stop('invalid state')
    
    # prepare outcome name
    outcome <- gsub(' ', '.', stringr::str_to_title(outcome)) 
    outcome <- paste("Hospital.30.Day.Death..Mortality..Rates.from.", outcome, sep='')
    
    # check validility of outcome
    if (!outcome %in% names(data)) stop('invalid outcome')
    
    # get sorted state names
    states_all <- unique(data$State[order(data$State)])
    
    # create data frame for output
    ranked_df <- data.frame()
    
    # iterate  over every state
    for (state in states_all) {
    
        # get list of hospitals in state
        hospitals_all <- data[data$State == state, c('Hospital.Name', outcome, 'State')]
        
        # change rate values to numeric
        hospitals_all[,outcome] <- suppressWarnings(as.numeric(hospitals_all[,outcome]))
        
        # remove hospitals with NA rate
        hospitals_all <- hospitals_all[complete.cases(hospitals_all),]
        
        # sort hospitals by rate and name
        hospitals_all <- hospitals_all[order(hospitals_all[,outcome], hospitals_all[,'Hospital.Name']),]
        
        # fill output data frame
        if (num == 'best') {
            ranked_df <- rbind(ranked_df, hospitals_all[1, c('Hospital.Name', 'State')])
        }
        else if (num == 'worst') {
            ranked_df <- rbind(ranked_df, hospitals_all[nrow(hospitals_all), c('Hospital.Name', 'State')])
        }
        
        else{
            ranked_df <- rbind(ranked_df, hospitals_all[num, c('Hospital.Name', 'State')])
        }
        
        ranked_df$State[nrow(ranked_df)] <- state
    }
    
    # beautify data frame and return it
    colnames(ranked_df) <- c('hospital', 'state')
    rownames(ranked_df) <- ranked_df$state
    
    return(ranked_df)
}









