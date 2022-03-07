#include<iostream>
#include<map>
#include<fstream>
#include<algorithm>
#include<list>
#include<string>

using namespace std;

int main(int argc, const char * argv[]){
    const int MAX = 100000; // arbtirary number to max 
    const int BUCKETMAX = 10; // max num of buckets

    int numElem = 0; // counter

    string str1[MAX];

    ifstream input;
    input.open(argv[1]);

    if(input.fail()){ // file checking
        cout << "ERROR: FILE " << argv[1] << " COULD NOT OPEN" << endl;
        return 1; 
    }

    while(input >> str1[numElem]){ // creating a local array from file
        numElem++;
    }
    input.close();

    char letters[MAX];
    int alphaSize = 26; // Size of alphabet
    bool createdBucket = false;

    int _end = 0, begin = 0, end = 0;

    for(int i = 0; i < alphaSize; i++) { // loads the array with letters 
        letters[i] = i + 'A';
    }

    map<int, list <string> > bucket;
    
    for(int i = 0; i < numElem; i++) {
        char select = str1[i].at(0);
        for(int j = 0; j < alphaSize; j++) {
            if(select == letters[j]){
                if(bucket[j].size() >= BUCKETMAX){
                    begin = j;
                    for(int x = j; x < alphaSize; x++) {
                        if(select != letters[x]){
                            if(bucket[x-1].size() >= BUCKETMAX) {
                                end = x;
                                _end = x;
                                ++alphaSize;
                                createdBucket = true;

                                break;

                            } else {
                                end = x -1;
                                _end = x - 1;
                                break;
                            }     
                        }
                    }
                    if(createdBucket) {
                        createdBucket = false;
                        for(int z = alphaSize; z >= _end; z--){
                            letters[z+1] = letters[z];
                        }
                    }
                    bucket[_end].push_back(str1[i]);

                    int numBuckets = _end - begin +1;
                    int numItems = 2*numBuckets;

                    string *sorted = new string[numItems];
                    
                    int outCount = 0;
                    for(int i = 0; i < numBuckets; i++){
                        for(int j = 0; j < 2; j++){
                            if(bucket[begin + i].size() == 0){ break; }
                        }
                        sorted[outCount] = bucket[begin + i].back();
                        ++outCount;
                        bucket[begin + i].pop_back();
                    }
                
                    sort(sorted, sorted + outCount);

                    int inCount = 0;
                    for(int h = 0; h < numBuckets; h++){
                        for(int i = 0; i < 2; i ++){
                            bucket[begin + h].push_back(sorted[inCount]);
                            ++inCount;
                            if(outCount == inCount) { break; }
                        }
                    }
                    break;
                } else {
                    bucket[j].push_back(str1[i]);
                    bucket[j].sort();
                    
                    break;
                }
            }
        }
    }
    ofstream outfile;
	outfile.open("output.txt"); // creates or opens the output.txt file

	int counter = 0;
	for (int i = 0; i < alphaSize; i++){
		for (int j = 0; j < BUCKETMAX; j++){
			if (bucket[begin + i].size() == 0){
				break;
			}
			outfile<<bucket[begin + i].back()<<" ";
			++counter;
			bucket[begin + i].pop_back();
		}
	}	
	outfile << "\r\n";
	outfile.close();
}


