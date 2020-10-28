Loch <- c("Ness", "Lomond" ,"Morar","Tay","Awe", "Maree","Ericht",
        "Lochy", "Rannoch","Shiel",  "Katrine","Arkaig","Shin")
Volume <- c(7.45,2.6,2.3,1.6,1.2,1.09,1.08,1.07,
            0.97,0.79,0.77,0.75,0.35)
Area <- c(56,71,27,26.4,39,28.6,18.6,16,
         19,19.5,12.4,16,22.5)
Lenght <- c(39,36,18.8,23,41,20,23,16,
            15.7,28,12.9,19.3,27.8)   
MaxDepth <- c(230,190,310,150,94,114,156,
             162,134,128,151,109,49)
MeanDepth <- c(132,37,87,60.6,32,38,57.6,
            70,51,40,43.4,46.5,15.5 )

data <- data.frame (Loch, Volume, Area, Lenght, MaxDepth, MeanDepth)
print(data)

#i can directly print the maximum lake without creating other variables
print(paste("Max volume lake: Loch" , data$Loch[which.max(data[,"Volume"])],
            "   Volume: ", max(data["Volume"])), max.levels=0)

#in case of future need of those informations i could have defined 3 variables 
#and printed them
# max_vol <- max(data["Volume"])
# max_vol_index <- which.max(data[,"Volume"])
# max_vol_name <- data$Loch[max_vol_index]

#same for the min volume and areas
print(paste("Min volume lake: Loch",data$Loch[which.min(data[,"Volume"])],
            "   Volume: ", min(data["Volume"])), max.levels=0)

print(paste("Max Area lake: Loch",data$Loch[which.max(data[,"Area"])],
            "   Area: ", max(data["Area"])), max.levels=0)
print(paste("Min Area lake: Loch",data$Loch[which.min(data[,"Area"])],
            "   Area: ", min(data["Area"])), max.levels=0)

data <- data[order(-Area),] #descending ordering
print("first 2 lake ordered by area: ")
print(head(data, n=2)) #print biggest 2 area lake

scotArea <-80077 #area of scotland
#metodo "sicuro"
#lakeArea <- lapply(data[, sapply(data,is.numeric)], sum)$Area
#metodo facile
lakeArea <- sum(data$Area)
print(paste("Lake total  Area:",lakeArea, " -> ", lakeArea*100/scotArea, "%"))
