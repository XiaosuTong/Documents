##For gacrux cluster 
library(Rhipe)
rhinit()
rhoptions(zips = '/ln/share/RhipeLib.tar.gz')
rhoptions(runner = 'sh ./RhipeLib/library/Rhipe/bin/RhipeMapReduce.sh')


##For rossmann cluster
library(Rhipe)
rhinit()
rhoptions(zips = '/wsc/share/RhipeLib.tar.gz')
rhoptions(runner = 'sh ./RhipeLib/library/Rhipe/bin/RhipeMapReduce.sh')
hdfs.setwd("/wsc/tongx/")

