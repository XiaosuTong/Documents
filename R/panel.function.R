#These functions are intended to replace common low level
#traditional graphics functions, primarily for use in panel
#functions.  The originals can not be used (at least not easily)
#because lattice panel functions need to use grid graphics.  Low
#level drawing functions in grid can be used directly as well, and
#is often more flexible.  These functions are provided for
#convenience and portability.

#you can use llines() or panel.abline(), use lpoints or panel.points(),
#use ltext() or panel.text(), use lsegments() or panel.segments(),

trellis.device(postscript, file = "panel.arrows.ps", color = "TRUE", paper="letter")
xyplot(error ~ distance, 
	data=slope,
	panel=function(x,y,...){
	   panel.xyplot(x,y,...)
	   for(i in 1:(length(x)-1)){
	     panel.arrows(x[i],y[i],x[i+1],y[i+1], angle=10, code=2, length=0.2,...)
           }
	}
)
dev.off()

trellis.device(postscript, file = "panel.abline.ps", color = "TRUE", paper="letter")
xyplot(error ~ distance | percent,
	data = slope,
	panel = function(x,y,...){
		panel.abline(h=mean(y), v=mean(x), lty=3,...)
		panel.xyplot(x,y,...)
	}
)
dev.off()

trellis.device(postscript, file = "panel.abline2.ps", color = "TRUE", paper="letter")
xyplot(error ~ distance | percent,
	data = slope,
	panel = function(x,y,...){
		cof <- lm(y ~ x)$coefficients
		panel.abline(a=cof[1], b=cof[2], col="red", ...)
		panel.xyplot(x,y,...)
	}
)
dev.off()

trellis.device(postscript, file = "panel.abline3.ps", color = "TRUE", paper="letter")
xyplot(error ~ distance | percent,
        data = slope,
        panel = function(x,y,...){
                cof <- lm(y ~ x)
                panel.abline(reg = cof, col="red", ...)
                panel.xyplot(x,y,...)
        }
)
dev.off()

trellis.device(postscript, file = "panel.lmline.ps", color = "TRUE", paper="letter")
xyplot(error ~ distance | percent,
        data = slope,
        panel = function(x,y,...){
		panel.lmline(x, y, ...)
                panel.xyplot(x,y,...)
        }
)
dev.off()

#trellis.par.get("reference.line")
trellis.device(postscript, file = "panel.refline.ps", color = "TRUE", paper="letter")
xyplot(error ~ distance | percent,
        data = slope,
        panel = function(x,y,...){
                panel.refline(h=mean(y), v=mean(x), ...)
                panel.xyplot(x,y,...)
        }
)
dev.off()

trellis.device(postscript, file = "panel.curve.ps", color = "TRUE", paper="letter")
xyplot(error ~ distance,
        data = slope,
        panel = function(x,y,...){
		panel.xyplot(x,y,...)
                panel.curve(exp(x/25)+5, from=min(x), to=max(x), ...)
        }
)
dev.off()

trellis.device(postscript, file = "panel.grid.ps", color = "TRUE", paper="letter")
xyplot(error ~ distance,
        data = slope,
        panel = function(x,y,...){
                panel.xyplot(x,y,...)
		panel.grid(h=-1, v=-1, col="red", ...)
        }
)
dev.off()

trellis.device(postscript, file = "panel.average.ps", color = "TRUE", paper="letter")
xyplot(error ~ percent,
        data = slope,
        panel = function(x,y,...){
                panel.xyplot(x,y,...)
                panel.grid(h=-1, v=-1, col="black", lty=3, ...)
		panel.average(x,y,fun = mean, horizontal = FALSE, col="black",...)
        }
)
dev.off()

trellis.device(postscript, file = "panel.linejoin.ps", color = "TRUE", paper="letter")
xyplot(error ~ percent,
        data = slope,
        panel = function(x,y,...){
                panel.xyplot(x,y,...)
		panel.linejoin(x, y, fun = mean, horizontal = FALSE, col="red", ...)

        }
)
dev.off()

trellis.device(postscript, file = "panel.segments.ps", color = "TRUE", paper="letter")
xyplot(error ~ distance | percent,
        data = slope,
        panel = function(x,y,...){
                panel.xyplot(x,y,...)
                panel.segments( min(x), y[which.min(x)], min(x), 0, col="red", ...)

        }
)
dev.off()

trellis.device(postscript, file = "panel.segments2.ps", color = "TRUE", paper="letter")
xyplot(error ~ distance | percent,
        data = slope,
	pch = 16,
        panel = function(x,y,...){
                panel.xyplot(x,y,...)
                panel.segments( rep(min(x),2), rep(y[which.min(x)],2), 
				c(0, min(x)), c(y[which.min(x)], 0), col="red", ...)
        }
)
dev.off()

trellis.device(postscript, file = "panel.segments3.ps", color = "TRUE", paper="letter")
xyplot(error ~ distance | percent,
        data = slope,
        pch = 16,
        panel = function(x,y,...){
                panel.xyplot(x,y,...)
                panel.segments( rep(min(x),2), rep(y[which.min(x)],2),
                                c(0, min(x)), c(y[which.min(x)], 0), col="red", ...)
		panel.text(min(x), y[which.min(x)], round(min(x),2), adj=c(.5,.5))
        }
)
dev.off()

trellis.device(postscript, file = "panel.points.ps", color = "TRUE", paper="letter")
xyplot(error ~ distance | percent,
        data = slope,
        pch = 16,
        panel = function(x,y,...){
                panel.xyplot(x,y,...)
                panel.points(mean(x), mean(y), col="red")
        }                       
)   
dev.off()




xyplot(error ~distance, 
        data=slope, 
        panel=function(x, y, subscripts, ...){
                xx1 <- subset(slope[subscripts,], resolution>=5)$distance
                xx2 <- subset(slope[subscripts,], resolution <5)$distance
                yy1 <- subset(slope[subscripts,], resolution>=5)$error
                yy2 <- subset(slope[subscripts,], resolution <5)$error
                panel.xyplot(xx1,yy1,pch="+", cex=2, col="red",...)
                panel.xyplot(xx2,yy2, pch=16, col="black",...)
        }
)

bwplot(yield ~ site , barley, groups = year,
       panel = function(x, y, groups, subscripts, ...) {
           panel.grid(h = -1, v = 0)
           panel.stripplot(x, y, ..., jitter.data = TRUE,
                           groups = groups, subscripts = subscripts)
           panel.superpose(x,y,...,panel.groups = panel.average,
                           groups = groups, subscripts = subscripts)
       },
       auto.key =
       list(points = FALSE, lines = TRUE, columns = 2))


my.panel <- function(x, y, subscripts, col, pch,...) {
	low95 <- fac.vals$low95[subscripts]
	up95 <- fac.vals$up95[subscripts]
	panel.xyplot(x, y, col=col, pch=pch, ...)
	panel.arrows(x, low95, x, up95, angle=90, code=3, length=0.05, col=col)
}

myPanel <- function(x,y,...) {
    panel.xyplot(x,y,...)
    panel.abline(lm(y~x), ...)
}

xyplot(yield ~ site, group=year, data=barley,
       panel=function(...) panel.superpose(panel.groups=myPanel, ...))






trellis.device(postscript, file = "aspect.fill.ps", color = "TRUE", paper="letter")
xyplot(error ~ resolution,
        data=slope,
        aspect = "fill",
)
dev.off()

trellis.device(postscript, file = "aspect.xy.ps", color = "TRUE", paper="letter")
xyplot(error ~ resolution,
        data=slope,
        aspect = "xy",
)
dev.off()

trellis.device(postscript, file = "aspect.iso.ps", color = "TRUE", paper="letter")
xyplot(error ~ resolution,
        data=slope,
        aspect = "iso",
)
dev.off()


prepanel <- function(x,...){
        ans <- prepanel.qqmathline(x,...)
        theo.quant <- qnorm(c(.25,.75))
        data.quant <- quantile(x, c(.25,.75), names = F)
        slope <- ans$dy / ans$dx 
        intercept <- data.quant[1] - slope*theo.quant[1]
        yylim <-  slope*(ans$xlim)+ intercept
        ans$ylim <- range(ans$ylim, yylim)
	ans
}

trellis.device(postscript, file = "prepanel.custom.ps", color = "TRUE", paper="letter")
qqmath(~ error,
	data=slope,
	aspect = "xy",
	prepanel = function(x,...){
		prepanel(x)
},
#       prepanel = function(x,...){
#		a <- prepanel.qqmathline(x,...)
#		print(a)
#		ydif <- diff(a$ylim)
#		xdif <- diff(a$xlim)
#		b <- abs((a$dy/a$dx)/(ydif/xdif))
#		print(b)
#	},
#	prepanel = function(x,...){
#		a <- prepanel.default.qqmath(x,...)
#		print(a)
#		ydif <- diff(a$ylim)
#		xdif <- diff(a$xlim)
#		b <- abs((a$dy/a$dx)/(ydif/xdif))
#		print(1/median(b))
#	},
	panel = function(x,...){
		panel.qqmathline(x,...)
		panel.qqmath(x,...)
	}
)
dev.off()

trellis.device(postscript, file = "prepanel.loess.ps", color = "TRUE", paper="letter")
xyplot(error ~ resolution, 
	data=slope,
	aspect = "xy", 
	prepanel = function(x,y,...){
		a <- prepanel.loess(x,y,span=2/3, degree=2,...)
		print(a)
		ydif <- diff(a$ylim)
                xdif <- diff(a$xlim)
		b <- abs((a$dy/a$dx)/(ydif/xdif))
		print(1/median(b))
	},
	panel = function(x,y,...){
		panel.xyplot(x,y,...)
		panel.loess(x,y,span=2/3, degree=2, col="red", ...)
	}
)
dev.off()
