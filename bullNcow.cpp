#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <chrono>

using namespace std;
using namespace std::chrono;

//rand number creation and storing
vector<int> createRand(const int& length)
{
    vector<int> numNOW; //representing the current random number

    int numero; // representing random number in individual

    bool OGnumb; //bool to check whether it's an original number or duplicated

    for(int i=0; i<length; i++)
    {
        while(true) //forever loop until broken with break or new condt.
        {
            OGnumb=true;
            numero = rand()%10; //rand number btw 1-9 cant allow double digit creation
            for(unsigned int j=0; j < numNOW.size(); j++)
            {
                if(numero == numNOW[j]) //if the numbers equal each other it wont be
                {                       //pushed into vector, hints false
                    OGnumb = false;
                    break;
                }
            }
            if(OGnumb == true)
            {
                numNOW.push_back(numero);
                break;
            }
        }

    }
    return numNOW;
}


void match(const vector<int>& numNOW, const vector<int>& userVect, vector<int>& randVect){

    //checking bull and cow count
    for(int i = 0; i < userVect.size(); i++){
        for(int j = 0; j < numNOW.size(); j++){
            if(userVect[i] == numNOW[j]){
                if(i == j)
                    randVect[0]++;//looks at first elem in vector, if == ,exact match
                else
                    randVect[1]++;//doesnt directly match elem but exists in int
                break;
            }
        }
    }
    cout << "bulls = " << randVect[0] << " and cows = " << randVect[1] << endl;
}
void OGguess(vector<int>& userVect){
    int number;
    cout << "Enter a 4 digit number(unique digits): ";
    cin >> number;
    for(int i = 1000; i > 0; i = i / 10)
    {
        userVect.push_back(number / i);
        number -= (number / i) * i;
    }
}

int main()
{

    srand(time(0));//time will be used for measuring how long guess takes
    steady_clock::time_point begin, end;
    long timing;


    vector<int> randVect{0,0};//keeps bull to cow ratio
    vector<int> numNOW = createRand(4); //A rand 4 digit numb
    int count = 0; //guess count

    begin = steady_clock::now();
    while(randVect[0] !=4) //do this while there isn't 4 equal elements
    {
        int numero; // random number guess
        vector<int> userVect; //users attempt at rand 4 digits
        count++;
        randVect[0] = 0;
        randVect[1] = 0; //start with bull cow at 0
        OGguess(userVect);
        match(numNOW, userVect, randVect);
    }
    end = steady_clock::now();
    timing = duration_cast<std::chrono::milliseconds>(end-begin).count();
    cout << "You guessed it in " << count << " tries, taking "<< timing/1000/60<<" minutes and " <<timing/1000<<" seconds ";

    return 0;
}