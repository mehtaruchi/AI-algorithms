#include <iostream>
#include <cstdlib>
#include <ctime>
#define LENGTH 4
using namespace std;

int score(int arr[], int fin[]){

    int sc = 0;
    for(int i=0;i<LENGTH;i++){
        if(arr[i] == fin[i]) sc++;
    }
    return sc;
}

/**Function to give index of bit to be changed **/
int changeOne(){

    srand(time(0));
    return rand()%4;
}

int main()
{
    int arr[LENGTH], fin[LENGTH];
    cout<<"Enter initial state of length "<<LENGTH<<endl;
        for(int i=0;i<LENGTH;i++) cin>>arr[i];
    cout<<"Enter goal state"<<endl;
        for(int i=0;i<LENGTH;i++) cin>>fin[i];

    /**Initial score calculated which gives difference between final state and initial state**/
    int comp = score(arr,fin);

    /**To calculate the number of time algorithm ran**/
    int times=0;

    /**If goal and in initial state are the same**/
    if(comp == LENGTH) cout<<"Both strings are similar"<<endl;


    else{

        while(comp != LENGTH){


            /**generate a random number to decide which position bit to change**/
            int i = changeOne();

            /**array storing intermediate states **/

            int temp[LENGTH];
            for(int j=0;j<LENGTH;j++){

                if(j==i){

                    if(arr[j] == 0) temp[j] = 1;
                    else temp[j] = 0;
                }
                else temp[j] = arr[j];
            }

            /**difference in score between intermediate and goal state**/
            int t_sc = score(temp,fin);

            if(t_sc > comp){
                    times++;
                for(int j=0;j<LENGTH;j++){
                    arr[j] = temp[j];
                    cout<<arr[j]<<" ";
                } cout<<"is the next state that is considered "<<endl;

                comp = t_sc;
            }
        }
    }

        cout<<"Number of times the algorithm ran is "<<times;
}
