double Solution::findMedianSortedArrays(const vector<int> &A, const vector<int> &B) 
{
    int m = A.size();
    int n = B.size();
    if(m > n) return findMedianSortedArrays(B,A);

    int imin = 0;
    int imax = m;
    int half = (m+n+1)/2;
    
    while(imin <= imax)
    {
        int i = (imin+imax)/2;
        int j = half-i;
        if(i<m && B[j-1] > A[i]) imin = i+1;
        else if(i>0 && B[j] < A[i-1]) imax = i-1;
        else
        {
            double maxl,minr;
            if(i==0) maxl = B[j-1];
            else if(j==0) maxl = A[i-1];
            else maxl = max(A[i-1],B[j-1]);
        
            if((m+n)%2) return maxl;
            
            if(i==m) minr = B[j];
            else if(j==n) minr = A[i];
            else minr = min(B[j],A[i]);
            
            double ans = (maxl+minr)/2.0;
            return ans;
        }
    }
    
    return -1;
}
