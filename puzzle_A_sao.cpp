#include<iostream>
#include<cmath>
using namespace std;
struct node{
    int n=0; // Kích thước của ma trận
    int *board; // Mảng lưu trạng thái của puzzle
    int cost=0;
    int heuristic=0;
    bool processed=false;
    int step=0; // Đây là bước đi tạo ra board hiện tại
    int f_score=0;
    int empty_col=0;
    int empty_row=0;
    int mother_index=0;//chi so cua node tao ra node nay

    void findEpmty(){
        for(int i=0; i<n*n; i++){
            if(board[i]==0){
                empty_col=i%n;
                empty_row=int(i/n);
                break; // Thoát khỏi vòng lặp khi tìm thấy
            }
        }
    }

    void cal_heur(int const answer[]){
        for(int i=0; i<n*n; i++){
            for(int j=0; j<n*n; j++){
                if(board[i]==answer[j]){
                    heuristic+= abs(i%n - j%n) + abs(int(i/n) - int(j/n));
                    break;
                }
            }
        }
        f_score=cost+heuristic;
    }

    void display_board(){
        cout<<"\n===========================";
        for (int i=0; i<n*n; i++){
            if(i % n == 0){
                cout << "\n\n";
            }
            if(board[i] == 0){
                cout << " ";
                continue;
            }
            cout << "\t" << board[i];
        }
        cout<<"\n===========================";
    }
    void displayAll(int answer[]){
        findEpmty();
        cal_heur(answer);
        // cout<<"\nn= "<<n;
        // cout<<"\ncost= "<<cost;
         cout<<"\nempty row= "<<empty_row;
         cout<<"\nempty columm= "<<empty_col;
    }

};
bool check_nhap(int number,int copy_answer[],int n){
    for(int i=0;i<n*n;i++){
        if(number==copy_answer[i]){
            copy_answer[i]=-1;
            return true;
        }
    }
    return false;
}
void nhap_board(int n,node *puzzle,int copy_answer[]){
    cout << "\nMoi ban nhap trang thai khoi tao cho puzzle: ";
    cout<<"\nBan nhap cac so tu 0 den "<<n*n-1<<" moi so chi duoc nhap 1 lan (so 0 duoc hieu la o trong)"; 
    for(int i=0; i<n*n; i++){
        puzzle->display_board();
        cout << "\nMoi ban nhap phan tu thu " << i+1 << " :";
        do{
            cin >> puzzle->board[i];
        } while(puzzle->board[i] < 0 || puzzle->board[i] >= n*n ||!check_nhap(puzzle->board[i],copy_answer, n));
    }
}
bool isValidMove(node *puzzle,int n,int choice){
    if(choice==1){
        if(puzzle->empty_row-1<0){return false;}else{return true;}
    }if(choice==2){
        if(puzzle->empty_row+1>=n){return false;}else{return true;}
    }if(choice==3){
        if(puzzle->empty_col-1<0){return false;}else{return true;}
    }if(choice==4){
        if(puzzle->empty_col+1>=n){return false;}else{return true;}
    }if(choice==0){return true;}
    return false;
}
void directions(node *puzzle,int n,int choice){
    int index=puzzle->empty_row*n+puzzle->empty_col;
    if(choice==1){
        int r=puzzle->board[index];
        puzzle->board[index]=puzzle->board[index-n];
        puzzle->board[index-n]=r;
    }if(choice==2){
        int r=puzzle->board[index];
        puzzle->board[index]=puzzle->board[index+n];
        puzzle->board[index+n]=r;
    }if(choice==3){
        int r=puzzle->board[index];
        puzzle->board[index]=puzzle->board[index-1];
        puzzle->board[index-1]=r;
    }if(choice==4){
        int r=puzzle->board[index];
        puzzle->board[index]=puzzle->board[index+1];
        puzzle->board[index+1]=r;
    }

}
void updateStatus(node *puzzle,int *const answer,int n){
    puzzle->n=n;
    puzzle->cal_heur(answer);
    puzzle->findEpmty();
}
int get_user_input() {
    string input;
    do {
        cout << "\nNhap huong di chuyen (u, d, l, r) nhan phim 0 de chuyen sang che do autorun: ";
        cin >> input;
    } while (input != "u" && input != "d" && input != "l" && input != "r" && input != "0");
    if (input == "u") {
        return 1;
    } else if (input == "d") {
        return 2;
    } else if (input == "l") {
        return 3;
    } else if (input == "r") {
        return 4;
    } else if (input == "0") {
        return 0;
    }
    return 0;
}
void transform(int x){
    if(x<0||x>4){cout<<"\nBuoc di khong hop le";}
    if(x==0){cout<<"\nDay la trang thai bat dau";}
    if(x==1){cout<<"\nDi len tren !";}
    if(x==2){cout<<"\nDi xuong duoi!";}
    if(x==3){cout<<"\nDi sang trai!";}
    if(x==4){cout<<"\nDi sang phai!";}
}
bool isGoal(node *puzzle,int n,int const answer[]){
    for(int i=0;i<n*n;i++){
        if(puzzle->board[i]!=answer[i]){
            return false;
        }
    }
    return true;
}
void xuat_mang(int mang[],int n){
    for(int i=0;i<n*n;i++){
        if(i%n==0){
            cout<<"\n\n";
        }
        if(mang[i]==0){
            cout<<"\t"<<" ";
            continue;
        }
        cout<<"\t"<<mang[i];
    }
}
node *findMotherNode(node puzzle[],int so_luong){
    node *p;
    int index=0;
    p=&puzzle[0];
    for(int i=0;i<so_luong;i++){
        if(puzzle[i].processed==false){
            p=&puzzle[i];
            index=i;
            break;
        }
    }
    for(int i=index+1;i<so_luong-index-1;i++){
        if(puzzle[i].f_score<p->f_score && !puzzle[i].processed){
            p=&puzzle[i];
        }
    }
    return p;
}
void createNode(node *Source,node *target,int n,int choice){
    target->board=new int [n*n]();
    for(int i=0;i<n*n;i++){
        target->board[i]=Source->board[i];
    }
}
bool flag(int preStep,int curStep){
    if(preStep==1&&curStep==2){
        return false;
    }if(preStep==2&&curStep==1){
        return false;
    }if(preStep==3&&curStep==4){
        return false;
    }if(preStep==4&&curStep==3){
        return false;
    }
    return true;
}
bool isSolvable(const int board[], int n, int empty_row) {
    int inversions = 0;
    for (int i = 0; i < n * n - 1; i++) {
        if (board[i] == 0) {
            continue;  // Bỏ qua ô trống
        }
        for (int j = i + 1; j < n * n; j++) {
            if (board[j] != 0 && board[i] > board[j]) {
                inversions++;
                }
        }
    }
    empty_row+=1;//empty row la dong cua o trong trong bang va bat dau tu 1
    if (n % 2 == 1) {
        return inversions % 2 == 0;
    } else {
        return (inversions % 2 == 0 && empty_row % 2 == n % 2) ||
                (inversions % 2 == 1 && empty_row % 2 != n % 2);
    }//ham isSolvable co the de lot mot so trung hop
}
int main(){
    int n;
    cout << "Vui long nhap kich thuoc cua ma tran vuong: ";
    do{
        cin >> n;
    } while(n < 2 || n > 4);

    node *puzzle = new node ();
    puzzle->n = n;
    puzzle->board=new int [n*n]();
    int *answer = new int[n*n];
    int *copy_answer=new int [n*n];
    for(int i = 0; i < n*n; i++){
        answer[i] = (i == n*n-1) ? 0 : i+1;
        copy_answer[i]=(i==n*n-1)?0:i+1;
    }
    xuat_mang(copy_answer,n);
    cout << "\nVui long nhap trang thai ban dau cho bang puzzle: ";
    nhap_board(n,puzzle,copy_answer);
    puzzle->findEpmty();
    while(! isGoal(puzzle,n,answer)){
        xuat_mang(puzzle->board,n);
        int lua_chon;
        do{lua_chon=get_user_input();}while(!isValidMove(puzzle,n,lua_chon));
        if(lua_chon==0){goto autorun;}
        directions(puzzle,n,lua_chon);
        puzzle->findEpmty();
        puzzle->displayAll(answer);
    }
    delete [] answer;
    delete  puzzle;
    delete [] copy_answer;
    cout<<"\nChuc mung ban da thang tro choi!";
    return 0;
    autorun:{
        cout<<"\nDa chuyen toi autorun";
        if( !isSolvable(puzzle->board,n,puzzle->empty_row)){
            cout<<"\nDay la trang thai khong the giai!";
            goto stop;
        }
        unsigned long long so_luong=0;
        node *puzzleAuto=new node [1000000];//mot trieu phan tu chiem 48 megabytes
        node *motherNode;
        //gan board cua nguoi choi cho puzzleAuto[0]
        puzzleAuto[so_luong].board=puzzle->board;
        updateStatus(&puzzleAuto[so_luong],answer,n);
        while(!isGoal(&puzzleAuto[so_luong],n,answer)){
            motherNode=findMotherNode(puzzleAuto,so_luong);
            motherNode->processed=true;
            unsigned long long motherIndex=motherNode-puzzleAuto;
            for(int i=1;i<5;i++){
                if(i==1&&isValidMove(motherNode,n,1)&&flag(motherNode->step,1)){
                    so_luong+=1;
                    createNode(motherNode,&puzzleAuto[so_luong],n,1);
                    puzzleAuto[so_luong].cost=motherNode->cost+1;
                    updateStatus(&puzzleAuto[so_luong],answer,n);
                    directions(&puzzleAuto[so_luong],n,1);
                    puzzleAuto[so_luong].mother_index=motherIndex;
                    puzzleAuto[so_luong].step=1;
                    if(isGoal(&puzzleAuto[so_luong],n,answer)){break;}
                }if(i==2&&isValidMove(motherNode,n,2)&&flag(motherNode->step,2)){
                    so_luong+=1;
                    createNode(motherNode,&puzzleAuto[so_luong],n,2);
                    puzzleAuto[so_luong].cost=motherNode->cost+1;
                    updateStatus(&puzzleAuto[so_luong],answer,n);
                    directions(&puzzleAuto[so_luong],n,2);
                    puzzleAuto[so_luong].mother_index=motherIndex;
                    puzzleAuto[so_luong].step=2;
                    if(isGoal(&puzzleAuto[so_luong],n,answer)){break;}   
                }if(i==3&&isValidMove(motherNode,n,3)&&flag(motherNode->step,3)){
                    so_luong+=1;
                    createNode(motherNode,&puzzleAuto[so_luong],n,3);
                    puzzleAuto[so_luong].cost=motherNode->cost+1;
                    updateStatus(&puzzleAuto[so_luong],answer,n);
                    directions(&puzzleAuto[so_luong],n,3);
                    puzzleAuto[so_luong].mother_index=motherIndex;
                    puzzleAuto[so_luong].step=3;
                    if(isGoal(&puzzleAuto[so_luong],n,answer)){break;}
                }if(i==4&&isValidMove(motherNode,n,4)&&flag(motherNode->step,4)){
                    so_luong+=1;
                    createNode(motherNode,&puzzleAuto[so_luong],n,4);
                    puzzleAuto[so_luong].cost=motherNode->cost+1;
                    updateStatus(&puzzleAuto[so_luong],answer,n);
                    directions(&puzzleAuto[so_luong],n,4);
                    puzzleAuto[so_luong].mother_index=motherIndex;
                    puzzleAuto[so_luong].step=4;
                    if(isGoal(&puzzleAuto[so_luong],n,answer)){break;}
                }if(so_luong>1000000){cout<<"\nOverload";delete [] puzzleAuto;goto stop;}
            }
        }
        cout<<"\nGiai thanh cong";
        unsigned long long Index;Index=so_luong;
        node **reverse=new node *[50];
        for(int i=0;i<50;i++){
            reverse[i]=&puzzleAuto[Index];
            if(Index==0){break;}
            Index=reverse[i]->mother_index;
        }
        for(int i=puzzleAuto[so_luong].cost;i>=0;i--){
            cout<<"\nBuoc "<<abs(i-puzzleAuto[so_luong].cost);
            transform(reverse[i]->step);
            reverse[i]->displayAll(answer);
            cout<<"\n================================";
        }
        cout<<"\nDa giai duoc bai toan sau "<<puzzleAuto[so_luong].cost<<" buoc!";
        cout<<"\nVoi so luong node da duyet qua la: "<<so_luong;
        delete [] reverse;
        delete [] puzzleAuto;
        goto stop;
    }
    stop:{ cout<<"\nChuc ban mot ngay toi lanh!";
        delete puzzle;
        delete [] answer;
        delete [] copy_answer;
        return 0;}
        return 0;
}