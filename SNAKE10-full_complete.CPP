//This software is the property of Paras Singh Kaphalia and Anant Dahiya,all copyRights of this project are reserved.
#include<fstream.h>
#include<ctype.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<dos.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define up 72
#define down 80
#define left 75
#define right 77

void menu();
void main_menu();
void play_menu();
void play1();
void write_score(int);
void scr();


struct data
{
	char name[20];
	int score;
};



class level1
{
int qx[200],qy[200],track,t,grow,top;//t-tail,h-head cordinates;
public:
int qfx[200],qfy[200],topf,score;    //note that these are public variables
level1();
void display(int);
void boundry();
int move();  //return 0 if esc key is pressed and game terminates
int scan(int,int,int check=0);     //will either 0 or 1 or 2;
void put_food();
void initialize(int);
void call_display()
{
	display(top);
}
int call_scan()
{
       int c=scan(qx[top],qy[top]);
       return c;
}
void get_head(int &hx,int &hy)
{
	hx=qx[top];
	hy=qy[top];
}

};

level1::level1()     //level1 constructor
{
	qx[0]=36;//index 0 contains tail;
	qy[0]=12;
	qx[1]=40;//index top contains head;
	qy[1]=12;
	score=0;
	topf=-1;
	grow=0;
	track=right;
	t=right;
	top=1;
}


class level2:public level1          //inherits level1 in public mode
{
public:
void boundry();   //overridden fun
int scan(int,int);
void put_food(int,int);  //overridden fun
};

void level2::boundry()
{
  for(int j=6;j<=11;j++)
  {
	gotoxy(30,j);
	cout<<"|";
  }
  for(int i=21;i>=16;i--)
  {
	gotoxy(50,i);
	cout<<"|";
  }
}

int level2::scan(int hx,int hy)
{
 if(hx==30 && hy>=6 && hy<=11)
	return 0;
 if(hx==50 && hy>=16 && hy<=21)
	return 0;
 return 1;
}


void level2::put_food(int hx,int hy)
{
	topf++;
	randomize();
	do
	{
		qfx[topf]=random(62);
		qfy[topf]=random(21);
	} while(scan(qfx[topf],qfy[topf])==0 || (qfy[topf]<6) || (qfx[topf]<20) || level1::scan(qfx[topf],qfy[topf],1)==0 ||  ((qfx[topf]==hx) && (qfy[topf]==hy)));
}



void play2()
{
	clrscr();
	level2 l;
	int c=2,wait=350;
	while(1)     //program runs till the value returned 0;
	{
		int hx,hy;
		l.get_head(hx,hy);
		if(c==2)   //scan returns 2 if eating is sucessful and hence put more food;
		{
			l.put_food(hx,hy);
			if(l.score%5==0&&wait>200)
			wait=wait-20;
		}
		clrscr();
		l.boundry();
	       l.level1::boundry();
		l.call_display();
		delay(wait);
		c=l.move();
		if(c==0)
		return;
		c=l.call_scan();
		if(c==0)
		{
			clrscr();
			write_score(l.score);
			return;
		}
		l.get_head(hx,hy);
		int cc=l.scan(hx,hy); //calling the overridden function
		if(cc==0)
		{
			clrscr();
			write_score(l.score);
			return;
		}
	}
}


void play1()
{
	clrscr();
	level1 l;
	int c=2,wait=350;
	while(1)     //program runs till the value returned 0;
	{
		if(c==2)   //scan returns 2 if eating is sucessful and hence put more food;
		{
			l.put_food();
			if(l.score%5==0&&wait>200)
			wait=wait-20;
		}
		clrscr();
		l.boundry();
		l.call_display();
		delay(wait);
		c=l.move();
		if(c==0)
		return;
		c=l.call_scan();
		if(c==0)
		{
			clrscr();
			write_score(l.score);
			return;
		}

	}
}





	void level1::put_food()
	{
		topf++;
			randomize();
		do
		{
			qfx[topf]=random(62);
			qfy[topf]=random(21);
		} while((qfy[topf]<6) || (qfx[topf]<20) || scan(qfx[topf],qfy[topf],1)==0 || ((qfx[topf]==qx[top]) && (qfy[topf]==qy[top])));
	}



/*
scan retuns 0 if snake is dead;
scan returns 1 if it is alive but it has not eaten anything
scan returns 2 if snake eats food;
*/

int level1::scan(int hx,int hy,int check)
{
// this part is scaning if snake touch itself
	for(int j=top-1;j>0;j--)
	{
		if(hx==qx[j]&&hx==qx[j-1])
		{
			if(hy>=qy[j]&&hy<=qy[j-1]) //0 implies snake dies
			return 0;
			else if(hy<=qy[j]&&hy>=qy[j-1])  //0 implies snake dies
			return 0;
		}
		else if(hy==qy[j]&&hy==qy[j-1])
		{
		if(hx>=qx[j]&&hx<=qx[j-1])
			return 0;      //0 implies snake dies
			else if(hx<=qx[j]&&hx>=qx[j-1])
			return 0;      //0 implies snake dies
		}
	}
	//this part if scaning if snake touches the boundry();
	if(hx==19||hx==62)
	return 0;//snake dies due to touching the boundry
	if(hy==5||hy==21)
	return 0;  //snake dies due to touching the boundry


       //check if eating sucessful or not
       if(check==0)
       {
		 int fx=qfx[topf];
		int fy=qfy[topf];
		if(fx==hx&&fy==hy)
		{
			 score++;
			return 2;
		}
       }



	 //this part should be in the end;
	return 1;  // snake continues to move without any change
	}



void level1::display(int top)
{
	//displaying snake
	int hx=qx[top],hy=qy[top];


	if(track==right)
	{
		if(qfy[topf]==hy&&hx+1==qfx[topf])
		{
			gotoxy(hx,hy+1);
			cout<<"*";
			gotoxy(hx,hy-1);
			cout<<"*";
		}
		else
		{
			gotoxy(hx,hy);
			cout<<">";
		}
	}
	else if(track==left)
	{
	 if(qfy[topf]==hy&&hx-1==qfx[topf])
	 {
	 gotoxy(hx,hy-1);
	 cout<<"*";
	 gotoxy(hx,hy+1);
	 cout<<"*";
	 }
		 else
		 {
		 gotoxy(hx,hy);
		 cout<<"<";
		 }
	}
	else if(track==up)
	{
		if(qfx[topf]==hx&&hy-1==qfy[topf])
		{
			gotoxy(hx-1,hy);
			cout<<"* *";
		}
		else
		{
			gotoxy(hx,hy);
			cout<<"^";
		}
	}
	else
	{
	      if(qfx[topf]==hx&&hy+1==qfy[topf])
		{
			gotoxy(hx-1,hy);
			cout<<"* *";
		}
		else
		{
		gotoxy(hx,hy);
		cout<<"v";
		}
	}
	top--;
		while(top>=0)
		{

			if(hx!=qx[top])
			{
			if(hx<qx[top])
			hx++;
			else
			hx--;
			}
			if(hy!=qy[top])
			{
			if(hy<qy[top])
			hy++;
			else
			hy--;
			}
			if(hx==qx[top]&&hy==qy[top])
			{
			top--;
			}
			gotoxy(hx,hy);
		cout<<"*";
		}

	//putting food
	gotoxy(qfx[topf],qfy[topf]);
	cout<<"k";

	//printing score
	gotoxy(70,2);
	cout<<"score -> "<<score;
}


/* scan return 0 if esc is pressed else it returns 1;
*/
int level1::move()
{
	if(kbhit())//kbhit check if some key is pressed or not if yes then returns non zero value
	{
	  t=getch();
	}

	if(t==27)//27 is the askee value of esc
	return 0;

	if(t==0||t==224) //if special keys are pressed
	{
		t=getch();
		if(t!=up&&t!=down&&t!=left&&t!=right)	//if special keys other than arrows are pressed
	    t=track;
	}
	else	//if normal keys are pressed
	t=track;

	if(track==up||track==down)
	{
		if(t==right)		//push operation in que;
		{
		top++;
		qx[top]=qx[top-1]+1;
		qy[top]=qy[top-1];
		track=t;
		}
		else if(t==left)		//emque;
		{
		 top++;
		qx[top]=qx[top-1]-1;
		qy[top]=qy[top-1];
		track=t;
		}
		else if(t==up||t==down)
		{
		if(track==up)
		qy[top]--;
		else
		qy[top]++;
		}
	}
	else
	{
		if(t==up)		//enque;
		{
		top++;
		qy[top]=qy[top-1]-1;
		qx[top]=qx[top-1];
		track=t;
		}
		else if(t==down)		//enque;
		{
		 top++;
		qy[top]=qy[top-1]+1;
		qx[top]=qx[top-1];
		track=t;
		}
		else if(t==right||t==left)
		{
		if(track==right)
		qx[top]++;
		else
		qx[top]--;
		}

	}



	//this segmaent is for movement of tail;

		if(qx[0]!=qx[1])
		{
		     if(qx[0]<qx[1])
			qx[0]++;
			 else
		     qx[0]--;
		}
		  else if(qy[0]!=qy[1])
		{
		if(qy[0]<qy[1])
		qy[0]++;
		else
		qy[0]--;
		}
		if(qx[0]==qx[1]&&qy[0]==qy[1])
		{
		for(int j=0;j<top;j++)
		{
		qx[j]=qx[j+1];
		qy[j]=qy[j+1];
		}
							//deque;
		top--;
		}

		if(grow==1)//then  grow tail by one
		{
		if(qx[1]<qx[0])
		qx[0]++;
		else if(qx[1]>qx[0])
		qx[0]--;
		else if(qy[1]<qy[0])
		qy[0]++;
		else if(qy[1]>qy[0])
		qy[0]--;
		grow=0;
		}


		if(qx[0]==qfx[0]&&qy[0]==qfy[0]&&topf>0)
		{
		grow=1;
			for(int j=0;j<topf;j++)
			{
				qfx[j]=qfx[j+1];
				qfy[j]=qfy[j+1];
			}
			topf--;
		}
	      return 1;
}








void level1::boundry()
{
	for(int j=0;j<43;j++)
	{
		gotoxy(19+j,5);
		cout<<"-";
		gotoxy(19+j,21);
		cout<<"-";
	}
	for(int i=0;i<17;i++)
	{
		gotoxy(19,5+i);
		cout<<"|";
		gotoxy(62,5+i);
		cout<<"|";
	}
}


void main()
{
	clrscr();
	char ch[68];
	int k=10;
	gotoxy(33,11);
	cout<<"S N A K E   G A M E";
	delay(2000);
	clrscr();
	strcpy(ch,"This game is developed by Paras Singh Kaphalia and Anant Dahiya");
	for(int j=0;j<63;j++)
	{
		gotoxy(k,11);
		cout<<ch[j];
		delay(60);
		k=k+1;
	}
	delay(3000);
	menu();
	getch();
}

void main_menu()
{
	gotoxy(27,5);
	cout<<"M  A  I  N      M  E  N  U";
	gotoxy(29,9);
	cout<<"1.Start New Game";
	gotoxy(29,10);
	cout<<"2.Instruction";
	gotoxy(29,11);
	cout<<"3.See scores";
	gotoxy(29,12);
	cout<<"4.exit";
}




void menu()
{
	int op;
	while(1)
	{
		clrscr();
		main_menu();
		gotoxy(25,21);
		cout<<"please enter your option ";
		cin>>op;
		flag:
		;
		switch(op)
		{
			case 1:
			play_menu();
			break;
			case 2:
			break;
			case 3:
				scr();
			break;
			case 4:
				exit(0);
			break;
			default:
				clrscr();
				main_menu();
			gotoxy(18,21);
			cout<<"Invalid Option!! Please enter your option ";
			cin>>op;
			goto flag;
		}
	}
}

void play_menu()
{
clrscr();
	int op;
	gotoxy(27,5);
	cout<<"G A M E      M  E  N  U";
	gotoxy(29,9);
	cout<<"1.Level 1";
	gotoxy(29,10);
	cout<<"2.Level 2";
	gotoxy(25,18);
	cout<<"please enter your option ";
	cin>>op;
	switch(op)
	{
		case 1:
			play1();
			break;
		case 2:
		play2();
		break;
		default:
			break;
	}

}




void scr()
{
	clrscr();
	fstream f;
	data d;
	int flag=0;
	gotoxy(31,2);
	int k=5;
	cout<<"--S C O R E S--";
	f.open("scr.dat",ios::in);
	char name[100];
		f.seekg(0);

		f.read((char*)&d,sizeof(d));
		while(f)
		{
			flag=1;
			gotoxy(25,k);
			cout<<d.name;
			gotoxy(50,k);
			cout<<d.score;
			//cout<<d.score<<"                       "<<d.name<<endl;
			f.read((char*)&d,sizeof(d));
			k++;
		}
		if(flag==0)
		{
			gotoxy(30,11);
			cout<<"No Scores to Display";
		}
	delay(1000);
	getch();
}

void write_score(int score)
{
	data d;
	cout<<"Enter name : ";
	fflush(stdin);
	fgets(d.name,sizeof(d.name),stdin);
	fstream f;
	f.open("scr.dat",ios::out | ios::app);
	d.score=score;
	f.write((char*)&d,sizeof(d));
	f.close();
	clrscr();
	gotoxy(33,11);
	cout<<"score saved successfully";
	delay(1000);
}

