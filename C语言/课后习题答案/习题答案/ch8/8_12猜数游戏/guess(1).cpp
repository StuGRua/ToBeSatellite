//������Ϸ2
#include <iostream.h>
#include <stdlib.h>
#include <time.h>
int main()
{
	int iMagic;     // ������
	int iGuess;     // �²���
	int iCounter=0; // �²����

	cout<<"====This is a Number Guess Game!====\n";
	srand(time(0)); //�û�����ǰʱ����Ϊ���������
	iMagic = rand()%100+1; //���ɱ�������ֵ

    for(int i=0; i<10; i++) //����10��
	{
	    
		cout<<"Please input a number between 1 and 100: ";
		cin>>iGuess;

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
			cout<<"Win!"<<"\nYou made "<<i<<" times."<<endl;
		    break;
		}
    }

	if(i==10) cout<<"You lose!"<<endl;
	return 0;
}

