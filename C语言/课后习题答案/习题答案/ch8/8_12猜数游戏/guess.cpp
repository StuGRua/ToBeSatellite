// ������Ϸ 
#include <iostream.h>
#include <stdlib.h>    // ����rand()��srand()
#include <time.h>      // ���ú���time( )����ͷ�ļ�
int main()
{
 	int iMagic;     // ������
 	int iGuess;     // �²���
 	int iCounter = 0; // �²����

 	cout<<"====This is a Number Guess Game!====\n";

    //���ɱ�������ֵ 
    srand(time(0));         //�û�����ǰʱ����Ϊ���������
 	iMagic = rand()%100+1; //����1~100�ڵ������

	do{	
        cout<<"Please input a number between 1 and 100: ";
		cin>>iGuess;

		iCounter++;  //��������1
	    //�жϲ²�����𰸵Ĵ�С
		if( iGuess>iMagic )
		{
		  cout<<"Wrong!Too large!"<<endl;
		}
		else if( iGuess<iMagic  )
		{
		    cout<<"Wrong!Too Small!"<<endl;
		}		
	} while(iGuess!=iMagic);

	cout<<"Win!"<<"\nYou made "<<iCounter
		<<((iCounter>1)?" times ":" time ")<<endl;    
	return 0;
}
