#include<iostream>
#include<vector>
#include<ctime>
#include<string>
#include<regex>
using namespace std;

#define PUZZLE_NUM 8
//map的高和宽
#define MAP_HIGHT 7
#define MAP_WIDTH 7

//地图上保留的空缺墙体
#define WALL 820
//地图上保留的日期空位
#define MONTH 74
#define DAY 75

//最小拼图块的大小，优化用
#define MIN_PUZZLE 5

//解日历拼图的宏定义，取消后可适用其他拼图，要先修改init函数里的拼图块
#define FOR_CALENDAR

// #define DEBUG

#define max(a,b) (a)>(b)?(a):(b)

//打印map上的一块
void print_block(int id){
    switch (id)
    {
    case 8:
        printf("\033[41m  \33[40m");
        break;
    case 1:
        printf("\033[42m  \33[40m");
        break;
    case 2:
        printf("\033[43m  \33[40m");
        break;
    case 7:
        printf("\033[44m  \33[40m");
        break;
    case 4:
        printf("\033[45m  \33[40m");
        break;
    case 5:
        printf("\033[46m  \33[40m");
        break;
    case 6:
        printf("\033[47m  \33[40m");
        break;
    case 3:
        printf("\033[41m()\33[40m");
        break;
    case MONTH:
        printf("\033[40m月\33[40m");
        break;
    case DAY:
        printf("\033[40m日\33[40m");
        break;
    case WALL:
        printf("\033[40m  \33[40m");
        break;
    default:
        printf("\033[40m[]\33[40m");
    }
}
void print_empty(){
    cout<<"  ";
}

class Shape{
public:
    int hight;
    int width;
    int* myshape;//为0则是空，反之则该处有形状
    Shape(){myshape=NULL;}
    Shape(int h,int w,int* s){
        hight=h;
        width=w;
        myshape=new int[h*w];
        for(int i=0;i<hight;i++){
            for(int j=0;j<width;j++){
                myshape[i*width+j]=s[i*width+j];
            }
        }
    }
    Shape(const Shape &s){
        hight=s.hight;
        width=s.width;
        myshape=new int[hight*width];
        for(int i=0;i<hight;i++){
            for(int j=0;j<width;j++){
                myshape[i*width+j]=s.myshape[i*width+j];
            }
        }
    }
    //顺时针旋转90度
    Shape rotate(){
        int* s=new int[hight*width];
        for(int i=0;i<width;i++){
            for(int j=0;j<hight;j++){
                s[i*hight+j]=myshape[(hight-1-j)*width+i];
            }
        }
        return Shape(width,hight,s);
    }
    //左右镜像翻转
    Shape flip(){
        int* s=new int[hight*width];
        for(int i=0;i<hight;i++){
            for(int j=0;j<width;j++){
                s[i*width+width-1-j]=myshape[i*width+j];
            }
        }
        return Shape(hight,width,s);
    }
    //检查两个形状是否一样
    bool equal(Shape &shape){
        bool ret=true;
        if(hight==shape.hight&&width==shape.width){
            for(int i=0;i<hight;i++){
                if(ret==false){
                    break;
                }
                for(int j=0;j<width;j++){
                    if(myshape[i*width+j]!=shape.myshape[i*width+j]){
                        ret=false;
                        break;
                    }
                }
            }
        }
        else{   
            ret=false;
        }
        return ret;
    }
    void show(){
        for(int i=0;i<hight;i++){
            for(int j=0;j<width;j++){
                cout<<myshape[i*width+j]<<' ';
            }
            cout<<endl;
        }
    }
    void mydelete(){
        delete[] myshape;
    }
};


class Map{
public:
    int map[MAP_HIGHT][MAP_WIDTH];
    Map(){
        for(int i=0;i<MAP_HIGHT;i++){
            for(int j=0;j<MAP_WIDTH;j++){
                map[i][j]=0;
            }
        }
#ifdef FOR_CALENDAR
        map[0][6]=WALL;
        map[1][6]=WALL;
        map[6][3]=WALL;
        map[6][4]=WALL;
        map[6][5]=WALL;
        map[6][6]=WALL;
#endif
    }
    Map(const Map& m){
        for(int i=0;i<MAP_HIGHT;i++){
            for(int j=0;j<MAP_WIDTH;j++){
                map[i][j]=m.map[i][j];
            }
        }
    }
    //设置日期，检查是否合法
    bool setDate(int month,int day){
        int max_day=30;
        if(month==1||month==3||month==5||month==7
        ||month==8||month==10||month==12){
            max_day=31;
        }
        else if(month==2){
            max_day=29;
        }
        else if(month==4||month==6||month==9||month==11){
            max_day=30;
        }
        else{
            cout<<"输入正确的月份(╯▔皿▔)╯"<<endl;
            return false;
        }
        if(day<=0||day>max_day){
            cout<<"输入合适的日期(╯▔皿▔)╯"<<endl;
            return false;
        }
        
        map[(month-1)/6][(month-1)%6]=MONTH;
        map[(day-1)/7+2][(day-1)%7]=DAY;
        return true;
    }
    void show(){
        for(int i=0;i<MAP_HIGHT;i++){
            for(int j=0;j<MAP_WIDTH;j++){
                if(map[i][j]==MONTH){
                    int month=i*6+j+1;
                    if(month<10)cout<<' ';
                    cout<<month;
                }
                else if(map[i][j]==DAY){
                    int day=(i-2)*7+j+1;
                    if(day<10)cout<<' ';
                    cout<<day;
                }
                else
                    print_block(map[i][j]);
            }
            cout<<endl;
        }
    }
    /*
    检查地图，提前剪枝一些不可能求解的情况
    1. 出现小于最小拼图块大小的联通区域
    */
    bool checkMap(){
        bool ret=true;
        #ifndef MIN_PUZZLE
        return ret;
        #endif


    }
};

class Puzzle{
    Shape* all_shapes[8];
public:
    int shape_num;
    int x;
    int y;//当前在图形中，左上角右上角坐标
    int shape_index;//当前拼图的形状
    Puzzle(){
        x=0;y=0;shape_index=0;
    }
    void initShape(Shape origin){
        //给定初始形状，生成8个旋转、翻转形状，相同的不保存
        all_shapes[0]=new Shape(origin);

        shape_num=1;
        Shape temp_shape=origin.flip();
        if(temp_shape.equal(origin)){
            temp_shape.mydelete();
        }
        else{
            all_shapes[1]=new Shape(temp_shape);
            shape_num++;
            temp_shape=*all_shapes[1];
            for(int i=0;i<3;i++){
                temp_shape=temp_shape.rotate();//可能空间泄露
                bool same=false;
                for(int j=0;j<shape_num;j++){
                    if(temp_shape.equal(*all_shapes[j])){
                        same=true;
                        temp_shape.mydelete();
                        temp_shape=*all_shapes[j];
                        break;
                    }
                }
                if(!same){
                    all_shapes[shape_num]=new Shape(temp_shape);
                    shape_num++;
                }
            }
        }
        
        temp_shape=origin;
        for(int i=0;i<3;i++){
            temp_shape=temp_shape.rotate();//可能空间泄露
            bool same=false;
            for(int j=0;j<shape_num;j++){
                if(temp_shape.equal(*all_shapes[j])){
                    same=true;
                    temp_shape.mydelete();
                    temp_shape=*all_shapes[j];
                    break;
                }
            }
            if(!same){
                all_shapes[shape_num]=new Shape(temp_shape);
                shape_num++;
            }
        }
    }
    void show(){
        cout<<"共"<<shape_num<<"种变形"<<endl;
        int max_len=max(all_shapes[0]->hight,all_shapes[0]->width);
        for(int i=0;i<max_len;i++){
            for(int j=0;j<shape_num;j++){
                //打印第j个shape的第i行
                if(i>=all_shapes[j]->hight){
                    for(int k=0;k<all_shapes[j]->width;k++){
                        print_empty();
                    }
                    cout<<" || ";
                }
                else{
                    for(int k=0;k<all_shapes[j]->width;k++){
                        print_block(all_shapes[j]->myshape[i*all_shapes[j]->width+k]);
                    }
                    cout<<" || ";
                }
            }
            cout<<endl;
        }
    }
    //检查是否能将本块放置在map上的xy位置处，左上角对齐xy
    //如果能放置，则放置，设置map对应区域和shape_index,x,y
    bool check(Map* map,int x,int y,int index){
        Shape* shape=all_shapes[index];
        if(y+shape->hight>MAP_HIGHT || x+shape->width>MAP_WIDTH){
            return false;
        }
        //本块不为0的坐标，map上要为0
        for(int i=0;i<shape->hight;i++){
            for(int j=0;j<shape->width;j++){
                if(shape->myshape[i*shape->width+j]&&map->map[y+i][x+j]){
                    return false;
                }
            }
        }
        for(int i=0;i<shape->hight;i++){
            for(int j=0;j<shape->width;j++){
                if(shape->myshape[i*shape->width+j]){
                    map->map[y+i][x+j]=shape->myshape[i*shape->width+j];
                }
            }
        }
        shape_index=index;
        this->x=x;
        this->y=y;
        return true;
    }
    //从map上的x y位置处移除本块的对应shape
    void clear(Map* map){
        Shape* shape=all_shapes[shape_index];
        for(int i=0;i<shape->hight;i++){
            for(int j=0;j<shape->width;j++){
                if(shape->myshape[i*shape->width+j]){
                    map->map[y+i][x+j]=0;
                }
            }
        }
    }
};