from math import comb

combinationTable = []
alreadyDone = set()
for i in range(256):
    binaryString = (bin(i)[2:])[::-1]
    combinations = []
    for j in range(8):
        if j >= len(binaryString):
            break
        if binaryString[j] == '1':
            combinations.append(j)

    combinationTable.append(combinations[::-1])

sortedCombinationTable = sorted(combinationTable, key=lambda x: len(x))

beta = 1
for rowi in range(2, len(sortedCombinationTable)):
    row = sortedCombinationTable[rowi]
    if len(row) == 0 or row[0] == 9:
        continue
    if len(row) > beta:
        beta = len(row)
        sortedCombinationTable.insert(rowi, [9])

rTable = []
beta = 1
i = 0
for row in sortedCombinationTable:
    if len(row) == 0:
        continue
    if len(row) > beta:
        beta = len(row)
        rTable.append(i)
    i += len(row)

resultAsString = str(sortedCombinationTable)
resultAsString = resultAsString.replace('[', '')
# resultAsString = resultAsString.replace(',', '')
resultAsString = resultAsString.replace(']', '')
# resultAsString = resultAsString.replace('\n ', '\n')
# resultAsString = resultAsString.replace(' ', ', ')

print("RESULT AS STRING")
print(resultAsString)
print("RESULT AS STRING LENGTH")
print(len(sortedCombinationTable))
print("rTable")
print(rTable)

singleArrayCombinationTable = []
for row in sortedCombinationTable:
    for element in row:
        singleArrayCombinationTable.append(element)

print("Testing")
for i in range(len(rTable)):
    r = rTable[i]
    elements = []
    for j in range(i+1):
        elements.append(singleArrayCombinationTable[r+j])
    print(elements)

singleArrayCombinationLen = []
for n in range(1,9):
    for r in range(1,n+1):
        singleArrayCombinationLen.append(comb(n,r))

print(singleArrayCombinationLen)
