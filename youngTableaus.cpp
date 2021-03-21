#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<fstream>
#include<sstream>

using namespace std;
void insert_new_element(int m,int n,int temp);
int Extract_min(int m,int n);
void print(int m,int n);
int Young_tableaus[10000][10000];
void Clear(){
    for(int i=0;i<10000;++i){
        for(int j=0;j<10000;++j){
            Young_tableaus[i][j]=INT_MAX;
        }
    }
}
fstream file,file2;
int main(){
    file.open("input.txt",ios::in);
    file2.open("output.txt",ios::out);
    int k;
    file>>k;
    while(k--){
        Clear();
        int c;
        file>>c;
        stringstream ss;
        string s;
        if(c==1){
            getline(file,s);  /*clean buffer*/
            getline(file,s);
            ss<<s;
            int val;
            vector<int> vec;
            while(ss>>val){
                vec.push_back(val);
            }
            file2<<"Insert ";
            for(int i=0;i<vec.size();++i){
                file2<<vec[i]<<" ";
            }
            file2<<endl;
            ss.clear();
            s.clear();
            int m=0,n=0;
            char ch,pre_ch;
            while(1){
                file.get(ch);
                if(ch>=48&&ch<=57){
                    s+=ch;
                }
                if(ch=='x'){
                    n++;
                }
                if((ch==' '||ch=='\n')&&(pre_ch>=48&&pre_ch<=57)){
                    ss<<s;
                    ss>>val;
                    vec.push_back(val);
                    s.clear();
                    ss.clear();
                    n++;
                }
                if(ch=='\n'){
                    m++;
                }
                if(ch=='\n'&&pre_ch=='\n'){
                    m--;
                    break;
                }
                pre_ch=ch;
            }
            n/=m;
            for(int i=0;i<vec.size();++i){
                insert_new_element(m,n,vec[i]);
            }
            print(m,n);
            file2<<endl;
        }else{
            getline(file,s); /*clean buffer*/
            vector<int> vec;
            int m=0,n=0;
            int val;
            char ch,pre_ch;
            while(1){
                file.get(ch);
                if(ch>=48&&ch<=57){
                    s+=ch;
                }
                if(ch=='x'){
                    n++;
                }
                if((ch==' '||ch=='\n')&&(pre_ch>=48&&pre_ch<=57)){
                    ss<<s;
                    ss>>val;
                    vec.push_back(val);
                    s.clear();
                    ss.clear();
                    n++;
                }
                if(ch=='\n'){
                    m++;
                }
                if(ch=='\n'&&pre_ch=='\n'){
                    m--;
                    break;
                }
                pre_ch=ch;
            }
            n/=m;
            for(int i=0;i<vec.size();++i){
                insert_new_element(m,n,vec[i]);
            }
            int e=Extract_min(0,0);
            file2<<"Extract-min "<<e<<endl;
            print(m,n);
            file2<<endl;
        }
    }
    file.close();
return 0;
}

void insert_new_element(int m,int n,int temp){
    int i=m-1;
    int j=n-1;
    Young_tableaus[i][j]=temp;
    while(Young_tableaus[i][j]<Young_tableaus[i][j-1]||Young_tableaus[i][j]<Young_tableaus[i-1][j]){
        if(Young_tableaus[i-1][j]<Young_tableaus[i][j-1]){
            swap(Young_tableaus[i][j],Young_tableaus[i][j-1]);
            j--;
        }else{
            swap(Young_tableaus[i][j],Young_tableaus[i-1][j]);
            i--;
        }
        if(i==0||j==0){
            break;
        }
    }
    if(i==0&&j!=0){
        while(Young_tableaus[i][j-1]>Young_tableaus[i][j]){
            swap(Young_tableaus[i][j-1],Young_tableaus[i][j]);
            j--;
            if(j==0){
                break;
            }
        }
    }
    if(i!=0&&j==0){
        while(Young_tableaus[i-1][j]>Young_tableaus[i][j]){
            swap(Young_tableaus[i-1][j],Young_tableaus[i][j]);
            i--;
            if(i==0){
                break;
            }
        }
    }
}
int Extract_min(int m,int n){
    int Min=Young_tableaus[m][n];
    if(Young_tableaus[m+1][n]==INT_MAX&&Young_tableaus[m][n+1]==INT_MAX){
        Young_tableaus[m][n]=INT_MAX;
        return Min;
    }
    if(Young_tableaus[m+1][n]>Young_tableaus[m][n+1]){
        Young_tableaus[m][n]=Young_tableaus[m][n+1];
        Young_tableaus[m][n+1]=Min;
        return Extract_min(m,n+1);
    }else{
        Young_tableaus[m][n]=Young_tableaus[m+1][n];
        Young_tableaus[m+1][n]=Min;
        return Extract_min(m+1,n);
    }
}

void print(int m,int n){
    for(int i=0;i<m;++i){
        for(int j=0;j<n;++j){
            if(Young_tableaus[i][j]==INT_MAX){
                file2<<"x ";
            }else{
                file2<<Young_tableaus[i][j]<<" ";
            }
        }
        file2<<endl;
    }
}



