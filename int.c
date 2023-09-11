int max_subsequence_sum(int a[], unsigned int n)
{
    int this_sum, max_sum, best_i, best_j, i, j, k;
    /*1*/ max_sum = 0;
    best_i = best_j = -1;
    /*2*/ for (i = 0; i < n; i++)
        /*3*/
        for (j = i; j < n; j++)
        {
            /*4*/ this_sum = 0;
            /*5*/ for (k = i; k <= j; k++)
            /*6*/
            /*7*/
            {
                this_sum += a[k];
                if (this_sum > max_sum)
                    /* update max_sum, best_i, best_j */
                    /*8*/ max_sum = this_sum;
                /*9*/ best_i = i; /*10*/
                best_j = j;
            }
        }
    /*11*/
    return (max_sum);
}