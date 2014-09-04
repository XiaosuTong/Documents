#Input:
#  -- dir:  location of data on the hdfs, can be relative path
#  -- keys: a list of keys

#Output:
#  -- a list of key,value pairs, each key,value pair is a list of two named elements: key and value


my.rhgetkey <- function(dir, keys) {

  path <- rhabsolute.hdfs.path(dir)

  ## check if this is map file format
  ## the target dir should contain "data" and "index" files
  files <- grep("part-r-",rhls(path, recurse=TRUE)$file, value=TRUE)
  # number of data files and number of index files
  data.files <- sum(grepl("data$", files))
  index.files <- sum(grepl("index$", files))
  if (data.files!=index.files | data.files+index.files!=length(files))
        stop("input is not map file\n")

  x <- rhmapfile(path)
  lapply(keys, function(r) list(key=r, value=x[[r]]) )

}
