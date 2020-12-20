#include <iostream>
#include <vector>
#include <cmath>
const long long INF  = 1e18;
const long N = 99999;



class cutTree {
    long long array[400000];


    void create_pr(long long mas[], long long node, long long left, long long right) {
        if (left == right) {
            array[node] = mas[left];
        }
        else {
            long long middle = (left + right) / 2;
            create_pr(mas,node*2,left,middle);
            create_pr(mas,node*2+1,middle+1,right);
            array[node] = (array[node*2]+array[node*2+1]);
        }
    }

    long long get_sum(long long left,long long right,long long now_left,long long now_right,long long node) {
        if (now_right < left || now_left > right) {
            return 0;
        }
        if ((left <= now_left) && (now_right <= right)) {
            return array[node];
        }
        long long middle = (now_left+now_right) / 2;
        return get_sum(left,right,now_left,middle,node*2) + get_sum(left,right,middle+1,now_right,node*2+1);
    }

    void change_p(long long index,long long value,long long now_left,long long now_right,long long node) {
        if ((now_left==now_right) && (now_left==index)) {
            array[node]=value;
        }
        else {
            long long middle = (now_left + now_right) / 2;
            if (index <= middle) {
                change_p(index, value, now_left, middle, node * 2);
                array[node] = array[node * 2]+ array[node * 2 + 1];
            } else {
                change_p(index, value, middle + 1, now_right, node * 2 + 1);
                array[node] = array[node * 2]+ array[node * 2 + 1];
            }
        }
    }

public:
    void create(long long mas[],long long Q) {
        create_pr(mas,1,0,Q);
    }

    long long take_sum (long long l , long long r,long long Q) {
        return get_sum(l-1,r-1,0,Q,1);
    }

    void  change(long long ind,long long val,long long Q) {
        change_p(ind-1,val,0,Q,1);
    }
};







int main() {
    long long ch[100000];
    long long nch[100000];
    long long n;
    std::cin >> n;
    long long value;
    for (long long i = 1; i<n+1; ++i) {
        std::cin >> value;
        if ( i % 2 == 1) {
           nch[i-1]=value;
           ch[i-1] =0;
        }
        else {
            ch[i-1]=value;
            nch[i-1]=0;
        }
    }
    cutTree Sch;
    cutTree Snch;
    Sch.create(ch,n-1);
    Snch.create(nch,n-1);
    long long req;
    std::cin >> req;
    int cmd1;
    int cmd2;
    int cmd3;
    for (int i=0; i < req; ++i) {
        std::cin >> cmd1 >> cmd2 >> cmd3;
        if (cmd1==0) {
            cmd2 % 2 ==0? Sch.change(cmd2,cmd3,n-1) : Snch.change(cmd2,cmd3,n-1);
        }
        if (cmd1 == 1) {
            if (cmd2 % 2 == 0)  std::cout << Sch.take_sum(cmd2,cmd3,n-1) - Snch.take_sum(cmd2,cmd3,n-1) << '\n';
            else std::cout << -(Sch.take_sum(cmd2,cmd3,n-1) - Snch.take_sum(cmd2,cmd3,n-1)) << '\n';
        }
    }
    //std::cout << S.take_sum(1,6);


    return 0;
}
