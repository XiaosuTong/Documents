
## install packages required to build the docs
#install.packages("devtools")
#library(devtools)
#install_github("staticdocs", "hadley")
#install_github("buildDocs", "hafen")


## load the pacakge
library(buildDocs)


## function to build the docs
#   assuming your working directory is 
#   doc.RHIPE/how-to-nuggets/
buildFunctionRef(
   packageLoc = "~/Downloads/plyr",
   outLoc = "./",
#   navPill = packageNavPill("https://github.com/user/project", docs = FALSE),
   copyrightText = "Somebody"
)
