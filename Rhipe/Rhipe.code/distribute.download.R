##Distribute download

map <- expression({
   lapply(map.keys, function(r){
    ## link to the file to be downloaded
    on <- sprintf("http://www.stat.purdue.edu/~mdw/519fall2008/stat519hw%s.pdf",r)
    ## use "wget" to download the file
    system(sprintf("wget  %s --directory-prefix ./tmp 2> ./errors",on))
   })
})


mr <- rhwatch(
        map = map,
        input = c(7,7), 
        output = rhfmt("/ln/tongx/userhipe/dist.down/", type="sequence"),
        mapred = list(mapred.reduce.tasks=1),
        jobname = "dist.down",
	## copyFiles needs to be TRUE to copy the files to HDFS
	copyFiles = TRUE,
        readback = FALSE
)

