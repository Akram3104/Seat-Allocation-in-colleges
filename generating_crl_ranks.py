

list1=[]
for i in range(20220001,20220501,1) :
    list1.append(i)


list2=[]

sett={"OC","EWS","OBC","SC","ST"}

for i in range(150) :
    list2.append("OC")

for i in range(100) :
    list2.append("OBC")

for i in range(100) :
    list2.append("EWS")

for i in range(75) :
    list2.append("SC")

for i in range(75) :
    list2.append("ST")




s=[]

for i in range(250,275) :
    s.append(i)

for i in range(100,125) :
    s.append(i)

for i in range(1,26) :
    s.append(i)

for i in range(325,350) :
    s.append(i)

for i in range(151,250) :
    s.append(i)

for i in range(26,100) :
    s.append(i)

for i in range(350,401) :
    s.append(i)

for i in range(300,325) :
    s.append(i)

for i in range(450,475) :
    s.append(i)

for i in range(125,151) :
    s.append(i)

for i in range(275,300) :
    s.append(i)

for i in range(401,426) :
    s.append(i)

for i in range(475,501) :
    s.append(i)

for i in range(426,450) :
    s.append(i)







list3=[]
for i in range(400,500) :
    list3.append(list1[i])
    list3.append(list2[i])
    list3.append(s[i])


for i in list3 :
    print(i)
