import os

print("Test passe de verification OK")
for i in range(10):
	com = './minicc -t 5 -v Tests/Verif/OK/test'+str(i)+'.c'
	#print(com);
	print("Test passe de verification (OK) de test"+str(i)+".c :")
	os.system(com);


print("Test passe de verification KO")
for i in range(5):
	com = './minicc -t 5 -v Tests/Verif/KO/test'+str(i)+'.c'
	#print(com);
	print("Test passe de verification (KO) de test"+str(i)+".c :")
	os.system(com)
