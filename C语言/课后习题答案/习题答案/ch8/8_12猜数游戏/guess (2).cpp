//������Ϸ
#include <iostream.h>
#include <stdlib.h>
#include <time.h>
int main()
{
	int iMagic;     // ������
	int iGuess;     // �²���
	int iCounter=0; // �²����
	char cChoice;

	cout<<"====This is a Number Guess Game!====\n";
	srand(time(0)); //�û�����ǰʱ����Ϊ���������
	iMagic = rand()%100+1; //���ɱ�������ֵ

    do
	{
	    
		cout<<"Please input a number between 1 and 100: ";
		cin>>iGuess;

		iCounter++;
		if( iGuess>iMagic )
		{
			 cout<<"Wrong!Too large!"<<endl;
		}
		else if( iGuess<iMagic  )
		{
			cout<<"Wrong!Too Small!"<<endl;
		}
		
        if(iGuess==iMagic)
		{
			cout<<"Win!"<<"\nYou made "<<iCounter<<" times."<<endl;
		    break;
		}

		cout<<"Do you want to continue the games?(y/n):";
		cin>>cChoice;
    }while(cChoice=='y'||cChoice=='Y');

	if(iCounter>10) cout<<"You lose!"<<endl;//����10��
	return 0;
}

