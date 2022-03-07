from collections import deque
CAPACITY = 50

class HashTable:
    def __init__(self):
        self.size = CAPACITY  # initialize size
        self.ht = self.create_buckets()  # bucket maker

    def create_buckets(self):
        return [deque() for _ in range(self.size)] 
		
	#def hash(self, key):
		#hashsum = 0
		#for idx, c in enumerate(key):
			#hashsum += (idx + len(key)) ** ord(c)
			#hashsum = hashsum % self.size
		#return hashsum
		
    def put(self, key, value):
        elem_ = self.get(key)  #

        idx = 0
        for i in range(len(key)):  # hashing reference from text
            idx += i   
        idx %= self.size   # apply the division method
        item = [key, value]  # object to insert

        hashsum = self.ht[idx] 
        if elem_ is "none":
            hashsum.append(item)
        else:
            for item in hashsum:  # else find the key in our bucket and update its value
                if item[0] == key:
                    item[1] = value

    def get(self, key):  # adapted from the CLRS pseudocode
        idx = 0
        for i in range(len(key)):  # hashing reference from text
            idx += i  
        idx %= self.size
        hashsum = self.ht[idx]

        for item in hashsum: 
            key_ = item[0]   
            val_ = item[1]
            if key_ == key:  
                return val_
        return "none"   # otherwise, it is not there so we return nul or "none" in this case

ht_ = HashTable()

file = open("input.txt", 'r')
output = open("output.txt", "w+")

for fifo in file:
    fifo = fifo.split()
    if fifo[0] == "put":
        ht_.put(fifo[1], fifo[2])  # our insert command
    elif fifo[0] == "get":
        output.write(ht_.get(fifo[1]) + "\n")  # formatting to make it look nice

output.close()