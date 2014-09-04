
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
buildDocs(
   docsLoc       = "./docs",
   outLoc        = "./",
   copyrightText = "Team-Rhipe",
   # pageList      = c("01.intro.Rmd", "02.wordcount.Rmd"),
   navPill       = packageNavPill("https://github.com/XiaosuTong"),
   # editHref      = "https://github.com/user/project/edit/gh-pages/docs/",
   knit          = TRUE,
   purl          = FALSE
)

