#include "puzzle.h"

int stack_index=0;//当前待放置的拼图序号
Puzzle puzzles[PUZZLE_NUM];
Map map;


void init(){
    //初始化公共map
    cout<<"今天是几月几日呢？(´･ω･`)? （月份日期用空格分开，例如\"7 4\"表示七月四日）"<<endl;
    int month,day;
    cin>>month>>day;
    while(!map.setDate(month,day)){
        cin>>month>>day;
    }

    //输入初始形状
    int s_2_4[3][2*4]={
        {0,1,1,1,
         1,1,0,0},
        {2,2,2,2,
         0,0,2,0},
        {3,3,3,3,
         3,0,0,0},
    };
    int s_3_3[2][3*3]=
        {{4,4,4,
         4,0,0,
         4,0,0},
        {5,5,0,
         0,5,0,
         0,5,5}};
    int s_2_3[3][2*3]={
        {6,6,6,
         6,6,6},
        {7,7,0,
         7,7,7},
        {8,0,8,
         8,8,8}
    };
    for(int i=0;i<PUZZLE_NUM;i++){
        if(i<3){
            puzzles[i].initShape(Shape(2,4,s_2_4[i]));
        }
        else if(i<5){
            puzzles[i].initShape(Shape(3,3,s_3_3[i-3]));
        }
        else{
            puzzles[i].initShape(Shape(2,3,s_2_3[i-5]));
        }
    }
}

int main(){
    init();
    //逐一为拼图块选好位置和形状，如果遇到无处安放的块，则回溯
    bool back=false;//回溯标志
    int back_count=0;
    while(stack_index<PUZZLE_NUM&&stack_index>=0){
        //初始化
        int i,j,k;
        if(back){
            back_count++;
        #ifdef DEBUG
            if(back_count%100000==0){
                cout<<"back "<<back_count<<endl;
            }
        #endif
            //需要回溯，也就是当前拼图需要一个新的位置,要先从旧的位置删除掉
            puzzles[stack_index].clear(&map);
            i=puzzles[stack_index].y;
            j=puzzles[stack_index].x;
            k=puzzles[stack_index].shape_index+1;
        }
        else{
            i=0;
            j=0;
            k=0;
        }

        //为stack_index号拼图找一个位置
        bool success=false;
        for(;i<7;i++){
            for(;j<7;j++){
                for(;k<puzzles[stack_index].shape_num;k++){
                    if(puzzles[stack_index].check(&map,j,i,k)){
                        success=true;
                        break;
                    }
                }
                if(success)break;
                k=0;
            }
            if(success)break;
            j=0;
        }
        if(success){
            stack_index++;
            back=false;
        }
        else{
            stack_index--;
            back=true;
        }
    }
    cout<<"down,total search "<<back_count<<" probability"<<endl;
    map.show();
    return 0;
}