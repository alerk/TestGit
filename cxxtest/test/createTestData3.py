from random import randint

# medium 1: no pit
listMedium1 = [];
for i in range(1, 99):
    listMedium1.append(randint(-1000000, 1000000));
listMedium1.sort();
print('int listMedium1[] = {');
print(listMedium1);
print('};');

# medium 2: 1 pit
listMedium2 = [];
listUp = [];
listDown = [];

for i in range(1, randint(40, 49)):
    listUp.append(randint(-1000000, 1000000));
listUp.sort();
listMedium2.extend(listUp);

for i in range(1, randint(40, 49)):
    listDown.append(randint(-1000000, 1000000));
listMedium2.extend(listDown);

for i in range(1, randint(40, 49)):
    listUp.append(randint(-1000000, 1000000));
listUp.sort();
listMedium2.extend(listUp);

print('int listMedium2[] = {');
print(listMedium2);
print('};');

# large pit 1
listLarge1 = [];
listUp = [];
listDown = [];

for i in range(1, randint(4000, 4900)):
    listUp.append(randint(-1000000, 1000000));
listUp.sort();
listLarge1.extend(listUp);

for i in range(1, randint(4000, 4900)):
    listDown.append(randint(-1000000, 1000000));
listLarge1.extend(listDown);

for i in range(1, randint(4000, 4900)):
    listUp.append(randint(-1000000, 1000000));
listUp.sort();
listLarge1.extend(listUp);

print('int listLarge1[] = {');
print(listLarge1);
print('};');

# large pit 2
listLarge2 = [];
listUp = [];
listDown = [];

for i in range(1, randint(4000, 4900)):
    listUp.append(randint(-1000000, 1000000));
listUp.sort();
listLarge2.extend(listUp);

for i in range(1, randint(4000, 4900)):
    listDown.append(randint(-1000000, 1000000));
listLarge2.extend(listDown);

for i in range(1, randint(4000, 4900)):
    listUp.append(randint(-1000000, 1000000));
listUp.sort();
listLarge2.extend(listUp);

print('int listLarge2[] = {');
print(listLarge2);
print('};');

# big pit 1
listBig1 = [];
listUp = [];
listDown = [];

for i in range(1, randint(40000, 49900)):
    listUp.append(randint(-1000000, 1000000));
listUp.sort();
listBig1.extend(listUp);

for i in range(1, randint(40000, 49900)):
    listDown.append(randint(-1000000, 1000000));
listBig1.extend(listDown);

for i in range(1, randint(40000, 49900)):
    listUp.append(randint(-1000000, 1000000));
listUp.sort();
listBig1.extend(listUp);

print('int listBig1[] = {');
print(listBig1);
print('};');

# big pit 2
listBig2 = [];
listUp = [];
listDown = [];

for i in range(1, randint(40000, 49900)):
    listUp.append(randint(-1000000, 1000000));
listUp.sort();
listBig2.extend(listUp);

for i in range(1, randint(40000, 49900)):
    listDown.append(randint(-1000000, 1000000));
listBig2.extend(listDown);

for i in range(1, randint(40000, 49900)):
    listUp.append(randint(-1000000, 1000000));
listUp.sort();
listBig2.extend(listUp);

print('int listBig2[] = {');
print(listBig2);
print('};');

# big pit 3_1
listBig31 = [];
listUp = [];
listDown = [];

for i in range(1, 1000000):
    listBig31.append(randint(-1000000, 1000000));

print('int listBig31[] = {');
print(listBig31);
print('};');

# big pit 3_2
listBig32 = [];
listUp = [];
listDown = [];

for i in range(1, 1000000):
    listBig32.append(randint(-1000000, 1000000));

print('int listBig32[] = {');
print(listBig32);
print('};');