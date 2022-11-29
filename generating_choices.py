listt=[]

for i in range(20220001,20220501) :
    listt.append(i)

s={"CSE","ECE","MECH"}

s1={"NIT W","IIIT TRICHY","NIT CALICUT","IIT GOA","IIIT RAIPUR"}

newlist=[]

for i in range(0,500) :
    newlist.append(listt[i])
    ele=s1.pop()
    newlist.append(ele)
    s1.add(ele)
    ele=s.pop()
    newlist.append(ele)
    s.add(ele)
    ele=s1.pop()
    newlist.append(ele)
    s1.add(ele)
    ele=s.pop()
    newlist.append(ele)
    s.add(ele)
    ele=s1.pop()
    newlist.append(ele)
    s1.add(ele)
    ele=s.pop()
    newlist.append(ele)
    s.add(ele)

for i in newlist :
    print(i)