from random import randint

# random list
listEx1 = [];
for i in range(1, 1000):
    listEx1.append(randint(1, 1000000));
listEx1.sort();
print('int mediumRan[] = {');
print(listEx1);
print('};');

# list with only 2 values
valueOne = randint(1, 1000000);
valueTwo = randint(1, 1000000);
numOfAppear = randint(40000, 60000);
listOne = [valueOne] * numOfAppear;
listTwo = [valueTwo] * (100000 - numOfAppear);
listOne.extend(listTwo);
print('int largeRan[] = {');
print(listOne);
print('};')

# large list with random values
valueLead = randint(1, 1000000);
numOfAppear = 50001;
listLead = [valueLead] * numOfAppear;
listEx3 = []
listTemp = []
for i in range(1, 20000):
    listTemp.append(randint(1, valueLead - 1));
listTemp.sort();
listEx3.extend(listTemp);
listEx3.extend(listLead);
del listTemp[:]

for i in range(1, 20000):
    listTemp.append(randint(valueLead + 1, 1000000));
listTemp.sort();
listEx3.extend(listTemp);
print('int largeRan2[] = {');
print(listEx3);
print('};');


