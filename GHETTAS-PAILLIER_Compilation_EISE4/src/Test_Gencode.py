import os

print("Test gencode OK")
for i in range(10):
	com = './minicc -o res'+str(i)+'.c Tests/Verif/OK/test'+str(i)+'.c'
	#print(com);
	print("Test gencode (OK) de test"+str(i)+".c :")
	os.system(com);


print("Test gencode KO")
for i in range(5):
	com = './minicc Tests/Verif/KO/test'+str(i)+'.c'
	#print(com);
	print("Test gencode (KO) de test"+str(i)+".c :")
	os.system(com)
