kdtree <- function(df, alpha)
{
	v <- data.frame()
	li <- list(0)
	cell <- list()
	depth <- 1
	N <- dim(df)[1]
	D <- dim(df)[2]
	package <- df
	names(df) <- c("x","y")
	rx <- range(df$x)
	ry <- range(df$y)
	dif.rx <- diff(rx)
	dif.rx <- diff(ry)
	if(depth == 1){
		v <- expand.grid(x=rx, y=ry)
	}
	while(length(li) != 0){
	  length(li) <- length(li) - 1
	  if(dim(package)[1] > max(alpha*N, 1)){
		rx <- range(package$x)
		ry <- range(package$y)
		dif.rx <- diff(rx)
		dif.ry <- diff(ry)
		if(dif.rx >= dif.ry){
			m <- median(package$x)
			v <- rbind(v, expand.grid(x=m, y=ry))
			li <- append(li, list(package[with(package, x<=m),]))
			li <- append(li, list(package[with(package, x>m),]))
			depth <- depth + 1
		}else{
			m <- median(package$y)
			v <- rbind(v, expand.grid(x=rx, y=m))
			li <- append(li, list(package[with(package, y<=m),]))
			li <- append(li, list(package[with(package, y>m),]))
			depth <- depth + 1
		}
	  }else{
		cell <- append(cell, list(package))
	  }
	  if(length(li) != 0){
		package <- li[[length(li)]]
	  }
	  else{
		package <- data.frame()
	  } 			
	}
	return(list(vertix=v, cells=cell))
}

#xyplot(y~x, data=a,
#		groups=group,
#		panel=function(x,y,...){
#			panel.xyplot(x,y, type="l", ...)
#			panel.xyplot(df$x, df$y, type="p", col="blue", ...)
#		})
