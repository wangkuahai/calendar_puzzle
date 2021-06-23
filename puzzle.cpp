#include "puzzle.h"

int stack_index=0;//当前待放置的拼图序号
Puzzle puzzles[PUZZLE_NUM];
Map map;
vector<Map> res_list;//存放所有的解

void showAllRes(){
    int res_size=res_list.size();
    
    //每行展示6个解
    for(int k=0;k<res_size;k=k+6){
        //展示从第k个解开始的6个解
        for(int i=0;i<MAP_HIGHT;i++){
            for(int l=k;l<k+6;l++){
                //展示第l个解的第i行
                for(int j=0;j<MAP_WIDTH;j++){
                    print_block(res_list[l].map[i][j]);
                }
                print_empty();
            }
            cout<<endl;
        }
        cout<<endl;
    }
}


void init(){
    //初始化公共map
#ifdef FOR_CALENDAR
    cout<<"今天是几月几日呢？(´･ω･`)? （月份日期用空格分开，例如\"7 4\"表示七月四日）"<<endl;
    int month,day;
    cin>>month>>day;
    while(!map.setDate(month,day)){
        while(!cin>>month>>day);
    }
#endif

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
         0,5,5}
    };
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
            puzzles[i].initShape(Shape(2,3,s_2_3[i]));
        }
        else if(i<5){
            puzzles[i].initShape(Shape(3,3,s_3_3[i-3]));
        }
        else{
            puzzles[i].initShape(Shape(2,4,s_2_4[i-5]));
        }
    }
}

int main(){
    cout<<"====为了保证输出格式正确，请尽量放大本窗口，或者全屏===="<<endl;
    init();
    //逐一为拼图块选好位置和形状，如果遇到无处安放的块，则回溯
    bool back=false;//回溯标志
    int back_count=0;
    int res_count=0;//已经找到的解的数量
    while(1||res_count<5){
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
            for(;i<MAP_HIGHT;i++){
                for(;j<MAP_WIDTH;j++){
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
        if(stack_index==PUZZLE_NUM){
            //循环因为找到解而中断
            // map.show();
            back=true;
            stack_index--;
            res_count++;
            res_list.push_back(Map(map));
#ifdef DEBUG
            cout<<"found "<<res_count<<" solution(s)"<<endl;
#endif 
        }
        else{
            //循环因为找不到解而中断
            break;
        }
    }
    cout<<"down,total search "<<back_count<<" probability"<<endl;
    cout<<"found "<<res_count<<" solution(s)"<<endl;
    showAllRes();
    return 0;
}