#include<bits/stdc++.h>
#include<string>
using namespace std;

int main()
{
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin );
    freopen("output.txt","w",stdout );
    #endif
    string pat,text;
    cin>>text;
    cin>>pat;
    int n = pat.length();
    int lps[n]={0};
    int i=1, j=0;
    while(i<n)
    {
        if(pat[i]==pat[j])
        {
            lps[i]=j+1;
            i++;
            j++;
        }
        else
        {
            if(j>0)
                j=lps[j-1];
            else
            {
                lps[i]=0;
                i++;
            }
        }
    }

     i=0, j=0;
    while(i<text.length())
    {
        if(text[i]==pat[j])
        {
            i++;
            j++;
        }
            
        else
        
            if(j>0)
                j=lps[j-1];
            else
                i=i+1;


        if(j==n)
            {
                j=lps[j-1];
                cout<<i-n<<endl;
                
            }
        
    }

    return 0;
}
