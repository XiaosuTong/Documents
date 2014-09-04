

###########################################
## function to get quantiles of count data
##  Assumes that for count data, 
##      there are a smaller number of values with a large number of replicates.
##      for values with few replicates, keep the values and make count=1
##      for values with large replicates, keep two copies of the values 
##          and make the first count=1 and second count=(actual.count - 1)
##  input:
##      - value: actual values, then count=NULL; 
##              or unique values, then count needs to be provided
##      - count: count of unique values
##      - nq:    number of quantiles to produce
##  output: 
##      - a data.frame with value and x
###########################################
get_quantile <- function(value, count=NULL, nq=30000) {
    # total number of values
    total.count <- if (is.null(count)) length(value) else sum(count)

    if (total.count <= nq) {    # not too many values

        # sort the values to make plotting easier
        value <- sort(value)
        x <- ((1:total.count) - 0.5) / total.count

    } else {    # too many values

        # get the unique values and counts if not supplied as input
        if (is.null(count)) {   
            v.tb <- table(value)
            value <- as.numeric(names(v.tb))
            count <- as.numeric(v.tb)
        }
        # find popular values that will be drawn as a line segment
        ord <- order(count)
        tmp.value <- value[ord]
        tmp.count <- count[ord]
        pop <- cumsum(tmp.count) > nq
        # duplicate popular values once with count=1
        value <- rep(tmp.value[which(pop)], times=2)
        count <- c(rep(1, times=sum(pop)), tmp.count[which(pop)] - 1)
        # duplicate other values by its count 
        value <- c(value, rep(tmp.value[which(!pop)], times=tmp.count[which(!pop)]))
        count <- c(count, rep(1, times=sum(tmp.count[which(!pop)])))
        # re-order by value then by count
        ord <- order(value, count)
        value <- value[ord]
        count <- count[ord]
        # compute f-value
        x <- (cumsum(count) - 0.5) / total.count

    }

    # return a data.frame of value and x
    data.frame(value = value, x = x)
}

## use this to draw the quantiles
##  in panel function, check if the difference of two consecutive x values are greater than twice (or maybe 1.95x) of the minimum difference of all consecutive x values, if so, draw a line to connect the two values, otherwise just plot the point
tmp.plot <- xyplot(log2(value) ~ x
    , data = df.plot
    , cex = 0.20
    , main = "Quantiles of"
    , ylab = "Log base 2 Number of"
    , xlab = "f-value"
    , col = "blue"
    , panel = function(x,y,...) {
        x.diff <- diff(x)   # get the difference of all consecutive x values
        x.diff.min <- min(x.diff)    # get the minimum difference 
        index <- which(x.diff > 1.95 * x.diff.min)  # find where to draw lines
        for (i in index) {  ## connect the lines
            panel.segments(x[i],y[i],x[i+1],y[i+1],col="blue",lwd=1.75)
        }
        panel.abline(v=(0:10)/10,h=0:ceiling(max(y)), col='lightgrey', lty=3, lwd=0.5)
        panel.xyplot(x,y,...)
    }
)
my_ps(plot = tmp.plot, file=file.path(dir.plot, "nongen.in.addr_quant.ps"), need.pdf=F)


