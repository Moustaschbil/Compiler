import os

print("Test syntaxe OK")
for i in range(16):
	com = './minicc -t 5 -s Tests/Syntaxe/OK/test'+str(i)+'.c'
	#print(com);
	print("Analyse syntaxique (OK) de test"+str(i)+".c :")
	os.system(com);


print("Test syntaxe KO")
for i in range(16):
	com = './minicc -t 5 -s Tests/Syntaxe/KO/test'+str(i)+'.c'
	#print(com);
	print("Analyse syntaxique (KO) de test"+str(i)+".c :")
	os.system(com)
