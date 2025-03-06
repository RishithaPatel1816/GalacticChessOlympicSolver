#include <bits/stdc++.h>
using namespace std;

class Comparator{
    private:
        bool incg;          //to make note whether we have to find increading and decreasing
    public:
        Comparator(string s){
            if(s=="ascending"){incg=true;}
            else if(s=="descending"){incg=false;}
        }
        bool operator()(int a,int b){   //Comparator functors 
            if(incg){return a<b;}
            return a>b;
        }
        bool getincg(){
            if(incg){return true;}
            return false;
        }
};

class Matrix{
    private:
        vector<int> arr;
        vector<int> copyarr;    //for inversions so thay original won't we replaced
        long long int n;        //to know number of rows
    public:
        Matrix(){
            //do nothing
        }
        void takeinput(){
            cin>>n;
            for(int i=0;i<n*n;i++){
                    int x;
                    cin>>x;
                    arr.push_back(x);
            }
            //taking the matrix as array so that it will be easy to handle
        }
        int medianOfAtMostFive(int low,int high) {
            int size=high-low+1;            //we will find the median based on size
            if(size==1)return arr[low];
            if(size==2)return min(arr[low], arr[high]);  // Median of two is the smaller one
            int a=arr[low],b=arr[low+1],c=arr[low+2];
            if(size==3) {
                if(a>b)swap(a,b);
                if (b>c)swap(b,c);
                if(a>b)swap(a,b);
                return b;
            }
            int d=arr[low+3];
            if(size==4) {
                if(a>b)swap(a,b);
                if(c>d)swap(c,d);
                if(a>c)swap(a,c),swap(b,d);
                return max(a, min(b, c)); 
            }
            int e=arr[low+4];
            return medianOfFive(a,b,c,d,e);
        }
        int medianOfFive(int a, int b, int c, int d, int e) {
            //finds median using optimal number of comparisions
            if (a>b) swap(a,b);
            if (c>d) swap(c,d);
            if (a>c) swap(a,c), swap(b,d);
            if (e<a) return c;
            if (e>d) return c;
            if (e<b) return b;
            if (e>c) return c;
            return e;
        }  
        void sortrows(Comparator c){
            //find sorted rows of size n
            for(int i=0;i<n*n;i=i+n){
                QuickSort(i,i+n-1,c);
            }
        }
        int QuickSelect(vector<int> & arr,int low,int high,int k,const Comparator & c){
            //BASE CASE 
            if(high-low+1<10){
                sort(arr.begin()+low,arr.begin()+high+1);
                //SORT AND SEND THE MIDDLE ELEMENT
                return arr[low+k];
            }
            //RECURSION
            vector<int> medians;
            for(int i=low;i<=high;i=i+5){
                int h=min(i+4,high);
                medians.push_back(medianOfAtMostFive(i,h));
            }
            int mom=QuickSelect(medians,0,medians.size()-1,(medians.size()-1)/2,c);
            //we got mom 
            int r=partition(low,high,mom,c);
            //PARTITION IT INTO 2 PARTS ONE WITH LESS VAL AND ONE WITH MORE VAL
            if(k>r-low){
                //we have to search in bigger half
                return QuickSelect(arr,r+1,high,k-(r-low+1),c);
            }
            else if(k<r-low){
                //SEARCH IN LOWER HALF
                return QuickSelect(arr,low,r-1,k,c);
            }
            else{
                //FOUND THE MID ONE SO RETURN IT..YAY!
                return arr[r];
            }
            return -1;   
        }
        int partition(int low,int high,int mom,Comparator c){
            int pivot;
            for(pivot=low;pivot<=high;pivot++){
                if(arr[pivot]==mom){
                    break;
                    //get that pivot
                }
            }
            //FIND THE INDEX OF PIVOT
            swap(arr[pivot],arr[high]);
            int i=low;
            for(int j=low;j<high;j++){
                if(c(arr[j],arr[high])){
                    //a is less that tha number
                    swap(arr[i],arr[j]);
                    i++;
                }
            }
            swap(arr[i],arr[high]);
            return i;
            //RETURN AFTER DIVIDING INTO 2 PARTS
        }
        void QuickSort(int low,int high,Comparator c){
            if(low<high){
                int pivot=QuickSelect(arr,low,high,(high-low)/2,c);
                int pivotIndex=partition(low,high,pivot,c);
                QuickSort(low,pivotIndex-1,c);       //sort left array
                QuickSort(pivotIndex+1,high,c);      //sort right array
            }
        }
        void countInversions(){
            copyarr=arr;
            cout<<Inversions(0,n*n-1)<<endl;
            return;
        }
        long long Inversions(int low,int high){
            if(high-low+1<=3){
                long long c=0;
                for(int i=low;i<=high;i++){
                    for(int j=i+1;j<=high;j++){
                        if(copyarr[i]>copyarr[j]){
                            c++;
                        }
                    }
                }
                sort(copyarr.begin()+low,copyarr.begin()+high+1);
                return c;
            }
            int mid=low+(high-low)/2;
            long long c1=Inversions(low,mid);
            long long c2=Inversions(mid+1,high);
            long long c3=MergeandCount(low,high,mid);
            return c1+c2+c3;
        }
        long long MergeandCount(int low,int high,int mid){
            long long int x=0;
            int i=low;int j=mid+1;
            vector<int> v1; 
            while(i<=mid && j<=high){
                if(copyarr[i]>copyarr[j]){
                    x=x+(mid-i+1);
                    v1.push_back(copyarr[j]);j++;
                }
                else{
                    v1.push_back(copyarr[i]);i++;
                }
            }
            while(i<=mid){
                v1.push_back(copyarr[i]);i++;
            }
            while(j<=high){
                v1.push_back(copyarr[j]);j++;
            }
            //we will copy them into copyarr
            int it=low;
            j=0;
            while(it<=high){
                copyarr[it]=v1[j];it++;j++;
            }
            return x;
        }
        void display(){
            int x=0;
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    cout<<arr[x]<<" ";x++;
                }
                cout<<endl;
            }
        }
};

//COMPARATORS FOR CLOSEST PAIR OF POINTS
bool comparex(const pair<int,int> & p1,const pair<int,int> & p2){
    if(p1.first==p2.first){return p1.second<p2.second;}
    return p1.first<p2.first;
}

bool comparey(const pair<int,int> & p1,const pair<int,int> & p2){
    if(p1.second==p2.second){return p1.first<p2.first;}
    return p1.second<p2.second;
}

class Pointpairs{
    private:
        vector<pair<int,int>> points;
        vector<pair<int,int>> copy;
        int n;
    public:
        void ClosestPair(){
            //prints the closest point
            //we will first sort them based on x coord
            copy=points;
            sort(points.begin(),points.end(),comparex);
            //idea is we will find the min in 2 of them 
            pair<float,vector<int>> varr=findclosest(0,n-1);
            //we have to print which comes first
            pair<int,int> p1={varr.second[0],varr.second[1]};
            pair<int,int> p2={varr.second[2],varr.second[3]};
            //printing whichever comes first
            for(int i=0;i<copy.size();i++){
                if(copy[i]==p1){
                    cout<<p1.first<<" "<<p1.second<<" "<<p2.first<<" "<<p2.second<<endl;
                    return;
                }
                else if(copy[i]==p2){
                    cout<<p2.first<<" "<<p2.second<<" "<<p1.first<<" "<<p1.second<<endl;
                    return;
                }
            }
        }
        float finddist(int i,int j){
            return sqrt(pow((points[i].first-points[j].first),2)+(pow(points[i].second-points[j].second,2)));
        }
        pair<float,vector<int>> findclosest(int low,int high){
            //base case
            if(high-low+1<=5){
                //brute force
                pair<float,vector<int>> ans;
                ans.first=FLT_MAX;
                ans.second.resize(4);
                for(int i=low;i<=high;i++){
                    for(int j=i+1;j<=high;j++){
                        float x=finddist(i,j);
                        if(x<ans.first){
                            ans.first=x;
                            ans.second[0]=points[i].first;
                            ans.second[1]=points[i].second;
                            ans.second[2]=points[j].first;
                            ans.second[3]=points[j].second;
                        }                        
                    }
                }
                return ans;
            }
            //recursion
            int mid=low+(high-low)/2;
            pair<float,vector<int>> ans1=findclosest(low,mid);
            pair<float,vector<int>> ans2=findclosest(mid+1,high);
            pair<float,vector<int>> curmin=chooseOne(ans1,ans2);
            pair<float,vector<int>> ans3=findbtw(low,high,mid,curmin);  
            return chooseOne(curmin,ans3);
        }
        //choosing the best one if dist are same ret x and same x ret small y
        pair<float,vector<int>> chooseOne(pair<float,vector<int>> ans1,pair<float,vector<int>> ans2){
            if(ans1.first>ans2.first){
                return ans2;
            }
            else if(ans1.first<ans2.first){
                return ans1;
            }
            else{
                if(ans1.second[0]>ans2.second[0]){return ans2;}
                else if(ans1.second[0]<ans2.second[0]){return ans1;}
                else{
                    if(ans1.second[2]<ans2.second[2]){
                        return ans1;
                    }
                    else{return ans2;}
                }
            }
        }
        //find if there are any points across
        pair<float,vector<int>> findbtw(int low,int high,int mid,pair<float,vector<int>> minans){
            vector<pair<int,int>> yarr;
            int x=points[mid].first;
            for(int i=low;i<=high;i++){
                if(abs(points[i].first-x)<=minans.first){
                    yarr.push_back(points[i]);
                }
            }
            pair<float,vector<int>> ans;
            ans.first=FLT_MAX;
            ans.second.resize(4);
            sort(yarr.begin(),yarr.end(),comparey);
            for(int i=0;i<yarr.size();i++){
                int z=yarr.size()-1;
                int upto=min(i+7,z);
                for(int j=i+1;j<=upto;j++){
                    float x= sqrt(pow(yarr[i].first - yarr[j].first, 2) + pow(yarr[i].second - yarr[j].second, 2));     
                    if(x<ans.first){
                        ans.first=x;
                        ans.second[0]=yarr[i].first;
                        ans.second[1]=yarr[i].second;
                        ans.second[2]=yarr[j].first;
                        ans.second[3]=yarr[j].second;
                    }      
                }
            }
            return ans;
        }
        void takeinput(){
            //taking the input
            cin>>n;
            for(int i=0;i<n;i++){
                int x,y;cin>>x>>y;
                points.push_back({x,y});
            }
            ClosestPair();
            return;
        }
};

int main(){
    string s;
    cin>>s;
    Matrix M;
    while(s!="END"){
        if(s=="CREATE_2D"){
            M.takeinput();
        }
        else if(s=="DISPLAY_2D"){
            M.display();
        }
        else if(s=="CLOSEST_2D"){
            Pointpairs p;
            p.takeinput();
        }
        else if(s=="INVERSION_2D"){
            M.countInversions();
        }
        else if(s=="SORT_2D"){
            string x;
            cin>>x;
            Comparator c(x);
            M.sortrows(c);
        }
        cin>>s;
    }
}