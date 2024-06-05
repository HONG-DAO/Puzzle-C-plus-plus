#include<iostream>
#include<time.h>
#include<fstream>
#include<windows.h>//GetStdHandle and SetConsoleCursorPosition, COORD 
#include<conio.h>
#include<iomanip>// De su dung dinh can le setw
#include<stdlib.h>
#include<string.h>

using namespace std;
void gotoxy(int x, int y);
void gotoxy(int x, int y){ // Ham di chuyen hien thi tren console
  	static HANDLE h = NULL;  
  	if(!h) // if (!h) nham de chi goi duoc ham gotoxy duoc 1 lan tranh loi
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  	COORD c = { x, y };  //Ctruc trong windown.h
  						//tao Toa do (x;y)
  	SetConsoleCursorPosition(h,c);
}// Dat vi tri con tro console tai toa do da cho

int d=0, N;

class puzzle{
	int **a, x, y;
	public:// data members co pham vi truy cap tu ben ngoai
		puzzle(){//(constructor) ham tao cac members cua coponent
			int r=1;
			a = new int*[N];//mang 2D a co size NxN
			for(int i=0; i<N; i++)// dien so vao o tu 1->(NxN)-1 
			{					 
				a[i] = new int[N];
				for(int j=0; j<N; j++){
					a[i][j] = r++;
				}				
			}
			a[N-1][N-1]=0;// o cuoi cung dat la 0 
			x=y=N-1;//x=y=N-1 o tróng trong mang 
		}
		~puzzle(){//Ham huy (destructor)
			delete []a;// Giai phong bo nho da cap phat
			x=y=0;
		}
		void in();
		void move(int i);	
		void play();
		void autoplay();
		void random();
		bool end()//Ham nay kiem tra cac so trong mang
		{//a co duoc sap xep tu 1->N-1 voi o cuoi la 0
			int r=1;
			for(int i=0; i<N; i++){
				for(int j=0; j<N; j++){
					if(a[i][j] == r)
					{
						r++;
					}				
					else if(r == N*N && a[N-1][N-1] == 0){
						return 1;
					}	
					else{
						return 0;
				}
				}
			}			
		}
};

void puzzle::in()//Vao game (Hien thi giao dien choi)
{
    system("cls");// Xoa màn hình Console
    cout << "\n\n\t\t\tMove: " << d;//in so buoc di chuyen
    cout << "\n\n\n\t\t\t";
    int t = 0;
    while(t < N)
    {	
        if(t == 0){
        	cout << char(218);
		}           
        else{
        	cout << char(194);
		}
        cout << string(5, char(196));
        t++;
    }
    cout << char(191);
    int i = 0;
    while(i < N)
    {
        cout << "\n\t\t\t";
        t = 0;
        while(t < N)
        {
            cout << char(179);
            if(a[i][t] == 0){
            	cout << setw(4) << "     ";
			}              
            else{
            	cout << setw(4) << a[i][t] << " ";
			}               
            t++;
        }
        cout << char(179);
        cout << "\n\t\t\t";
        if(i == N-1){
        	 break;
		}    
        t = 0;
        while(t < N)
        {	
            if(t == 0){
            	cout << char(195);	
			}
            else{
            	cout << char(197);
			}               
            cout << string(5, char(196));
            t++;
        }
        cout << char(180);
        i++;
    }	
	t = 0;
    while(t < N)
    {
        if(t == 0){
        	cout << char(192);
		}           
        else{
        	cout << char(193);
		}          
        cout << string(5, char(196));
        t++;
    }
    cout << char(217);
}

void puzzle::autoplay(){//Ham choi tu dong
	puzzle a;
	a.in();
}
void puzzle::move(int i){// Ham di chuyen
	d++;//So lan di chuyen
	if(i==1)//i=1 thi Down
	{
		if(x<N-1)
		{
			swap(a[x][y], a[x+1][y]);
			x++;
		}
	}
	else if(i==2)//i=2 thì Up
	{
		if(x>0)
		{
			swap(a[x][y], a[x-1][y]);
			x--;
		}
	}
	else if(i==3)//i=3 thì Right
	{
		if(y>0)
		{
			swap(a[x][y], a[x][y-1]);
			y--;
		}
	}
	else if(i==4)//i=4 thì Left
	{
		if(y<N-1)
		{
			swap(a[x][y], a[x][y+1]);
			y++;
		}
	}
}
void puzzle::play(){//Ham choi
		in();// Goi lai Ham vao hien thi tro choi
		cout<<"\n\n\n\tNhan A de auto choi\n"<<"\tNhan E de thoat game";
		while(!end())// choi den khi thang
		{
			int c = getch();//Doc phim tren ban phim ma khong xai Enter
			if(c == 72)	{
				move(1);//Down
			}
			else if(c == 80){
				move(2);//Up
			}
			else if(c == 77){
				move(3);//Right
			}
			else if(c == 75){
				move(4);//Left
			}
			else if(c == 65||c == 97){
				autoplay();
				return;
			}// nhan a hoac A se tu dong choi
			else if(c == 69||c == 101){
				system("cls");
				exit(0);
			}// Nhan e hoac E se tu dong End
			in();// Hien thi man hinh xong xoa
			cout<<"\n\n\n\tNhan A de auto choi\n"<<"\tNhan E de thoat game";
		}
		system("cls");// Xoa man hinh Console
		in();
		cout<<"\n\n\n\t\t\tYou Win !!!\n\n\n";
		d=0;
}
void puzzle::random(){//Cho so ngau nhien vao o
	int z, c;
	srand(time(NULL));//Cho seed NULL theo thoi gian de lay so ngau nhien
	cout<<"\n\n\tPress any key to start";
	c = getch();
	for(int i=0; i<int(abs(c)); i++)
	{
		z=rand()%10;
		if(z==1){
			move(1);
		} 
		else if(z==2){
			move(2);
		} 
		else if(z==3){
			move(3);
		} 
		else if(z==4){
			move(4);
		} 
	}
	d=0;
}
main(){
	char c, s[]="Hong Dao - Xuan Tan - Minh Nguyet";
	int len=strlen(s);
	int y=0;
	while (!kbhit())
    {
    	system("cls");
    	cout<<"  ______                      ______                   _  "     
		<<endl<<" / _____)                    (_____ \\                 | |      "
		<<endl<<"| /  ___  ____ ____   ____    _____) )   _ _____ _____| | ____ "
		<<endl<<"||  (___)/ _  |    \\ / _  )  |  ____/ | | (___  (___  ) |/ _  )"
		<<endl<<"| \\____/( ( | | | | ( (/ /   | |    | |_| |/ __/ / __/| ( (/ / "
		<<endl<<" \\_____/ \\_||_|_|_|_|\\____)  |_|     \\____(_____(_____)_|\\____)"
		<<endl<<"---------------------------------------------------------------";
        if (y == 65 - len)
        {
            y = 0;
            continue;
        }
        gotoxy(y,8);
        y++;
        cout<<s;
  		cout<<"\n\n\t\tNhan R de xem huong dan"<<endl<<"\t\tNhan P de bat dau choi";
		Sleep(200);
	}
	int b=getch();
	if(b==82||b==114)
	{
		system("cls");
		ifstream fin("huongdan.txt");
		while(!fin.eof())
		{
			fin.get(c);
			cout << c;
		}
		fin.close();
		cout<<"\n\n\tBan muon choi chu ? (y/n)";
		b=getch();
		if(b==121||b==89){
			b=80;
		}	
		else if(b==78||b==110){
			exit(0);
		}	
	}
	if(b==80||b==112)
	{
		while(1)
		{
			system("cls");
			cout<<"\n\tChon level: ";
			cin>>N;
			puzzle a;
			if(N==1)			
			{
				system("cls");
				a.in();
				cout<<"\n\n\n\t\t\tYou don't need to play\n\t\t\tYou Win !!!\n\n\n\n";
			}
			else{
				a.in();
				a.random();
				a.play();
			}
			cout<<"\n\n\n\tBan muon choi tiep chu ? (y/n)";
			b=getch();
			if(b==121||b==89);
			else exit(0);
			}
	}
}
