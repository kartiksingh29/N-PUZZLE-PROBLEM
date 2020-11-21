#include <bits/stdc++.h>
#define fastIO ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define ll long long
#define mx LLONG_MAX
#define mn LLONG_MIN
#define pii pair<int,int>
#define vi vector<int>
#define vll vector< long long >
#define pb push_back
#define pop pop_back
#define all(x) (x).begin(), (x).end()
#define F first
#define S second
#define f(i,a,n) for( i = a ; i < n ; i++)
using namespace std;
vector<vector<int> >s,g,ans,sr;
int r,r1,c,c1,n, currheuristic = 0,heuristic;
bool reached_goalstate()
{
    int i,j,flag = 1;
    f(i,0,n)
    {
        f(j,0,n)
        {
            if(s[i][j]!=g[i][j])
                flag = 0;
        }
    }
    if(flag)
        return true;
    return false;
}
void display()
{
    int i,j;
    f(i,0,n) 
    {
        f(j,0,n)
            cout<<setw(2)<<setfill('0')<<s[i][j]<<"   "; 
        
    cout<<endl<<endl;
    }

}
int getheuristic()
{
    int i,j,heuristicvalue = 0;
    f(i,0,n)
        {
            f(j,0,n)
            {
                if(s[i][j] != g[i][j] )
                    heuristicvalue++;
            }
        }
    return heuristicvalue;
}

bool Check_Neighbour()
{

    int hvalue = currheuristic,i,j,choicecode = 0; 

    if(c< n-1)
    {
        
        swap(s[r][c], s[r][c+1]);
        int heuristicvalue =getheuristic();
        
        if(heuristicvalue < hvalue){
            choicecode = 1;
            hvalue = heuristicvalue;
        }
        swap(s[r][c], s[r][c+1]);

    }

    if(r< n-1)
    {
        swap(s[r][c], s[r+1][c]);
        int heuristicvalue = getheuristic();

        if(heuristicvalue < hvalue){
            choicecode = 2;
            hvalue = heuristicvalue;
        }
        swap(s[r][c], s[r+1][c]);     
    }

    if(c> 0)
    {
        swap(s[r][c], s[r][c-1]);
        int heuristicvalue = getheuristic();
        
        if(heuristicvalue < hvalue){
            choicecode = 3;
            hvalue = heuristicvalue;
        }
        swap(s[r][c], s[r][c-1]);  
    }

    if(r> 0)
    {
        swap(s[r][c], s[r-1][c]);
        int heuristicvalue = getheuristic();
        
        if(heuristicvalue < hvalue){
            choicecode = 4;
            hvalue = heuristicvalue;
        }
        swap(s[r][c], s[r-1][c]);      
    }

    if(choicecode == 0)
        return false;
    
    else
    {
         currheuristic = hvalue;

        if(choicecode == 1){
            swap(s[r][c], s[r][c+1]);
            c++;

        }

        else if(choicecode == 2){
            swap(s[r][c], s[r+1][c]);
            r++;
        }

        else if(choicecode == 3){
            swap(s[r][c], s[r][c-1]);
            c--;
        }

        else{
            swap(s[r][c], s[r-1][c]);
            r--;
        }
        return true;
    }
    
}
void Simple_Hill_Climbing()
{
    while(Check_Neighbour())
        continue;
}
void Random_Restart()
{
    int i,j,k,optimheuristic = INT_MAX;
    currheuristic = heuristic;
    Simple_Hill_Climbing();
    
    if(currheuristic < optimheuristic)
    {
        optimheuristic = currheuristic;
        ans = s;
    }

    f(i,0,200000)
    {
        vi v(n*n,0);
        f(j,0,n)
        {
            f(k,0,n)
            {
                bool condition  = true;   
                while(condition)
                {
                    int val = rand()%(n*n);
                    if(v[val] == 0)
                    {
                        v[val]++;
                        condition  = false;
                        s[j][k] = val;
                        if(val == 0)
                        {
                            r = j;
                            c = k;
                        }
                    }
                }
            }
        }
        
        currheuristic = getheuristic();
      
        Simple_Hill_Climbing();
        
        if(currheuristic < optimheuristic)
        {
            optimheuristic = currheuristic;
            ans = s;
        }

    }

    s = ans; 
    if(reached_goalstate())
        cout<<"This is best state the random restart algorithm found!,We have reached goal state "<<endl<<endl;
    else
        cout<<"This is best state the random restart algorithm found!,but Unfortunately this is not our goal state with heuristic value : "<<optimheuristic<<endl<<endl;
    
    f(i,0,n){f(j,0,n) cout<<setw(2)<<setfill('0')<<ans[i][j]<<"   "; cout<<endl<<endl;}


}
int getRandomNeighbour()
{
    bool condition = true;

    while(condition)
    {
        int value = 1+(rand()%4);
        if(value == 1 && r>0)
            return value;
        if(value == 2 && r<n-1)
            return value;
        if(value == 3 && c>0)
            return value;
        if(value == 4 && c<n-1)
            return value;
    }
}

vector<vector<int> > Simulate_Annealing()
{
    int temperature = 200000;
    while(temperature>0)
    {
        int choicecode = getRandomNeighbour();
        //cout<<choicecode<<endl;
        int prev_h = getheuristic();
        vector<vector<int> >stemp(n); stemp = s;
        if(choicecode == 1)
        {
            swap(s[r][c] ,s[r-1][c]);
            int h = getheuristic();
            if(h == 0)
                return s;
            if(prev_h - h > 0 )
                r--;
            else
            {
                double determiner = ((double)rand()/(double)RAND_MAX);
                double probability = exp(((double)(prev_h-h))/(double)temperature);
                if(determiner<=probability)
                    r--;
                else
                    s = stemp; 
            }
        }
        else if(choicecode == 2)
        {
            swap(s[r][c] ,s[r+1][c]);
            int h = getheuristic();
            if(h == 0)
                return s;
            if(prev_h - h > 0 )
                r++;
            else
            {
                double determiner = ((double)rand()/(double)RAND_MAX);
                double probability = exp(((double)(prev_h-h))/(double)temperature);
                if(determiner<=probability)
                    r++;
                else
                    s = stemp; 
            }
        }
        else if(choicecode == 3)
        {
            swap(s[r][c] ,s[r][c-1]);
            int h = getheuristic();
            if(h == 0)
                return s;
            if(prev_h - h > 0 )
                c--;
            else
            {
                double determiner = ((double)rand()/(double)RAND_MAX);
                double probability = exp(((double)(prev_h-h))/(double)temperature);
                if(determiner<=probability)
                    c--;
                else
                    s = stemp; 
            }
        }
        else
        {
            swap(s[r][c] ,s[r][c+1]);
            int h = getheuristic();
            if(h == 0)
                return s;
            if(prev_h - h > 0 )
                c++;
            else
            {
                double determiner = ((double)rand()/(double)RAND_MAX);
                double probability = exp(((double)(prev_h-h))/(double)temperature);
                if(determiner<=probability)
                    c++;
                else
                    s = stemp; 
            }
        }
        temperature = temperature - (double)1;
        //display(); cout<<endl<<endl;
    }
    return s ;
}

int main()
{
    fastIO ;
    int TESTS = 1; 
    //cin>>TESTS;
    while(TESTS--)
    {
        srand(time(0));
        int i,j;
        cout<<" Please enter the size of the puzzle you want to create " <<endl<<endl ;
        cin>>n; 
        s.clear(), g.clear() ,sr.clear() , ans.clear() ;
        s.resize(n) , g.resize(n),sr.resize(n),ans.resize(n);
    
        vi v(n*n);

        f(i,0,n)
        {
            f(j,0,n){
                bool condition  = true;   
                while(condition)
                {
                    int value = rand()%(n*n);
                    if(v[value] == 0)
                    {
                        v[value]++;
                        condition  = false;
                        s[i].pb(value);
                        if(value == 0)
                        {
                            r = i;
                            c = j;
                        }
                    }
                }
            }
        }
        r1= r, c1 = c;
        sr = s;
        cout<<"This is our start state "<<endl<<endl<<endl;
        display(); cout<<endl<<endl;

       // v.clear(); v.resize(n*n);
       int value = 0 ;

        f(i,0,n)
        {
            f(j,0,n)
            {
                      g[i].pb(value++) ;
            }            
        }
        

        cout<<"This is our goal state "<<endl<<endl<<endl;

        f(i,0,n) {f(j,0,n) cout<<setw(2)<<setfill('0')<<g[i][j]<<"   "; cout<<endl<<endl;}


        heuristic = getheuristic();
        cout <<" The initial misplaced cells/heuristic is " << heuristic << endl << endl ;
        cout<<"Now, here we can perform operation with the cell containing zero in order to achieve goal state "<<endl<<endl;

        r = r1 , c = c1;

        cout<<"Simple Hill Climbing starts :"<<endl<<endl;
        currheuristic = heuristic;
        Simple_Hill_Climbing();
        cout<<"This is optimized state which we've recieved through simple Hill Climbing "<<endl<<endl;
        display();
        if(reached_goalstate())
            cout<<"this is our goal state"<<endl<<endl;
        else
            cout<<"Unfortunately this is not our goal state, but is a optimized state with heuristic value : "<<getheuristic()<<endl<<endl;
        r = r1 , c = c1;


        s = sr;
    
        cout<<"Hill Climbing Algorithm with Random restart proceeds here :"<<endl<<endl;
        Random_Restart();

        s = sr;
        r = r1 , c = c1;
        cout<< "Hill Climbing Algorithm with simulated annealing starts here :"<<endl<<endl;
        s = Simulate_Annealing();
        display();
        if(reached_goalstate())
            cout<<"It is most optimized state of stimulated annealing algorithm, we have reached goal state"<<endl;
        else
            cout<<"It is most optimized state of stimulated annealing algorithm with heuristic value : "<<getheuristic()<<" , but we have not reached goal state"<<endl;
    } 
}