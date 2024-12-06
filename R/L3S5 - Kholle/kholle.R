options(scipen=999)
library(FactoMineR)

temp = read.csv(file.choose(), header = T,  row.names = 1)
library(FactoMineR)
install.packages(c("Factoshiny","missMDA","FactoInvestigate"))
library(Factoshiny)


res.pca <- PCA(temp, quanti.sup = 16:29, quali.sup = 30, ind.sup =1)
summary(res.pca)


res <- Factoshiny(temp)


view(res)




dimdesc(res.pca)

res.pca = PCA(decathlon[,1:10], scale.unit=TRUE, ncp=5, graph=T) # PCA graph variable

plot.PCA(res.pca, axes = c(1,2), choix = "ind", habillage = 16) #habillage

plotellipses(res.pca)    #ellipse

barplot(height=res.pca$eig[,1]) # graphique colone


library(FactoMineR)
jus = read.csv(file.choose(), header = T, row.names = 1)
res.pca <- PCA(jus, quali.sup = 16, quanti.sup = 8:15)
