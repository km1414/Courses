## A pair of functions that cache the inverse of a matrix 
## rather than compute it repeatedly.


# creates a special object that can cache its inverse.
makeCacheMatrix <- function(x = matrix()) {
    
    # reset cached inverse value
    cached_inverse <- NULL
    
    # reset matrix value
    set_matrix <- function(m) {
        x <<- m
        cached_inverse <<- NULL
    }
    
    # give back cached matrix
    get_matrix <- function() x
    
    # cache inverse
    set_inverse <- function(inverse) cached_inverse <<- inverse
    
    # give back cached inverse
    get_inverse <- function() cached_inverse
    
    #return list of functions
    list(set_matrix=set_matrix,
         get_matrix=get_matrix,
         set_inverse=set_inverse,
         get_inverse=get_inverse)
}


# computes the inverse of the special "matrix" returned by makeCacheMatrix().
# if the inverse has already been calculated, retrieve it from the cache.
cacheSolve <- function(x, ...) {
    
    # return the inverse of 'x'
    cached_inverse <- x$get_inverse()
    
    # if it's already computed, return value
    if (!is.null(cached_inverse)) {
        message("getting cached data")
        return(cached_inverse)
    }
    
    # otherwise: get original matrix
    data <- x$get_matrix()
    
    # compute its inverse
    inverse <- solve(data, ...)
    
    # cache inverse
    x$set_inverse(inverse)
    
    # return inverse value
    inverse
    
}


          