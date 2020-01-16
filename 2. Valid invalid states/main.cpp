#include <iostream>

using namespace std;

#define MAX_LEVEL_NUMBER 10
//utility function for nCr operation
long int selection(int n, int r){
    int c = r;
    long int temp = 1;
    if(n>=r){
        for(;c>0;c--){
            temp*=n--;
        }
        while(r){
            temp/=r--;
        }
        return temp;
    }
    else{
        cout<<"\nInvalid input for selection! ";
        return 0;
    }
}

//utility function for nPr operation
long int arrangement(int n, int r){
    long int temp = 1;
    if(n>=r){
        for(;r>0;r--){
            temp*=n--;
        }
        return temp;
    }
    else{
        cout<<"\nInvalid input for arrangement! ";
        return 0;
    }
}

//utility function to print the move arrays, branching and all possible states
void print_1(int c[],int u[], int bL[],long int NL[]){
    cout<<"\nComputer Moves: "<<endl;
    for(int i = 0;i<MAX_LEVEL_NUMBER;i++){
        cout<<c[i]<<"\t";
    }
    cout<<"\nUser Moves: "<<endl;
    for(int i = 0;i<MAX_LEVEL_NUMBER;i++){
        cout<<u[i]<<"\t";
    }
    cout<<"\nNL: "<<endl;
    for(int i = 0;i<MAX_LEVEL_NUMBER;i++){
        cout<<NL[i]<<"\t";
    }
    cout<<"\nBL: "<<endl;
    for(int i = 0;i<MAX_LEVEL_NUMBER;i++){
        cout<<bL[i]<<"\t";
    }
}

void print_2(long int NVS[],long int NIS[]){
    for(int i = 0; i<MAX_LEVEL_NUMBER;i++){
        cout<<"Current level: "<<i<<endl;
        cout<<"Valid states: "<<NVS[i]<<endl;
        cout<<"Invalid states: "<<NIS[i]<<endl;
        cout<<"\n";
    }
}

int main()
{
    /**
    c = array that stores number of computer moves at each level
    u = array that stores number of user moves at each level
    bL = array that stores number of branches from the previous level to reach the current level
    **/
    int c[MAX_LEVEL_NUMBER],u[MAX_LEVEL_NUMBER],bL[MAX_LEVEL_NUMBER];
    long int NL[MAX_LEVEL_NUMBER],NVS[MAX_LEVEL_NUMBER],NIS[MAX_LEVEL_NUMBER];
    c[0] = u[0] = bL[0] = 0;
    NL[0] = 1;
    int temp = 9;
    while(temp){
        /**
        since temp stores the branching of the previous level,hence
        when it is odd computer played in current level
        and when it is even the user played in current level
        the index is basically a logic to generate the right index number
        **/
        if(temp%2==0){
            c[MAX_LEVEL_NUMBER-temp] = c[MAX_LEVEL_NUMBER-temp-1];
            u[MAX_LEVEL_NUMBER-temp] = u[MAX_LEVEL_NUMBER-temp-1]+1;
        }
        else{
            c[MAX_LEVEL_NUMBER-temp] = c[MAX_LEVEL_NUMBER-temp-1]+1;
            u[MAX_LEVEL_NUMBER-temp] = c[MAX_LEVEL_NUMBER-temp-1];
        }
        bL[MAX_LEVEL_NUMBER-temp] = temp;
        NL[MAX_LEVEL_NUMBER-temp] = NL[MAX_LEVEL_NUMBER-temp-1]*temp;
        temp--;
    }
    /**
    print_1(c,u,bL,NL);
    **/
    for(int i = 0;i<MAX_LEVEL_NUMBER;i++){
        if(i<6){
            NVS[i] = NL[i];
            NIS[i] = 0;
        }
        else{
            long int level_invalid_states,child_invalid_states,intersection;
            child_invalid_states = 0;
            intersection = 0;
            level_invalid_states = (8*((i>=8)?selection(3,2):1))*arrangement(3,3)*selection(6,(i-3))*arrangement(i-3,i-3);
            if(i>6){
                child_invalid_states = NIS[i-1]*bL[i];
                int c1,u1;
                c1 = c[i];
                u1 = u[i];
                if(i%2==0)
                    u1--;
                else
                    c1--;
                intersection = (i>7?selection(c1,3):1)*(i>8?selection(u1,3):1)*2*selection(3,2)*arrangement(3,3)*arrangement(3,3)*selection(3,i-6)*arrangement(i-6,i-6);
            }
            NIS[i] = level_invalid_states + child_invalid_states - intersection;
            NVS[i] = NL[i] - NIS[i];
        }
    }
    print_2(NVS,NIS);
    return 0;
}
