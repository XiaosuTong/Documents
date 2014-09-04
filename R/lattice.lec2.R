outputdir <- "/home/tongx/Projects/stat695t/slice/ps/"

trellis.device(postscript, file = paste(outputdir, "key.autokey",".ps", sep = ""), color=TRUE, paper="letter")
xyplot(error ~ distance,  
	groups = as.factor(percent),
	data = subset(slope, percent <= 70),
	auto.key = TRUE,
	type = "b",
	pch = 1:5,
	col = 1:5,
	scales = list(y=list(tick.number=8)),
	xlab="Distance (degrees)",
	ylab="Absolute Error (%)")
dev.off()


trellis.device(postscript, file = paste(outputdir, "key.points",".ps", sep = ""), color=TRUE, paper="letter")
xyplot(error ~ distance,
        groups = as.factor(percent),
        data = subset(slope, percent <= 70),
        auto.key = TRUE,
        type = "p",
        pch = 1:5,
        col = 1:5,
        key = list(type = c("p"), text = list(levels(as.factor(subset(slope, percent <=70)$percent))), points = list(col=1:5, pch = 1:5), column = 5, space = "top"),                           
#       key = list(type = "b", text = list(levels(as.factor(subset(slope, percent <=70)$percent))), lines = list(col = 12:16, lty = 2, lwd = 1.5), space = "top"),                                             
        scales = list(y=list(tick.number=8)),
        xlab="Distance (degrees)",
        ylab="Absolute Error (%)")
dev.off()


trellis.device(postscript, file = paste(outputdir, "key.both",".ps", sep = ""), color=TRUE, paper="letter")
xyplot(error ~ distance,  
        groups = as.factor(percent),
        data = subset(slope, percent <= 70),
        auto.key = TRUE,
        type = "b",
        pch = 1:5,
        col = 1:5,
        key = list(type = c("l"), text = list(levels(as.factor(subset(slope, percent <=70)$percent))),  lines = list(col =1:5, lwd =1.5), points = list(col=1:5, pch = 1:5), column = 5, space = "top"),                                                    
#       key = list(type = "b", text = list(levels(as.factor(subset(slope, percent <=70)$percent))), lines = list(col = 12:16, lty = 2, lwd = 1.5), space = "top"),                                             
        scales = list(y=list(tick.number=8)),
        xlab="Distance (degrees)",
        ylab="Absolute Error (%)")
dev.off()


trellis.device(postscript, file = paste(outputdir, "key.lines",".ps", sep = ""), color=TRUE, paper="letter")
xyplot(error ~ distance,
        groups = as.factor(percent),
        data = subset(slope, percent <= 70),
        auto.key = TRUE,
        type = "l",
	lty = 1:5,
	lwd = 1.5,
        col = 1:5,
#        key = list(type = "p", text = list(levels(as.factor(subset(slope, percent <=70)$percent))), points = list(pch = 1:5, col = 1:5), column = 5, space = "top"),
        key = list(type = "l", text = list(levels(as.factor(subset(slope, percent <=70)$percent))), lines = list(col = 1:5, lty = 1:5, lwd = 1.5), column = 5, space = "top"),                                             
        scales = list(y=list(tick.number=8)),
        xlab="Distance (degrees)",
        ylab="Absolute Error (%)")
dev.off()

trellis.device(postscript, file = paste(outputdir, "distrib.type",".ps", sep = ""), color=TRUE, paper="letter")
xyplot(error ~ distance,
        groups = as.factor(percent),
        data = subset(slope, percent < 60),
        type = c("b","l"),
        distribute.type = TRUE, 
        pch = 16,
        col = 1:2,
        lwd = 1.5,
        cex = 2,
        scales = list(y=list(tick.number=8)),
        xlab="Distance (degrees)",
        ylab="Absolute Error (%)")
dev.off()


trellis.device(postscript, file = paste(outputdir, "strip",".ps", sep = ""), color=TRUE, paper="letter")
xyplot(error ~ distance | as.factor(percent),
        data = slope,
        strip = strip.custom(par.strip.text= list(cex = 1.5, col = "red")),
        par.settings = list(layout.heights = list(strip = 1.5), strip.background=list(col="lightgrey")),
        scales = list(y=list(tick.number=8)),
        xlab="Distance (degrees)",
        ylab="Absolute Error (%)")
dev.off()


trellis.device(postscript, file = paste(outputdir, "strip.left",".ps", sep = ""), color=TRUE, paper="letter")
xyplot(error ~ distance | as.factor(percent),
        data = slope,
	strip = FALSE,
        strip.left = strip.custom(par.strip.text= list(cex = 1.5, col = "red")),
        par.settings = list(layout.heights = list(strip = 1.5), strip.background=list(col="lightgrey")),
        scales = list(y=list(tick.number=8)),
        xlab="Distance (degrees)",
        ylab="Absolute Error (%)")
dev.off()


