# hello - AGNIDIPTO BANIK.py
n=int(input())
coin=[100,50,20,10,5,2,1]
count=[0,0,0,0,0,0,0]
j=0
k=0
while 1:
    if n>=coin[j]:
        
        n=n-coin[j]
        count[j]=count[j]+1
    else:
        if j==6:
            break

        j=j+1
l=[]        
#print(count)   
l2=["01100100","00110010","00010100","00001010","00000101","00000010","00000001"] 
l100=[0,1,1,0,0,1,0,0] 
l50=[0,0,1,1,0,0,1,0]
l20=[0,0,0,1,0,1,0,0]
l10=[0,0,0,0,1,0,1,0]
l5=[0,0,0,0,0,1,0,1]
l2=[0,0,0,0,0,0,1,0]
l1=[0,0,0,0,0,0,0,1]
l.append(l100)
l.append(l50)
l.append(l20)
l.append(l10)
l.append(l5)
l.append(l2)
l.append(l1)
actual=[]
#print(l[0])

for i in range(0,7):
    for j in range(0,count[i]):
        actual.append(l[i])
#print(actual)        
size =len(actual)
s=[]
#print(size)
for j in range(0,8):
    k=1
    sum=0
    for i in range(0,size):
        sum =sum+actual[i][j]*pow(2,size-k)
        k+=1
    s.append(sum)
# print(s)    
size2=len(s)
changed_currency=0
for i in range(0,size2):
    for j in range(i+1,size2):
        if s[i]<s[j]:
            t=s[i]
            s[i]=s[j]
            s[j]=t
for i in range(0,size2):
    if s[i]==0:
        continue
    # changed_currency=changed_currency*10+s[i]
    print(s[i], end = " ")
# print(changed_currency)




