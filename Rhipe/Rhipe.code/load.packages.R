#######################
## load another package
#######################
## install R package plyr
install.packages("plyr", lib="/home/shaula/u16/tongx/R_LIBS")
## default can be found by
.libPaths()


map = expression({
  library(plyr, lib.loc="/home/shaula/u16/tongx/R_LIBS")
  for (r in map.values){
        if (exists("stl2")) rhcounter("fun","ddply",1)
  }
})

mr <- rhwatch(
        map = map,
        input = c(1,1),
        output = rhfmt("/ln/tongx/userhipe/package", type="sequence"),
        mapred = list(mapred.reduce.tasks=1),
        jobname = "package",
        readback = FALSE
)


